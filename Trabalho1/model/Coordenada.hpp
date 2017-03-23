#ifndef COORD_HPP
#define COORD_HPP

//! Representa uma coordenada (X,Y)
class Coordenada{

private:
	double x; /*!< Valor X da coordenada*/
	double y; /*!< Valor Y da coordenada*/

public:

	//! Construtor
	Coordenada () {}

	//! Construtor
	/*
		/param _x é o valor inicial de X dessa coordenada.
		/param _y é o valor inicial de y dessa coordenada.
	*/
	Coordenada(double _x, double _y) {
		x = _x;
		y = _y;
	}

	//! Método que obtém o valor X da coordenada.
	/*
		/return o valor X da coordenada.
	*/
	double getX() {
		return x;
	}

	//! Método que obtém o valor Y da coordenada.
	/*
		/return o valor Y da coordenada.
	*/
	double getY() {
		return y;
	}

	//! Método que define o valor X da coordenada.
	/*
		/param novoX o novo valor X da coordenada.
	*/
	void setX(double novoX) {
		x = novoX;
	}

	//! Método que define o valor Y da coordenada.
	/*
		/param novoY o novo valor Y da coordenada.
	*/
	void setY(double novoY) {
		y = novoY;
	}

};

#endif
