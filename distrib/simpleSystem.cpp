
#include "simpleSystem.h"

using namespace std;

SimpleSystem::SimpleSystem()
{
	Vector3f o(-1, 1, 0);
	m_vVecState = vector<Vector3f>(1);
	m_vVecState[0]=o;
}

// TODO: implement evalF
// for a given state, evaluate f(X,t)
vector<Vector3f> SimpleSystem::evalF(vector<Vector3f> state)
{
	// YOUR CODE HERE
	vector<Vector3f> f(state.size());
	for(int i=0;i<state.size();i++)
	{
		float newX = (-1)*(state[i].y());
		float newY = state[i].x();
		Vector3f curf=Vector3f(newX,newY,0);
		f[i]=curf;
	}
	return f;
}

// render the system (ie draw the particles)
void SimpleSystem::draw()
{
	for (int i = 0;i < m_vVecState.size();i++)
	{
		Vector3f pos=m_vVecState[i];
		glPushMatrix();
		glTranslatef(pos[0], pos[1], pos[2]);
		glutSolidSphere(0.075f, 10.0f, 10.0f);
		glPopMatrix();
	}
}
