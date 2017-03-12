#include <gtk/gtk.h>
#include <iostream>
#include <vector>

#include "Ponto.hpp"
#include "Reta.hpp"
#include "Poligono.hpp"
#include "Window.hpp"

#include "Coordenada.hpp"

using namespace std;

static cairo_surface_t *surface = NULL;
GtkWidget *window_Main;

GtkWidget *elmnt_List, *elmnt_Btn_Novo, *elmnt_Btn_Del;

GtkWidget *pos_Txt_Fator, *pos_Btn_Cima, *pos_Btn_Baixo, *pos_Btn_Esq, *pos_Btn_Dir;

GtkWidget *viewport_DrawingArea;
GtkWidget *window_NovoElemento;

ListaEnc<ElementoGrafico*> *displayFile;

// Main de testes básicos
int main(int argc, char *argv[]){
	
	// Objetos para teste
	Coordenada* windowInfEsq = new Coordenada();
	windowInfEsq->x = 0;
	windowInfEsq->y = 0;
	
	Coordenada* windowSupDir = new Coordenada();
	windowSupDir->x = 10;
	windowSupDir->y = 10;
	
	Coordenada* c = new Coordenada();
	c->x = 300;
	c->setY(100);
	
	Coordenada* c2 = new Coordenada();
	c2->x = 200;
	c2->y = 500;
	
	Coordenada* c3 = new Coordenada();
	c2->x = 400;
	c2->y = 200;
	
	Coordenada* c4 = new Coordenada();
	c2->x = 250;
	c2->y = 541.5;
	
	
	Ponto* p = new Ponto(c);
	p->setNome("a");
	
	
	Reta* r = new Reta(c, c2);
	
	Poligono* pol = new Poligono();
	pol->adicionarCoordenada(c);
	pol->adicionarCoordenada(c2);
	pol->adicionarCoordenada(c3);
	pol->adicionarCoordenada(c4);
	
	// Display File
	displayFile = new ListaEnc<ElementoGrafico*>();
	displayFile->adiciona(pol);
	
	// Window
	Window *window;
	window->setPontoInferiorEsquerdo(windowInfEsq);
	window->setPontoSuperiorDireito(windowSupDir);
	

	GtkBuilder  *gtkBuilder;
	gtk_init(&argc, &argv);

	gtkBuilder = gtk_builder_new();
	gtk_builder_add_from_file(gtkBuilder, "janela.glade", NULL);

	window_Main = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Window_Main"));
	window_NovoElemento = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Window_NovoElmnt"));
	viewport_DrawingArea = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Viewport_DrawingArea"));
	/*
	g_signal_connect (viewport_DrawingArea, "draw", G_CALLBACK (viewport_DrawingArea_draw_cb), NULL);
	g_signal_connect (viewport_DrawingArea,"configure-event", G_CALLBACK (viewport_DrawingArea_configure_event_cb), NULL);
	*/
	gtk_builder_connect_signals(gtkBuilder, NULL);
	gtk_widget_show(window_Main);
	gtk_main ();
	
	return 0;
}

void desenhaElemento(ElementoGrafico *elem) {	
	cairo_t *cr;
	cr = cairo_create (surface);
	
	// Desenha o elemento de acordo com seu tipo
	switch (elem->getTipo()) {
		case PONTO:
			// FAZER
			break;
			
		case RETA:
			{
				Reta* r = static_cast<Reta*> (elem);

				cairo_move_to(cr, r->getPontoInicial()->x, r->getPontoInicial()->y);
				cairo_line_to(cr, r->getPontoFinal()->x, r->getPontoFinal()->y);
				break;
			}
			
		case POLIGONO:
			{
				Poligono* p = static_cast<Poligono*> (elem);
				ListaEnc<Coordenada*> *lista = p->getLista();
				Elemento<Coordenada*> *elementoCoord = lista->getHead();
				Coordenada* coord = elementoCoord->getInfo();

				cairo_move_to(cr, coord->x, coord->y);
				elementoCoord = elementoCoord->getProximo();
				while (elementoCoord != NULL) {
					coord = elementoCoord->getInfo();
					cairo_line_to(cr, coord->x, coord->y);
					elementoCoord = elementoCoord->getProximo();
				}
				cairo_close_path(cr);
				break;
			}
	}
	
	cairo_stroke(cr);
	gtk_widget_queue_draw (window_Main);
}

static void update_Surface () {
	Elemento<ElementoGrafico*> *elementoLista = displayFile->getHead();
	while (elementoLista != NULL) {
		// Desenha esse elemento
		desenhaElemento(elementoLista->getInfo());
		elementoLista = elementoLista->getProximo();
	}	
}

static void clear_surface (){
  cairo_t *cr;

  cr = cairo_create (surface);

  cairo_set_source_rgb (cr, 1, 1, 1);
  cairo_paint (cr);

  cairo_destroy (cr);
}

#include "Callbacks.hpp"
