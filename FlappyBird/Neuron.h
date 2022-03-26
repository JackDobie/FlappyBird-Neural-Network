#pragma once

#define NN_INPUTS 2

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
	float Calculate(float inputs[NN_INPUTS]);

	float Sigmoid(float value);
	float ReLu(float value);
private:
	float _weights[NN_INPUTS];
	float _bias = 1.0f;
	Function _activationFunc = Function::Identity;
};
