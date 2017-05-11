#ifndef COORD3_HPP
#define COORD3_HPP

class Coordenada3D : public Coordenada {

private:
	double z; /*!< Valor Z da coordenada*/

public:

	//! Construtor
	Coordenada3D() : Coordenada() {
		z = 0;
	}

	//! Construtor
	/*
		/param _x é o valor inicial de X dessa coordenada.
		/param _y é o valor inicial de y dessa coordenada.
		/param _z é o valor inicial de y dessa coordenada.
	*/
	Coordenada3D(double _x, double _y, double _z) : Coordenada(_x, _y) {
		z = _z;
	}

	//! Construtor
	/*
		/param coord é uma coordenada cujos valores serão copiados para esta.
	*/
	Coordenada3D(Coordenada3D* coord) {
		setX(coord->getX());
		setY(coord->getY());
		z = coord->getZ();
	}
	
	//! Construtor
	/*
		/param coord é uma coordenada 2D cujos valores serão copiados para esta e Z setado para 0.
	*/
	Coordenada3D(Coordenada* coord) {
		setX(coord->getX());
		setY(coord->getY());
		z = 0;
	}

	//! Método que obtém o valor Z da coordenada.
	/*
		/return o valor Z da coordenada.
	*/
	double getZ() {
		return z;
	}

	//! Método que define o valor Z da coordenada.
	/*
		/param novoX o novo valor Z da coordenada.
	*/
	void setZ(double novoZ) {
		z = novoZ;
	}

};

#endif
