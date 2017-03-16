#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "Coordenada.hpp"

class Window {
	
private:
	Coordenada *inferiorEsquerdo, *superiorDireito; /*!< As coordenadas que indicam os pontos inferior esquerdo e superior direito da Window, respectivamente.*/
	
public:
	//! Construtor
	/*!
		/param inferiorEsq é o ponto inferior esquerdo da Window
		/param superiorDir é o ponto superior direito da Window
	*/
	Window(Coordenada* inferiorEsq, Coordenada* superiorDir) {
		inferiorEsquerdo = inferiorEsq;
		superiorDireito = superiorDir;
	}

	//! Método que retorna o valor do ponto inferior esquerdo da Window.
	/*!
		/return a coordenada do ponto inferior esquerdo.
	*/
	Coordenada* getPontoInferiorEsquerdo() {
		return inferiorEsquerdo;
	}
	
	//! Método que altera o valor da coordenada do ponto inferior esquerdo da Window.
	/*!
		/param p é o valor que a coordenada receberá.
	*/
	void setPontoInferiorEsquerdo(Coordenada* p) {
		inferiorEsquerdo = p;
	}
	
	//! Método que retorna o valor do ponto superior direito da Window.
	/*!
		/return a coordenada do ponto superior direito.
	*/
	Coordenada* getPontoSuperiorDireito() {
		return superiorDireito;
	}
	
	//! Método que altera o valor da coordenada do ponto superior direito da Window.
	/*!
		/param p é o valor que a coordenada receberá.
	*/
	void setPontoSuperiorDireito(Coordenada* p) {
		superiorDireito = p;
	}
	
	//! Método que move a Window.
	/*!
		/param fatX é o valor que o eixo X da Window será somado.
		/param fatY é o valor que o eixo Y da Window será somado.
	*/
	void moverWindow(double fatX, double fatY) {
		inferiorEsquerdo->x += fatX;
		inferiorEsquerdo->y += fatY;
		superiorDireito->x += fatX;
		superiorDireito->y += fatY;
	}
	
	//! Método que dá zoom na Window.
	/*!
		/param fator é um double que indica o quanto de aproximação ou afastamento será feito.
	*/
	void zoom(double fator) {
		double min = 0;
		double quant = fator/2;
		inferiorEsquerdo->x += quant;
		inferiorEsquerdo->y += quant;
		superiorDireito->x -= quant;
		superiorDireito->y -= quant;
		
		if (inferiorEsquerdo->x > superiorDireito-> x) {
			double med = (inferiorEsquerdo->x + superiorDireito->x)/2;
			inferiorEsquerdo->x = med - min/2;
			superiorDireito->x = med + min/2;
		}
		
		if (inferiorEsquerdo->y > superiorDireito-> y) {
			double med = (inferiorEsquerdo->y + superiorDireito->y)/2;
			inferiorEsquerdo->y = med - min/2;
			superiorDireito->y = med + min/2;
		}
	}
};

#endif