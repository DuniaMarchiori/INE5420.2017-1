#ifndef RETA_HPP
#define RETA_HPP

#include "model_ElementoGrafico.hpp"
#include "model_Coordenada3D.hpp"

class Reta: public ElementoGrafico {

private:
	Coordenada3D *coordenadaMundoInicial, *coordenadaMundoFinal; /*!< Coordenadas dos pontos inicial e final da reta no mundo*/
	Coordenada3D *coordenadaNormalInicial, *coordenadaNormalFinal; /*!< Coordenadas dos pontos inicial e final da reta normalizadas*/

public:

	//! Construtor
	Reta() {
		coordenadaMundoInicial = new Coordenada3D();
		coordenadaMundoFinal = new Coordenada3D();
		setNome("");
		setTipo(RETA);
	}

	//! Construtor
	/*!
		/param nome é o nome da reta
		/param pInicial é a coordenada do ponto inicial da reta.
		/param pFinal é a coordenada do ponto final da reta.
	*/
	Reta(string nome, Coordenada3D* pInicial, Coordenada3D* pFinal) {
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
	Coordenada3D* getCoordenadaMundoInicial() {
		return coordenadaMundoInicial;
	}

	//! Método que altera o valor da coordenada do ponto inicial no mundo.
	/*!
		/param p é o valor que a coordenada inicial receberá.
	*/
	void setCoordenadaMundoInicial(Coordenada3D* p) {
		coordenadaMundoInicial = p;
	}

	//! Método que retorna o valor da coordenada do ponto final no mundo.
	/*!
		/return a coordenada do ponto final no mundo.
	*/
	Coordenada3D* getCoordenadaMundoFinal() {
		return coordenadaMundoFinal;
	}

	//! Método que altera o valor da coordenada do ponto final no mundo.
	/*!
		/param p é o valor que a coordenada final receberá.
	*/
	void setCoordenadaMundoFinal(Coordenada3D* p) {
		coordenadaMundoFinal = p;
	}

	// Coordenadas Normalizadas

	//! Método que retorna o valor da coordenada do ponto inicial normalizada.
	/*!
		/return a coordenada do ponto inicial normalizada.
	*/
	Coordenada3D* getCoordenadaNormalInicial() {
		return coordenadaNormalInicial;
	}

	//! Método que altera o valor da coordenada do ponto inicial normalizada.
	/*!
		/param p é o valor que a coordenada inicial receberá.
	*/
	void setCoordenadaNormalInicial(Coordenada3D* p) {
		coordenadaNormalInicial = p;
	}

	//! Método que retorna o valor da coordenada do ponto final normalizada.
	/*!
		/return a coordenada do ponto final normalizada.
	*/
	Coordenada3D* getCoordenadaNormalFinal() {
		return coordenadaNormalFinal;
	}

	//! Método que altera o valor da coordenada do ponto final normalizada.
	/*!
		/param p é o valor que a coordenada final receberá.
	*/
	void setCoordenadaNormalFinal(Coordenada3D* p) {
		coordenadaNormalFinal = p;
	}


	//! Método que retorna o centro geométrico da reta.
	/*!
		/return uma Coordenada que indica o centro geométrico da reta.
	*/
	Coordenada3D* getCentroGeometrico() override {
		double retornoX = (coordenadaMundoInicial->getX() + coordenadaMundoFinal->getX()) /2;
		double retornoY = (coordenadaMundoInicial->getY() + coordenadaMundoFinal->getY()) /2;
		double retornoZ = (coordenadaMundoInicial->getZ() + coordenadaMundoFinal->getZ()) /2;
		Coordenada3D* coord = new Coordenada3D(retornoX, retornoY, retornoZ);
		return coord;
	}
};

#endif