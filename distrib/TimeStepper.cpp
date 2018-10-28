#include "TimeStepper.hpp"
///TODO: implement Explicit Euler time integrator here
void ForwardEuler::takeStep(ParticleSystem* particleSystem, float stepSize)
{
	vector<Vector3f> curState=particleSystem->getState();
	vector<Vector3f> f=particleSystem->evalF(curState);
	vector<Vector3f> newState(curState.size());
	for(int i=0;i<f.capacity();i++)
	{
		newState[i]=curState[i]+stepSize*f[i];
	}
	particleSystem->setState(newState);
}

///TODO: implement Trapzoidal rule here
void Trapzoidal::takeStep(ParticleSystem* particleSystem, float stepSize)
{
	vector<Vector3f> curState = particleSystem->getState();
	vector<Vector3f> f1(curState.size());
	vector<Vector3f> f2(curState.size());
	vector<Vector3f> newState = curState;

	f1 = particleSystem->evalF(newState);
	for (int i = 0;i < curState.size();i++)
	{
		curState[i] = newState[i] + stepSize*f1[i];
	}
	f2 = particleSystem->evalF(curState);
	for (int j = 0;j < curState.size();j++)
	{
		newState[j] = newState[j] + stepSize*(f1[j] + f2[j]) / 2;
	}
	particleSystem->setState(newState);
}
