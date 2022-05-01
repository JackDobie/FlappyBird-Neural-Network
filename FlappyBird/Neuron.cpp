#include "Neuron.h"
#include <math.h>
#include <algorithm>
#include "NeuralNetwork.h"
#include <iostream>

Neuron::Neuron()
{
	_currentLayer = 0;
	_weights.clear();
	_bias = 0.0f;
	_output = 0.0f;
}

Neuron::Neuron(int layerIndex, int prevLayerSize)
{
	_currentLayer = layerIndex;
	_weights.clear();
	_bias = 0.0f;
	_output = 0.0f;
	for (int i = 0; i < prevLayerSize; i++)
	{
		_weights.push_back(RandFrom(_weightsMin, _weightsMax));
	}
}

Neuron::~Neuron()
{
	_weights.clear();
}

float Neuron::Calculate(NeuralNetwork network)
{
	_output = 0.0f;

	// use previous layers outputs as inputs
	std::vector<Neuron> prevlayer = network.GetLayers()[_currentLayer - 1];
	for (int i = 0; i < prevlayer.size(); i++)
	{
		_output += prevlayer[i]._output * _weights[i];
	}
	_output += _bias;

	switch (_activationFunc)
	{
	case ActivationFunction::Sigmoid:
		_output = Sigmoid(_output);
		break;
	case ActivationFunction::ReLu:
		_output = ReLu(_output);
		break;
	default:
		break;
	}

	return _output;
}

float Neuron::Sigmoid(float value)
{
	return (value / (1 + abs(value)));
}

float Neuron::ReLu(float value)
{
	return std::max(0.0f, value);
}

float Neuron::RandFrom(float min, float max)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	random = random * (max - min);
	random += min;
	return random;
}

float Neuron::RandInRange(float val, float range)
{
	float halfRange = range * 0.5f;
	float min = range - halfRange;
	float max = range + halfRange;
	min = min < _weightsMin ? _weightsMin : min;
	max = max > _weightsMax ? _weightsMax : max;
	return RandFrom(min, max);
}

void Neuron::Mutate()
{
	for (int i = 0; i < _weights.size(); i++)
	{
		//_weights[i] = RandFrom(_weightsMin, _weightsMax);
		_weights[i] = RandInRange(_weights[i], 0.5f);
	}
}

void Neuron::operator=(Neuron n)
{
	_currentLayer = n._currentLayer;
	_weights = n._weights;
	_bias = n._bias;
	_output = n._output;
}
