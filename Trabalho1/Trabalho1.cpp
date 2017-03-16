#include <gtk/gtk.h>
#include <iostream>
#include <vector>
#include <math.h>

#include "Ponto.hpp"
#include "Reta.hpp"
#include "Poligono.hpp"
#include "Window.hpp"
#include "Coordenada.hpp"
#include "Desenhista.hpp"
#include "Viewport.hpp"
#include "Console.hpp"
#include "DisplayFile.hpp"

using namespace std;

// Objetos relacionados à interface
GtkWidget *window_Main; /*!< Referência para a janela principal.*/

GtkListBox *elmnt_List; /*!< Referência para a lista de elementos.*/
GtkWidget *elmnt_Btn_Novo, *elmnt_Btn_Del; /*!< Referência para os botões de novo e deletar elementos.*/

GtkWidget *pos_Txt_Fator; /*!< Referência para a caixa de texto de Fator da movimentação.*/
GtkWidget *pos_Btn_Cima, *pos_Btn_Baixo, *pos_Btn_Esq, *pos_Btn_Dir; /*!< Referência para os botões das quatro direções.*/

GtkWidget *zoom_Txt_Fator; /*!< Referência para a caixa de texto de Fator de zoom.*/
GtkWidget *zoom_Btn_Menos, *zoom_Btn_Mais; /*!< Referência para os botões de mais e menos zoom.*/

GtkTextView* consoleWidget; /*!< Referência para a caixa de texto do console.*/

GtkWidget *window_NovoElemento; /*!< Referência para a janela de novo elemento.*/

GtkEntry *textoNomeElemento; /*!< Referência para a caixa de texto de inserção de nome para um elemento.*/
GtkEntry *textoPontoX, *textoPontoY, *textoRetaInicialX, *textoRetaInicialY, 
		*textoRetaFinalX, *textoRetaFinalY, *textoPoligonoX, *textoPoligonoY; /*!< Referência para as caixas de texto que recebem valores de coordenadas.*/

GtkWidget *poligono_Btn_Add, *poligono_Btn_Del; /*!< Referência para os botões de adicionar e deletar coordenadas na criação de poligono.*/
GtkWidget *poligono_Listbox; /*!< Referência para a listbox coma s coordenadas do poligono.*/

GtkNotebook *notebook; /*!< Referência para o notebook na criação de elemento.*/

// Objetos relacionados ao sistema
Window *window; /*!< Objeto encarregado de administrar a Window*/
ListaEnc<Coordenada*> *listaCoordsPoligono; /*!< Uma lista de coordenadas para criar novos poligonos*/
DisplayFile* displayFile; /*!< Objeto encarregado de administrar a Display File*/
Desenhista* desenhista; /*!< Objeto encarregado de desenhar os objetos na viewport*/
Viewport* view; /*!< Objeto encarregado de administrar a Viewport*/
Console* console; /*!< Objeto encarregado de administrar o console*/


// !Método inicial
int main(int argc, char *argv[]){
		
	listaCoordsPoligono = new ListaEnc<Coordenada*>();
	
	// Window
	Coordenada* windowInfEsq = new Coordenada();
	windowInfEsq->x = 0;
	windowInfEsq->y = 0;
	Coordenada* windowSupDir = new Coordenada();
	windowSupDir->x = 200;
	windowSupDir->y = 200;
	window = new Window(windowInfEsq, windowSupDir);

	GtkBuilder  *gtkBuilder;
	gtk_init(&argc, &argv);

	gtkBuilder = gtk_builder_new();
	gtk_builder_add_from_file(gtkBuilder, "janela.glade", NULL);

	window_Main = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Window_Main"));
	
	elmnt_List = GTK_LIST_BOX(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Elmnt_List"));
	elmnt_Btn_Del = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Elmnt_Btn_Del"));
	// Esse botão começa desativado
	gtk_widget_set_sensitive (elmnt_Btn_Del, FALSE);
	
	pos_Txt_Fator = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Pos_Txt_Fator"));
	
	zoom_Txt_Fator = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Zoom_Txt_Fator"));

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
	poligono_Btn_Del = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Pol_Del"));
	// Esse botão começa desativado
	gtk_widget_set_sensitive (poligono_Btn_Del, FALSE);

	consoleWidget = GTK_TEXT_VIEW(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Console_Text"));
	
	displayFile = new DisplayFile(elmnt_List);
	desenhista = new Desenhista();
	view = new Viewport(gtkBuilder);
	console = new Console(consoleWidget);
	
	gtk_builder_connect_signals(gtkBuilder, NULL);
	gtk_widget_show_all(window_Main);
	gtk_main ();
	
	return 0;
}

//! Método que desenha os elementos na display file.	
static void update_Surface () {
	desenhista->clear_surface();
	Elemento<ElementoGrafico*> *elementoLista = displayFile->getHead();
	while (elementoLista != NULL) {
		// Desenha esse elemento
		desenhista->desenhaElemento(elementoLista->getInfo(), view, window, window_Main);
		elementoLista = elementoLista->getProximo();
	}
}

//! Método que adiciona a uma GtkListBox um novo elemento.
/*!
	/param listBox é a GtkListBox que queremos adicionar o elemento.
	/param nome é o texto a ser adicionado.
*/
void addToListBox(GtkWidget* listBox, string nome) {
	GtkWidget* row = gtk_list_box_row_new();
	GtkWidget* label = gtk_label_new(nome.c_str());
	gtk_container_add((GtkContainer*) listBox, label);
	gtk_widget_show_all(listBox);
}

//! Método que remove de uma GtkListBox a linha selecionada e retorna seu índice.
/*!
	/param list é a GtkListBox que queremos deletar o elemento selecionado.
	/return o valor do índice do elemento removido.
*/
int getIndexElementoDeletado(GtkWidget* list) {
	GtkListBoxRow* row = gtk_list_box_get_selected_row ((GtkListBox*) list);
	if (row != NULL) {
		int index = gtk_list_box_row_get_index(row);
		gtk_container_remove((GtkContainer*) list, (GtkWidget*) row);
		return index;
	}
	return 0;
}

//! Método que limpa a caixa de texto do nome da janela de novo objeto.
void limparTextoNomeNovoElmnt() {
	gtk_entry_set_text(textoNomeElemento, "");
}

//! Método que limpa as caixas de texto de ponto da janela de novo objeto.
void limparTextoNovoPonto() {
	limparTextoNomeNovoElmnt();
	gtk_entry_set_text(textoPontoX, "");
	gtk_entry_set_text(textoPontoY, "");
}

//! Método que limpa as caixas de texto de reta da janela de novo objeto.
void limparTextoNovaReta() {
	limparTextoNomeNovoElmnt();
	gtk_entry_set_text(textoRetaInicialX, "");
	gtk_entry_set_text(textoRetaInicialY, "");
	gtk_entry_set_text(textoRetaFinalX, "");
	gtk_entry_set_text(textoRetaFinalY, "");
}

//! Método que limpa as caixas de texto de polígono da janela de novo objeto.
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

//! Método que insere em uma lista as coordenadas do polígono a ser criado.
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
			console->inserirTexto("ERRO: coordenadas devem ser valores numéricos.");
			return "";
		}
		listaCoordsPoligono->adiciona(c);
		return "(" + polX + "," + polY + ")";
	} else {
		console->inserirTexto("ERRO: não é possível inserir coordenada sem valor X ou Y.");
	}
	return "";
}

#include "Callbacks.hpp"
