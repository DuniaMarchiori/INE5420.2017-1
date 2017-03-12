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
	c->x = 5;
	c->setY(6);
	
	Coordenada* c2 = new Coordenada();
	c2->x = 7;
	c2->y = 8;
	
	
	Ponto* p = new Ponto(c);
	p->setNome("a");
	
	
	Reta* r = new Reta(c, c2);
	
	Poligono* pol = new Poligono();
	pol->adicionarCoordenada(c);
	
	// Display File
	displayFile = new ListaEnc<ElementoGrafico*>(); // Fiz baseado no Poligono.hpp, mas não teria que ser ListaEnc<ElementoGrafico*>() ?
	displayFile->adiciona(p);
	
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

static void update_Surface () {
	Elemento<ElementoGrafico> *elementoLista = displayFile->primeiroElemento();
	while (elementoLista != NULL) {
		// Desenha esse elemento
		
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
