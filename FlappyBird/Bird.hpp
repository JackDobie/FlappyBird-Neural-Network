#pragma once

#include <SFML/Graphics.hpp>

#include "DEFINITIONS.hpp"
#include "Game.hpp"

#include <vector>

namespace Sonar
{
	class Bird
	{
	public:
		Bird(GameDataRef data);
		~Bird();

		void ResetPosition();

		void Draw();

		void Animate(float dt);

		void Update(float dt);

		void Tap();

		const sf::Sprite &GetSprite() const;

		void GetHeight(int& x, int& y);

		bool GetShouldFlap() { return _shouldFlap; }
		void SetShouldFlap(bool flap) { _shouldFlap = flap; }

		bool GetAlive() { return _alive; }
		void SetAlive(bool alive) { _alive = alive; }

		int _score;

	private:
		GameDataRef _data;

		sf::Sprite _birdSprite;
		std::vector<sf::Texture> _animationFrames;

		unsigned int _animationIterator;

		sf::Clock _clock;

		sf::Clock _movementClock;

		int _birdState;

		float _rotation;

		bool _shouldFlap;

		bool _alive;
	};
}