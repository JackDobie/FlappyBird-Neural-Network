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
	_aliveBirds = _birds;
}

AIController::~AIController()
{
	for (Bird* b : _birds)
	{
		if(b) delete(b);
	}
	_birds.clear();
	for (Bird* b : _aliveBirds)
	{
		if (b) delete(b);
	}
	_aliveBirds.clear();
}

// update - the AI method which determines whether the bird should flap or not. 
// set m_bShouldFlap to true or false.
void AIController::Update()
{
	if (_gameState == nullptr)
		return;

	Pipe* pipe = _gameState->GetPipeContainer();
	Land* land = _gameState->GetLandContainer();

	_aliveBirds = _birds;
	for (int i = 0; i < _aliveBirds.size(); i++)
	{
		if (!_aliveBirds[i]->GetAlive())
		{
#if !OUTPUT_ON_UPDATE
			if (_aliveBirds[i]->GetWaitingToOutput())
			{
				float fDistanceToFloor = DistanceToFloor(land, _aliveBirds[i]);
				float fDistanceToNearestPipe = DistanceToNearestPipes(pipe, _aliveBirds[i]);
				float fDistanceToCentreOfGap = DistanceToCentreOfPipeGap(pipe, _aliveBirds[i]);

				std::vector<float> weights = _aliveBirds[i]->GetChrom()._weights;
				float bias = _aliveBirds[i]->GetChrom()._bias;
				// output the inputs and weights etc
				std::cout << "Inputs:\t" << fDistanceToFloor << ", " << fDistanceToNearestPipe << ", " << fDistanceToCentreOfGap <<
					"\nWeights:\t" << weights[0] << ", " << weights[1] << ", " << weights[2] <<
					"\nBias:\t" << bias << "\n-------------" << std::endl;
			}
#endif
			_aliveBirds.erase(_aliveBirds.begin() + i);
			i--;
		}
	}
	for (int i = 0; i < _aliveBirds.size(); i++)
	{
		Bird* b = _aliveBirds[i];

		float fDistanceToFloor = DistanceToFloor(land, b);

		float fDistanceToNearestPipe = DistanceToNearestPipes(pipe, b);
		//if (fDistanceToNearestPipe != ERROR_DISTANCE) {

		/*if (fDistanceToNearestPipe == ERROR_DISTANCE)
		{
			fDistanceToNearestPipe = 0;
		}*/

		float fDistanceToCentreOfGap = DistanceToCentreOfPipeGap(pipe, b);

		b->Calculate({ fDistanceToFloor, fDistanceToNearestPipe, fDistanceToCentreOfGap });

		float output = b->GetNNOutput();
		if (output > 0.5f)
		{
			b->SetShouldFlap(true);
		}

#if OUTPUT_ON_UPDATE
		if (i == 0)
		{
			std::vector<float> weights = b->GetChrom()._weights;
			float bias = b->GetChrom()._bias;
			// output the inputs and weights etc
			std::cout << "Bird 0:\nInputs:\t" << fDistanceToFloor << ", " << fDistanceToNearestPipe << ", " << fDistanceToCentreOfGap <<
				"\nWeights:\t" << weights[0] << ", " << weights[1] << ", " << weights[2] <<
				"\nBias:\t" << bias << "\n-------------" << std::endl;
		}
#endif
	}
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
	for (unsigned int i = 0; i < pipeSprites.size(); i++)
	{
		sf::Sprite s = pipeSprites.at(i);
		float fDistance = s.getPosition().x - bird->GetSprite().getPosition().x;
		if (fDistance > 0 && fDistance < nearest1)
		{
			nearestSprite1 = &(pipeSprites.at(i));
			nearest1 = fDistance;
		}
		else if (fDistance > 0 && fDistance < nearest2)
		{
			nearestSprite2 = &(pipeSprites.at(i));
			nearest2 = fDistance;
		}
	}

	if (nearestSprite1 == nullptr || nearestSprite2 == nullptr)
		return ERROR_DISTANCE;


	sf::Sprite* topSprite = nullptr;
	sf::Sprite* bottomSprite = nullptr;

	if (nearestSprite1->getPosition().y < nearestSprite2->getPosition().y)
	{
		topSprite = nearestSprite1;
		bottomSprite = nearestSprite2;
	}
	else
	{
		topSprite = nearestSprite2;
		bottomSprite = nearestSprite1;
	}

	float distance = ((bottomSprite->getGlobalBounds().top) - (topSprite->getGlobalBounds().height + topSprite->getGlobalBounds().top)) / 2;
	distance += (topSprite->getGlobalBounds().top + topSprite->getGlobalBounds().height);

	return distance - bird->GetSprite().getPosition().y;
}

void AIController::TryFlap()
{
	for (Bird* b : _aliveBirds)
	{
		// check if b needs to flap, then flap and set to false
		if (b->GetShouldFlap())
		{
			b->Tap();
			b->SetShouldFlap(false);
		}
	}
}

int AIController::AliveBirdsCount()
{
	int count = 0;
	for (Bird* b : _birds)
	{
		if (b->GetAlive())
		{
			count++;
		}
	}
	return count;

	//return _aliveBirds.size();
}

std::vector<Bird*> AIController::GetAliveBirds()
{
	std::vector<Bird*> alivebirds;
	for (Bird* b : _birds)
	{
		if (b->GetAlive())
		{
			alivebirds.push_back(b);
		}
	}
	_aliveBirds = alivebirds;

	return _aliveBirds;
}

void AIController::Reset()
{
	for (Bird* b : _birds)
	{
		b->Reset();
	}
	_aliveBirds = _birds;
}

void AIController::TryOutput(bool overrideCheck)
{
	for (Bird* b : _birds)
	{
		TryOutput(b, overrideCheck);
	}
}

void AIController::TryOutput(Bird* b, bool overrideCheck)
{
	Pipe* pipe = _gameState->GetPipeContainer();
	Land* land = _gameState->GetLandContainer();
	if (b->GetWaitingToOutput() || overrideCheck)
	{
		float fDistanceToFloor = DistanceToFloor(land, b);
		float fDistanceToNearestPipe = DistanceToNearestPipes(pipe, b);
		float fDistanceToCentreOfGap = DistanceToCentreOfPipeGap(pipe, b);

		std::vector<float> weights = b->GetChrom()._weights;
		float bias = b->GetChrom()._bias;
		// output the inputs and weights etc
		std::cout << "Inputs:\t\t" << fDistanceToFloor << ", " << fDistanceToNearestPipe << ", " << fDistanceToCentreOfGap <<
			"\nWeights:\t" << weights[0] << ", " << weights[1] << ", " << weights[2] <<
			"\nBias:\t\t" << bias << "\n-------------" << std::endl;

		b->SetWaitingToOutput(false);
	}
}
