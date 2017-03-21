#include "Coordenada.hpp"

#include <iostream>
using namespace std;

#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP

class Viewport {

private:
	//Coordenada *viewportMin, *viewportMax; /*!< Coordenadas que indicam os pontos mínimo e máximo do viewport, respectivamente.*/
	//GtkWidget *viewport_DrawingArea; /*!< A área de desenho*/

public: 
	//! Construtor
	//Viewport() {
		//viewport_DrawingArea = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Viewport_DrawingArea"));
	//	Coordenada* viewportMin = new Coordenada(0, 0);
	//	Coordenada* viewportMax = new Coordenada();
	//}

	//! Método que retorna o valor do ponto mínimo do viewport.
	/*!
		/return a coordenada do ponto mínimo.
	*/
	//Coordenada* getViewportMin () {
	//	return viewportMin;
	//}

	//! Método que retorna o valor do ponto máximo do viewport.
	/*!
		/return a coordenada do ponto máximo.
	*/
	/*Coordenada* getViewportMax () {
		viewportMax->x = gtk_widget_get_allocated_width(viewport_DrawingArea);
		viewportMax->y = gtk_widget_get_allocated_height(viewport_DrawingArea);
		return viewportMax;
	}*/

	//! Método que faz a transformada de viewport.
	/*!
		/return a coordenada após a transformada.
	*/
	Coordenada* transformaViewport(Coordenada* ponto, Window* wind, Coordenada* vpMax) {
		Coordenada* transformada = new Coordenada();
		Coordenada* wMin = wind->getPontoInferiorEsquerdo();
		Coordenada* wMax = wind->getPontoSuperiorDireito();
		transformada->setX ( ( (ponto->getX() - wMin->getX())/(wMax->getX() - wMin->getX()) ) * (vpMax->getX()) );
		transformada->setY ( ( 1 - ( (ponto->getY() - wMin->getY())/(wMax->getY() - wMin->getY()) ) ) * (vpMax->getY()) );
		return transformada;
	}
};

#endif