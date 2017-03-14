#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "Coordenada.hpp"

class Window {
	
private:
	Coordenada *inferiorEsquerdo, *superiorDireito;
	
public:
	Window(Coordenada* inferiorEsq, Coordenada* superiorDir) {
		inferiorEsquerdo = inferiorEsq;
		superiorDireito = superiorDir;
	}

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
	
	void moverWindow(double fatX, double fatY) {
		inferiorEsquerdo->x += fatX;
		inferiorEsquerdo->y += fatY;
		superiorDireito->x += fatX;
		superiorDireito->y += fatY;
	}
};

#endif