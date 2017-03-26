#ifndef PONTO_HPP
#define PONTO_HPP

#include "model_ElementoGrafico.hpp"
#include "model_Coordenada.hpp"

class Ponto: public ElementoGrafico {
	
private:
	Coordenada* coordenadaMundo; /*!< A coordenada do ponto no mundo*/
	Coordenada* coordenadaNormal; /*!< A coordenada do ponto normalizada*/
	
public:
	//! Construtor
	/*!
		/param nome é o nome do ponto
		/param c é a coordenada do ponto no mundo.
	*/
	Ponto(string nome, Coordenada* c) {
		setCoordenadaMundo(c);
		setNome(nome);
		setTipo(PONTO);
	}
	
	//! Método que retorna o valor da coordenada no mundo.
	/*!
		/return a coordenada do ponto no mundo.
	*/
	Coordenada* getCoordenadaMundo() {
		return coordenadaMundo;
	}
	
	//! Método que altera o valor da coordenada do ponto no mundo.
	/*!
		/param c é o valor que a coordenada receberá.
	*/
	void setCoordenadaMundo(Coordenada* c) {
		coordenadaMundo = c;
	}
	
	//! Método que retorna o valor da coordenada normalizada.
	/*!
		/return a coordenada do ponto normalizada.
	*/
	Coordenada* getCoordenadaNormal() {
		return coordenadaNormal;
	}
	
	//! Método que altera o valor da coordenada do ponto normalizada.
	/*!
		/param c é o valor que a coordenada receberá.
	*/
	void setCoordenadaNormal(Coordenada* c) {
		coordenadaNormal = c;
	}

	//! Método que retorna o centro geométrico do ponto.
	/*!
		/return uma Coordenada que indica o centro geométrico do ponto.
	*/
	Coordenada* getCentroGeometrico() override {
		return coordenadaMundo;
	}
};

#endif