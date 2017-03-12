#ifndef RETA_HPP
#define RETA_HPP

#include "ElementoGrafico.hpp"
#include "Coordenada.hpp"

class Reta: public ElementoGrafico {
	
private:
	Coordenada *pontoInicial, *pontoFinal;
	
public:
	Reta(Coordenada* pInicial, Coordenada* pFinal) {
		pontoInicial = pInicial;
		pontoFinal = pFinal;
		setTipo(RETA);
	}
	
	Coordenada* getPontoInicial() {
		return pontoInicial;
	}
	
	void setPontoInicial(Coordenada* p) {
		pontoInicial = p;
	}
	
	Coordenada* getPontoFinal() {
		return pontoFinal;
	}
	
	void setPontoFinal(Coordenada* p) {
		pontoFinal = p;
	}
};

#endif