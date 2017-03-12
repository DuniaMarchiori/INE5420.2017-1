#ifndef PONTO_HPP
#define PONTO_HPP

#include "ElementoGrafico.hpp"
#include "Coordenada.hpp"

class Ponto: public ElementoGrafico {
	
private:
	Coordenada coord;
	
public:
	Ponto(double x, double y) {
		setCoordenada(x,y);
		setTipo(PONTO);
	}
	
	Coordenada getCoordenada() {
		return coord;
	}
	
	void setCoordenada(double x, double y) {
		coord.x = x;
		coord.y = y;
	}
};

#endif