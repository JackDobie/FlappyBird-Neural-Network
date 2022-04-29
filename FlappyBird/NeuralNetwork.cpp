#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork()
{
	_layers.clear();

	for (int i = 0; i < NN_LAYERS; i++)
	{
		_layers.push_back({});
		for (int j = 0; j < NN_NEURONS; j++)
		{
			// i==0 does not have a previous layer so make with default constructor
			if (i == 0)
			{
				_layers[i].push_back(Neuron());
			}
			else
			{
				_layers[i].push_back(Neuron(i, _layers[i - 1].size()));
			}
		}
	}
}

NeuralNetwork::~NeuralNetwork()
{

}

void NeuralNetwork::Calculate(std::vector<float> inputs)
{
	for (int i = 0; i < _layers.size(); i++)
	{
		for (int j = 0; j < _layers[i].size(); j++)
		{
			// i==0 will have no previous layers, so set to the inputs
			if (i == 0)
			{
				_layers[i][j].SetOutput(inputs[j]);
			}
			else
			{
				_layers[i][j].Calculate(*this);
			}
		}
	}
}

void NeuralNetwork::Mutate()
{
	for (int i = 0; i < _layers.size(); i++)
	{
		for (int j = 0; j < _layers[0].size(); j++)
		{
			_layers[i][j].Mutate();
		}
	}
}
