#include <gtk/gtk.h>
#include <iostream>
#include <vector>
#include <math.h>

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

GtkEntry *textoNomeElemento, *textoPontoX, *textoPontoY, *textoRetaInicialX, *textoRetaInicialY, 
		*textoRetaFinalX, *textoRetaFinalY, *textoPoligonoX, *textoPoligonoY;

GtkWidget *poligono_Btn_Add, *poligono_Btn_Del, *poligono_Listbox;

GtkNotebook *notebook;

ListaEnc<ElementoGrafico*> *displayFile;

void addToListBox(GtkWidget* ListBox, string nome);
//Coordenada* getViewportMin ();
//Coordenada* getViewportMax ();

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
	c->x = 10;
	c->setY(10);
	
	Coordenada* c2 = new Coordenada();
	c2->x = 20;
	c2->y = 30;
	
	Coordenada* c3 = new Coordenada();
	c3->x = 40;
	c3->y = 20;
	
	Coordenada* c4 = new Coordenada();
	c4->x = 25;
	c4->y = 54;
	
	
	Ponto* p = new Ponto("ponto1", c);
		
	Reta* r = new Reta("reta1", c, c2);
	Reta* r2 = new Reta("reta2", c3, c4);
	//Reta* r3 = new Reta("reta3", getViewportMin(), getViewportMax());
	
	Poligono* pol = new Poligono("poligono1");
	pol->adicionarCoordenada(c);
	pol->adicionarCoordenada(c2);
	pol->adicionarCoordenada(c3);
	pol->adicionarCoordenada(c4);
	
	// Display File
	displayFile = new ListaEnc<ElementoGrafico*>();
	displayFile->adiciona(p);
	displayFile->adiciona(r2);
	//displayFile->adiciona(r3);
	
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
	
	elmnt_List = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Elmnt_List"));
		
	textoNomeElemento = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Nome"));
	textoPontoX = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Ponto_X"));
	textoPontoY = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Ponto_Y"));
	textoRetaInicialX = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Reta_X1"));
	textoRetaInicialY = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Reta_Y1"));
	textoRetaFinalX = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Reta_X2"));
	textoRetaFinalY = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Reta_Y2"));
	textoPoligonoX = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Pol_X"));
	textoPoligonoX = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Pol_Y"));

	/*
	NovoElmnt_Pol_Add
	NovoElmnt_Pol_Del
	NovoElmnt_Listbox_Pol
	*/

	notebook = GTK_NOTEBOOK(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Notebook"));
	/*
	g_signal_connect (viewport_DrawingArea, "draw", G_CALLBACK (viewport_DrawingArea_draw_cb), NULL);
	g_signal_connect (viewport_DrawingArea,"configure-event", G_CALLBACK (viewport_DrawingArea_configure_event_cb), NULL);
	*/
	
	
	addToListBox(elmnt_List, "Reta_0");
	addToListBox(elmnt_List, "Reta_1");
	
	gtk_builder_connect_signals(gtkBuilder, NULL);
	gtk_widget_show_all(window_Main);
	gtk_main ();
	
	return 0;
}

double transformaViewportX(double xW, double xWMin, double xWMax, double xVPMax, double xVPMin) {
	return ( ( (xW - xWMin)/(xWMax - xWMin) ) * (xVPMax - xVPMin) );
}

double transformaViewportY(double yW, double yWMin, double yWMax, double yVPMax, double yVPMin) {
	return ( ( 1 - ( (yW - yWMin)/(yWMax - yWMin) ) ) * (yVPMax - yVPMin) );
}

void desenhaPonto(cairo_t* c, ElementoGrafico *elem){
	Ponto* p = static_cast<Ponto*> (elem);
	//Seria apenas um pixel, mas é feito um círculo ao redor do ponto para ficar visível.
	cairo_move_to(c, p->getCoordenada()->x, p->getCoordenada()->y);
	cairo_arc(c,p->getCoordenada()->x, p->getCoordenada()->y, 1.5, 0.0, 2*M_PI);
	cairo_fill(c);
}

void desenhaReta(cairo_t* c, ElementoGrafico *elem) {
	Reta* r = static_cast<Reta*> (elem);

	cairo_move_to(c, r->getPontoInicial()->x, r->getPontoInicial()->y);
	cairo_line_to(c, r->getPontoFinal()->x, r->getPontoFinal()->y);
}

void desenhaPoligono(cairo_t* c, ElementoGrafico *elem) {
	Poligono* p = static_cast<Poligono*> (elem);
	ListaEnc<Coordenada*> *lista = p->getLista();
	Elemento<Coordenada*> *elementoCoord = lista->getHead();
	Coordenada* coord = elementoCoord->getInfo();

	cairo_move_to(c, coord->x, coord->y);
	elementoCoord = elementoCoord->getProximo();
	while (elementoCoord != NULL) {
		coord = elementoCoord->getInfo();
		cairo_line_to(c, coord->x, coord->y);
		elementoCoord = elementoCoord->getProximo();
	}
	cairo_close_path(c);
}

void desenhaElemento(ElementoGrafico *elem) {	
	cairo_t *cr;
	cr = cairo_create (surface);
	
	// Desenha o elemento de acordo com seu tipo
	switch (elem->getTipo()) {
		case PONTO:
			desenhaPonto(cr, elem);
			break;
			
		case RETA:
			desenhaReta(cr, elem);
			break;
			
		case POLIGONO:
			desenhaPoligono(cr, elem);
			break;
	}
	
	cairo_stroke(cr);
	gtk_widget_queue_draw (window_Main);
}

void addToListBox(GtkWidget* ListBox, string nome) {
	GtkWidget* row = gtk_list_box_row_new();
	GtkWidget* label = gtk_label_new(nome.c_str());
	gtk_container_add((GtkContainer*) ListBox, label);
}

static void update_Surface () {
	Elemento<ElementoGrafico*> *elementoLista = displayFile->getHead();
	while (elementoLista != NULL) {
		// Desenha esse elemento
		desenhaElemento(elementoLista->getInfo());
		elementoLista = elementoLista->getProximo();
	}	
}

Coordenada* getViewportMin () {
	Coordenada* viewportMin;
	viewportMin->x = 0;
	viewportMin->y = 0;
	return viewportMin;
}

Coordenada* getViewportMax () {
	Coordenada* viewportMax;
	
	viewportMax->x = 10; // Aqui teriamos que pegar o width da viewport
	viewportMax->y = 10; // Aqui teriamos que pegar o height da viewport
	
	return viewportMax;
}

static void clear_surface (){
  cairo_t *cr;

  cr = cairo_create (surface);

  cairo_set_source_rgb (cr, 1, 1, 1);
  cairo_paint (cr);

  cairo_destroy (cr);
}

void inserirNovoPonto(string nome) {
	// Pega coordenadas
	string coordX = gtk_entry_get_text(textoPontoX);
	string coordY = gtk_entry_get_text(textoPontoY);

	/// Se os campos de coordenada não estão em branco
	if ( !(coordX.empty()) && !(coordY.empty()) ) {
		// Cria novo objeto
		Coordenada* c = new Coordenada();
		// Verifica se os campos são números
		try {
			// stod = string to double
			c->setX(stod(coordX));
			c->setY(stod(coordY));
		} catch (const invalid_argument& e) {
			// Mensagem de erro
			cout << "catch de texto no campo numérico" << endl;
			return;
		}

		Ponto *p = new Ponto(nome, c);
		// Adiciona objeto na display file
		displayFile->adiciona(p);
	} else {
		//mensagem de ERRO
	}
}

void inserirNovaReta(string nome) {
	// Pega coordenadas
	string coordIniX = gtk_entry_get_text(textoRetaInicialX);
	string coordIniY = gtk_entry_get_text(textoRetaInicialY);
	string coordFinX = gtk_entry_get_text(textoRetaFinalX);
	string coordFinY = gtk_entry_get_text(textoRetaFinalY);

	/// Se os campos de coordenada não estão em branco
	if ( !(coordIniX.empty()) && !(coordIniY.empty()) && !(coordFinX.empty()) && !(coordFinY.empty()) ) { 
		// Cria novo objeto
		Coordenada* cI = new Coordenada();
		Coordenada* cF = new Coordenada();

		// Verifica se os campos são números
		try {
			// stod = string to double
			cI->setX(stod(coordIniX));
			cI->setY(stod(coordIniY));

			cF->setX(stod(coordFinX));
			cF->setY(stod(coordFinY));
		} catch (const invalid_argument& e) {
			// Mensagem de erro
			cout << "catch de texto no campo numérico" << endl;
			return;
		}

		Reta *r = new Reta(nome, cI, cF);
		// Adiciona objeto na display file
		displayFile->adiciona(r);
	} else {
		//mensagem de erro
	}
	
}

void inserirNovoPoligono(string nome) {
	
}

void inserirNovoElemento() {

	// Pega o nome do elemento
	string nome = gtk_entry_get_text(textoNomeElemento);

	// Se o campo de nome não está em branco
	if ( !(nome.empty()) ) {	
		// Verifica que tipo de figura está sendo inserida (as páginas do notebook são as abas da janela de novo elemento)
		switch (gtk_notebook_get_current_page(notebook)) {
			case 0:
				// A page 0 corresponde à aba de Ponto
				inserirNovoPonto(nome);
				break;
			case 1:
				// A page 1 corresponde à aba de Reta
				inserirNovaReta(nome);
				break;
			case 2:
				// A page 2 corresponde à aba de Polígono
				inserirNovoPoligono(nome);
				break;
		}
	} else {
		//mensagem de erro
	}
}

#include "Callbacks.hpp"
