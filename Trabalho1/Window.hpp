#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "Coordenada.hpp"

class Window {
	
private:
	Coordenada *inferiorEsquerdo, *superiorDireito;
	
public:
	Coordenada* getPontoInferiorEsquerdo() {
		return inferiorEsquerdo;
	}
	
	void setPontoInferiorEsquerdo(Coordenada* p) {
		inferiorEsquerdo = p;
	}
	
	Coordenada* getPontoSuperiorDireito() {
		return superiorDireito;
	}
	
	void setPontoSuperiorDireito(Coordenada* p) {
		superiorDireito = p;
	}	
}
#endif