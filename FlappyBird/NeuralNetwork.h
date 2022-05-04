#pragma once

#include <vector>
#include "DEFINITIONS.hpp"
#include "Neuron.h"

class NeuralNetwork
{
public:
	NeuralNetwork();
	NeuralNetwork(Chrom* c);
	~NeuralNetwork();

	void Update();

	void Calculate(std::vector<float> inputs);

	std::vector<std::vector<Neuron>> GetLayers() { return _layers; }
	void SetLayers(std::vector<std::vector<Neuron>> newLayers) { _layers = newLayers; }

	void operator=(NeuralNetwork nn);

private:
	std::vector<std::vector<Neuron>> _layers;
};

