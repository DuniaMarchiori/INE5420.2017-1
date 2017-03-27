#include <math.h>

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "model_Coordenada.hpp"

class Window {

private:
	Coordenada *centro; /*!< A coordenada que indica a posição da window.*/
	Coordenada *viewUpVector; /*!< O vetor que aponta para onde esta rotacionada a window.*/
	double altura, largura; /*!< Altura e Largura da window.*/

public:
	//! Construtor
	/*!
		/param posInicial é a cooordenada inicial da window.
	*/
	Window(Coordenada* posInicial, double alt, double larg) {
		centro = posInicial;
		viewUpVector = new Coordenada(0, 1);
		altura = alt;
		largura = larg;
	}

	//! Método que retorna a posição da Window.
	/*!
		/return a coordenada da posição da window.
	*/
	Coordenada* getCentro() {
		return centro;
	}

	//! Método que altera a coordenada da posição da Window.
	/*!
		/param p é a coordenada que a posição receberá.
	*/
	void setCentro(Coordenada* p) {
		centro = p;
	}

	//! Método que retorna a altura da window.
	/*!
		/return altura da window.
	*/
	double getAltura() {
		return altura;
	}

	//! Método que altera a altura da Window.
	/*!
		/param h é nova altura da window.
	*/
	void setAltura(double h) {
		altura = h;
	}

	//! Método que retorna a largura da window.
	/*!
		/return largura da window.
	*/
	double getLargura() {
		return largura;
	}

	//! Método que altera a largura da Window.
	/*!
		/param w é nova largura da window.
	*/
	void setLargura(double w) {
		largura = w;
	}

	//! Método que move a Window.
	/*!
		/param fatX é o quanto a window ira se mover no eixo X.
		/param fatY é o quanto a window ira se mover no eixo Y.
	*/
	void moverWindow(double fatX, double fatY) {
		double angulo = getAngulo() * M_PI/180.0;
		centro->setX(centro->getX() + fatX * cos(angulo) - fatY * sin(angulo));
		centro->setY(centro->getY() + fatX * sin(angulo) + fatY * cos(angulo));



		//centro->setX(centro->getX() + viewUpVector->getX() * fatX);
		//centro->setY(centro->getY() + viewUpVector->getY() * fatY);
	}

	//! Método que dá zoom na Window.
	/*!
		/param fator é um double que indica o quanto de aproximação ou afastamento será feito.
	*/
	void zoom(double fator) {
		altura -= altura * (fator/100.0);
		largura -= largura * (fator/100.0);
	}

	//! Método que rotaciona a Window.
	/*!
		/param graus é o quanto a window sera rotacionada em graus.
	*/
	void rotacionarWindow(double graus) {
		Coordenada *novoVetor = new Coordenada();
		double radianos = graus * M_PI/180.0;

		double cosseno = cos(radianos);
		double seno = sin(radianos);

		novoVetor->setX(viewUpVector->getX() * cosseno - viewUpVector->getY() * seno);
		novoVetor->setY(viewUpVector->getX() * seno + viewUpVector->getY() * cosseno);

		free(viewUpVector);
		viewUpVector = novoVetor;
	}

	//! Método que diz o angulo em que a Window se encontra.
	/*!
		/return o angulo entre a window e o eixo Y.
	*/
	double getAngulo() {
		double angulo = atan2(viewUpVector->getY(), viewUpVector->getX()) - atan2(1, 0);
		angulo = (angulo * 180.0) / M_PI;
		return angulo;
	}

};

#endif