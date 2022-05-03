#include "AIController.h"

#include <iostream>
#include <vector>

using namespace std;
#define ERROR_DISTANCE 9999

AIController::AIController(GameDataRef data, GA* ga)
{
	_gameState = nullptr;

	for (int i = 0; i < BIRD_COUNT; i++)
	{
		_birds.push_back(new Bird(data, ga->GetChroms()[i]));
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

		if (fDistanceToNearestPipe == ERROR_DISTANCE)
		{
			fDistanceToNearestPipe = 0;
		}

		float fDistanceToCentreOfGap = DistanceToCentreOfPipeGap(pipe, b);

		b->Calculate({ fDistanceToFloor, fDistanceToNearestPipe, fDistanceToCentreOfGap });

		float output = b->GetNNOutput();
		if (output >= 0.5f)
		{
			b->SetShouldFlap(true);
			//std::cout << output << std::endl;
		}
		else
		{
			//std::cout << output << std::endl;
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

	return ERROR_DISTANCE;
}

float AIController::DistanceToNearestPipes(Pipe* pipe, Bird* bird)
{
	float nearest1 = 999999;
	sf::Sprite* nearestSprite1 = nullptr;

	// get nearest pipes
	std::vector<sf::Sprite> pipeSprites = pipe->GetSprites();
	for (unsigned int i = 0; i < pipeSprites.size(); i++)
	{
		sf::Sprite s = pipeSprites.at(i);
		float fDistance = s.getPosition().x - bird->GetSprite().getPosition().x;
		if (fDistance > 0 && fDistance < nearest1)
		{
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
	//// sort birds by score descending
	//sort(_birds.rbegin(), _birds.rend(),
	//	[](const Bird* lhs, const Bird* rhs)
	//	{ return lhs->_score < rhs->_score; });

	////// split birds in half, birds in second half (worse scoring) are mutated
	////int halfSize = _birds.size() / 2;
	////for (int i = 0; i < halfSize; i++)
	////{
	////	_birds[i + halfSize]->SetNeuralNetwork(_birds[i]->GetNeuralNetwork());
	////	_birds[i + halfSize]->Mutate(_birds[i + halfSize]->_score);

	////	// if scores are same because first half was also bad, mutate that too
	////	/*if (_birds[i]->_score == _birds[i + halfSize]->_score)
	////	{
	////		_birds[i]->Mutate();
	////	}*/
	////}

	///*for (int i = 0; i < _birds.size() - PARENT_COUNT; i++)
	//{
	//	_birds[i + PARENT_COUNT]->SetNeuralNetwork(_birds[i]->GetNeuralNetwork());
	//	_birds[i + PARENT_COUNT]->Mutate(_birds[i + PARENT_COUNT]->_score);
	//}*/

	//// crossover

	//// start at parent count to start on children
	//for (int i = GA_PARENT_COUNT; i < _birds.size(); i++)
	//{
	//	int parentIndex = i % GA_PARENT_COUNT;
	//	int parent2Index = (i + 1) % GA_PARENT_COUNT;

	//	// copy weights
	//	_birds[i]->pGetNeuralNetwork()->SetWeights(_birds[parentIndex]->GetNeuralNetwork().GetWeights());

	//	// copy layer count
	//	int parentLayerCount = _birds[parent2Index]->GetNeuralNetwork().GetLayerCount();
	//	_birds[i]->pGetNeuralNetwork()->SetLayerCount(parentLayerCount);

	//	if(rand() % 2 == 1)
	//		_birds[i]->Mutate();
	//}

	for (Bird* b : _birds)
	{
		b->Reset();
	}
}
