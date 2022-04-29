#include "AIController.h"

#include <iostream>
#include <vector>

using namespace std;
#define ERROR_DISTANCE 9999

AIController::AIController(GameDataRef data)
{
	m_pGameState = nullptr;

	for (int i = 0; i < BIRD_COUNT; i++)
	{
		m_birds.push_back(new Bird(data));
	}
}

AIController::~AIController()
{

}

// update - the AI method which determines whether the bird should flap or not. 
// set m_bShouldFlap to true or false.
void AIController::Update()
{
	if (m_pGameState == nullptr)
		return;

	Pipe* pipe = m_pGameState->GetPipeContainer();
	Land* land = m_pGameState->GetLandContainer();

	for (Bird* b : m_birds)
	{
		float fDistanceToFloor = DistanceToFloor(land, b);

		float fDistanceToNearestPipe = DistanceToNearestPipes(pipe, b);

		if (fDistanceToNearestPipe != ERROR_DISTANCE) {
			float fDistanceToCentreOfGap = DistanceToCentreOfPipeGap(pipe, b);

			b->Calculate({ fDistanceToFloor, fDistanceToNearestPipe, fDistanceToCentreOfGap });
		}
		else
		{
			b->Calculate({ fDistanceToFloor, fDistanceToNearestPipe });
		}

		if (b->GetNeuralNetwork()->GetLayers().back()[0].GetOutput() >= 0.5f)
		{
			b->SetShouldFlap(true);
			std::cout << b->GetNeuralNetwork()->GetLayers().back()[0].GetOutput() << std::endl;
		}
	}

	// this means the birdie always flaps. Should only be called when the bird should need to flap. 
	//m_bShouldFlap = true;
}

float AIController::DistanceToFloor(Land* land, Bird* bird)
{
	// the land is always the same height so get the first sprite
	std::vector<sf::Sprite> landSprites = land->GetSprites();
	if (landSprites.size() > 0)
	{
		return landSprites.at(0).getPosition().y - bird->GetSprite().getPosition().y;
	}

	return ERROR_DISTANCE; // this is an error but also means 
}

float AIController::DistanceToNearestPipes(Pipe* pipe, Bird* bird)
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

float AIController::DistanceToCentreOfPipeGap(Pipe* pipe, Bird* bird)
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

void AIController::TryFlap()
{
	for (Bird* b : m_birds)
	{
		// check if b needs to flap, then flap and set to false
		if (b->GetShouldFlap())
		{
			b->Tap();
			b->SetShouldFlap(false);
		}
	}
}

void AIController::Reset()
{
	// sort birds by score
	sort(m_birds.begin(), m_birds.end(),
		[](const Bird* lhs, const Bird* rhs)
		{ return lhs->_score < rhs->_score; });

	int halfSize = m_birds.size() / 2;
	for (int i = 0; i < halfSize; i++)
	{
		m_birds[i + halfSize] = m_birds[i];
		m_birds[i + halfSize]->Mutate();
		m_birds[i + halfSize]->ResetPosition();
		m_birds[i]->ResetPosition();
	}

	for (Bird* b : m_birds)
	{
		b->_score = 0;
		b->SetAlive(true);
	}
}

void AIController::UpdateScore(int score)
{
	for (Bird* b : m_birds)
	{
		b->_score = score;
	}
}
