#pragma once

#include <vector>
#include "DEFINITIONS.hpp"
#include "Neuron.h"

class NeuralNetwork
{
public:
	NeuralNetwork();
	NeuralNetwork(chrom* c);
	~NeuralNetwork();

	void Update();

	void Calculate(std::vector<float> inputs);

	void Mutate(int score);

	std::vector<std::vector<Neuron>> GetLayers() { return _layers; }
	void SetLayers(std::vector<std::vector<Neuron>> newLayers) { _layers = newLayers; }

	//int GetLayerCount() { return _layerCount; }
	//void SetLayerCount(int newLayerCount) { _layerCount = newLayerCount; }

	/*std::vector<float> GetWeights() { return _weights; }
	void SetWeights(std::vector<float> newWeights) { _weights = newWeights; }*/

	void operator=(NeuralNetwork nn);

private:
	std::vector<std::vector<Neuron>> _layers;
	//std::vector<float> _weights;

	const float _weightsMin = -0.7f;
	const float _weightsMax = 0.7f;

	//int _layerCount;
};

