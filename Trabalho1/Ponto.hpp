#ifndef PONTO_HPP
#define PONTO_HPP

#include "ElementoGrafico.hpp"
#include "Coordenada.hpp"

class Ponto: public ElementoGrafico {
	
private:
	Coordenada* coord; /*!< A coordenada do ponto*/
	
public:
	//! Construtor
	/*!
		/param c é a coordenada do ponto.
	*/
	Ponto(string nome, Coordenada* c) {
		setCoordenada(c);
		setNome(nome);
		setTipo(PONTO);
	}
	
	//! Método que retorna o valor da coordenada.
	/*!
		/return a coordenada do ponto.
	*/
	Coordenada* getCoordenada() {
		return coord;
	}
	
	//! Método que altera o valor da coordenada do ponto.
	/*!
		/param c é o valor que a coordenada receberá.
	*/
	void setCoordenada(Coordenada* c) {
		coord = c;
	}
};

#endif