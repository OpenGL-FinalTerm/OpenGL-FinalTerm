#include "stdafx.h"
#include "Picking.h"

double		Picking::m_pdPickedPoint[3];
bool		Picking::m_bPicked{ false };

void Picking::get(int x, int y)
{
	GLdouble proj[16];
	GLdouble model[16];
	GLint	viewport[4];

	glGetDoublev(GL_PROJECTION_MATRIX, proj);
	glGetDoublev(GL_MODELVIEW_MATRIX, model);
	glGetIntegerv(GL_VIEWPORT, viewport);

	GLdouble fZ;
	GLdouble fX = static_cast<GLdouble>(x);
	GLdouble fY = static_cast<GLdouble>(viewport[3] - y);
	glReadPixels(x, static_cast<int>(fY), 1, 1, GL_DEPTH_COMPONENT, GL_DOUBLE, &fZ);

	auto result = gluUnProject(
		fX, fY, fZ,
		model, proj, viewport,
		&m_pdPickedPoint[0],
		&m_pdPickedPoint[1],
		&m_pdPickedPoint[2]
	);

	if (result == GLU_FALSE)
		std::cout << "Error with unprojecting mouse pick!" << std::endl;
	else
		m_bPicked = true;
}

void Picking::draw(int nPointSize)
{
	if (!m_bPicked) return;
	glPointSize(static_cast<GLfloat>(nPointSize));
	glBegin(GL_POINTS);
	glVertex3d(m_pdPickedPoint[0], m_pdPickedPoint[1], m_pdPickedPoint[2]);
	glEnd();
}

Vector3 Picking::toVector3()
{
	return Vector3
	(
		static_cast<float>(m_pdPickedPoint[0]),
		static_cast<float>(m_pdPickedPoint[1]),
		static_cast<float>(m_pdPickedPoint[2])
	);
}
