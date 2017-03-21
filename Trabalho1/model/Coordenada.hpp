#ifndef COORD_HPP
#define COORD_HPP

//! Representa uma coordenada (X,Y)
class Coordenada{

private:
	double x; /*!< Valor X da coordenada*/
	double y; /*!< Valor Y da coordenada*/

public:
	Coordenada () {

	}
	
	Coordenada(double novoX, double novoY) {
		x = novoX;
		y = novoY;
	}

	double getX() {
		return x;
	}

	double getY() {
		return y;
	}

	void setX(double novoX) {
		x = novoX;
	}

	void setY(double novoY) {
		y = novoY;
	}
	
};	

#endif
