#pragma once

#include <vector>
#include <math.h>
#include <algorithm>
#include "GA.h"

enum class ActivationFunction
{
	Identity = 0,
	Sigmoid,
	ReLu
};

class NeuralNetwork;

class Neuron
{
public:
	Neuron();
	Neuron(Chrom* c);
	Neuron(int layerIndex, int prevLayerSize);
	Neuron(int layerIndex, Chrom* c);
	~Neuron();

	void Update();

	float Calculate(NeuralNetwork network);

	float Sigmoid(float value);
	float ReLu(float value);

	std::vector<float> GetWeights() { return _weights; }
	void SetWeights(std::vector<float> newWeights) { _weights = newWeights; }

	float GetOutput() { return _output; }
	void SetOutput(float newOutput) { _output = newOutput; }

	float RandFrom(float min, float max);
	float RandInRange(float val, float range);

	int GetLayer() { return _currentLayer; }

	void operator=(Neuron n);
private:
	std::vector<float> _weights;
	const float _weightsMin = -0.7f;
	const float _weightsMax = 0.7f;
	float _bias;
	ActivationFunction _activationFunc = ActivationFunction::Sigmoid;

	float _output;
	int _currentLayer;

	Chrom* _chrom;
};
