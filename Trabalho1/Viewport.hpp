#include <gtk/gtk.h>
#include "Coordenada.hpp"

#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP

class Viewport {

private:
	Coordenada *viewportMin, *viewportMax; 
	GtkWidget *viewport_DrawingArea;

public: 
	Viewport(GtkBuilder *gtkBuilder) {
		viewport_DrawingArea = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Viewport_DrawingArea"));
		Coordenada* viewportMin = new Coordenada();
		Coordenada* viewportMax = new Coordenada();
		viewportMin->x = 0;
		viewportMin->y = 0;
	}

	Coordenada* getViewportMin () {
		return viewportMin;
	}

	Coordenada* getViewportMax () {
		viewportMax->x = gtk_widget_get_allocated_width(viewport_DrawingArea);
		viewportMax->y = gtk_widget_get_allocated_height(viewport_DrawingArea);
		return viewportMax;
	}

	Coordenada* transformaViewport(Coordenada* ponto, Window* wind) {
		Coordenada* transformada = new Coordenada();
		Coordenada* wMin = wind->getPontoInferiorEsquerdo();
		Coordenada* wMax = wind->getPontoSuperiorDireito();
		transformada->x = ( ( (ponto->x - wMin->x)/(wMax->x - wMin->x) ) * (getViewportMax()->x - getViewportMin()->x) );
		transformada->y = ( ( 1 - ( (ponto->y - wMin->y)/(wMax->y - wMin->y) ) ) * (getViewportMax()->y - getViewportMin()->y) );
		return transformada;
	}
};

#endif