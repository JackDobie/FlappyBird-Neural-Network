#pragma once

#include "Bird.hpp"
#include "GameState.hpp"
#include "NeuralNetwork.h"
using namespace Sonar;

class AIController
{
public:
	AIController(Bird* bird);
	~AIController();

	void setGameState(GameState* pGameState) { m_pGameState = pGameState; }
	void update();
	// note when this is called, it resets the flap state
	bool shouldFlap();

	Bird* GetBird() { return m_bird; }

private:
	float distanceToFloor(Land* land, Bird* bird);
	float distanceToNearestPipes(Pipe* pipe, Bird* bird);
	float distanceToCentreOfPipeGap(Pipe* pipe, Bird* bird);

	GameState*	m_pGameState;
	bool		m_bShouldFlap;

	NeuralNetwork* m_neuralNet;

	Bird* m_bird;
};

