#include <iostream>

#ifndef CURVABSPLINE_HPP
#define CURVABSPLINE_HPP

#include "model_Matriz.hpp"

#include "model_Curva.hpp"
#include "model_Coordenada.hpp"
#include "ListaEnc.hpp"

class CurvaBSpline : public Curva {
private:

	void desenhaCurvaFwdDiff(int n, double x, double deltaX, double delta2X, double delta3X, double y, double deltaY,  double delta2Y, double delta3Y, ListaEnc<Coordenada*>* lista) {
		int i = 1;
		double xVelho, yVelho;
		xVelho = x;
		yVelho = y;

		std::cout << x << ", " << y << std::endl;
		Coordenada* c = new Coordenada(x, y);
		lista->adiciona(c);

		while (i < n) {
			x = x + deltaX;
			deltaX = deltaX + delta2X;
			delta2X = delta2X + delta3X;

			y = y + deltaY;
			deltaY = deltaY + delta2Y;
			delta2Y = delta2Y + delta3Y;

			Coordenada* c = new Coordenada(x, y);
			lista->adiciona(c);
			std::cout << x << ", " << y << std::endl;

			xVelho = x;
			yVelho = y;

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
	CurvaBSpline(string nome, ListaEnc<Coordenada*> *novaLista) : Curva(nome, novaLista) {}

	//! Método que retorna os pontos da curva.
	/*!
		/param segmentos em quantos segmentos a curva sera dividida.
		/return uma lista de coordenadas
	*/
	ListaEnc<Coordenada*>* getCurvaFinal(int segmentos) override{
		ListaEnc<Coordenada*>* listaFinal = new ListaEnc<Coordenada*>();

		std::cout << "A" << std::endl;

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

		Elemento<Coordenada*>* elementoLista = getListaMundo()->getHead();
		Coordenada *C1, *C2, *C3, *C4;

		C1 = elementoLista->getInfo();

		elementoLista = elementoLista->getProximo();
		C2 = elementoLista->getInfo();

		elementoLista = elementoLista->getProximo();
		C3 = elementoLista->getInfo();

		elementoLista = elementoLista->getProximo();

		std::cout << "A" << std::endl;

		while (elementoLista != NULL) {
			std::cout << "B" << std::endl;
			C4 = elementoLista->getInfo();

			Matriz<double>* gx = new Matriz<double>(4, 1);
			Matriz<double>* gy = new Matriz<double>(4, 1);

			gx->setValor(0, 0, C1->getX());
			gx->setValor(1, 0, C2->getX());
			gx->setValor(2, 0, C3->getX());
			gx->setValor(3, 0, C4->getX());

			gy->setValor(0, 0, C1->getY());
			gy->setValor(1, 0, C2->getY());
			gy->setValor(2, 0, C3->getY());
			gy->setValor(3, 0, C4->getY());

			Matriz<double>* cx = mbs->multiplica(gx);
			Matriz<double>* cy = mbs->multiplica(gy);

			Matriz<double>* colunaDeFx = eDelta->multiplica(cx);
			Matriz<double>* colunaDeFy = eDelta->multiplica(cy);

			double n, x, dx,d2x, d3x, y, dy, d2y, d3y;

			n = 1.0/d;

			x   = colunaDeFx->getValor(0, 0);
			dx  = colunaDeFx->getValor(1, 0);
			d2x = colunaDeFx->getValor(2, 0);
			d3x = colunaDeFx->getValor(3, 0);

			y   = colunaDeFy->getValor(0, 0);
			dy  = colunaDeFy->getValor(1, 0);
			d2y = colunaDeFy->getValor(2, 0);
			d3y = colunaDeFy->getValor(3, 0);

			std::cout << n << std::endl;
			desenhaCurvaFwdDiff(n, x, dx, d2x, d3x, y, dy, d2y, d3y, listaFinal);

			C1 = C2;
			C2 = C3;
			C3 = C4;
			elementoLista = elementoLista->getProximo();
			std::cout << "C" << std::endl;
		}

		std::cout << "A" << std::endl;

		if (listaFinal->getHead() == NULL) {
			free(listaFinal);
			return NULL;
		}
		return listaFinal;
	}

};

#endif