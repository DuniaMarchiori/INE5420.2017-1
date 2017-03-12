#ifndef PONTO_HPP
#define PONTO_HPP

#include "ElementoGrafico.hpp"
#include "Coordenada.hpp"

class Ponto: public ElementoGrafico {
	
private:
	Coordenada* coord;
	
public:
	Ponto(Coordenada* c) {
		setCoordenada(c);
		setTipo(PONTO);
	}
	
	Coordenada* getCoordenada() {
		return coord;
	}
	
	void setCoordenada(Coordenada* c) {
		coord = c;
	}
};

#endif