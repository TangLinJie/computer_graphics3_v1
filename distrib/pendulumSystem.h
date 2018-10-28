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
	float r; //��̬����
	float k;//����ϵ��
};

class PendulumSystem: public ParticleSystem
{
public:
	PendulumSystem(int numParticles);
	vector<Vector3f> evalF(vector<Vector3f> state);
	
	void draw();

	//��������ʵ�λ��״̬
	vector<Vector3f> getPosition();
	//��������ʵ��ٶ�״̬
	vector<Vector3f> getVelocity();
private:
	link* l;
	int linkNumber;
};

#endif
