#ifndef RETA_HPP
#define RETA_HPP

#include "model_ElementoGrafico.hpp"
#include "model_Coordenada.hpp"

class Reta: public ElementoGrafico {

private:
	Coordenada *coordenadaMundoInicial, *coordenadaMundoFinal; /*!< Coordenadas dos pontos inicial e final da reta no mundo*/
	Coordenada *coordenadaNormalInicial, *coordenadaNormalFinal; /*!< Coordenadas dos pontos inicial e final da reta normalizadas*/

public:
	//! Construtor
	/*!
		/param nome é o nome da reta
		/param pInicial é a coordenada do ponto inicial da reta.
		/param pFinal é a coordenada do ponto final da reta.
	*/
	Reta(string nome, Coordenada* pInicial, Coordenada* pFinal) {
		coordenadaMundoInicial = pInicial;
		coordenadaMundoFinal = pFinal;
		setNome(nome);
		setTipo(RETA);
	}

	// Coordenadas no Mundo.

	//! Método que retorna o valor da coordenada do ponto inicial no mundo.
	/*!
		/return a coordenada do ponto inicial no mundo.
	*/
	Coordenada* getCoordenadaMundoInicial() {
		return coordenadaMundoInicial;
	}

	//! Método que altera o valor da coordenada do ponto inicial no mundo.
	/*!
		/param p é o valor que a coordenada inicial receberá.
	*/
	void setCoordenadaMundoInicial(Coordenada* p) {
		coordenadaMundoInicial = p;
	}

	//! Método que retorna o valor da coordenada do ponto final no mundo.
	/*!
		/return a coordenada do ponto final no mundo.
	*/
	Coordenada* getCoordenadaMundoFinal() {
		return coordenadaMundoFinal;
	}

	//! Método que altera o valor da coordenada do ponto final no mundo.
	/*!
		/param p é o valor que a coordenada final receberá.
	*/
	void setCoordenadaMundoFinal(Coordenada* p) {
		coordenadaMundoFinal = p;
	}

	// Coordenadas Normalizadas

	//! Método que retorna o valor da coordenada do ponto inicial normalizada.
	/*!
		/return a coordenada do ponto inicial normalizada.
	*/
	Coordenada* getCoordenadaNormalInicial() {
		return coordenadaNormalInicial;
	}

	//! Método que altera o valor da coordenada do ponto inicial normalizada.
	/*!
		/param p é o valor que a coordenada inicial receberá.
	*/
	void setCoordenadaNormalInicial(Coordenada* p) {
		coordenadaNormalInicial = p;
	}

	//! Método que retorna o valor da coordenada do ponto final normalizada.
	/*!
		/return a coordenada do ponto final normalizada.
	*/
	Coordenada* getCoordenadaNormalFinal() {
		return coordenadaNormalFinal;
	}

	//! Método que altera o valor da coordenada do ponto final normalizada.
	/*!
		/param p é o valor que a coordenada final receberá.
	*/
	void setCoordenadaNormalFinal(Coordenada* p) {
		coordenadaNormalFinal = p;
	}


	//! Método que retorna o centro geométrico da reta.
	/*!
		/return uma Coordenada que indica o centro geométrico da reta.
	*/
	Coordenada* getCentroGeometrico() override {
		double retornoX = (coordenadaMundoInicial->getX() + coordenadaMundoFinal->getX()) /2;
		double retornoY = (coordenadaMundoInicial->getY() + coordenadaMundoFinal->getY()) /2;
		Coordenada* coord = new Coordenada(retornoX,retornoY);
		return coord;
	}
};

#endif