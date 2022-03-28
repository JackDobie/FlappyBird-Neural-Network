#pragma once

#include <vector>

#define NN_INPUTS 3

enum class Function
{
	Identity = 0,
	Sigmoid,
	ReLu
};

class Neuron
{
public:
	Neuron();
	~Neuron();
	float Calculate(std::vector<float> inputs);

	float Sigmoid(float value);
	float ReLu(float value);
private:
	std::vector<float> _weights;
	float _weightsMin = -0.7f;
	float _weightsMax = 0.7f;
	float _bias = 0.05f;
	Function _activationFunc = Function::Identity;
};
