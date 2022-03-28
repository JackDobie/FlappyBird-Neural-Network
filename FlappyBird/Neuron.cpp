#include "Neuron.h"
#include <math.h>
#include <algorithm>

Neuron::Neuron()
{
	_weights = std::vector<float>(NN_INPUTS);
	for (int i = 0; i < NN_INPUTS; i++)
	{
		float random = ((float)rand()) / (float)RAND_MAX;
		random = random * (_weightsMax - _weightsMin);
		random += _weightsMin;
		_weights[i] = random;
	}
}

Neuron::~Neuron()
{
}

float Neuron::Calculate(std::vector<float> inputs)
{
	_weights = std::vector<float>(inputs.size());
	for (int i = 0; i < inputs.size(); i++)
	{
		float random = ((float)rand()) / (float)RAND_MAX;
		random = random * (_weightsMax - _weightsMin);
		random += _weightsMin;
		_weights[i] = random;
	}

	float sum = 0;
	for (int i = 0; i < inputs.size(); i++)
	{
		sum += (inputs[i] * _weights[i]);
	}
	float result = sum + _bias;
	switch (_activationFunc)
	{
	case Function::Identity:
		return result;
	case Function::Sigmoid:
		return Sigmoid(result);
	case Function::ReLu:
		return ReLu(result);
	default:
		return result;
	}
}

float Neuron::Sigmoid(float value)
{
	return (value / (1 + abs(value)));
}

float Neuron::ReLu(float value)
{
	return std::max(0.0f, value);
}