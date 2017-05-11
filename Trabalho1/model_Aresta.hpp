#ifndef ARESTA_HPP
#define ARESTA_HPP

#include "model_Coordenada.hpp"

class Aresta {

private:
	Coordenada3D *coordA, *coordB;

public:
	//! Construtor
	Aresta(Coordenada3D* A, Coordenada3D* B) {
		coordA = A;
		coordB = B;
	}

	//! Método que retorna a coordenada A da aresta.
	/*!
		/return a coordenada A.
	*/
	Coordenada3D* getCoordA() {
		return coordA;
	}
	
	//! Método que altera a coordenada A.
	/*!
		/param c é a nova coordenada A.
	*/
	void setCoordenadaA(Coordenada3D* c) {
		coordA = c;
	}
	
	//! Método que retorna a coordenada B da aresta.
	/*!
		/return a coordenada B.
	*/
	Coordenada3D* getCoordB() {
		return coordB;
	}
	
	//! Método que altera a coordenada B.
	/*!
		/param c é a nova coordenada B.
	*/
	void setCoordenadaB(Coordenada3D* c) {
		coordB = c;
	}
};

#endif