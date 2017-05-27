#ifndef FORWARDDIFFERENCES_HPP
#define FORWARDDIFFERENCES_HPP

#include "model_Matriz.hpp"

//! Classe que contém os métodos redundantes de forward differences usados em curvas b-spline e em superfícies
class ForwardDifferences {
private:

public:

	void desenhaCurvaFwdDiff(int n, double x, double deltaX, double delta2X, double delta3X, double y, double deltaY,  double delta2Y, double delta3Y, double z, double deltaZ,  double delta2Z, double delta3Z, ListaEnc<Coordenada3D*>* lista) {
		int i = 1;
		double xVelho, yVelho, zVelho;
		xVelho = x;
		yVelho = y;
		zVelho = z;

		Coordenada3D* c = new Coordenada3D(x, y, z);
		lista->adiciona(c);

		while (i < n) {
			x = x + deltaX;
			deltaX = deltaX + delta2X;
			delta2X = delta2X + delta3X;

			y = y + deltaY;
			deltaY = deltaY + delta2Y;
			delta2Y = delta2Y + delta3Y;

			z = z + deltaZ;
			deltaZ = deltaZ + delta2Z;
			delta2Z = delta2Z + delta3Z;

			//Coordenada* c = new Coordenada(x, y);
			Coordenada3D* c = new Coordenada3D(x, y, z);
			lista->adiciona(c);

			xVelho = x;
			yVelho = y;
			zVelho = z;

			i++;
		}
	}

	Matriz<double>* criaMatrizE(double delta) {
		double dQuad = pow(delta, 2);
		double dCubo = pow(delta, 3);

		Matriz<double>* eDelta = new Matriz<double>(4, 4);
		eDelta->setValor(0, 3, 1.0);

		eDelta->setValor(1, 0, dCubo);
		eDelta->setValor(1, 1, dQuad);
		eDelta->setValor(1, 2, delta);

		eDelta->setValor(2, 0, 6*dCubo);
		eDelta->setValor(2, 1, 2*dQuad);

		eDelta->setValor(3, 0, 6*dCubo);

		return eDelta;
	}

	Matriz<double>* inicializaMatrizMbs() {
		Matriz<double>* mbs = new Matriz<double>(4, 4);
		mbs->setValor(0, 0, (double)-1/6);
		mbs->setValor(0, 1, (double)1/2);
		mbs->setValor(0, 2, (double)-1/2);
		mbs->setValor(0, 3, (double)1/6);

		mbs->setValor(1, 0, (double)1/2);
		mbs->setValor(1, 1, -1.0);
		mbs->setValor(1, 2, (double)1/2);

		mbs->setValor(2, 0, (double)-1/2);
		mbs->setValor(2, 2, (double)1/2);

		mbs->setValor(3, 0, (double)1/6);
		mbs->setValor(3, 1, (double)2/3);
		mbs->setValor(3, 2, (double)1/6);

		return mbs;
	}

	

};

#endif