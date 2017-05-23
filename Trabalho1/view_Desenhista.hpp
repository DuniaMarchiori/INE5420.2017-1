#include <math.h>
#include "model_Coordenada.hpp"
#include "model_Ponto.hpp"
#include "model_Reta.hpp"
#include "model_Poligono.hpp"

using namespace std;

#ifndef DESENHISTA_HPP
#define DESENHISTA_HPP

static cairo_surface_t *surface = NULL;

class Desenhista {

public:
	//! Método que desenha um ponto na tela.
	/*!
		/param coord é a coordenada do ponto a ser desenhado.
	*/
	void desenhaPonto(Coordenada* coord){
		cairo_t *c = cairo_create (surface);

		//Seria apenas um pixel, mas é feito um círculo ao redor do ponto para ficar visível.
		cairo_move_to(c, coord->getX(), coord->getY());
		cairo_arc(c,coord->getX(), coord->getY(), 1.0, 0.0, 2*M_PI);
		cairo_fill(c);

		cairo_stroke(c);
	}

	//! Método que desenha uma reta na tela.
	/*!
		/param coordInicial é a coordenada inicial da reta.
		/param coordFinal é a coordenada final da reta.
	*/
	void desenhaReta(Coordenada* coordInicial, Coordenada* coordFinal) {
		if ((fabs( coordInicial->getX()-coordFinal->getX() ) < 10e-9) && (fabs( coordInicial->getY()-coordFinal->getY() ) < 10e-9)) {
			desenhaPonto(coordInicial);
		} else {
			cairo_t *c = cairo_create (surface);
			cairo_set_line_width(c, 0.5);

			cairo_move_to(c, coordInicial->getX(), coordInicial->getY());
			cairo_line_to(c, coordFinal->getX(), coordFinal->getY());

			cairo_stroke(c);
		}
	}

	//! Método que desenha um polígono na tela.
	/*!
		/param lista é a lista de coordenadas do poligono a ser desenhado.
		/param preenchido é um valor booleado que diz se este poligono deve ser preenchido ou não.
	*/
	void desenhaPoligono(ListaEnc<Coordenada*>* lista, bool preenchido) {
		cairo_t *c = cairo_create (surface);
		cairo_set_line_width(c, 0.5);

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
		if (preenchido) {
			cairo_fill(c);
		}

		cairo_stroke(c);
	}

	//! Método que desenha uma curva na tela.
	/*!
		/param lista é a lista de retas da curva a ser desenhada.
	*/
	void desenhaCurva(ListaEnc<Reta*>* lista) {
		Elemento<Reta*> *elementoLista = lista->getHead();
		while (elementoLista != NULL) {
			Reta* reta = elementoLista->getInfo();
			desenhaReta(reta->getCoordenadaNormalInicial(), reta->getCoordenadaNormalFinal());
			
			elementoLista = elementoLista->getProximo();
		}
	}
	/*
	void desenhaCurva(ListaEnc<Coordenada*>* lista) {
		cairo_t *c = cairo_create (surface);

		Elemento<Coordenada*> *elementoCoord = lista->getHead();
		Coordenada* coord = elementoCoord->getInfo();

		cairo_move_to(c, coord->getX(), coord->getY());
		elementoCoord = elementoCoord->getProximo();

		while (elementoCoord != NULL) {
			coord = elementoCoord->getInfo();
			cairo_line_to(c, coord->getX(), coord->getY());
			elementoCoord = elementoCoord->getProximo();
		}

		cairo_stroke(c);
	}
	*/

	//! Método que limpa a tela(pintando-a de branco).
	static void clear_surface (){
	  cairo_t *cr;

	  cr = cairo_create (surface);

	  cairo_set_source_rgb (cr, 1, 1, 1);
	  cairo_paint (cr);

	  cairo_destroy (cr);
	}

	//! Desenha a margem para a observação do clipping.
	void desenhaMargem(Coordenada* coord) {
		// Diferença entre a window e o máximo da viewport é 20 pixels.
		int margem = 20;
		cairo_t *c = cairo_create (surface);
		cairo_set_source_rgb (c, 1, 0, 0); // linha vermelha

		cairo_move_to(c, margem, margem);
		cairo_line_to(c, (coord->getX() - margem) , margem);
		cairo_line_to(c, (coord->getX() - margem), (coord->getY() - margem));
		cairo_line_to(c, margem, (coord->getY() - margem));
		cairo_close_path(c);

		cairo_stroke(c);
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