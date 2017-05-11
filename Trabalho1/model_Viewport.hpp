#include "model_Coordenada.hpp"

#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP

class Viewport {

public:

	//! Método que faz a transformada de viewport.
	/*!
		/param ponto o ponto que sera transformado.
		/param vpMax o valor maximo da viewport que a transformação se baseia.
		/return a coordenada após a transformada.
	*/
	Coordenada* transformaViewport(Coordenada3D* ponto, Coordenada* vpMax) {
		Coordenada* c = new Coordenada(ponto->getX(), ponto->getY());
		
		int margem = 20;
		Coordenada* transformada = new Coordenada();
		Coordenada* wMin = new Coordenada((-1),(-1));
		Coordenada* wMax = new Coordenada(1,1);
		Coordenada* vpMin = new Coordenada(margem, margem);
		
		transformada->setX( ( ( (c->getX() - wMin->getX())/(wMax->getX() - wMin->getX()) ) * ((vpMax->getX() - margem) - vpMin->getX()) ) + vpMin->getX() );
		transformada->setY( ( ( 1 - ( (c->getY() - wMin->getY())/(wMax->getY() - wMin->getY()) ) ) * ((vpMax->getY() - margem) - vpMin->getY()) ) + vpMin->getY() );
		
		free(c);
		return transformada;
	}
};

#endif