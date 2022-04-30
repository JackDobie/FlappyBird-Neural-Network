#include "AIController.h"

#include <iostream>
#include <vector>

using namespace std;
#define ERROR_DISTANCE 9999

AIController::AIController(GameDataRef data)
{
	_gameState = nullptr;

	for (int i = 0; i < BIRD_COUNT; i++)
	{
		_birds.push_back(new Bird(data));
	}
}

AIController::~AIController()
{
	for (Bird* b : _birds)
	{
		delete(b);
	}
	_birds.clear();
}

// update - the AI method which determines whether the bird should flap or not. 
// set m_bShouldFlap to true or false.
void AIController::Update()
{
	if (_gameState == nullptr)
		return;

	Pipe* pipe = _gameState->GetPipeContainer();
	Land* land = _gameState->GetLandContainer();

	for (Bird* b : _birds)
	{
		if (!b->GetAlive())
			continue;

		float fDistanceToFloor = DistanceToFloor(land, b);

		float fDistanceToNearestPipe = DistanceToNearestPipes(pipe, b);

		//if (fDistanceToNearestPipe != ERROR_DISTANCE) {
		float fDistanceToCentreOfGap = DistanceToCentreOfPipeGap(pipe, b);

		b->Calculate({ fDistanceToFloor, fDistanceToNearestPipe, fDistanceToCentreOfGap });
		//}
		//else
		//{
		//	b->Calculate({ fDistanceToFloor });
		//}

		if (b->GetNeuralNetwork()->GetLayers().back()[0].GetOutput() >= 0.5f)
		{
			b->SetShouldFlap(true);
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
	for (Bird* b : _birds)
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
	sort(_birds.begin(), _birds.end(),
		[](const Bird* lhs, const Bird* rhs)
		{ return lhs->_score < rhs->_score; });

	for (Bird* b : _birds)
	{
		if (b->_score == _birds.back()->_score)
		{
			b->Mutate();
		}
	}

	/*int halfSize = _birds.size() / 2;
	for (int i = 0; i < halfSize; i++)
	{
		_birds[i + halfSize] = _birds[i];
		_birds[i + halfSize]->Mutate();
		_birds[i + halfSize]->ResetPosition();
		_birds[i]->ResetPosition();
	}*/

	for (Bird* b : _birds)
	{
		b->ResetPosition();
		b->_score = 0;
		b->SetAlive(true);
	}
}

void AIController::UpdateScore(int score)
{
	for (Bird* b : _birds)
	{
		b->_score = score;
	}
}
