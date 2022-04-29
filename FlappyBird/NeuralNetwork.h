#pragma once

#include <vector>
#include "Neuron.h"

#define NN_LAYERS 4
#define NN_NEURONS 1

class NeuralNetwork
{
public:
	NeuralNetwork();
	~NeuralNetwork();

	void Calculate(std::vector<float> inputs);

	std::vector<std::vector<Neuron>> GetLayers() { return _layers; }
	void SetLayers(std::vector<std::vector<Neuron>> newLayers) { _layers = newLayers; }
private:
	std::vector<std::vector<Neuron>> _layers;
};

