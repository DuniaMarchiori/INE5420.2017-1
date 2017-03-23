#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "model_Coordenada.hpp"

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
		inferiorEsquerdo->setX(inferiorEsquerdo->getX() + fatX);
		inferiorEsquerdo->setY(inferiorEsquerdo->getY() + fatY);
		superiorDireito->setX(superiorDireito->getX() + fatX);
		superiorDireito->setY(superiorDireito->getY() + fatY);
	}
	
	//! Método que dá zoom na Window.
	/*!
		/param fator é um double que indica o quanto de aproximação ou afastamento será feito.
	*/
	void zoom(double fator) {
		double janelaMinima = 0;
		double quant = fator/2;
		
		inferiorEsquerdo->setX(inferiorEsquerdo->getX() + quant);
		inferiorEsquerdo->setY(inferiorEsquerdo->getY() + quant);
		superiorDireito->setX(superiorDireito->getX() - quant);
		superiorDireito->setY(superiorDireito->getY() - quant);
		
		if (inferiorEsquerdo->getX() > superiorDireito->getX()) {
			double med = (inferiorEsquerdo->getX() + superiorDireito->getX())/2;
			inferiorEsquerdo->setX(med - janelaMinima/2);
			superiorDireito->setX(med + janelaMinima/2);
		}
		
		if (inferiorEsquerdo->getY() > superiorDireito->getY()) {
			double med = (inferiorEsquerdo->getY() + superiorDireito->getY())/2;
			inferiorEsquerdo->setY(med - janelaMinima/2);
			superiorDireito->setY(med + janelaMinima/2);
		}
	}
};

#endif