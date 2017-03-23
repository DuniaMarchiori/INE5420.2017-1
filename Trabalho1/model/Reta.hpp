#ifndef RETA_HPP
#define RETA_HPP

#include "ElementoGrafico.hpp"
#include "Coordenada.hpp"

class Reta: public ElementoGrafico {
	
private:
	Coordenada *pontoInicial, *pontoFinal; /*!< Coordenadas dos pontos inicial e final da reta*/
	
public:
	//! Construtor
	/*!
		/param nome é o nome da reta
		/param pInicial é a coordenada do ponto inicial da reta.
		/param pFinal é a coordenada do ponto final da reta.
	*/
	Reta(string nome, Coordenada* pInicial, Coordenada* pFinal) {
		pontoInicial = pInicial;
		pontoFinal = pFinal;
		setNome(nome);
		setTipo(RETA);
	}
	
	//! Método que retorna o valor da coordenada do ponto inicial.
	/*!
		/return a coordenada do ponto inicial.
	*/
	Coordenada* getPontoInicial() {
		return pontoInicial;
	}
	
	//! Método que altera o valor da coordenada do ponto inicial.
	/*!
		/param p é o valor que a coordenada inicial receberá.
	*/
	void setPontoInicial(Coordenada* p) {
		pontoInicial = p;
	}
	
	//! Método que retorna o valor da coordenada do ponto final.
	/*!
		/return a coordenada do ponto final.
	*/
	Coordenada* getPontoFinal() {
		return pontoFinal;
	}
	
	//! Método que altera o valor da coordenada do ponto final.
	/*!
		/param p é o valor que a coordenada final receberá.
	*/
	void setPontoFinal(Coordenada* p) {
		pontoFinal = p;
	}

	//! Método que retorna o centro geométrico da reta.
	/*!
		/return uma Coordenada que indica o centro geométrico da reta.
	*/
	Coordenada* getCentroGeometrico() override {
		double retornoX = (pontoInicial->getX() + pontoFinal->getX()) /2;
		double retornoY = (pontoInicial->getY() + pontoFinal->getY()) /2;
		Coordenada* coord = new Coordenada(retornoX,retornoY);
		return coord;
	}
};

#endif