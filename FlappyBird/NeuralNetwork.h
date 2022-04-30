#pragma once

#include <vector>
#include "Neuron.h"

#define NN_LAYERS 2
#define NN_NEURONS 3

class NeuralNetwork
{
public:
	NeuralNetwork();
	~NeuralNetwork();

	void Calculate(std::vector<float> inputs);

	void Mutate();

	std::vector<std::vector<Neuron>> GetLayers() { return _layers; }
	void SetLayers(std::vector<std::vector<Neuron>> newLayers) { _layers = newLayers; }
private:
	std::vector<std::vector<Neuron>> _layers;
};

