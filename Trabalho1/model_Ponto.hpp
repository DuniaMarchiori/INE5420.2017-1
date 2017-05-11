#ifndef PONTO_HPP
#define PONTO_HPP

#include "model_ElementoGrafico.hpp"
#include "model_Coordenada3D.hpp"

class Ponto: public ElementoGrafico {
	
private:
	Coordenada3D* coordenadaMundo; /*!< A coordenada do ponto no mundo*/
	Coordenada3D* coordenadaNormal; /*!< A coordenada do ponto normalizada*/
	
public:
	//! Construtor
	/*!
		/param nome é o nome do ponto
		/param c é a coordenada do ponto no mundo.
	*/
	Ponto(string nome, Coordenada3D* c) {
		setCoordenadaMundo(c);
		setNome(nome);
		setTipo(PONTO);
	}
	
	//! Método que retorna o valor da coordenada no mundo.
	/*!
		/return a coordenada do ponto no mundo.
	*/
	Coordenada3D* getCoordenadaMundo() {
		return coordenadaMundo;
	}
	
	//! Método que altera o valor da coordenada do ponto no mundo.
	/*!
		/param c é o valor que a coordenada receberá.
	*/
	void setCoordenadaMundo(Coordenada3D* c) {
		coordenadaMundo = c;
	}
	
	//! Método que retorna o valor da coordenada normalizada.
	/*!
		/return a coordenada do ponto normalizada.
	*/
	Coordenada3D* getCoordenadaNormal() {
		return coordenadaNormal;
	}
	
	//! Método que altera o valor da coordenada do ponto normalizada.
	/*!
		/param c é o valor que a coordenada receberá.
	*/
	void setCoordenadaNormal(Coordenada3D* c) {
		coordenadaNormal = c;
	}

	//! Método que retorna o centro geométrico do ponto.
	/*!
		/return uma Coordenada que indica o centro geométrico do ponto.
	*/
	Coordenada3D* getCentroGeometrico() override {
		Coordenada3D* retorno = new Coordenada3D(coordenadaMundo);
		return retorno;
	}
};

#endif