#include "GA.h"

GA::GA()
{
	evpop();
}

GA::~GA()
{
}

void GA::evpop()
{
	// generate chroms for population size
	for (int i = 0; i < BIRD_COUNT; i++)
	{
		_chroms.push_back(new chrom());
		for (int j = 0; j < NN_NEURONS; j++)
		{
			_chroms[i]->_weights.push_back(RandFrom(_weightsMin, _weightsMax));
			_chroms[i]->_bias = RandFrom(_weightsMin, _weightsMax);
		}
	}
}

void GA::UpdateGA()
{
	Sort();
	Crossover();
	Mutate();
}

void GA::Sort()
{
	// sort chroms by score descending
	sort(_chroms.rbegin(), _chroms.rend(),
		[](const chrom* lhs, const chrom* rhs)
		{ return lhs->_score < rhs->_score; });
}

void GA::Crossover()
{
	// start at parent count to start on children
	for (int i = GA_PARENT_COUNT; i < BIRD_COUNT; i++)
	{
		int parentIndex1 = i % (GA_PARENT_COUNT - 1);
		int parentIndex2 = (i + 1) % (GA_PARENT_COUNT - 1);

		// set weight and bias as parent 1 and 2's
		_chroms[i]->_weights = _chroms[parentIndex1]->_weights;
		_chroms[i]->_bias = _chroms[parentIndex2]->_bias;
	}
}

void GA::Mutate()
{
	for (int i = 0; i < BIRD_COUNT; i++)
	{
		if (rand() % 2 == 1)
		{
			Mutate(i);
		}
	}
}

void GA::Mutate(int index)
{
	for (int i = 0; i < _chroms[index]->_weights.size(); i++)
	{
		_chroms[index]->_weights[i] = RandFrom(_weightsMin, _weightsMax);
		_chroms[index]->_weights[i] = RandInRange(_chroms[index]->_weights[i], 0.5f);
	}
}

float GA::RandFrom(float min, float max)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	random = random * (max - min);
	random += min;
	return random;
}

float GA::RandInRange(float val, float range)
{
	float halfRange = range * 0.5f;
	float min = range - halfRange;
	float max = range + halfRange;
	return RandFrom(min, max);
}
