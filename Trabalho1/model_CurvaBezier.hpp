#ifndef CURVABEZIER_HPP
#define CURVABEZIER_HPP

#include "model_Curva.hpp"
#include "model_Coordenada.hpp"
#include "ListaEnc.hpp"
#include <math.h>

class CurvaBezier : public Curva {

public:

	//! Construtor
	/*CurvaBezier() : Curva() {
		setTipo(CURVA);
	}

	//! Construtor
	/*
		/param nome é o nome da curva
	*/
	/*CurvaBezier() : Curva(string nome) {
		setTipo(CURVA);
	}

	//! Construtor
	/*
		/param nome é o nome da curva
		/param novaLista é a lista de coordenadas da curva
	*/
	CurvaBezier(string nome, ListaEnc<Coordenada3D*> *novaLista) : Curva(nome, novaLista) {}

	//! Método que retorna os pontos da curva.
	/*!
		/param segmentos em quantos segmentos a curva sera dividida.
		/return uma lista de coordenadas
	*/
	ListaEnc<Coordenada3D*>* getCurvaFinal(int segmentos) override{

		double d = 1.0/(double)segmentos;
		ListaEnc<Coordenada3D*>* curvaB = new ListaEnc<Coordenada3D*>();
		double x, y, z, p1x, p2x, p3x, p4x, p1y, p2y, p3y, p4y, p1z, p2z, p3z, p4z, quantidadePontos;
		int indice = 0;
		quantidadePontos = listaMundo->getSize();

		// Calcula os pontos da curva
		while (indice < quantidadePontos - 1) { // indice começa em 0 mas quantidadePontos começa em 1
			p1x = listaNormal->elementoNoIndice(indice)->getX();
			p1y = listaNormal->elementoNoIndice(indice)->getY();
			p1z = listaNormal->elementoNoIndice(indice)->getZ();

			p2x = listaNormal->elementoNoIndice(indice + 1)->getX();
			p2y = listaNormal->elementoNoIndice(indice + 1)->getY();
			p2z = listaNormal->elementoNoIndice(indice + 1)->getZ();

			p3x = listaNormal->elementoNoIndice(indice + 2)->getX();
			p3y = listaNormal->elementoNoIndice(indice + 2)->getY();
			p3z = listaNormal->elementoNoIndice(indice + 2)->getZ();

			p4x = listaNormal->elementoNoIndice(indice + 3)->getX();
			p4y = listaNormal->elementoNoIndice(indice + 3)->getY();
			p4z = listaNormal->elementoNoIndice(indice + 3)->getZ();

			double passo = 0;
			for (int i = 0; i <= segmentos; i++) {
				x = blendingFunction(p1x, p2x, p3x, p4x, passo);
				y = blendingFunction(p1y, p2y, p3y, p4y, passo);
				z = blendingFunction(p1z, p2z, p3z, p4z, passo);

				if ( !(indice != 0 && passo == 0.0) ) { // para não adicionar duas vezes os pontos comuns de duas sub-curvas
					Coordenada3D* coord = new Coordenada3D(x, y, z);
					curvaB->adiciona(coord);
				}
				passo += d;
			}

			indice += 3;
		}
		return curvaB;

		return NULL;
	}

private:
	double blendingFunction(double p1, double p2, double p3, double p4, double t) {
		double t3 = pow(t, 3);
		double t2 = pow(t, 2);
		return p1 *( (-t3) + (3*t2) + (-3*t) + 1) + p2 * ( (3*t3) + (-6 * t2) + 3*t ) + p3 *( (-3 * t3) + (3 * t2) ) + p4 * (t3);
	}

};

#endif