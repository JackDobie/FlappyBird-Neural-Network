#pragma once

#include <vector>
#include "Neuron.h"
#include "Layer.h"

#define NN_LAYERS 2
#define NN_OUTPUTS 1

class NeuralNetwork
{
public:
	NeuralNetwork();
	~NeuralNetwork();

	std::vector<float> Calculate(std::vector<float> inputs);

	std::vector<Layer> _layers;
	std::vector<float> _outputs;
};

