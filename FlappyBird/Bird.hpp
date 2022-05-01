#pragma once

#include <SFML/Graphics.hpp>

#include "DEFINITIONS.hpp"
#include "Game.hpp"
#include "NeuralNetwork.h"

#include <vector>

namespace Sonar
{
	class Bird
	{
	public:
		Bird(GameDataRef data);
		~Bird();

		void Reset();

		void Draw();

		void Animate(float dt);

		void Update(float dt);

		void Tap();

		void Calculate(std::vector<float> inputs);
		void Mutate();

		const sf::Sprite &GetSprite() const;

		void GetHeight(int& x, int& y);

		bool GetShouldFlap() { return _shouldFlap; }
		void SetShouldFlap(bool flap) { _shouldFlap = flap; }

		bool GetAlive() { return _alive; }
		void SetAlive(bool alive) { _alive = alive; }

		NeuralNetwork GetNeuralNetwork() { return _neuralNet; }
		void SetNeuralNetwork(NeuralNetwork newNeuralNet) { _neuralNet = newNeuralNet; }

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

		NeuralNetwork _neuralNet;
	};
}