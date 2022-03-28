#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork()
{
	for (int i = 0; i < NN_LAYERS; i++)
	{
		_layers.push_back(Layer());
	}
}

NeuralNetwork::~NeuralNetwork()
{
	_layers.clear();
	_outputs.clear();
}

std::vector<float> NeuralNetwork::Calculate(std::vector<float> inputs)
{
	std::vector<float> out = _layers[0].Calculate(inputs);
	for (int i = 1; i < NN_LAYERS; i++)
	{
		out = _layers[i].Calculate(out);
	}
	_outputs = out;
	return _outputs;
}
