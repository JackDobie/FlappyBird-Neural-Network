#include "Layer.h"

Layer::Layer()
{
	for (int i = 0; i < LAYER_NEURONS; i++)
	{
		_neurons.push_back(Neuron());
	}
}

Layer::~Layer()
{
	_neurons.clear();
	_outputs.clear();
}

std::vector<float> Layer::Calculate(std::vector<float> inputs)
{
	_outputs.clear();
	for (Neuron n : _neurons)
	{
		_outputs.push_back(n.Calculate(inputs));
	}

	return _outputs;
}
