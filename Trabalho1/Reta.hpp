#ifndef RETA_HPP
#define RETA_HPP

#include "ElementoGrafico.hpp"
#include "Ponto.hpp"

class Reta: public ElementoGrafico {
	
private:
	Ponto *pontoInicial, *pontoFinal;
	
public:
	Reta(Ponto* pInicial, Ponto* pFinal) {
		pontoInicial = pInicial;
		pontoFinal = pFinal;
		setTipo(RETA);
	}
	
	Ponto* getPontoInicial() {
		return pontoInicial;
	}
	
	void setPontoInicial(Ponto* p) {
		pontoInicial = p;
	}
	
	Ponto* getPontoFinal() {
		return pontoFinal;
	}
	
	void setPontoFinal(Ponto* p) {
		pontoFinal = p;
	}
};

#endif