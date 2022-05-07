#pragma once

#include <SFML/Graphics.hpp>

#include "DEFINITIONS.hpp"
#include "Game.hpp"
#include "NeuralNetwork.h"
#include "GA.h"

#include <vector>

namespace Sonar
{
	class Bird
	{
	public:
		Bird(GameDataRef data, Chrom* c);
		~Bird();

		void Reset();

		void Draw();

		void Animate(float dt);

		void Update(float dt);

		void Tap();

		void Calculate(std::vector<float> inputs);
		//void Mutate();

		const sf::Sprite &GetSprite() const;

		void GetHeight(int& x, int& y);

		bool GetShouldFlap() { return _shouldFlap; }
		void SetShouldFlap(bool flap) { _shouldFlap = flap; }

		bool GetAlive() { return _alive; }
		void SetAlive(bool alive) { _alive = alive; }

		float GetNNOutput() { return _neuralNet->GetLayers().back()[0].GetOutput(); }
		void SetNeuralNetwork(NeuralNetwork* newNeuralNet) { _neuralNet = newNeuralNet; }

		Chrom* pGetChrom() { return _chrom; }
		Chrom GetChrom() { return *_chrom; }
		void SetChrom(Chrom* newChrom) { _chrom = newChrom; }

		void SetScore(int newScore) { _chrom->_score = newScore; }
		int GetScore() { return _chrom->_score; }

		void SetWaitingToOutput(bool output) { _waitingToOutput = output; }
		bool GetWaitingToOutput() { return _waitingToOutput; }

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

		NeuralNetwork* _neuralNet;

		Chrom* _chrom;

		bool _waitingToOutput;
	};
}