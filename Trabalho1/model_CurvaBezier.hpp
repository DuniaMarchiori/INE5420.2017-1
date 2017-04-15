#ifndef POLIGONO_HPP
#define POLIGONO_HPP

#include "model_Curva.hpp"
#include "model_Coordenada.hpp"
#include "ListaEnc.hpp"

class CurvaBezier : public Curva {

public:

	//! Construtor
	CurvaBezier() : Curva() {
		setTipo(CURVABEZIER);
	}

	//! Construtor
	/*
		/param nome é o nome da curva
	*/
	CurvaBezier() : Curva(string nome) {
		setTipo(CURVABEZIER);
	}

	//! Construtor
	/*
		/param nome é o nome da curva
		/param novaLista é a lista de coordenadas da curva
	*/
	CurvaBezier() : Curva(string nome, ListaEnc<Coordenada*> *novaLista) {
		setTipo(CURVABEZIER);
	}

	//! Método que retorna os pontos da curva.
	/*!
		/param segmentos em quantos segmentos a curva sera dividida.
		/return uma lista de coordenadas
	*/
	ListaEnc<Coordenada*>* getCurvaFinal(int segmentos) {
		double d = 1/segmentos; // deltinha
		
		// Calcula os pontos da curva e retorna.
		
	}

};

#endif