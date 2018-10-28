
#include "pendulumSystem.h"
vector<Vector3f> PendulumSystem::getPosition()
{
	vector<Vector3f> position(m_vVecState.size() / 2);
	int j = 0;
	for (int i = 0;i < m_vVecState.size();i += 2)  //偶数存储位置
	{
		position[j] = m_vVecState[i];
		j++;
	}
	return position;
}
vector<Vector3f> PendulumSystem::getVelocity()
{
	vector<Vector3f> velocity(m_vVecState.size()/2);
	int j = 0;
	for (int i = 1;i < m_vVecState.size();i += 2)  //奇数存储速度
	{
		velocity[j] = m_vVecState[i];
		j++;
	}
	return velocity;
}
PendulumSystem::PendulumSystem(int numParticles):ParticleSystem(numParticles)
{
	/*
	初始化含有一个固定质点和多个可动质点的系统，其中质点依次连接
	*/
	if (numParticles == 0)
	{
		m_vVecState = vector<Vector3f>(0);
		return;
	}
	linkNumber = 0;
	//将第一个点作为固定点
	if (numParticles > 1)
	{
		l = new link[numParticles - 1];
	}
	int size = numParticles * 2;
	m_numParticles = numParticles;
	m_vVecState = vector<Vector3f>(size); 
	//第一个节点存储固定点，它的位置为原点，初始速度为0
	m_vVecState[0] = Vector3f();
	m_vVecState[1] = Vector3f();
	// fill in code for initializing the state based on the number of particles
	for (int i = 2; i < size; i+=2) {
		// for this system, we care about the position and the velocity
		m_vVecState[i] = Vector3f(0, -(i*0.1), 0);
		m_vVecState[i+1] = Vector3f(0, 0.01*i, 0);
		/*
		//单摆链初始化
		l[i / 2 - 1].index1 = 0;
		l[i / 2 - 1].index2 = i;
		l[i / 2 - 1].r = 0.5;
		l[i / 2 - 1].k = 1;
		linkNumber++;
		*/
		//多粒子链，包含多个可动质点和一个固定质点，他们之间依次用弹簧连接
		l[i / 2 - 1].index1 = i-2;
		l[i / 2 - 1].index2 = i;
		l[i / 2 - 1].r = 0.5;
		l[i / 2 - 1].k = 5;
		linkNumber++;
	}
}


// TODO: implement evalF
// for a given state, evaluate f(X,t)
vector<Vector3f> PendulumSystem::evalF(vector<Vector3f> state)
{
	/*
	对于弹簧系统通用的求f函数
	*/
	if (state.size() == 0)
		return vector<Vector3f>(0);
	vector<Vector3f> f(state.size());
	//固定点的力为0
	f[0] = Vector3f();
	f[1] = Vector3f();
	for (int i = 2;i < state.size();i += 2)
	{
		f[i] = state[i + 1];
		//多粒子链的加速度计算，要考虑旁边两个质点给他的力，先加上非弹力，g取0.2，阻尼系数取0.05
		f[i + 1] = Vector3f(0, -0.2, 0) - (0.05*f[i]);
	}
	//遍历所有的弹簧链
	for (int i = 0;i < linkNumber;i++)
	{
		Vector3f v = state[l[i].index2] - state[l[i].index1];
		float dis = v.abs();
		if(l[i].index2!=0)
			f[l[i].index2 + 1] -= l[i].k*(dis - l[i].r)*(v / dis);
		if(l[i].index1!=0)
			f[l[i].index1 + 1] += l[i].k*(dis - l[i].r)*(v / dis);  //两连接质点的弹力方向相反
	}
	return f;
}

// render the system (ie draw the particles)
void PendulumSystem::draw()
{
	for (int i = 0; i < m_numParticles; i++) {
		Vector3f pos=m_vVecState[i*2] ;//  position of particle i. YOUR CODE HERE
		glPushMatrix();
		glTranslatef(pos[0], pos[1], pos[2] );
		glutSolidSphere(0.075f,10.0f,10.0f);
		glPopMatrix();
	}
}
