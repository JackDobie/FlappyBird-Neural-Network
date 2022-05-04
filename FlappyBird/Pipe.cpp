#include "Pipe.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>

namespace Sonar
{
	Pipe::Pipe(GameDataRef data) : _data(data)
	{
		_landHeight = this->_data->assets.GetTexture("Land").getSize().y;
		_pipeSpawnYOffset = 0;

		_offsets.push_back(0);
		_offsets.push_back(_landHeight / 4);
		_offsets.push_back(_landHeight / 2);
		_offsets.push_back((_landHeight / 4) + (_landHeight / 2));
		_offsets.push_back(_landHeight);
		_offsets.push_back(_landHeight);
		_offsets.push_back((_landHeight / 4) + (_landHeight / 2));
		_offsets.push_back(_landHeight / 2);
		_offsets.push_back(_landHeight / 4);
	}

	Pipe::~Pipe()
	{
		_pipeSprites.clear();
		_scoringPipes.clear();
		_offsets.clear();
	}

	void Pipe::SpawnBottomPipe()
	{
		sf::Sprite sprite(this->_data->assets.GetTexture("Pipe Up"));

		sprite.setPosition((float)this->_data->window.getSize().x, (float)this->_data->window.getSize().y - sprite.getLocalBounds().height - _pipeSpawnYOffset);

		_pipeSprites.push_back(sprite);
	}

	void Pipe::SpawnTopPipe()
	{
		sf::Sprite sprite(this->_data->assets.GetTexture("Pipe Down"));

		sprite.setPosition((float)this->_data->window.getSize().x, (float)-_pipeSpawnYOffset);

		_pipeSprites.push_back(sprite);
	}

	void Pipe::SpawnInvisiblePipe()
	{
		sf::Sprite sprite(this->_data->assets.GetTexture("Pipe Down"));

		sprite.setPosition((float)this->_data->window.getSize().x, (float)-_pipeSpawnYOffset);
		sprite.setColor(sf::Color(0, 0, 0, 0));

		_pipeSprites.push_back(sprite);
	}

	void Pipe::SpawnScoringPipe()
	{
		sf::Sprite sprite(this->_data->assets.GetTexture("Scoring Pipe"));

		sprite.setPosition((float)this->_data->window.getSize().x, 0);

		_scoringPipes.push_back(sprite);
	}

	void Pipe::MovePipes(float dt)
	{
		for ( unsigned int i = 0; i < _pipeSprites.size(); i++)
		{
			if (_pipeSprites.at(i).getPosition().x < 0 - _pipeSprites.at(i).getLocalBounds().width)
			{
				_pipeSprites.erase( _pipeSprites.begin( ) + i );
			}
			else
			{
				sf::Vector2f position = _pipeSprites.at(i).getPosition();
				float movement = PIPE_MOVEMENT_SPEED * dt;

				_pipeSprites.at(i).move(-movement, 0);
			}
		}

		for (unsigned int i = 0; i < _scoringPipes.size(); i++)
		{
			if (_scoringPipes.at(i).getPosition().x < 0 - _scoringPipes.at(i).getLocalBounds().width)
			{
				_scoringPipes.erase(_scoringPipes.begin() + i);
			}
			else
			{
				sf::Vector2f position = _scoringPipes.at(i).getPosition();
				float movement = PIPE_MOVEMENT_SPEED * dt;

				_scoringPipes.at(i).move(-movement, 0);
			}
		}
	}

	void Pipe::DrawPipes()
	{
		for (unsigned short int i = 0; i < _pipeSprites.size(); i++)
		{
			this->_data->window.draw(_pipeSprites.at(i));
		}
	}

	void Pipe::RandomisePipeOffset()
	{
		_pipeSpawnYOffset = rand() % (_landHeight + 1);
	}

	void Pipe::PickPipeOffset(int score)
	{
		_pipeSpawnYOffset = _offsets[score % _offsets.size()];
	}

	void Pipe::Reset()
	{
		_pipeSpawnYOffset = 0;
		_pipeSprites.clear();
		_scoringPipes.clear();
	}

	const std::vector<sf::Sprite> &Pipe::GetSprites() const
	{
		return _pipeSprites;
	}

	std::vector<sf::Sprite> &Pipe::GetScoringSprites()
	{
		return _scoringPipes;
	}
}