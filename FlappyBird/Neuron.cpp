#include "Neuron.h"
#include <math.h>
#include <algorithm>

Neuron::Neuron()
{
	for (int i = 0; i < NN_INPUTS; i++)
	{
		_weights[i] = 1.0f;
	}
}

Neuron::~Neuron()
{
}

float Neuron::Calculate(float inputs[NN_INPUTS])
{
	float sum = 0;
	for (int i = 0; i < NN_INPUTS; i++)
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
