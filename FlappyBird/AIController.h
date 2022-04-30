#pragma once

#include "Bird.hpp"
#include "GameState.hpp"
#include "NeuralNetwork.h"
using namespace Sonar;

#define BIRD_COUNT 50

class AIController
{
public:
	AIController(GameDataRef data);
	~AIController();

	void SetGameState(GameState* pGameState) { _gameState = pGameState; }
	void Update();
	// note when this is called, it resets the flap state
	//bool shouldFlap();

	void TryFlap();

	//Bird* GetBird() { return m_bird; }
	std::vector<Bird*> GetBirds() { return _birds; }

	void Reset();

	void UpdateScore(int score);

private:
	float DistanceToFloor(Land* land, Bird* bird);
	float DistanceToNearestPipes(Pipe* pipe, Bird* bird);
	float DistanceToCentreOfPipeGap(Pipe* pipe, Bird* bird);

	GameState*	_gameState;

	std::vector<Bird*> _birds;
};

