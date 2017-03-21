#include <math.h>
#include "../model/Coordenada.hpp"
#include "../model/Ponto.hpp"
#include "../model/Reta.hpp"
#include "../model/Poligono.hpp"
#include "../model/Fachada.hpp"

#include <iostream>
using namespace std;

#ifndef DESENHISTA_HPP
#define DESENHISTA_HPP

static cairo_surface_t *surface = NULL;

class Desenhista {

public:
	//! Método que desenha um ponto na tela.
	/*!
		/param c é um objeto cairo_t utilizado para desenhar.
		/param elem é o elemento gráfico(o ponto) a ser desenhado.
		/param v é um objeto da classe Viewport.
		/param window é a Window do sistema.
	*/
	void desenhaPonto(Ponto* p){
		cairo_t *c = cairo_create (surface);

		//Seria apenas um pixel, mas é feito um círculo ao redor do ponto para ficar visível.
		cairo_move_to(c, p->getCoordenada()->getX(), p->getCoordenada()->getY());
		cairo_arc(c,p->getCoordenada()->getX(), p->getCoordenada()->getY(), 1.5, 0.0, 2*M_PI);
		cairo_fill(c);

		cairo_stroke(c);
		//gtk_widget_queue_draw (window_Main);
	}

	//! Método que desenha uma reta na tela.
	/*!
		/param c é um objeto cairo_t utilizado para desenhar.
		/param elem é o elemento gráfico(a reta) a ser desenhado.
		/param v é um objeto da classe Viewport.
		/param window é a Window do sistema.
	*/
	void desenhaReta(Reta* r) {
		cairo_t *c = cairo_create (surface);

		cairo_move_to(c, r->getPontoInicial()->getX(), r->getPontoInicial()->getY());
		cairo_line_to(c, r->getPontoFinal()->getX(), r->getPontoFinal()->getY());

		cairo_stroke(c);
		//gtk_widget_queue_draw (window_Main);
	}

	//! Método que desenha um polígono na tela.
	/*!
		/param c é um objeto cairo_t utilizado para desenhar.
		/param elem é o elemento gráfico(o polígono) a ser desenhado.
		/param v é um objeto da classe Viewport.
	*/
	void desenhaPoligono(Poligono* p) {
		cairo_t *c = cairo_create (surface);

		ListaEnc<Coordenada*> *lista = p->getLista();
		Elemento<Coordenada*> *elementoCoord = lista->getHead();
		Coordenada* coord = elementoCoord->getInfo();	
		//Coordenada* transformada = f->transformaViewport(coord,vpMax);

		cairo_move_to(c, coord->getX(), coord->getY());
		elementoCoord = elementoCoord->getProximo();
		if (elementoCoord == NULL) {
			// Quando há só uma coordenada, desenha um ponto
			cairo_arc(c,coord->getX(), coord->getY(), 1.5, 0.0, 2*M_PI);
			cairo_fill(c);
		} else {
			while (elementoCoord != NULL) {
				coord = elementoCoord->getInfo();
				//transformada = f->transformaViewport(coord, vpMax);
				cairo_line_to(c, coord->getX(), coord->getY());
				elementoCoord = elementoCoord->getProximo();
			}
		}
		cairo_close_path(c);

		cairo_stroke(c);
		//gtk_widget_queue_draw (window_Main);
	}

	/*Desenhista() {
		
	}*/

	//! Método que desenha na tela.
	/*!
		/param elem é o elemento gráfico(o ponto) a ser desenhado.
		/param v é um objeto da classe Viewport.
		/param window é a Window do sistema.
		/param window_Main é o widget da interface do sistema a ser desenhado.
	*/
	/*void desenhaElemento(ElementoGrafico *elem, Fachada* f, Coordenada* vpMax, GtkWidget *window_Main) {	
		cairo_t *cr;
		cr = cairo_create (surface);
		
		// Desenha o elemento de acordo com seu tipo
		switch (elem->getTipo()) {
			case PONTO:
				desenhaPonto(cr, elem, f, vpMax);
				break;
				
			case RETA:
				desenhaReta(cr, elem, f, vpMax);
				break;
				
			case POLIGONO:
				desenhaPoligono(cr, elem, f, vpMax);
				break;
		}
		
		cairo_stroke(cr);
		gtk_widget_queue_draw (window_Main);
	}*/

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