//#pragma once
#ifndef _H_escena_H_
#define _H_escena_H_
#include "tipos.h"

//-------------------------------------------------------------------------
class Ejes {
public:
	Ejes(GLdouble l);
	~Ejes() {};
	void draw();
public:
	PVec3 vertices[6];
	PVec3 colores[6];
};
//-------------------------------------------------------------------------
class Triangulo {
public:
	Triangulo();
	Triangulo(float radio);
	~Triangulo() {};

	void draw();
public:
	float radio;

	PVec3 vertices[3];
	PVec3 normales[3];

};
//-------------------------------------------------------------------------
class PiramideTri {
public:
	PiramideTri() {};
	PiramideTri(float radio, float altura);

	void draw();
public:
	Triangulo base;
	Triangulo caras[3];

};

//-------------------------------------------------------------------------

class TriAnimado {
public:
	TriAnimado(GLdouble rotacion, GLdouble giro, GLdouble radio);
	void update();
	void const draw();
	GLdouble const getRadio() { return _rad; };
private:
	Triangulo*tri = new Triangulo(50);
	GLdouble _rotaux, _giroaux, _rad;
	GLdouble _rot = 0;
	GLdouble _giro = 0;
};

//-------------------------------------------------------------------------

class Escena {
public:
	Escena() : ejes(200), triangulo(50.0), piramide(50, 120), tri(20, 2, 220) {};
	~Escena();
	void init();
	void draw();
	void drawDiabolo();
public:
	Ejes ejes;
	Triangulo triangulo;
	PiramideTri piramide;
	TriAnimado tri;
};

//-------------------------------------------------------------------------
#endif  // _H_escena_H_