#ifndef CURVABSPLINE_HPP
#define CURVABSPLINE_HPP

#include "model_Matriz.hpp"

#include "model_Curva.hpp"
#include "model_Coordenada3D.hpp"
#include "ListaEnc.hpp"

class CurvaBSpline : public Curva {
private:

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

public:

	//! Construtor
	/*CurvaBSpline() : Curva() {
		setTipo(CURVA);
	}

	//! Construtor
	/*
		/param nome é o nome da curva
	*/
	/*CurvaBSpline() : Curva(string nome) {
		setTipo(CURVA);
	}

	//! Construtor
	/*
		/param nome é o nome da curva
		/param novaLista é a lista de coordenadas da curva
	*/
	CurvaBSpline(string nome, ListaEnc<Coordenada3D*> *novaLista) : Curva(nome, novaLista) {}

	//! Método que retorna os pontos da curva.
	/*!
		/param segmentos em quantos segmentos a curva sera dividida.
		/return uma lista de coordenadas
	*/
	ListaEnc<Coordenada3D*>* getCurvaFinal(int segmentos) override{
		
		ListaEnc<Coordenada3D*>* listaFinal = new ListaEnc<Coordenada3D*>();

		double d = 1.0/(double)segmentos; // deltinha

		double dQuad = pow(d, 2);
		double dCubo = pow(d, 3);

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

		Matriz<double>* eDelta = new Matriz<double>(4, 4);
		eDelta->setValor(0, 3, 1.0);

		eDelta->setValor(1, 0, dCubo);
		eDelta->setValor(1, 1, dQuad);
		eDelta->setValor(1, 2, d);

		eDelta->setValor(2, 0, 6*dCubo);
		eDelta->setValor(2, 1, 2*dQuad);

		eDelta->setValor(3, 0, 6*dCubo);

		Elemento<Coordenada3D*>* elementoLista = getListaNormal()->getHead();
		Coordenada3D *C1, *C2, *C3, *C4;

		C1 = elementoLista->getInfo();

		elementoLista = elementoLista->getProximo();
		C2 = elementoLista->getInfo();

		elementoLista = elementoLista->getProximo();
		C3 = elementoLista->getInfo();

		elementoLista = elementoLista->getProximo();

		while (elementoLista != NULL) {
			C4 = elementoLista->getInfo();

			Matriz<double>* gx = new Matriz<double>(4, 1);
			Matriz<double>* gy = new Matriz<double>(4, 1);
			Matriz<double>* gz = new Matriz<double>(4, 1);

			gx->setValor(0, 0, C1->getX());
			gx->setValor(1, 0, C2->getX());
			gx->setValor(2, 0, C3->getX());
			gx->setValor(3, 0, C4->getX());

			gy->setValor(0, 0, C1->getY());
			gy->setValor(1, 0, C2->getY());
			gy->setValor(2, 0, C3->getY());
			gy->setValor(3, 0, C4->getY());

			gz->setValor(0, 0, C1->getZ());
			gz->setValor(1, 0, C2->getZ());
			gz->setValor(2, 0, C3->getZ());
			gz->setValor(3, 0, C4->getZ());

			Matriz<double>* cx = mbs->multiplica(gx);
			Matriz<double>* cy = mbs->multiplica(gy);
			Matriz<double>* cz = mbs->multiplica(gz);

			Matriz<double>* colunaDeFx = eDelta->multiplica(cx);
			Matriz<double>* colunaDeFy = eDelta->multiplica(cy);
			Matriz<double>* colunaDeFz = eDelta->multiplica(cz);

			double n, x, dx,d2x, d3x, y, dy, d2y, d3y, z, dz, d2z, d3z;

			n = 1.0/d;

			x   = colunaDeFx->getValor(0, 0);
			dx  = colunaDeFx->getValor(1, 0);
			d2x = colunaDeFx->getValor(2, 0);
			d3x = colunaDeFx->getValor(3, 0);

			y   = colunaDeFy->getValor(0, 0);
			dy  = colunaDeFy->getValor(1, 0);
			d2y = colunaDeFy->getValor(2, 0);
			d3y = colunaDeFy->getValor(3, 0);

			z   = colunaDeFz->getValor(0, 0);
			dz  = colunaDeFz->getValor(1, 0);
			d2z = colunaDeFz->getValor(2, 0);
			d3z = colunaDeFz->getValor(3, 0);
			
			desenhaCurvaFwdDiff(n, x, dx, d2x, d3x, y, dy, d2y, d3y, z, dz, d2z, d3z, listaFinal);

			C1 = C2;
			C2 = C3;
			C3 = C4;
			elementoLista = elementoLista->getProximo();
		}

		if (listaFinal->getHead() == NULL) {
			free(listaFinal);
			return NULL;
		}
		return listaFinal;
		
		return NULL;
	}

};

#endif
