#include "escena.h"
#include <GL/freeglut.h>

//-------------------------------------------------------------------------

void Escena::init() {
	// texturas
	// luces
}

//-------------------------------------------------------------------------

Escena::~Escena() {
	// liberar memoria y recursos 
}

//-------------------------------------------------------------------------

void Escena::draw() {
	ejes.draw();
	//triangulo.draw();
	//piramide.draw();
	drawDiabolo();
}

void Escena::drawDiabolo() {
	glTranslated(0, 0, -120);
	piramide.draw();

	glRotated(60, 0, 0, 1);
	piramide.draw();

	glTranslated(0, 0, 240);
	glRotated(180, 1, 0, 0);
	piramide.draw();

	glRotated(60, 0, 0, 1);
	piramide.draw();
}

//-------------------------------------------------------------------------

Ejes::Ejes(GLdouble l) {
	vertices[0].set(0, 0, 0);
	vertices[1].set(l, 0, 0);
	vertices[2].set(0, 0, 0);
	vertices[3].set(0, l, 0);
	vertices[4].set(0, 0, 0);
	vertices[5].set(0, 0, l);

	colores[0].set(1, 0, 0);
	colores[1].set(1, 0, 0);
	colores[2].set(0, 1, 0);
	colores[3].set(0, 1, 0);
	colores[4].set(0, 0, 1);
	colores[5].set(0, 0, 1);
}

//-------------------------------------------------------------------------

void Ejes::draw() {
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_DOUBLE, 0, vertices);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_DOUBLE, 0, colores);

	glLineWidth(2);
	glDrawArrays(GL_LINES, 0, 6);
	glLineWidth(1);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	/*
	glLineWidth(2);
	glBegin(GL_LINES);
	glColor3d(1.0, 0.0, 0.0); // red
	glVertex3d(vertices[0].x, vertices[0].y, vertices[0].z);   // origin
	glVertex3d(vertices[1].x, vertices[1].y, vertices[1].z);   // x
	glColor3d(0.0, 1.0, 0.0); // green
	glVertex3d(vertices[2].x, vertices[2].y, vertices[2].z);   // origin
	glVertex3d(vertices[3].x, vertices[3].y, vertices[3].z);	  // y
	glColor3d(0.0, 0.0, 1.0); // blue
	glVertex3d(vertices[4].x, vertices[4].y, vertices[4].z);   // origin
	glVertex3d(vertices[5].x, vertices[5].y, vertices[5].z);	  // z
	glEnd();
	glLineWidth(1);
	*/
}

//-------------------------------------------------------------------------

Triangulo::Triangulo() {

}

Triangulo::Triangulo(float radio) {
	vertices[0].set(radio, 0, 0);
	vertices[1].set(radio*cos((2 * PI) / 3), radio*sin((2 * PI) / 3), 0);
	vertices[2].set(vertices[1].x, -vertices[1].y, 0);
	for (int i = 0; i < 3; i++)
		normales[i].cross(vertices[i]);
}

void Triangulo::draw() {
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_DOUBLE, 0, vertices);
	//glEnableClientState(GL_COLOR_ARRAY);
	//glColorPointer(3, GL_DOUBLE, 0, 0);

	//glLineWidth(2);
	glColor3d(100, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	//glLineWidth(1);

	//glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

//-------------------------------------------------------------------------

PiramideTri::PiramideTri(float radio, float altura) {
	base = Triangulo(radio);
	Triangulo aux = base;
	int j = 2;
	for (int i = 0; i < 3; i++) {
		aux.vertices[j].set(0, 0, altura);
		caras[i] = aux;
		aux = base;
		j++;
		if (j > 2) j = 0;
	}
};

void PiramideTri::draw() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	for (int i = 0; i < 3; i++)
		caras[i].draw();
};

//-------------------------------------------------------------------------

TriAnimado::TriAnimado(GLdouble rotacion, GLdouble giro, GLdouble radio) {
	_rotaux = rotacion;
	_giroaux = giro;
	_rad = radio;
};

void TriAnimado::draw() {
	GLdouble radio = getRadio();
	GLdouble x = radio * cos(_giro / 6.28);
	GLdouble y = radio * sin(_giro / 6.28);
	glTranslated(x, y, 0);
	glRotated(TriAnimado::_rot, 0.0, 0.0, 1.0);
	tri->draw();
	glRotated(-TriAnimado::_rot, 0.0, 0.0, 1.0);
	glTranslated(-x, -y, 0);
};

void TriAnimado::update() {
	_rot += _rotaux;
	_giro += _giroaux;
};