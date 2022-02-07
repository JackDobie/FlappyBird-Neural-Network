#pragma once


#include "GameState.hpp"
using namespace Sonar;

class AIController
{
public:
	AIController();
	~AIController();

	void setGameState(GameState* pGameState) { m_pGameState = pGameState; }
	void update();
	bool shouldFlap(); // note when this is called, it resets the flap state

public:

private:
	float distanceToFloor(Land* land, Bird* bird);
	float distanceToNearestPipes(Pipe* pipe, Bird* bird);
	float distanceToCentreOfPipeGap(Pipe* pipe, Bird* bird);


private:
	GameState*	m_pGameState;
	bool		m_bShouldFlap;


};

