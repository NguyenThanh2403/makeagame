#include "Ball.h"
void Ball::CaculateWorldMatrix()
{
	Matrix m_Sc, m_Rx, m_Ry, m_Rz, m_T;
	m_Sc.SetScale(m_Vec3Scale);
	GLfloat tempX = (GLfloat)(m_Vec3Rotation.x * PI * 2 / MAX_DEGREE);
	m_Rx.SetRotationX(tempX);
	GLfloat tempY = (GLfloat)(m_Vec3Rotation.y * PI * 2 / MAX_DEGREE);
	m_Ry.SetRotationY(tempY);
	GLfloat tempZ = (GLfloat)(m_Vec3Rotation.z * PI * 2 / MAX_DEGREE);
	m_Rz.SetRotationZ(tempZ);
	m_T.SetTranslation(m_Vec3Position);

	m_WorldMat = m_Sc * m_Rz * m_Rx * m_Ry * m_T;
}

