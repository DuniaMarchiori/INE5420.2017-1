#include <gtk/gtk.h>
#include "Viewport.hpp"

#ifndef DESENHISTA_HPP
#define DESENHISTA_HPP

static cairo_surface_t *surface = NULL;

class Desenhista {

private:
	//! Método que desenha um ponto na tela.
	/*!
		/param c é um objeto cairo_t utilizado para desenhar.
		/param elem é o elemento gráfico(o ponto) a ser desenhado.
		/param v é um objeto da classe Viewport.
		/param window é a Window do sistema.
	*/
	void desenhaPonto(cairo_t* c, ElementoGrafico *elem, Viewport* v, Window *window){
		Ponto* p = static_cast<Ponto*> (elem);
		Coordenada* transformada = v->transformaViewport(p->getCoordenada(), window);
		//Seria apenas um pixel, mas é feito um círculo ao redor do ponto para ficar visível.
		cairo_move_to(c, transformada->x, transformada->y);
		cairo_arc(c,transformada->x, transformada->y, 1.5, 0.0, 2*M_PI);
		cairo_fill(c);
	}

	//! Método que desenha uma reta na tela.
	/*!
		/param c é um objeto cairo_t utilizado para desenhar.
		/param elem é o elemento gráfico(a reta) a ser desenhado.
		/param v é um objeto da classe Viewport.
		/param window é a Window do sistema.
	*/
	void desenhaReta(cairo_t* c, ElementoGrafico *elem, Viewport* v, Window *window) {
		Reta* r = static_cast<Reta*> (elem);
		
		Coordenada* transformadaPInicial = v->transformaViewport(r->getPontoInicial(), window);
		Coordenada* transformadaPFinal = v->transformaViewport(r->getPontoFinal(), window);

		cairo_move_to(c, transformadaPInicial->x, transformadaPInicial->y);
		cairo_line_to(c, transformadaPFinal->x, transformadaPFinal->y);
	}

	//! Método que desenha um polígono na tela.
	/*!
		/param c é um objeto cairo_t utilizado para desenhar.
		/param elem é o elemento gráfico(o polígono) a ser desenhado.
		/param v é um objeto da classe Viewport.
		/param window é a Window do sistema.
	*/
	void desenhaPoligono(cairo_t* c, ElementoGrafico *elem, Viewport* v, Window *window) {
		Poligono* p = static_cast<Poligono*> (elem);
		ListaEnc<Coordenada*> *lista = p->getLista();
		Elemento<Coordenada*> *elementoCoord = lista->getHead();
		Coordenada* coord = elementoCoord->getInfo();
		
		Coordenada* transformada = v->transformaViewport(coord, window);

		cairo_move_to(c, transformada->x, transformada->y);
		elementoCoord = elementoCoord->getProximo();
		if (elementoCoord == NULL) {
			// Quando há só uma coordenada, desenha um ponto
			cairo_arc(c,transformada->x, transformada->y, 1.5, 0.0, 2*M_PI);
			cairo_fill(c);
		} else {
			while (elementoCoord != NULL) {
				coord = elementoCoord->getInfo();
				transformada = v->transformaViewport(coord, window);
				cairo_line_to(c, transformada->x, transformada->y);
				elementoCoord = elementoCoord->getProximo();
			}
		}
		cairo_close_path(c);
	}

public:
	/*Desenhista() {
		
	}*/

	//! Método que desenha na tela.
	/*!
		/param elem é o elemento gráfico(o ponto) a ser desenhado.
		/param v é um objeto da classe Viewport.
		/param window é a Window do sistema.
		/param window_Main é o widget da interface do sistema a ser desenhado.
	*/
	void desenhaElemento(ElementoGrafico *elem, Viewport* v, Window *window, GtkWidget *window_Main) {	
		cairo_t *cr;
		cr = cairo_create (surface);
		
		// Desenha o elemento de acordo com seu tipo
		switch (elem->getTipo()) {
			case PONTO:
				desenhaPonto(cr, elem, v, window);
				break;
				
			case RETA:
				desenhaReta(cr, elem, v, window);
				break;
				
			case POLIGONO:
				desenhaPoligono(cr, elem, v, window);
				break;
		}
		
		cairo_stroke(cr);
		gtk_widget_queue_draw (window_Main);
	}

	//! Método que limpa a tela(pintando-a de branco).
	static void clear_surface (){
	  cairo_t *cr;

	  cr = cairo_create (surface);

	  cairo_set_source_rgb (cr, 1, 1, 1);
	  cairo_paint (cr);

	  cairo_destroy (cr);
	}

	//! Método que altera a surface do cairo usada.
	/*!
		/param cr é um objeto cairo_t utilizado para desenhar.
	*/
	void modifica_surface(cairo_t *cr){
		cairo_set_source_surface (cr, surface, 0, 0);
		cairo_paint (cr);
	}

	//! Método que inicializa a surface do cairo usada.
	/*!
		/param widget é a window que será feita a nova "surface". 
	*/
	void nova_surface(GtkWidget *widget) {
		if (surface) {
			cairo_surface_destroy (surface);
		}

		surface = gdk_window_create_similar_surface (gtk_widget_get_window (widget),
													CAIRO_CONTENT_COLOR,
													gtk_widget_get_allocated_width (widget),
													gtk_widget_get_allocated_height (widget));
	}
};

#endif