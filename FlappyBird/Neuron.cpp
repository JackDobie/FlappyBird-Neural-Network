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
}

float Neuron::Calculate(NeuralNetwork network)
{
	_output = 0.0f;

	// use previous layers outputs as inputs
	for (int i = 0; i < network.GetLayers()[_currentLayer - 1].size(); i++)
	{
		_output += network.GetLayers()[_currentLayer - 1][i]._output * _weights[i];
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

//float Neuron::Calculate(std::vector<float> inputs)
//{
//	_weights = std::vector<float>(inputs.size());
//	for (int i = 0; i < inputs.size(); i++)
//	{
//		float random = ((float)rand()) / (float)RAND_MAX;
//		random = random * (_weightsMax - _weightsMin);
//		random += _weightsMin;
//		_weights[i] = random;
//	}
//
//	float sum = 0;
//	for (int i = 0; i < inputs.size(); i++)
//	{
//		sum += (inputs[i] * _weights[i]);
//	}
//	switch (_activationFunc)
//	{
//	case ActivationFunction::Identity:
//		return sum;
//	case ActivationFunction::Sigmoid:
//		return Sigmoid(sum);
//	case ActivationFunction::ReLu:
//		return ReLu(sum);
//	default:
//		return sum;
//	}
//}

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

void Neuron::Mutate()
{
	for (int i = 0; i < _weights.size(); i++)
	{
		_weights[i] = RandFrom(_weightsMin, _weightsMax);
	}
}

void Neuron::operator=(Neuron n)
{
	_currentLayer = n._currentLayer;
	_weights = n._weights;
	_bias = n._bias;
	_output = n._output;
}
