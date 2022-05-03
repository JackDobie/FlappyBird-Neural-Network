#include "Neuron.h"
#include "NeuralNetwork.h"
#include <iostream>

Neuron::Neuron()
{
	_currentLayer = 0;
	_weights.clear();
	_bias = 0.0f;
	_output = 0.0f;
}

Neuron::Neuron(chrom* c) : _chrom(c), _bias(c->_bias)
{
	_currentLayer = 0;
	_weights.clear();
	_weights = c->_weights;
	_output = 0.0f;
}

Neuron::Neuron(int layerIndex, int prevLayerSize) : _currentLayer(layerIndex)
{
	_weights.clear();
	_output = 0.0f;
	for (int i = 0; i < prevLayerSize; i++)
	{
		_weights.push_back(RandFrom(_weightsMin, _weightsMax));
	}
}

Neuron::Neuron(int layerIndex, chrom* c) : _currentLayer(layerIndex), _chrom(c), _bias(c->_bias)
{
	_weights.clear();
	_weights = c->_weights;
	_output = 0.0f;
	/*for (int i = 0; i < prevLayerSize; i++)
	{
		_weights.push_back(RandFrom(_weightsMin, _weightsMax));
	}*/
}

Neuron::~Neuron()
{
	_weights.clear();
}

void Neuron::Update()
{
	_weights = _chrom->_weights;
	_bias = _chrom->_bias;
}

float Neuron::Calculate(NeuralNetwork network)
{
	_output = 0.0f;

	// use previous layers outputs as inputs
	std::vector<Neuron> prevlayer = network.GetLayers()[_currentLayer - 1];
	for (int i = 0; i < prevlayer.size(); i++)
	{
		_output += prevlayer[i]._output * _chrom->_weights[i];
	}
	_output += _chrom->_bias;

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
	return RandFrom(min, max);
}

void Neuron::Mutate(int score)
{
	for (int i = 0; i < _weights.size(); i++)
	{
		//_weights[i] = RandFrom(_weightsMin, _weightsMax);
		_weights[i] = RandInRange(_weights[i], 0.5f);

		/*float r = RandFrom(_weightsMin, _weightsMax);
		float l = (1. / pow(score + 1., 2));
		float w = l * r;

		_weights[i] += w;

		if (_weights[i] < _weightsMin)
			_weights[i] = _weightsMin;
		if (_weights[i] > _weightsMax)
			_weights[i] = _weightsMax;*/
	}
}

void Neuron::operator=(Neuron n)
{
	_currentLayer = n._currentLayer;
	_weights = n._weights;
	_bias = n._bias;
	_output = n._output;
}
