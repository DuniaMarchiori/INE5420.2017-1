#ifndef COORD_HPP
#define COORD_HPP

//! Struct que representa uma coordenada (X,Y)
struct Coordenada{

	double x; /*!< Valor X da coordenada*/
	double y; /*!< Valor Y da coordenada*/

	//! Método que altera o valor X da coordenada.
	/*!
		/param valor é o valor que o X da coordenada receberá.
	*/
	void setX(double valor) { x = valor; }

	//! Método que altera o valor Y da coordenada.
	/*!
		/param valor é o valor que o Y da coordenada receberá.
	*/
	void setY(double valor) { y = valor; }
};	

#endif
