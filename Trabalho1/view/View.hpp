#include <gtk/gtk.h>
#include <string>
#include <stdexcept>
#include <iostream>
#include "Console.hpp"
#include "Desenhista.hpp"

#ifndef VIEW_HPP
#define VIEW_HPP

using namespace std;
using std::string;
using std::stod;
using std::invalid_argument;
using std::to_string;

class View {

private:
	Console* console;
	Desenhista* desenhista;
	ListaEnc<Coordenada*> *listaCoordsPoligono; /*!< Uma lista de coordenadas para criar novos poligonos*/

	// Objetos relacionados à interface
	GtkWidget *window_Main; /*!< Referência para a janela principal.*/

	GtkListBox *elmnt_List; /*!< Referência para a lista de elementos.*/
	GtkButton *elmnt_Btn_Novo, *elmnt_Btn_Del; /*!< Referência para os botões de novo e deletar elementos.*/

	GtkEntry *pos_Txt_Fator; /*!< Referência para a caixa de texto de Fator da movimentação.*/
	GtkButton *pos_Btn_Cima, *pos_Btn_Baixo, *pos_Btn_Esq, *pos_Btn_Dir; /*!< Referência para os botões das quatro direções.*/

	GtkEntry *zoom_Txt_Fator; /*!< Referência para a caixa de texto de Fator de zoom.*/
	GtkButton *zoom_Btn_Menos, *zoom_Btn_Mais; /*!< Referência para os botões de mais e menos zoom.*/

	GtkTextView *consoleWidget; /*!< Referência para a caixa de texto do console.*/
	GtkWidget *viewport_DrawingArea; /*!< A área de desenho*/

	GtkWindow *window_NovoElemento; /*!< Referência para a janela de novo elemento.*/
	
	GtkEntry *textoNomeElemento; /*!< Referência para a caixa de texto de inserção de nome para um elemento.*/
	GtkEntry *textoPontoX, *textoPontoY, *textoRetaInicialX, *textoRetaInicialY, 
			*textoRetaFinalX, *textoRetaFinalY, *textoPoligonoX, *textoPoligonoY; /*!< Referência para as caixas de texto que recebem valores de coordenadas.*/

	GtkButton *poligono_Btn_Add, *poligono_Btn_Del; /*!< Referência para os botões de adicionar e deletar coordenadas na criação de poligono.*/
	GtkListBox *poligono_Listbox; /*!< Referência para a listbox coma s coordenadas do poligono.*/

	GtkNotebook *notebook; /*!< Referência para o notebook na criação de elemento.*/
	
	// Metodos privados que adicionei
	
	double getFator(GtkEntry* area) {
		double fator = 0;
		
		try {
			fator = stod(gtk_entry_get_text(area));
		} catch (const invalid_argument& e) {
			throw -1;
		}
		
		if (fator != 0) {
			return fator;
		} else {
			throw -2;
		}
	}
	
public:

	void inicializarComponentes(int argc, char *argv[]) {
		GtkBuilder  *gtkBuilder;
		gtk_init(&argc, &argv);

		//gtkBuilder = gtk_builder_new();
		//gtk_builder_add_from_file(gtkBuilder, "janela.glade", NULL);
		gtkBuilder = gtk_builder_new_from_file("janela.glade");
		
		window_Main = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Window_Main"));
		
		viewport_DrawingArea = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Viewport_DrawingArea"));
		
		elmnt_List = GTK_LIST_BOX(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Elmnt_List"));
		elmnt_Btn_Del = GTK_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Elmnt_Btn_Del"));
		gtk_widget_set_sensitive ((GtkWidget*) elmnt_Btn_Del, FALSE); // Esse botão começa desativado.
		
		pos_Txt_Fator = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Pos_Txt_Fator"));
		gtk_entry_set_text(pos_Txt_Fator, "1");
		
		zoom_Txt_Fator = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Zoom_Txt_Fator"));
		gtk_entry_set_text(zoom_Txt_Fator, "1");
		window_NovoElemento = GTK_WINDOW(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Window_NovoElmnt"));
		g_signal_connect (window_NovoElemento, "delete-event", G_CALLBACK (gtk_widget_hide_on_delete), NULL); // Essa janela não se deletará ao fechá-la, apenas esconderá.
		
		textoNomeElemento = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Nome"));
		textoPontoX = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Ponto_X"));
		textoPontoY = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Ponto_Y"));
		textoRetaInicialX = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Reta_X1"));
		textoRetaInicialY = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Reta_Y1"));
		textoRetaFinalX = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Reta_X2"));
		textoRetaFinalY = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Reta_Y2"));
		textoPoligonoX = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Pol_X"));
		textoPoligonoY = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Pol_Y"));
		poligono_Listbox = GTK_LIST_BOX(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Listbox_Pol"));
		notebook = GTK_NOTEBOOK(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Notebook"));
		poligono_Btn_Del = GTK_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Pol_Del"));
		gtk_widget_set_sensitive ((GtkWidget*) poligono_Btn_Del, FALSE); // Esse botão começa desativado.
		consoleWidget = GTK_TEXT_VIEW(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Console_Text"));

		console = new Console(consoleWidget);
		desenhista = new Desenhista();
		
		gtk_builder_connect_signals(gtkBuilder, NULL);
		gtk_widget_show_all(window_Main);
		gtk_main ();

	}

	//! Método que adiciona a uma GtkListBox um novo elemento.
	/*!
		/param listBox é a GtkListBox que queremos adicionar o elemento.
		/param nome é o texto a ser adicionado.
	*/
	void addToListBox(GtkListBox* listBox, string nome) {
		GtkWidget* row = gtk_list_box_row_new();
		GtkWidget* label = gtk_label_new(nome.c_str());
		gtk_container_add((GtkContainer*) listBox, label);
		gtk_widget_show_all((GtkWidget*) listBox);
	}

	//! Método que remove de uma GtkListBox a linha selecionada e retorna seu índice.
	/*!
		/param list é a GtkListBox que queremos deletar o elemento selecionado.
		/return o valor do índice do elemento removido.
	*/
	int getIndexElementoDeletado(GtkListBox* list) {
		GtkListBoxRow* row = gtk_list_box_get_selected_row (list);
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
	
	//! Método que limpa as caixa de texto da coordenada de um novo poligono.
	void limparTextoCoordPoligono() {
		gtk_entry_set_text(textoPoligonoX, "");
		gtk_entry_set_text(textoPoligonoY, "");
	}

	//! Método que limpa as caixas de texto de polígono da janela de novo objeto.
	void limparTextoNovoPoligono() {
		limparTextoNomeNovoElmnt();
		limparTextoCoordPoligono();
		// Limpa a listBox
		GtkListBoxRow* row = gtk_list_box_get_row_at_index (poligono_Listbox, 0);
		while (row != NULL) {
			gtk_container_remove((GtkContainer*) poligono_Listbox, (GtkWidget*) row);
			row = gtk_list_box_get_row_at_index (poligono_Listbox, 0);
		}
	}

	//! Método que retorna o valor do ponto máximo do viewport.
	/*!
		/return a coordenada do ponto máximo.
	*/
	Coordenada* getViewportMax () {
		Coordenada* coord = new Coordenada();
		coord->setX(gtk_widget_get_allocated_width(viewport_DrawingArea));
		coord->setY(gtk_widget_get_allocated_height(viewport_DrawingArea));
		return coord;
	}

	

	//! Método que limpa a tela(pintando-a de branco).
	void clear_surface (){
		desenhista->clear_surface();
	}

	//! Método que altera a surface do cairo usada.
	/*!
		/param cr é um objeto cairo_t utilizado para desenhar.
	*/
	void modifica_surface(cairo_t *cr){
		desenhista->modifica_surface(cr);
	}

	//! Método que inicializa a surface do cairo usada.
	/*!
		/param widget é a window que será feita a nova "surface". 
	*/
	void nova_surface(GtkWidget *widget) {
		desenhista->nova_surface(widget);
	}

	void desenhaPonto(Ponto* p) {
		desenhista->desenhaPonto(p);
		gtk_widget_queue_draw ((GtkWidget*) window_Main);
	}

	void desenhaReta(Reta* r) {
		desenhista->desenhaReta(r);
		gtk_widget_queue_draw ((GtkWidget*) window_Main);
	}

	void desenhaPoligono(Poligono* p) {
		desenhista->desenhaPoligono(p);
		gtk_widget_queue_draw ((GtkWidget*) window_Main);
	}

	//! Método que insere em uma lista as coordenadas do polígono a ser criado.
	void inserirCoordListaEnc() {
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
				throw -1;
			}
			listaCoordsPoligono->adiciona(c);
			
			string nomeNaLista = "(" + polX + "," + polY + ")";
			addToListBox(poligono_Listbox, nomeNaLista);
		} else {
			console->inserirTexto("ERRO: não é possível inserir coordenada sem valor X ou Y.");
			throw -2;
		}
	}
	
	// Metodos publicos que adicionei
	
	void fecharPrograma() {
		gtk_main_quit();
	}
	
	void setElmnt_Btn_DelSensitive(gboolean valor) {
		gtk_widget_set_sensitive ((GtkWidget*) elmnt_Btn_Del, valor);	
	}
	
	void Elmnt_Btn_Novo_Clicado() {
		listaCoordsPoligono = new ListaEnc<Coordenada*>();
		gtk_widget_show((GtkWidget*) window_NovoElemento);
	};
	
	int deletarElemento(){
		GtkListBoxRow* row = gtk_list_box_get_selected_row (elmnt_List);
		if (row != NULL) {
			int index = gtk_list_box_row_get_index(row);
			gtk_container_remove((GtkContainer*) elmnt_List, (GtkWidget*) row);
			return index;
		} else {
			throw -1;
		}
	}
	
	void inserirTextoConsole(const gchar *texto) {
		console->inserirTexto(texto);
	}
	
	double getFatorMovimento() {
		try {
			return getFator(pos_Txt_Fator);
		} catch (int erro) {
			if (erro == -1) {
				console->inserirTexto("ERRO: Você deve inserir um valor numérico como fator de movimento");
				gtk_entry_set_text(pos_Txt_Fator, "1");
				throw -1;
			} else if (erro == -2) {
				console->inserirTexto("ERRO: Você deve inserir um valor diferente de 0 como fator de movimento");
				gtk_entry_set_text(pos_Txt_Fator, "1");
				throw -2;
			}
		}
	}
	
	double getFatorZoom() {
		try {
			return getFator(zoom_Txt_Fator);
		} catch (int erro) {
			if (erro == -1) {
				console->inserirTexto("ERRO: Você deve inserir um valor numérico como fator de zoom");
				gtk_entry_set_text(zoom_Txt_Fator, "1");
				throw -1;
			} else if (erro == -2) {
				console->inserirTexto("ERRO: Você deve inserir um valor diferente de 0 como fator de zoom");
				gtk_entry_set_text(zoom_Txt_Fator, "1");
				throw -2;
			}
		}
	}
	
	string getNomeElemento () {
		return gtk_entry_get_text(textoNomeElemento);
	}
	
	int getTipoNovoElemento () {
		return gtk_notebook_get_current_page(notebook);
	}
	
	string getCoordXNovoPonto() {
		string entradaX = gtk_entry_get_text(textoPontoX);
		return entradaX;
	}
	
	string getCoordYNovoPonto() {
		string entradaY = gtk_entry_get_text(textoPontoY);
		return entradaY;
	}
	
	string getCoordIniXNovaReta() {
		string entradaXini = gtk_entry_get_text(textoRetaInicialX);
		return entradaXini;
	}
	
	string getCoordIniYNovaReta() {
		string entradaYini = gtk_entry_get_text(textoRetaInicialY);
		return entradaYini;
	}
	
	string getCoordFinXNovaReta() {
		string entradaXfin = gtk_entry_get_text(textoRetaFinalX);
		return entradaXfin;
	}
	
	string getCoordFinYNovaReta() {
		string entradaYfin = gtk_entry_get_text(textoRetaFinalY);
		return entradaYfin;
	}

	int getIndexLinhaElementosSelecionada() {
		return gtk_list_box_row_get_index(gtk_list_box_get_selected_row (elmnt_List));
	}
	
	ListaEnc<Coordenada*>* getListaCoordsPoligono() {
		return listaCoordsPoligono;
	}
	
	void adicionaElementoListbox(string nome) {
		addToListBox(elmnt_List, nome);
	}
	
	void setPoligono_Btn_DelSensitive(gboolean valor) {
		gtk_widget_set_sensitive((GtkWidget*) poligono_Btn_Del, valor);	
	}
	
	void focusNome() {
		gtk_widget_grab_focus((GtkWidget*) textoNomeElemento);
	}
	
	void focusCoordPoligono() {
		gtk_widget_grab_focus((GtkWidget*) textoPoligonoX);
	}
	
	void deletarCoordPoligono () {
		listaCoordsPoligono->retiraDaPosicao(getIndexElementoDeletado(poligono_Listbox));
		setPoligono_Btn_DelSensitive(FALSE);	
	}
	
	void resetarJanelaNovoElemento() {
		limparTextoNomeNovoElmnt();
		limparTextoNovoPonto();
		limparTextoNovaReta();
		limparTextoNovoPoligono();
		setPoligono_Btn_DelSensitive(FALSE);	
		gtk_notebook_set_current_page(notebook, 0);
		free(listaCoordsPoligono);
	}
	
	void resetarListaCoordenadasPoligono() {
		listaCoordsPoligono = new ListaEnc<Coordenada*>();
	}
	
};

#endif