#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "State.hpp"
#include "Game.hpp"
#include "Pipe.hpp"
#include "Land.hpp"
#include "Bird.hpp"
#include "Collision.hpp"
#include "HUD.hpp"
#include "GA.h"

class AIController;

namespace Sonar
{
	class GameState : public State
	{
	public:
		GameState(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

		Pipe* GetPipeContainer() { return _pipe; };
		Land* GetLandContainer() { return _land; };

	private:
		void Reset();

		GameDataRef _data;

		sf::Sprite _background;

		Pipe* _pipe;
		Land* _land;
		Collision _collision;
		//Flash* _flash;
		HUD* _hud;

		sf::Clock _clock;

		int _gameState;

		sf::RectangleShape _gameOverFlash;
		bool _flashOn;

		int _score;
		int _generation;

		sf::SoundBuffer _hitSoundBuffer;
		sf::SoundBuffer _wingSoundBuffer;
		sf::SoundBuffer _pointSoundBuffer;

		sf::Sound _hitSound;
		sf::Sound _wingSound;
		sf::Sound _pointSound;

		AIController* _AIController;

		GA* _GA;
	};
}