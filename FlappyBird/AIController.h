#pragma once

#include "Bird.hpp"
#include "GameState.hpp"
#include "NeuralNetwork.h"
#include "GA.h"
using namespace Sonar;

class AIController
{
public:
	AIController(GameDataRef data, GA* ga);
	~AIController();

	void SetGameState(GameState* pGameState) { _gameState = pGameState; }
	void Update();

	void TryFlap();

	std::vector<Bird*> GetBirds() { return _birds; }
	void SetBirds(std::vector<Bird*> newBirds) { _birds = newBirds; }

	int AliveBirdsCount();

	void Reset();

private:
	float DistanceToFloor(Land* land, Bird* bird);
	float DistanceToNearestPipes(Pipe* pipe, Bird* bird);
	float DistanceToCentreOfPipeGap(Pipe* pipe, Bird* bird);

	GameState*	_gameState;

	std::vector<Bird*> _birds;
};

