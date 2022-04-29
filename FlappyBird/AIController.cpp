#include "AIController.h"

#include <iostream>
#include <vector>

using namespace std;
#define ERROR_DISTANCE 9999

AIController::AIController(Bird* bird)
{
	m_pGameState = nullptr;
	m_bShouldFlap = false;
	m_neuralNet = new NeuralNetwork();
	m_bird = bird;
}

AIController::~AIController()
{
	if (m_neuralNet)
	{
		delete(m_neuralNet);
	}
}

// update - the AI method which determines whether the bird should flap or not. 
// set m_bShouldFlap to true or false.
void AIController::update()
{
	if (m_pGameState == nullptr)
		return;

	Pipe* pipe = m_pGameState->GetPipeContainer();
	Land* land = m_pGameState->GetLandContainer();

	// do some AI stuff, decide whether to flap
	float fDistanceToFloor = distanceToFloor(land, m_bird);

	float fDistanceToNearestPipe = distanceToNearestPipes(pipe, m_bird);

	if (fDistanceToNearestPipe != ERROR_DISTANCE) {
		float fDistanceToCentreOfGap = distanceToCentreOfPipeGap(pipe, m_bird);

		m_neuralNet->Calculate({ fDistanceToFloor, fDistanceToNearestPipe, fDistanceToCentreOfGap });
	}
	else
	{
		m_neuralNet->Calculate({ fDistanceToFloor, fDistanceToNearestPipe });
	}

	if (m_neuralNet->GetLayers().back()[0].GetOutput() >= 0.5f)
	{
		m_bShouldFlap = true;
	}


	//if (outf > 0.5f)
	//{
	//	m_bShouldFlap = true;
	//	std::cout << /*"2 " << */outf << std::endl;
	//}

	// this means the birdie always flaps. Should only be called when the bird should need to flap. 
	//m_bShouldFlap = true;

	return;
}

float AIController::distanceToFloor(Land* land, Bird* bird)
{
	// the land is always the same height so get the first sprite
	std::vector<sf::Sprite> landSprites = land->GetSprites();
	if (landSprites.size() > 0)
	{
		return landSprites.at(0).getPosition().y - bird->GetSprite().getPosition().y;
	}

	return ERROR_DISTANCE; // this is an error but also means 
}

float AIController::distanceToNearestPipes(Pipe* pipe, Bird* bird)
{
	float nearest1 = 999999;
	sf::Sprite* nearestSprite1 = nullptr;

	// get nearest pipes
	std::vector<sf::Sprite> pipeSprites = pipe->GetSprites();
	for (unsigned int i = 0; i < pipeSprites.size(); i++) {
		sf::Sprite s = pipeSprites.at(i);
		float fDistance = s.getPosition().x - bird->GetSprite().getPosition().x;
		if (fDistance > 0 && fDistance < nearest1) {
			nearestSprite1 = &(pipeSprites.at(i));
			nearest1 = fDistance;
		}
	}

	if (nearestSprite1 == nullptr)
		return ERROR_DISTANCE;

	return nearestSprite1->getPosition().x - bird->GetSprite().getPosition().x;
}

float AIController::distanceToCentreOfPipeGap(Pipe* pipe, Bird* bird)
{
	float nearest1 = 999999;
	float nearest2 = 999999;
	sf::Sprite* nearestSprite1 = nullptr;
	sf::Sprite* nearestSprite2 = nullptr;

	// get nearest pipes
	std::vector<sf::Sprite> pipeSprites = pipe->GetSprites();
	for (unsigned int i = 0; i < pipeSprites.size(); i++) {
		sf::Sprite s = pipeSprites.at(i);
		float fDistance = s.getPosition().x - bird->GetSprite().getPosition().x;
		if (fDistance > 0 && fDistance < nearest1) {
			nearestSprite1 = &(pipeSprites.at(i));
			nearest1 = fDistance;
		}
		else if (fDistance > 0 && fDistance < nearest2) {
			nearestSprite2 = &(pipeSprites.at(i));
			nearest2 = fDistance;
		}
	}

	if (nearestSprite1 == nullptr || nearestSprite2 == nullptr)
		return ERROR_DISTANCE;


	sf::Sprite* topSprite = nullptr;
	sf::Sprite* bottomSprite = nullptr;

	if (nearestSprite1->getPosition().y < nearestSprite2->getPosition().y) {
		topSprite = nearestSprite1;
		bottomSprite = nearestSprite2;
	}
	else {
		topSprite = nearestSprite2;
		bottomSprite = nearestSprite1;
	}

	float distance = ((bottomSprite->getGlobalBounds().top) - (topSprite->getGlobalBounds().height + topSprite->getGlobalBounds().top)) / 2;
	distance += (topSprite->getGlobalBounds().top + topSprite->getGlobalBounds().height);

	return distance - bird->GetSprite().getPosition().y;
}

// note when this is called, it resets the flap state (don't edit)
bool AIController::shouldFlap()
{
	bool output = m_bShouldFlap;
	m_bShouldFlap = false;

	return output;
}

