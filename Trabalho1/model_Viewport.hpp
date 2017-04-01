#include "model_Coordenada.hpp"

#include <iostream>
using namespace std;

#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP

class Viewport {

public: 
	
	//! Método que faz a transformada de viewport.
	/*!
		/param ponto o ponto que sera transformado.
		/param wind a janela na qual a transformação se baseia.
		/param vpMax o valor maximo da viewport que a transformação se baseia.
		/return a coordenada após a transformada.
	*/
	Coordenada* transformaViewport(Coordenada* ponto, Window* wind, Coordenada* vpMax) {
		Coordenada* transformada = new Coordenada();
		Coordenada* wMin = new Coordenada(-1,-1);
		Coordenada* wMax = new Coordenada(1,1);
		vpMax->setX(vpMax->getX() - 10);
		vpMax->setY(vpMax->getY() - 10);
		
		vpMin = new Coordenada(10, 10);
		transformada->setX ( ( (ponto->getX() - wMin->getX())/(wMax->getX() - wMin->getX()) ) * (vpMax->getX() - vpMin->getX()) );
		transformada->setY ( ( 1 - ( (ponto->getY() - wMin->getY())/(wMax->getY() - wMin->getY()) ) ) * (vpMax->getY() - vpMin->getY()) );
		return transformada;
	}
};

#endif