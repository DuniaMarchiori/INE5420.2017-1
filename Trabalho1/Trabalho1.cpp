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

// Relacionados à interface
static cairo_surface_t *surface = NULL;
GtkWidget *window_Main;

GtkWidget *elmnt_List, *elmnt_Btn_Novo, *elmnt_Btn_Del;

GtkWidget *pos_Txt_Fator, *pos_Btn_Cima, *pos_Btn_Baixo, *pos_Btn_Esq, *pos_Btn_Dir;

GtkWidget *zoom_Txt_Fator, *zoom_Btn_Menos, *zoom_Btn_Mais;

GtkWidget *viewport_DrawingArea;
GtkWidget *window_NovoElemento;

GtkEntry *textoNomeElemento, *textoPontoX, *textoPontoY, *textoRetaInicialX, *textoRetaInicialY, 
		*textoRetaFinalX, *textoRetaFinalY, *textoPoligonoX, *textoPoligonoY;

GtkWidget *poligono_Btn_Add, *poligono_Btn_Del, *poligono_Listbox;

GtkNotebook *notebook;
GtkTextView* console;
GtkTextBuffer *buffer;

// Relacionados ao sistema
Window *window;
ListaEnc<ElementoGrafico*> *displayFile;
ListaEnc<Coordenada*> *listaCoordsPoligono;

//void addToListBox(GtkWidget* ListBox, string nome);
//Coordenada* getViewportMin ();
//Coordenada* getViewportMax ();

// Main de testes básicos
int main(int argc, char *argv[]){
	
	// Objetos para teste	
	/*Coordenada* c = new Coordenada();
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
	Reta* r2 = new Reta("reta2", c3, c4);*/
	//Reta* r3 = new Reta("reta3", getViewportMin(), getViewportMax());
	
	//Poligono* pol = new Poligono("poligono1");
	/*pol->adicionarCoordenada(c);
	pol->adicionarCoordenada(c2);
	pol->adicionarCoordenada(c3);
	pol->adicionarCoordenada(c4);*/
	
	// Display File
	displayFile = new ListaEnc<ElementoGrafico*>();
	
	//-------------------------------------------------------
	listaCoordsPoligono = new ListaEnc<Coordenada*>();

	// Window
	Coordenada* windowInfEsq = new Coordenada();
	windowInfEsq->x = 0;
	windowInfEsq->y = 0;
	
	Coordenada* windowSupDir = new Coordenada();
	windowSupDir->x = 200;
	windowSupDir->y = 200;
	
	window = new Window(windowInfEsq, windowSupDir);
	//

	GtkBuilder  *gtkBuilder;
	gtk_init(&argc, &argv);

	gtkBuilder = gtk_builder_new();
	gtk_builder_add_from_file(gtkBuilder, "janela.glade", NULL);

	window_Main = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Window_Main"));
	
	elmnt_List = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Elmnt_List"));
	
	pos_Txt_Fator = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Pos_Txt_Fator"));
	
	zoom_Txt_Fator = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Zoom_Txt_Fator"));
	
	viewport_DrawingArea = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Viewport_DrawingArea"));

	window_NovoElemento = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Window_NovoElmnt"));
	g_signal_connect (window_NovoElemento, "delete-event", G_CALLBACK (gtk_widget_hide_on_delete), NULL);
	
	textoNomeElemento = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Nome"));
	textoPontoX = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Ponto_X"));
	textoPontoY = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Ponto_Y"));
	textoRetaInicialX = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Reta_X1"));
	textoRetaInicialY = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Reta_Y1"));
	textoRetaFinalX = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Reta_X2"));
	textoRetaFinalY = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Reta_Y2"));
	textoPoligonoX = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Pol_X"));
	textoPoligonoY = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Pol_Y"));

	poligono_Listbox = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Listbox_Pol"));
	notebook = GTK_NOTEBOOK(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Notebook"));

	console = GTK_TEXT_VIEW(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Console_Text"));
	buffer = gtk_text_view_get_buffer (console);

	/*
	g_signal_connect (viewport_DrawingArea, "draw", G_CALLBACK (viewport_DrawingArea_draw_cb), NULL);
	g_signal_connect (viewport_DrawingArea,"configure-event", G_CALLBACK (viewport_DrawingArea_configure_event_cb), NULL);
	*/
	
	gtk_builder_connect_signals(gtkBuilder, NULL);
	gtk_widget_show_all(window_Main);
	gtk_main ();
	
	return 0;
}

void inserirTextoConsole(const gchar *texto) {
	//GtkTextMark *mark;
    //GtkTextIter iter;
    //mark = gtk_text_buffer_get_insert (buffer);
    //gtk_text_buffer_get_iter_at_mark (buffer, &iter, mark);
    //gtk_text_buffer_insert (buffer, &iter, texto, -1);

    // -1 indica que é para adicionar o texto todo
    gtk_text_buffer_insert_at_cursor (buffer, texto, -1);
}

Coordenada* transformaViewport(Coordenada* ponto, Window* wind, Coordenada* vpMin, Coordenada* vpMax) {
	Coordenada* transformada = new Coordenada();
	Coordenada* wMin = wind->getPontoInferiorEsquerdo();
	Coordenada* wMax = wind->getPontoSuperiorDireito();
	transformada->x = ( ( (ponto->x - wMin->x)/(wMax->x - wMin->x) ) * (vpMax->x - vpMin->x) );
	transformada->y = ( ( 1 - ( (ponto->y - wMin->y)/(wMax->y - wMin->y) ) ) * (vpMax->y - vpMin->y) );
	return transformada;
}

/*
double transformaViewportX(double xW, double xWMin, double xWMax, double xVPMax, double xVPMin) {
	return ( ( (xW - xWMin)/(xWMax - xWMin) ) * (xVPMax - xVPMin) );
}

double transformaViewportY(double yW, double yWMin, double yWMax, double yVPMax, double yVPMin) {
	return ( ( 1 - ( (yW - yWMin)/(yWMax - yWMin) ) ) * (yVPMax - yVPMin) );
}
*/

Coordenada* getViewportMin () {
	Coordenada* viewportMin = new Coordenada();;
	viewportMin->x = 0;
	viewportMin->y = 0;
	return viewportMin;
}

Coordenada* getViewportMax () {
	Coordenada* viewportMax = new Coordenada();

	viewportMax->x = gtk_widget_get_allocated_width(viewport_DrawingArea);
	viewportMax->y = gtk_widget_get_allocated_height(viewport_DrawingArea);

	return viewportMax;
}

void desenhaPonto(cairo_t* c, ElementoGrafico *elem){
	Ponto* p = static_cast<Ponto*> (elem);
	Coordenada* transformada = transformaViewport(p->getCoordenada(), window, getViewportMin(), getViewportMax());
	//Seria apenas um pixel, mas é feito um círculo ao redor do ponto para ficar visível.
	cairo_move_to(c, transformada->x, transformada->y);
	cairo_arc(c,transformada->x, transformada->y, 1.5, 0.0, 2*M_PI);
	cairo_fill(c);
}

void desenhaReta(cairo_t* c, ElementoGrafico *elem) {
	Reta* r = static_cast<Reta*> (elem);
	
	Coordenada* transformadaPInicial = transformaViewport(r->getPontoInicial(), window, getViewportMin(), getViewportMax());
	Coordenada* transformadaPFinal = transformaViewport(r->getPontoFinal(), window, getViewportMin(), getViewportMax());

	cairo_move_to(c, transformadaPInicial->x, transformadaPInicial->y);
	cairo_line_to(c, transformadaPFinal->x, transformadaPFinal->y);
}

void desenhaPoligono(cairo_t* c, ElementoGrafico *elem) {
	Poligono* p = static_cast<Poligono*> (elem);
	ListaEnc<Coordenada*> *lista = p->getLista();
	Elemento<Coordenada*> *elementoCoord = lista->getHead();
	Coordenada* coord = elementoCoord->getInfo();
	
	Coordenada* transformada = transformaViewport(coord, window, getViewportMin(), getViewportMax());

	cairo_move_to(c, transformada->x, transformada->y);
	elementoCoord = elementoCoord->getProximo();
	if (elementoCoord == NULL) {
		// Quando há só uma coordenada, desenha um ponto
		cairo_arc(c,transformada->x, transformada->y, 1.5, 0.0, 2*M_PI);
		cairo_fill(c);
	} else {
		while (elementoCoord != NULL) {
			coord = elementoCoord->getInfo();
			transformada = transformaViewport(coord, window, getViewportMin(), getViewportMax());
			cairo_line_to(c, transformada->x, transformada->y);
			elementoCoord = elementoCoord->getProximo();
		}
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

void addToListBox(GtkWidget* listBox, string nome) {
	GtkWidget* row = gtk_list_box_row_new();
	GtkWidget* label = gtk_label_new(nome.c_str());
	gtk_container_add((GtkContainer*) listBox, label);
	gtk_widget_show_all(listBox);
}

static void clear_surface (){
  cairo_t *cr;

  cr = cairo_create (surface);

  cairo_set_source_rgb (cr, 1, 1, 1);
  cairo_paint (cr);

  cairo_destroy (cr);
}

static void update_Surface () {
	clear_surface();
	Elemento<ElementoGrafico*> *elementoLista = displayFile->getHead();
	while (elementoLista != NULL) {
		// Desenha esse elemento
		desenhaElemento(elementoLista->getInfo());
		elementoLista = elementoLista->getProximo();
	}
}

// list é a listbox que queremos deletar o elemento
int getIndexElementoDeletado(GtkWidget* list) {
	GtkListBoxRow* row = gtk_list_box_get_selected_row ((GtkListBox*) list);
	if (row != NULL) {
		int index = gtk_list_box_row_get_index(row);
		gtk_container_remove((GtkContainer*) list, (GtkWidget*) row);
		return index;
	}
	return 0;
}

void limparTextoNomeNovoElmnt() {
	gtk_entry_set_text(textoNomeElemento, "");
}

void limparTextoNovoPonto() {
	limparTextoNomeNovoElmnt();
	gtk_entry_set_text(textoPontoX, "");
	gtk_entry_set_text(textoPontoY, "");
}

void limparTextoNovaReta() {
	limparTextoNomeNovoElmnt();
	gtk_entry_set_text(textoRetaInicialX, "");
	gtk_entry_set_text(textoRetaInicialY, "");
	gtk_entry_set_text(textoRetaFinalX, "");
	gtk_entry_set_text(textoRetaFinalY, "");
}

void limparTextoNovoPoligono() {
	limparTextoNomeNovoElmnt();
	gtk_entry_set_text(textoPoligonoX, "");
	gtk_entry_set_text(textoPoligonoY, "");
	// Limpa a listBox
	GtkListBoxRow* row = gtk_list_box_get_row_at_index ((GtkListBox*) poligono_Listbox, 0);
	while (row != NULL) {
		gtk_container_remove((GtkContainer*) poligono_Listbox, (GtkWidget*) row);
		row = gtk_list_box_get_row_at_index ((GtkListBox*) poligono_Listbox, 0);
	}
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
			inserirTextoConsole("ERRO: coordenadas devem ser valores numéricos.");
			return;
		}

		Ponto *p = new Ponto(nome, c);
		// Adiciona objeto na display file
		displayFile->adiciona(p);
		addToListBox(elmnt_List, nome);
		limparTextoNovoPonto();
	} else {
		inserirTextoConsole("ERRO: não é possível inserir ponto sem valor X ou Y.");
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
			inserirTextoConsole("ERRO: coordenadas devem ser valores numéricos.");
			return;
		}

		Reta *r = new Reta(nome, cI, cF);
		// Adiciona objeto na display file
		displayFile->adiciona(r);
		addToListBox(elmnt_List, nome);
		limparTextoNovaReta();
	} else {
		inserirTextoConsole("ERRO: não é possível inserir reta sem dois pares de coordenadas.");
	}
	
}

string inserirCoordListaEnc() {
	// Pega coordenadas
	string polX = gtk_entry_get_text(textoPoligonoX);
	string polY = gtk_entry_get_text(textoPoligonoY);

	/// Se os campos de coordenada não estão em branco
	if ( !(polX.empty()) && !(polY.empty()) ) {
		// Cria novo objeto
		Coordenada* c = new Coordenada();
		// Verifica se os campos são números
		try {
			// stod = string to double
			c->setX(stod(polX));
			c->setY(stod(polY));
		} catch (const invalid_argument& e) {
			inserirTextoConsole("ERRO: coordenadas devem ser valores numéricos.");
			return "";
		}
		listaCoordsPoligono->adiciona(c);
		return "(" + polX + "," + polY + ")";
	} else {
		inserirTextoConsole("ERRO: não é possível inserir coordenada sem valor X ou Y.");
	}
	return "";
}

void inserirNovoPoligono(string nome) {
	if ( !(listaCoordsPoligono->listaVazia()) ) {
		Poligono *pol = new Poligono(nome, listaCoordsPoligono);
		displayFile->adiciona(pol);
		addToListBox(elmnt_List, nome);
		listaCoordsPoligono = new ListaEnc<Coordenada*>();
		limparTextoNovoPoligono();
	} else {
		inserirTextoConsole("ERRO: não é possível inserir polígono sem coordenadas.");
	}
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
		inserirTextoConsole("ERRO: não é possível inserir elemento sem nome.");
	}
}

// método para uso em testes
void exibeDisplayFile() {
	Elemento<ElementoGrafico*> *elementoCoord = displayFile->getHead();

	if (elementoCoord != NULL) {
		ElementoGrafico* e = elementoCoord->getInfo();
		cout << "primeiro:" + e->getNome() << endl;

		elementoCoord = elementoCoord->getProximo();
		while (elementoCoord != NULL) {
			e = elementoCoord->getInfo();
			cout << e->getNome() << endl;
			elementoCoord = elementoCoord->getProximo();
		}
	} else {
		cout << "lista vazia" << endl;
	}
}

#include "Callbacks.hpp"
