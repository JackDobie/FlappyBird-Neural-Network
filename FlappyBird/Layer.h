#pragma once

#include <vector>
#include "Neuron.h"

#define LAYER_NEURONS 2

class Layer
{
public:
	Layer();
	~Layer();

	std::vector<float> Calculate(std::vector<float> inputs);

	std::vector<Neuron> _neurons;
	std::vector<float> _outputs;
};

