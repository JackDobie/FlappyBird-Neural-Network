#pragma once

#include <sstream>
#include "DEFINITIONS.hpp"
#include "GameState.hpp"
#include "AIController.h"

#include <iostream>

namespace Sonar
{
	GameState::GameState(GameDataRef data) : _data(data)
	{
		Init();
	}

	void GameState::Init()
	{
		if (!_hitSoundBuffer.loadFromFile(HIT_SOUND_FILEPATH))
		{
			std::cout << "Error Loading Hit Sound Effect" << std::endl;
		}

		if (!_wingSoundBuffer.loadFromFile(WING_SOUND_FILEPATH))
		{
			std::cout << "Error Loading Wing Sound Effect" << std::endl;
		}

		if (!_pointSoundBuffer.loadFromFile(POINT_SOUND_FILEPATH))
		{
			std::cout << "Error Loading Point Sound Effect" << std::endl;
		}

		_hitSound.setBuffer(_hitSoundBuffer);
		_wingSound.setBuffer(_wingSoundBuffer);
		_pointSound.setBuffer(_pointSoundBuffer);

		this->_data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
		this->_data->assets.LoadTexture("Pipe Up", PIPE_UP_FILEPATH);
		this->_data->assets.LoadTexture("Pipe Down", PIPE_DOWN_FILEPATH);
		this->_data->assets.LoadTexture("Land", LAND_FILEPATH);
		this->_data->assets.LoadTexture("Bird Frame 1", BIRD_FRAME_1_FILEPATH);
		this->_data->assets.LoadTexture("Bird Frame 2", BIRD_FRAME_2_FILEPATH);
		this->_data->assets.LoadTexture("Bird Frame 3", BIRD_FRAME_3_FILEPATH);
		this->_data->assets.LoadTexture("Bird Frame 4", BIRD_FRAME_4_FILEPATH);
		this->_data->assets.LoadTexture("Scoring Pipe", SCORING_PIPE_FILEPATH);
		this->_data->assets.LoadFont("Flappy Font", FLAPPY_FONT_FILEPATH);

		_pipe = new Pipe(_data);
		_land = new Land(_data);
		//_flash = new Flash(_data);
		_hud = new HUD(_data);

		_AIController = new AIController(_data);
		_AIController->SetGameState(this);

		_background.setTexture(this->_data->assets.GetTexture("Game Background"));

		_score = 0;
		_hud->UpdateScore(_score);

		_gameState = GameStates::eReady;
	}

	void GameState::HandleInput()
	{
		if (GameStates::eGameOver != _gameState)
		{
			_gameState = GameStates::ePlaying;

			_AIController->Update();
			_AIController->TryFlap();
		}

		sf::Event event;
		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}

			// player tap
			if (this->_data->input.IsSpriteClicked(this->_background, sf::Mouse::Left, this->_data->window))
			{
				if (GameStates::eGameOver != _gameState)
				{
					_gameState = GameStates::ePlaying;
					_AIController->GetBirds()[0]->Tap();
					//bird->Tap();
					//_wingSound.play();
				}
			}
		}
	}

	void GameState::Update(float dt)
	{
		if (GameStates::eGameOver != _gameState)
		{
			for (Bird* b : _AIController->GetBirds())
			{
				b->Animate(dt);
			}
			_land->MoveLand(dt);
		}

		if (GameStates::ePlaying == _gameState)
		{
			_pipe->MovePipes(dt);

			if (_clock.getElapsedTime().asSeconds() > PIPE_SPAWN_FREQUENCY)
			{
				_pipe->RandomisePipeOffset();

				_pipe->SpawnInvisiblePipe();
				_pipe->SpawnBottomPipe();
				_pipe->SpawnTopPipe();
				_pipe->SpawnScoringPipe();

				_clock.restart();
			}

			for (Bird* b : _AIController->GetBirds())
			{
				if (b->GetAlive())
				{
					b->Update(dt);
				}
			}

			std::vector<sf::Sprite> landSprites = _land->GetSprites();

			for (unsigned int i = 0; i < landSprites.size(); i++)
			{
				bool allCollide = true;
				for (Bird* b : _AIController->GetBirds())
				{
					if (!b->GetAlive())
						continue;

					if (_collision.CheckSpriteCollision(b->GetSprite(), 0.7f, landSprites.at(i), 1.0f, false))
					{
						//_hitSound.play();
						b->_score = _score;
						b->SetAlive(false);
					}
					else
					{
						allCollide = false;
					}
				}
				if (allCollide)
				{
					_gameState = GameStates::eGameOver;

					_clock.restart();
				}
			}

			std::vector<sf::Sprite> pipeSprites = _pipe->GetSprites();

			for (unsigned int i = 0; i < pipeSprites.size(); i++)
			{
				bool allCollide = true;
				for (Bird* b : _AIController->GetBirds())
				{
					if (!b->GetAlive())
						continue;

					if (_collision.CheckSpriteCollision(b->GetSprite(), 0.625f, pipeSprites.at(i), 1.0f, true))
					{
						//_hitSound.play();
						b->_score = _score;
						b->SetAlive(false);
					}
					else
					{
						allCollide = false;
					}
				}
				if (allCollide)
				{
					_gameState = GameStates::eGameOver;

					_clock.restart();
				}
			}

			if (GameStates::ePlaying == _gameState)
			{
				std::vector<sf::Sprite> &scoringSprites = _pipe->GetScoringSprites();

				for (unsigned int i = 0; i < scoringSprites.size(); i++)
				{
					for (Bird* b : _AIController->GetBirds())
					{
						if (_collision.CheckSpriteCollision(b->GetSprite(), 0.625f, scoringSprites.at(i), 1.0f, false))
						{
							_score++;

							_hud->UpdateScore(_score);

							scoringSprites.erase(scoringSprites.begin() + i);

							//_pointSound.play();
						}
					}
				}
			}
		}

		if (GameStates::eGameOver == _gameState)
		{
			//_flash->Show(dt);

			std::cout << "Generation: " << _generation + 1 << "\tScore: " << _score << std::endl;
			Reset();

			/*if (clock.getElapsedTime().asSeconds() > TIME_BEFORE_GAME_OVER_APPEARS)
			{
				std::cout << "Score: " << _score << std::endl;
				Reset();
			}*/
		}
	}

	void GameState::Draw(float dt)
	{
		this->_data->window.clear( sf::Color::Red );

		this->_data->window.draw(this->_background);

		_pipe->DrawPipes();
		_land->DrawLand();

		for (Bird* b : _AIController->GetBirds())
		{
			b->Draw();
		}

		//_flash->Draw();

		_hud->Draw();

		this->_data->window.display();
	}

	void GameState::Reset()
	{
		delete(_hud);
		_hud = new HUD(_data);
		_hud->UpdateScore(_score);

		_pipe->Reset();
		_land->Reset();
		/*_pipe = new Pipe(_data);
		_land = new Land(_data);*/

		srand(time(NULL));

		_score = 0;
		_AIController->Reset();
		_gameState = GameStates::eReady;
		_generation++;

		srand(1);
	}
}