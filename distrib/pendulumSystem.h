#ifndef PENDULUMSYSTEM_H
#define PENDULUMSYSTEM_H

#include <vecmath.h>
#include <vector>
#ifdef _WIN32
#include "GL/freeglut.h"
#else
#include <GL/glut.h>
#endif

#include "particleSystem.h"
struct link
{
	int index1;
	int index2;
	float r; //静态长度
	float k;//弹性系数
};

class PendulumSystem: public ParticleSystem
{
public:
	PendulumSystem(int numParticles);
	vector<Vector3f> evalF(vector<Vector3f> state);
	
	void draw();

	//获得所有质点位置状态
	vector<Vector3f> getPosition();
	//获得所有质点速度状态
	vector<Vector3f> getVelocity();
private:
	link* l;
	int linkNumber;
};

#endif
