#include <gtk/gtk.h>
#include <string>
#include <stdexcept>
#include "view_Console.hpp"
#include "view_Desenhista.hpp"
#include "ParCoord.hpp"

#ifndef VIEW_HPP
#define VIEW_HPP

//using namespace std;
using std::string;
using std::stod;
using std::invalid_argument;
using std::to_string;

class View {

private:
	Console* console; /*!< Uma instância do administrador do Console da interface grafica.*/
	Desenhista* desenhista; /*!< Uma instância da classe que desenha os objetos na tela.*/
	ListaEnc<Coordenada3D*> *listaCoordsPoligono; /*!< Uma lista de coordenadas para criar novos poligonos.*/
	ListaEnc<Coordenada3D*> *listaCoordsCurva; /*!< Uma lista de coordenadas para criar novas curvas.*/

	ListaEnc<Coordenada3D*> *listaCoordsObjeto3D; /*!< Uma lista de coordenadas para criar novos Objetos3D.*/
	ListaEnc<ParCoord*> *listaArestas; /*!< Uma lista de inteiros para criar as arestas do novo Objeto3D.*/

	// Objetos relacionados à interface
	GtkWindow *window_Main; /*!< Referência para a janela principal.*/

	GtkMenuItem *menuBar_Salvar_Obj; /*!< O botão de Salvar .obj*/
	GtkMenuItem *menuBar_Carregar_Obj; /*!< O botão de carregar .obj*/
	GtkMenuItem *menuBar_Separator_01; /*!< Separador 1 do menubar*/
	GtkMenuItem *menuBar_Salvar_Elemento_Obj; /*!< O botão de Salvar Elemento.*/

	GtkListBox *elmnt_List; /*!< Referência para a lista de elementos.*/
	GtkButton *elmnt_Btn_Novo, *elmnt_Btn_Del, *elmnt_Btn_Edit; /*!< Referência para os botões de novo, deletar e editar elementos.*/

	GtkEntry *pos_Txt_Fator; /*!< Referência para a caixa de texto de Fator da movimentação.*/
	GtkButton *pos_Btn_Cima, *pos_Btn_Baixo, *pos_Btn_Esq, *pos_Btn_Dir; /*!< Referência para os botões das quatro direções.*/
	GtkButton *pos_Btn_Top_Esq, *pos_Btn_Top_Dir; /*!< Referência para os botões de cima no posicionamento da window.*/
	GtkRadioButton *pos_radio_0, *pos_radio_1; /*!< Referência para os botões de seleção do tipo de movimento da window.*/

	GtkEntry *zoom_Txt_Fator; /*!< Referência para a caixa de texto de Fator de zoom.*/
	GtkButton *zoom_Btn_Menos, *zoom_Btn_Mais; /*!< Referência para os botões de mais e menos zoom.*/

	GtkWidget *viewport_DrawingArea; /*!< A área de desenho*/

	GtkRadioButton *clipping_radio_0, *clipping_radio_1; /*!< Referência para os botões de seleção do tipo de clipping de reta.*/

	GtkRadioButton *projecao_radio_0, *projecao_radio_1; /*!< Referência para os botões de seleção do tipo de projeção.*/
	GtkAdjustment* projecao_DistFocal_Ajuste;
	GtkScale* projecao_Scale_COP;
	
	GtkTextView *consoleWidget; /*!< Referência para a caixa de texto do console.*/

	GtkWindow *window_NovoElemento; /*!< Referência para a janela de novo elemento.*/

	GtkEntry *textoNomeElemento; /*!< Referência para a caixa de texto de inserção de nome para um elemento.*/
	GtkEntry *textoPontoX, *textoPontoY, *textoPontoZ,
			*textoRetaInicialX, *textoRetaInicialY, *textoRetaInicialZ, *textoRetaFinalX, *textoRetaFinalY, *textoRetaFinalZ,
			*textoPoligonoX, *textoPoligonoY, *textoPoligonoZ,
			*textoCurvaX, *textoCurvaY, *textoCurvaZ,
			*textoObjeto3DX, *textoObjeto3DY, *textoObjeto3DZ; /*!< Referência para as caixas de texto que recebem valores de coordenadas.*/

	GtkButton *poligono_Btn_Add, *poligono_Btn_Del; /*!< Referência para os botões de adicionar e deletar coordenadas na criação de um poligono.*/
	GtkListBox *poligono_Listbox; /*!< Referência para a listbox com as coordenadas do poligono.*/
	GtkCheckButton *poligono_Preenchido; /*!< Caixa que marca se o poligono cirado deve ou não ser preenchido.*/

	GtkButton *curva_Btn_Add, *curva_Btn_Del; /*!< Referência para os botões de adicionar e deletar coordenadas na criação de uma curva.*/
	GtkListBox *curva_Listbox; /*!< Referência para a listbox com as coordenadas da curva.*/
	GtkRadioButton *curva_radio_0, *curva_radio_1; /*!< Referência para os botões de seleção do tipo de clipping de reta.*/

	GtkButton *Objeto3D_Coord_Btn_Add, *Objeto3D_Coord_Btn_Del; /*!< Referência para os botões de adicionar e deletar coordenadas na criação de um Objeto3D.*/
	GtkButton *Objeto3D_Aresta_Btn_Add, *Objeto3D_Aresta_Btn_Del; /*!< Referência para os botões de adicionar e deletar arestas na criação de um Objeto3D.*/
	GtkListBox *Objeto3D_Coord_Listbox; /*!< Referência para a listbox com as coordenadas do objeto3D.*/
	GtkListBox *Objeto3D_Aresta_Listbox; /*!< Referência para a listbox com as arestas do objeto3D.*/
	GtkEntry *textoObjeto3DA, *textoObjeto3DB;

	GtkNotebook *novoElmnt_Notebook; /*!< Referência para o notebook na criação de elemento.*/

	GtkWindow *window_EditElemento; /*!< Referência para a janela de editar elemento.*/

	GtkEntry *editElmnt_trans_X, *editElmnt_trans_Y, *editElmnt_trans_Z; /*!< Referência para a caixa de texto das coordenadas de translação.*/

	GtkEntry *editElmnt_escal_X, *editElmnt_escal_Y, *editElmnt_escal_Z; /*!< Referência para a caixa de texto da quantidade de escalonamento.*/

	GtkEntry *editElmnt_rot_angulo; /*!< Referência para a caixa de texto do angulo de rotação.*/

	GtkRadioButton *editElmnt_radio_0, *editElmnt_radio_1, *editElmnt_radio_2; /*!< Referência para os botões de seleção do tipo de rotação.*/
	GtkRadioButton *editElmnt_radio_eixo_0, *editElmnt_radio_eixo_1, *editElmnt_radio_eixo_2; /*!< Referência para os botões de seleção do eixo de rotação.*/

	GtkEntry *editElmnt_rot_X, *editElmnt_rot_Y, *editElmnt_rot_Z; /*!< Referência para a caixa de texto do ponto arbitrário da rotação.*/

	GtkNotebook *editElmnt_Notebook; /*!< Referência para o notebook na edição de elemento.*/

	GtkButton *editElmnt_aplicar; /*!< Botão que confirma a edição de um elemento.*/

	//! Método que obtem um valor numérico de um GtkEntry
    /*!
        Converte o valor contido em um GtkEntry para um valor double.
        /param area é a GtkEntry cujo valor sera convertido.
		/return um valor double correspondente ao valor em string contido na GtkEntry.
    */
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

	//! Método que inicializa todos os atributos desta classe.
    /*!
        Liga os atributos aos seus correspondentes widgets contidos na janela criada no glade,
		assim como inicializa outros elementos necessários para o funcionamento da interface grafica.
    */
	void inicializarComponentes(int argc, char *argv[]) {
		GtkBuilder  *gtkBuilder;
		gtk_init(&argc, &argv);

		//gtkBuilder = gtk_builder_new();
		//gtk_builder_add_from_file(gtkBuilder, "janela.glade", NULL);
		gtkBuilder = gtk_builder_new_from_file("janela.glade");

		window_Main = GTK_WINDOW(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Window_Main"));

		menuBar_Salvar_Elemento_Obj = GTK_MENU_ITEM(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "MenuBar_Salvar_Obj_Elemento"));
		gtk_widget_set_sensitive ((GtkWidget*) menuBar_Salvar_Elemento_Obj, FALSE); // Esse botão começa desativado.

		menuBar_Salvar_Obj = GTK_MENU_ITEM(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "MenuBar_Salvar_Obj"));
		gtk_widget_destroy((GtkWidget*) menuBar_Salvar_Obj); // Destruindo esses botões pois a classe WavefrontOBJ não foi atualizada para 3D
		menuBar_Carregar_Obj = GTK_MENU_ITEM(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "MenuBar_Carregar_Obj"));
		//gtk_widget_destroy((GtkWidget*) menuBar_Carregar_Obj); // Destruindo esses botões pois a classe WavefrontOBJ não foi atualizada para 3D
		menuBar_Separator_01 = GTK_MENU_ITEM(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "MenuBar_Separator_01"));
		//gtk_widget_destroy((GtkWidget*) menuBar_Separator_01); // Destruindo esses botões pois a classe WavefrontOBJ não foi atualizada para 3D

		viewport_DrawingArea = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Viewport_DrawingArea"));

		elmnt_List = GTK_LIST_BOX(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Elmnt_List"));
		elmnt_Btn_Del = GTK_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Elmnt_Btn_Del"));
		gtk_widget_set_sensitive ((GtkWidget*) elmnt_Btn_Del, FALSE); // Esse botão começa desativado.
		elmnt_Btn_Edit = GTK_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Elmnt_Btn_Edit"));
		gtk_widget_set_sensitive ((GtkWidget*) elmnt_Btn_Edit, FALSE); // Esse botão começa desativado.

		pos_Txt_Fator = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Pos_Txt_Fator"));
		gtk_entry_set_text(pos_Txt_Fator, "1");
		pos_Btn_Top_Esq = GTK_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Pos_Btn_Top_Esq"));
		pos_Btn_Top_Dir = GTK_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Pos_Btn_Top_Dir"));
		pos_radio_0 = GTK_RADIO_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Pos_Radio_0"));
		pos_radio_1 = GTK_RADIO_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Pos_Radio_1"));

		zoom_Txt_Fator = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Zoom_Txt_Fator"));
		gtk_entry_set_text(zoom_Txt_Fator, "1");
		window_NovoElemento = GTK_WINDOW(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Window_NovoElmnt"));
		g_signal_connect (window_NovoElemento, "delete-event", G_CALLBACK (gtk_widget_hide_on_delete), NULL); // Essa janela não se deletará ao fechá-la, apenas esconderá.

		textoNomeElemento = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Nome"));

		textoPontoX = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Ponto_X"));
		textoPontoY = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Ponto_Y"));
		textoPontoZ = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Ponto_Z"));

		textoRetaInicialX = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Reta_X1"));
		textoRetaInicialY = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Reta_Y1"));
		textoRetaInicialZ = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Reta_Z1"));
		textoRetaFinalX = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Reta_X2"));
		textoRetaFinalY = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Reta_Y2"));
		textoRetaFinalZ = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Reta_Z2"));

		textoPoligonoX = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Pol_X"));
		textoPoligonoY = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Pol_Y"));
		textoPoligonoZ = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Pol_Z"));
		poligono_Listbox = GTK_LIST_BOX(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Listbox_Pol"));
		poligono_Preenchido = GTK_CHECK_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Pol_Preenchido"));
		poligono_Btn_Del = GTK_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Pol_Del"));
		gtk_widget_set_sensitive ((GtkWidget*) poligono_Btn_Del, FALSE); // Esse botão começa desativado.

		textoCurvaX = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Curv_X"));
		textoCurvaY = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Curv_Y"));
		textoCurvaZ = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Curv_Z"));
		curva_Listbox = GTK_LIST_BOX(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Listbox_Curv"));
		curva_Btn_Del = GTK_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Curv_Del"));
		gtk_widget_set_sensitive ((GtkWidget*) curva_Btn_Del, FALSE); // Esse botão começa desativado.
		curva_radio_0 = GTK_RADIO_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Curv_Radio_0"));
		curva_radio_1 = GTK_RADIO_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Curv_Radio_1"));

		textoObjeto3DX = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Obj_Coord_X"));
		textoObjeto3DY = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Obj_Coord_Y"));
		textoObjeto3DZ = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Obj_Coord_Z"));
		textoObjeto3DA = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Obj_Aresta_A"));
		textoObjeto3DB = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Obj_Aresta_B"));
		Objeto3D_Coord_Listbox = GTK_LIST_BOX(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Obj_Coord_Listbox"));
		Objeto3D_Aresta_Listbox = GTK_LIST_BOX(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Obj_Aresta_Listbox"));
		Objeto3D_Coord_Btn_Del = GTK_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Obj_Coord_Del"));
		gtk_widget_set_sensitive ((GtkWidget*) Objeto3D_Coord_Btn_Del, FALSE); // Esse botão começa desativado.
		Objeto3D_Aresta_Btn_Del = GTK_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Obj_Aresta_Del"));
		gtk_widget_set_sensitive ((GtkWidget*) Objeto3D_Aresta_Btn_Del, FALSE); // Esse botão começa desativado.

		novoElmnt_Notebook = GTK_NOTEBOOK(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "NovoElmnt_Notebook"));
		consoleWidget = GTK_TEXT_VIEW(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Console_Text"));

		clipping_radio_0 = GTK_RADIO_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Clipping_Radio_0"));
		clipping_radio_1 = GTK_RADIO_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Clipping_Radio_1"));

		projecao_radio_0 = GTK_RADIO_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Projecao_Radio_0"));
		projecao_radio_1 = GTK_RADIO_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Projecao_Radio_1"));
		projecao_DistFocal_Ajuste = GTK_ADJUSTMENT(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Projecao_DistFocal_Ajuste"));
		projecao_Scale_COP = GTK_SCALE(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Projecao_Scale_COP"));
		setProjecao_Scale_COPSensitive(FALSE);
		
		window_EditElemento = GTK_WINDOW(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Window_EditElmnt"));
		g_signal_connect (window_EditElemento, "delete-event", G_CALLBACK (gtk_widget_hide_on_delete), NULL);

		editElmnt_trans_X = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EditElmnt_Trans_X"));
		editElmnt_trans_Y = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EditElmnt_Trans_Y"));
		editElmnt_trans_Z = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EditElmnt_Trans_Z"));
		editElmnt_escal_X = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EditElmnt_Escal_Fator_X"));
		editElmnt_escal_Y = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EditElmnt_Escal_Fator_Y"));
		editElmnt_escal_Z = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EditElmnt_Escal_Fator_Z"));
		editElmnt_rot_angulo = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EditElmnt_Rot_Angulo"));

		editElmnt_radio_0 = GTK_RADIO_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EditElmnt_Rot_Op_0"));
		editElmnt_radio_1 = GTK_RADIO_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EditElmnt_Rot_Op_1"));
		editElmnt_radio_2 = GTK_RADIO_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EditElmnt_Rot_Op_2"));

		editElmnt_radio_eixo_0 = GTK_RADIO_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EditElmnt_Rot_Eixo_0"));
		editElmnt_radio_eixo_1 = GTK_RADIO_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EditElmnt_Rot_Eixo_1"));
		editElmnt_radio_eixo_2 = GTK_RADIO_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EditElmnt_Rot_Eixo_2"));

		editElmnt_rot_X = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EditElmnt_Rot_X"));
		editElmnt_rot_Y = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EditElmnt_Rot_Y"));
		editElmnt_rot_Z = GTK_ENTRY(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EditElmnt_Rot_Z"));
		editElmnt_Notebook = GTK_NOTEBOOK(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EditElmnt_Notebook"));

		editElmnt_aplicar = GTK_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "EditElmnt_Aplicar"));

		console = new Console(consoleWidget);
		desenhista = new Desenhista();

		gtk_builder_connect_signals(gtkBuilder, NULL);
		gtk_widget_show_all((GtkWidget*) window_Main);
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
		gtk_entry_set_text(textoPontoX, "0");
		gtk_entry_set_text(textoPontoY, "0");
		gtk_entry_set_text(textoPontoZ, "0");
	}

	//! Método que limpa as caixas de texto de reta da janela de novo objeto.
	void limparTextoNovaReta() {
		limparTextoNomeNovoElmnt();
		gtk_entry_set_text(textoRetaInicialX, "0");
		gtk_entry_set_text(textoRetaInicialY, "0");
		gtk_entry_set_text(textoRetaInicialZ, "0");
		gtk_entry_set_text(textoRetaFinalX, "0");
		gtk_entry_set_text(textoRetaFinalY, "0");
		gtk_entry_set_text(textoRetaFinalZ, "0");
	}

	//! Método que limpa as caixa de texto da coordenada de um novo poligono.
	void limparTextoCoordPoligono() {
		gtk_entry_set_text(textoPoligonoX, "0");
		gtk_entry_set_text(textoPoligonoY, "0");
		gtk_entry_set_text(textoPoligonoZ, "0");
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

	//! Método que limpa as caixa de texto da coordenada de um novo poligono.
	void limparTextoCoordCurva() {
		gtk_entry_set_text(textoCurvaX, "0");
		gtk_entry_set_text(textoCurvaY, "0");
		gtk_entry_set_text(textoCurvaZ, "0");
	}

	//! Método que limpa as caixas de texto de curva da janela de novo objeto.
	void limparTextoNovaCurva() {
		limparTextoNomeNovoElmnt();
		limparTextoCoordCurva();
		// Limpa a listBox
		GtkListBoxRow* row = gtk_list_box_get_row_at_index (curva_Listbox, 0);
		while (row != NULL) {
			gtk_container_remove((GtkContainer*) curva_Listbox, (GtkWidget*) row);
			row = gtk_list_box_get_row_at_index (curva_Listbox, 0);
		}
	}

	//! Método que limpa as caixa de texto da coordenada de um novo poligono.
	void limparTextoCoordObjeto3D() {
		gtk_entry_set_text(textoObjeto3DX, "0");
		gtk_entry_set_text(textoObjeto3DY, "0");
		gtk_entry_set_text(textoObjeto3DZ, "0");
	}

	void limparTextoArestaObjeto3D() {
		gtk_entry_set_text(textoObjeto3DA, "0");
		gtk_entry_set_text(textoObjeto3DB, "1");
	}

	//! Método que limpa as caixas de texto de Objeto3D da janela de novo objeto.
	void limparTextoNovoObjeto3D() {
		limparTextoNomeNovoElmnt();
		limparTextoCoordObjeto3D();
		limparTextoArestaObjeto3D();
		// Limpa a listBox de coord
		GtkListBoxRow* row = gtk_list_box_get_row_at_index (Objeto3D_Coord_Listbox, 0);
		while (row != NULL) {
			gtk_container_remove((GtkContainer*) Objeto3D_Coord_Listbox, (GtkWidget*) row);
			row = gtk_list_box_get_row_at_index (Objeto3D_Coord_Listbox, 0);
		}
		// Limpa a listBox de aresta
		row = gtk_list_box_get_row_at_index (Objeto3D_Aresta_Listbox, 0);
		while (row != NULL) {
			gtk_container_remove((GtkContainer*) Objeto3D_Aresta_Listbox, (GtkWidget*) row);
			row = gtk_list_box_get_row_at_index (Objeto3D_Aresta_Listbox, 0);
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

	//! Desenha a margem para a observação do clipping.
	void desenhaMargem() {
		desenhista->desenhaMargem(getViewportMax());
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

	//! Método que repassa a instrução de desenhar um ponto para o desenhista.
	/*!
		/param coord é a coordenada do ponto a ser desenhado.
	*/
	void desenhaPonto(Coordenada* coord) {
		desenhista->desenhaPonto(coord);
		gtk_widget_queue_draw ((GtkWidget*) window_Main);
	}

	//! Método que repassa a instrução de desenhar uma reta para o desenhista.
	/*!
		/param coordInicial é a coordenada inicial da reta.
		/param coordFinal é a coordenada final da reta.
	*/
	void desenhaReta(Coordenada* coordInicial, Coordenada* coordFinal) {
		desenhista->desenhaReta(coordInicial, coordFinal);
		gtk_widget_queue_draw ((GtkWidget*) window_Main);
	}

	//! Método que repassa a instrução de desenhar um poligono para o desenhista.
	/*!
		/param lista é a lista de coordenadas do poligono a ser desenhado.
		/param preenchido é um valor booleado que diz se este poligono deve ser preenchido ou não.
	*/
	void desenhaPoligono(ListaEnc<Coordenada*>* lista, bool preenchido) {
		desenhista->desenhaPoligono(lista, preenchido);
		gtk_widget_queue_draw ((GtkWidget*) window_Main);
	}

	//! Método que desenha uma curva.
	/*!
		/param lista é a lista de retas da curva a ser desenhada.
	*/
	void desenhaCurva(ListaEnc<Reta*>* lista) {
		desenhista->desenhaCurva(lista);
		gtk_widget_queue_draw ((GtkWidget*) window_Main);
	}

	//! Método que insere em uma lista as coordenadas do polígono a ser criado.
	void inserirCoordListaEncPoligono() {
		// Pega coordenadas
		string polX = gtk_entry_get_text(textoPoligonoX);
		string polY = gtk_entry_get_text(textoPoligonoY);
		string polZ = gtk_entry_get_text(textoPoligonoZ);

		/// Se os campos de coordenada não estão em branco
		if ( !(polX.empty()) && !(polY.empty()) && !(polZ.empty()) ) {
			// Cria novo objeto
			Coordenada3D* c = new Coordenada3D();
			// Verifica se os campos são números
			try {
				// stod = string to double
				c->setX(stod(polX));
				c->setY(stod(polY));
				c->setZ(stod(polZ));
			} catch (const invalid_argument& e) {
				console->inserirTexto("ERRO: coordenadas devem ser valores numéricos.");
				throw -1;
			}
			listaCoordsPoligono->adiciona(c);

			string nomeNaLista = "(" + polX + "," + polY + "," + polZ + ")";
			addToListBox(poligono_Listbox, nomeNaLista);
		} else {
			console->inserirTexto("ERRO: não é possível inserir coordenada sem valor X, Y ou Z.");
			throw -2;
		}
	}

	//! Método que insere em uma lista as coordenadas da curva a ser criada.
	void inserirCoordListaEncCurva() {
		// Pega coordenadas
		string polX = gtk_entry_get_text(textoCurvaX);
		string polY = gtk_entry_get_text(textoCurvaY);
		string polZ = gtk_entry_get_text(textoCurvaZ);

		/// Se os campos de coordenada não estão em branco
		if ( !(polX.empty()) && !(polY.empty()) && !(polZ.empty()) ) {
			// Cria novo objeto
			Coordenada3D* c = new Coordenada3D();
			// Verifica se os campos são números
			try {
				// stod = string to double
				c->setX(stod(polX));
				c->setY(stod(polY));
				c->setZ(stod(polZ));
			} catch (const invalid_argument& e) {
				console->inserirTexto("ERRO: coordenadas devem ser valores numéricos.");
				throw -1;
			}
			listaCoordsCurva->adiciona(c);

			string nomeNaLista = "(" + polX + "," + polY + "," + polZ + ")";
			addToListBox(curva_Listbox, nomeNaLista);
		} else {
			console->inserirTexto("ERRO: não é possível inserir coordenada sem valor X, Y ou Z.");
			throw -2;
		}
	}

	//! Método que insere em uma lista as coordenadas do polígono a ser criado.
	void inserirCoordListaEncObjeto3D() {
		// Pega coordenadas
		string polX = gtk_entry_get_text(textoObjeto3DX);
		string polY = gtk_entry_get_text(textoObjeto3DY);
		string polZ = gtk_entry_get_text(textoObjeto3DZ);

		/// Se os campos de coordenada não estão em branco
		if ( !(polX.empty()) && !(polY.empty()) && !(polZ.empty()) ) {
			// Cria novo objeto
			Coordenada3D* c = new Coordenada3D();
			// Verifica se os campos são números
			try {
				// stod = string to double
				c->setX(stod(polX));
				c->setY(stod(polY));
				c->setZ(stod(polZ));
			} catch (const invalid_argument& e) {
				console->inserirTexto("ERRO: coordenadas devem ser valores numéricos.");
				throw -1;
			}
			listaCoordsObjeto3D->adiciona(c);

			string nomeNaLista = to_string(listaCoordsObjeto3D->getSize() - 1) + ": (" + polX + "," + polY + "," + polZ + ")";
			addToListBox(Objeto3D_Coord_Listbox, nomeNaLista);
		} else {
			console->inserirTexto("ERRO: não é possível inserir coordenada sem valor X, Y ou Z.");
			throw -2;
		}
	}

	//! Método que insere em uma lista as coordenadas do polígono a ser criado.
	void inserirArestaListaEncObjeto3D() {
		// Pega coordenadas
		string polA = gtk_entry_get_text(textoObjeto3DA);
		string polB = gtk_entry_get_text(textoObjeto3DB);

		/// Se os campos de coordenada não estão em branco
		if ( !(polA.empty()) && !(polB.empty()) ) {
			// Cria novo objeto
			ParCoord* aresta;
			// Verifica se os campos são números
			try {
				// stod = string to double
				aresta = new ParCoord(stod(polA), stod(polB));
			} catch (const invalid_argument& e) {
				console->inserirTexto("ERRO: coordenadas devem ser valores numéricos.");
				throw -1;
			}
			int numCoords = listaCoordsObjeto3D->getSize() - 1;
			if ((aresta->getA() <= numCoords) && (aresta->getB() <= numCoords) && (aresta->getA() != aresta->getB())) {
				listaArestas->adiciona(aresta);

				string nomeNaLista = "(" + polA + "," + polB + ")";
				addToListBox(Objeto3D_Aresta_Listbox, nomeNaLista);
			} else {
				console->inserirTexto("ERRO: as coordenadas escolhidas não são validas");
				throw -3;
			}

		} else {
			console->inserirTexto("ERRO: você deve inserir valores inteiros");
			throw -2;
		}
	}

	//! Método que fecha o programa.
	void fecharPrograma() {
		gtk_main_quit();
	}

	//! Método que altera a sensibilidade do botao de salvar elemento.
	/*!
		/param valor é o novo valor da sensibilidade do botao (TRUE ou FALSE).
	*/
	void setMenuBar_Salvar_Elemento_ObjSensitive(gboolean valor) {
		gtk_widget_set_sensitive ((GtkWidget*) menuBar_Salvar_Elemento_Obj, valor);
	}

	//! Método que altera a sensibilidade do botao de deletar.
	/*!
		/param valor é o novo valor da sensibilidade do botao (TRUE ou FALSE).
	*/
	void setElmnt_Btn_DelSensitive(gboolean valor) {
		gtk_widget_set_sensitive ((GtkWidget*) elmnt_Btn_Del, valor);
	}

	//! Método que altera a sensibilidade do botao de editar.
	/*!
		/param valor é o novo valor da sensibilidade do botao (TRUE ou FALSE).
	*/
	void setElmnt_Btn_EditSensitive(gboolean valor) {
		gtk_widget_set_sensitive ((GtkWidget*) elmnt_Btn_Edit, valor);
	}

	//! Metodo que exibe a janela de novo elemento.
	void elmnt_Btn_Novo_Clicado() {
		listaCoordsPoligono = new ListaEnc<Coordenada3D*>();
		listaCoordsCurva = new ListaEnc<Coordenada3D*>();
		listaCoordsObjeto3D = new ListaEnc<Coordenada3D*>();
		listaArestas = new ListaEnc<ParCoord*>();
		gtk_widget_show((GtkWidget*) window_NovoElemento);
	}

	//! Metodo que exibe a janela de editar elemento.
	void elmnt_Btn_Edit_Clicado() {
		gtk_widget_show((GtkWidget*) window_EditElemento);
	}

	//! Metodo que pega o elemento atualmente seleciona na listbox e o deleta.
	/*!
		/return o indice na lista encadeada onde se encontra esse elemento.
	*/
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

	//! Metodo que repassa a mensagem para o console para que esta seja exibida.
	/*!
		/param texto é o texto que sera adicionado ao final do console.
	*/
	void inserirTextoConsole(const gchar *texto) {
		console->inserirTexto(texto);
	}

	//! Metodo que retorna o valor numérico contido na caixa de Fator na regição da edição de posição.
	/*!
		/return o fator da caixa na região da posição.
	*/
	double getFatorPosicao() {
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

	//! Metodo que retorna o tipo de transformação na window da window.
	/*!
		/return inteiro correspondendo à um dos dois tipos de movimento da window.
	*/
	int getTipoMovimentoWindow() {
		if (gtk_toggle_button_get_active((GtkToggleButton*) pos_radio_0)) {
			return 0;
		} else {
			return 1;
		}
	}

	//! Metodo que altera o texto dos botões de movimento da window.
	/*!
		/param tipo inteiro correspondendo à um dos dois possiveis conjunto de textos para estes botões.
	*/
	int alterarBotoesMovimentoWindow(int tipo) {
		switch (tipo) {
			case 0: {
				gtk_widget_show((GtkWidget*) pos_Btn_Top_Esq);
				gtk_widget_show((GtkWidget*) pos_Btn_Top_Dir);
				gtk_button_set_label(pos_Btn_Top_Esq, "↥");
				gtk_button_set_label(pos_Btn_Top_Dir, "↧");
				break;
			} case 1: {
				gtk_widget_hide((GtkWidget*) pos_Btn_Top_Esq);
				gtk_widget_hide((GtkWidget*) pos_Btn_Top_Dir);
				gtk_button_set_label(pos_Btn_Top_Esq, "⟲");
				gtk_button_set_label(pos_Btn_Top_Dir, "⟳");
				break;
			}
		}
	}

	//! Metodo que retorna o valor numérico contido na caixa de Fator de Zoom.
	/*!
		/return o fator de zoom.
	*/
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

	//! Metodo que retorna o tipo de clipping de reta.
	/*!
		/return inteiro correspondendo à um dos dois tipos de clipping de reta.
	*/
	int getTipoClippingReta() {
		if (gtk_toggle_button_get_active((GtkToggleButton*) clipping_radio_0)) {
			return 0;
		} else {
			return 1;
		}
	}
	
	//! Metodo que retorna o tipo de projeção.
	/*!
		/return inteiro correspondendo à um dos dois tipos de projeção.
	*/
	int getTipoProjecao() {
		if (gtk_toggle_button_get_active((GtkToggleButton*) projecao_radio_0)) {
			return 0;
		} else {
			return 1;
		}
	}
	
	//! Metodo que retorna a distância do COP.
	/*!
		/return a distância definida pelo usuário para COP.
	*/
	double getDistFocal() {
		return gtk_adjustment_get_value(projecao_DistFocal_Ajuste);
	}
	
	//! Metodo que desativa a barra de alteração de COP.
	/*!
		/param valor é o novo valor da sensibilidade da barra (TRUE ou FALSE).
	*/
	void setProjecao_Scale_COPSensitive(gboolean valor) {
		gtk_widget_set_sensitive ((GtkWidget*) projecao_Scale_COP, valor);
	}

	// ------------------------------------------------------------------------------------------------
	// Comandos Da Janela de Novo Elemento


	//! Metodo que retorna o valor contido na caixa de Nome do novo elemento.
	/*!
		/return o nome do novo elemento.
	*/
	string getNomeElemento () {
		return gtk_entry_get_text(textoNomeElemento);
	}

	//! Metodo que retorna o tipo do novo elemento.
	/*!
		/return inteiro correspondendo a qual o tipo do novo elemento que esta sendo criaddo.
	*/
	int getTipoNovoElemento () {
		return gtk_notebook_get_current_page(novoElmnt_Notebook);
	}

	//! Metodo que retorna o valor contido na caixa de coordenada X da criação de um ponto.
	/*!
		/return a coordenada X desse novo ponto.
	*/
	string getCoordXNovoPonto() {
		string entradaX = gtk_entry_get_text(textoPontoX);
		return entradaX;
	}

	//! Metodo que retorna o valor contido na caixa de coordenada Y da criação de um ponto.
	/*!
		/return a coordenada Y desse novo ponto.
	*/
	string getCoordYNovoPonto() {
		string entradaY = gtk_entry_get_text(textoPontoY);
		return entradaY;
	}

	//! Metodo que retorna o valor contido na caixa de coordenada Z da criação de um ponto.
	/*!
		/return a coordenada Z desse novo ponto.
	*/
	string getCoordZNovoPonto() {
		string entradaZ = gtk_entry_get_text(textoPontoZ);
		return entradaZ;
	}

	//! Metodo que retorna o valor contido na caixa de coordenada X Inicial da criação de uma reta.
	/*!
		/return a coordenada X Inicial dessa nova reta.
	*/
	string getCoordIniXNovaReta() {
		string entradaXini = gtk_entry_get_text(textoRetaInicialX);
		return entradaXini;
	}

	//! Metodo que retorna o valor contido na caixa de coordenada Y Inicial da criação de uma reta.
	/*!
		/return a coordenada Y Inicial dessa nova reta.
	*/
	string getCoordIniYNovaReta() {
		string entradaYini = gtk_entry_get_text(textoRetaInicialY);
		return entradaYini;
	}

	//! Metodo que retorna o valor contido na caixa de coordenada Z Inicial da criação de uma reta.
	/*!
		/return a coordenada Z Inicial dessa nova reta.
	*/
	string getCoordIniZNovaReta() {
		string entradaZini = gtk_entry_get_text(textoRetaInicialZ);
		return entradaZini;
	}

	//! Metodo que retorna o valor contido na caixa de coordenada X Final da criação de uma reta.
	/*!
		/return a coordenada X Final dessa nova reta.
	*/
	string getCoordFinXNovaReta() {
		string entradaXfin = gtk_entry_get_text(textoRetaFinalX);
		return entradaXfin;
	}

	//! Metodo que retorna o valor contido na caixa de coordenada Y Final da criação de uma reta.
	/*!
		/return a coordenada Y Final dessa nova reta.
	*/
	string getCoordFinYNovaReta() {
		string entradaYfin = gtk_entry_get_text(textoRetaFinalY);
		return entradaYfin;
	}

	//! Metodo que retorna o valor contido na caixa de coordenada Z Final da criação de uma reta.
	/*!
		/return a coordenada Z Final dessa nova reta.
	*/
	string getCoordFinZNovaReta() {
		string entradaZfin = gtk_entry_get_text(textoRetaFinalZ);
		return entradaZfin;
	}

	//! Metodo que retorna o indice do elemento selecionado na ListBox de elementos.
	/*!
		/return o indice do elemento selecionado.
	*/
	int getIndexLinhaElementosSelecionada() {
		return gtk_list_box_row_get_index(gtk_list_box_get_selected_row (elmnt_List));
	}

	//! Metodo que retorna a lista de coordenadas na criação de um novo poligono.
	/*!
		/return a lista de coordenadas do novo poligono.
	*/
	ListaEnc<Coordenada3D*>* getListaCoordsPoligono() {
		return listaCoordsPoligono;
	}

	//! Metodo que retorna a lista de coordenadas na criação de uma nova curva.
	/*!
		/return a lista de coordenadas da nova curva.
	*/
	ListaEnc<Coordenada3D*>* getListaCoordsCurva() {
		return listaCoordsCurva;
	}

	//! Metodo que retorna a lista de coordenadas na criação de um Objeto3D.
	/*!
		/return a lista de coordenadas do novo Objeto3D.
	*/
	ListaEnc<Coordenada3D*>* getListaCoordsObjeto3D() {
		return listaCoordsObjeto3D;
	}

	//! Metodo que retorna a lista de coordenadas na criação de um Objeto3D.
	/*!
		/return a lista de coordenadas do novo Objeto3D.
	*/
	ListaEnc<ParCoord*>* getListaArestasObjeto3D() {
		return listaArestas;
	}

	//! Metodo que adiciona o nome de um elemento à listbox de elementos.
	/*!
		/param nome o nome desse novo elemento.
		/param tipo é o tipo do elemento.
	*/
	void adicionaElementoListbox(string nome, string tipo) {
		addToListBox(elmnt_List, nome + " (" + tipo + ")");
	}

	//! Método que altera a sensibilidade do botao de deletar na criação de poligonos.
	/*!
		/param valor é o novo valor da sensibilidade do botao (TRUE ou FALSE).
	*/
	void setPoligono_Btn_DelSensitive(gboolean valor) {
		gtk_widget_set_sensitive((GtkWidget*) poligono_Btn_Del, valor);
	}

	//! Método que altera a sensibilidade do botao de deletar na criação de curvas.
	/*!
		/param valor é o novo valor da sensibilidade do botao (TRUE ou FALSE).
	*/
	void setCurva_Btn_DelSensitive(gboolean valor) {
		gtk_widget_set_sensitive((GtkWidget*) curva_Btn_Del, valor);
	}

	//! Método que altera a sensibilidade do botao de deletar coordenada na criação de Objetos3D.
	/*!
		/param valor é o novo valor da sensibilidade do botao (TRUE ou FALSE).
	*/
	void setObjeto3D_Coord_Btn_DelSensitive(gboolean valor) {
		gtk_widget_set_sensitive((GtkWidget*) Objeto3D_Coord_Btn_Del, valor);
	}

	//! Método que altera a sensibilidade do botao de deletar arestas na criação de Objetos3D.
	/*!
		/param valor é o novo valor da sensibilidade do botao (TRUE ou FALSE).
	*/
	void setObjeto3D_Aresta_Btn_DelSensitive(gboolean valor) {
		gtk_widget_set_sensitive((GtkWidget*) Objeto3D_Aresta_Btn_Del, valor);
	}

	//! Metodo que retorna o tipo de curva sendo criada.
	/*!
		/return inteiro correspondendo à um dos dois tipos de curva.
	*/
	int getTipoCurva() {
		if (gtk_toggle_button_get_active((GtkToggleButton*) curva_radio_0)) {
			return 0;
		} else {
			return 1;
		}
	}

	//! Método que passa o foco do cursor para a caixa de Nome na janela de novo elemento.
	void focusNome() {
		gtk_widget_grab_focus((GtkWidget*) textoNomeElemento);
	}

	//! Método que passa o foco do cursor para a caixa de Coordenada X na janela de criação de poligono.
	void focusCoordPoligono() {
		gtk_widget_grab_focus((GtkWidget*) textoPoligonoX);
	}

	//! Método que passa o foco do cursor para a caixa de Coordenada X na janela de criação de curva.
	void focusCoordCurva() {
		gtk_widget_grab_focus((GtkWidget*) textoCurvaX);
	}

	//! Método que passa o foco do cursor para a caixa de Coordenada X na janela de criação de Objeto3D.
	void focusCoordObjeto3D() {
		gtk_widget_grab_focus((GtkWidget*) textoObjeto3DX);
	}

	//! Método que passa o foco do cursor para a caixa de Coordenada X na janela de criação de Objeto3D.
	void focusArestaObjeto3D() {
		gtk_widget_grab_focus((GtkWidget*) textoObjeto3DA);
	}

	//! Método que deleta a coordenada selecionada na janela de criação de poligono.
	void deletarCoordPoligono() {
		listaCoordsPoligono->retiraDaPosicao(getIndexElementoDeletado(poligono_Listbox));
		setPoligono_Btn_DelSensitive(FALSE);
	}

	//! Método que deleta a coordenada selecionada na janela de criação de curva.
	void deletarCoordCurva() {
		listaCoordsCurva->retiraDaPosicao(getIndexElementoDeletado(curva_Listbox));
		setCurva_Btn_DelSensitive(FALSE);
	}

	//! Método que deleta a coordenada selecionada na janela de criação de um Objeto3D.
	void deletarCoordObjeto3D() {
		listaCoordsObjeto3D->retiraDaPosicao(getIndexElementoDeletado(Objeto3D_Coord_Listbox));
		setObjeto3D_Coord_Btn_DelSensitive(FALSE);

		GtkListBoxRow* row = gtk_list_box_get_row_at_index (Objeto3D_Coord_Listbox, 0);
		while (row != NULL) {
			gtk_container_remove((GtkContainer*) Objeto3D_Coord_Listbox, (GtkWidget*) row);
			row = gtk_list_box_get_row_at_index (Objeto3D_Coord_Listbox, 0);
		}

		Elemento<Coordenada3D*>* elementoLista = listaCoordsObjeto3D->getHead();
		int count = 0;
		while (elementoLista != NULL) {
			Coordenada3D* coord = elementoLista->getInfo();
			string polX = to_string(coord->getX());
			polX.erase( polX.find_last_not_of('0') + 1, std::string::npos);
			if (polX.back() == ',') { polX.erase(polX.end()-1); }

			string polY = to_string(coord->getY());
			polY.erase( polY.find_last_not_of('0') + 1, std::string::npos);
			if (polY.back() == ',') { polY.erase(polY.end()-1); }

			string polZ = to_string(coord->getZ());
			polZ.erase( polZ.find_last_not_of('0') + 1, std::string::npos);
			if (polZ.back() == ',') { polZ.erase(polZ.end()-1); }

			string nomeNaLista = to_string(count) + ": (" + polX + "," + polY + "," + polZ + ")";
			addToListBox(Objeto3D_Coord_Listbox, nomeNaLista);
			count++;
			elementoLista = elementoLista->getProximo();
		}


	}

	//! Método que deleta a aresta selecionada na janela de criação de poligono.
	void deletarArestaObjeto3D() {
		listaArestas->retiraDaPosicao(getIndexElementoDeletado(Objeto3D_Aresta_Listbox));
		setObjeto3D_Aresta_Btn_DelSensitive(FALSE);
	}

	//! Método que retorna se a caixa de Preenchimento na criação de poligono esta marcada.
	/*!
		/return true se a caixa esta marcada.
	*/
	bool poligonoPreenchido() {
		return gtk_toggle_button_get_active((GtkToggleButton*) poligono_Preenchido);
	}

	//! Método que reinicia todos os valores da janela de novo elemento para seus valores iniciais.
	void resetarJanelaNovoElemento() {
		limparTextoNomeNovoElmnt();
		limparTextoNovoPonto();
		limparTextoNovaReta();
		limparTextoNovoPoligono();
		limparTextoNovaCurva();
		limparTextoNovoObjeto3D();
		setPoligono_Btn_DelSensitive(FALSE);
		setCurva_Btn_DelSensitive(FALSE);
		setObjeto3D_Coord_Btn_DelSensitive(FALSE);
		setObjeto3D_Aresta_Btn_DelSensitive(FALSE);
		gtk_toggle_button_set_active((GtkToggleButton*) poligono_Preenchido, FALSE);
		gtk_notebook_set_current_page(novoElmnt_Notebook, 0);
		free(listaCoordsPoligono);
		free(listaCoordsCurva);
		free(listaCoordsObjeto3D);
		free(listaArestas);
	}

	//! Método que reinicia a lista de coordenadas na janela de criação de poligono.
	void resetarListaCoordenadasPoligono() {
		listaCoordsPoligono = new ListaEnc<Coordenada3D*>();
	}

	//! Método que reinicia a lista de coordenadas na janela de criação de curvas.
	void resetarListaCoordenadasCurva() {
		listaCoordsCurva = new ListaEnc<Coordenada3D*>();
	}

	//! Método que reinicia a lista de coordenadas na janela de criação de Objetos3D.
	void resetarListaCoordenadasObjeto3D() {
		listaCoordsObjeto3D = new ListaEnc<Coordenada3D*>();
	}

	//! Método que reinicia a lista de aresta na janela de criação de Objetos3D.
	void resetarListaArestaObjeto3D() {
		listaArestas = new ListaEnc<ParCoord*>();
	}

	// ------------------------------------------------------------------------------------------------
	// Comandos Da Janela de Editar

	//! Método que limpa as caixas de texto de translação da janela de editar objeto.
	void limparTextoTranslacao() {
		gtk_entry_set_text(editElmnt_trans_X, "0");
		gtk_entry_set_text(editElmnt_trans_Y, "0");
		gtk_entry_set_text(editElmnt_trans_Z, "0");
	}

	//! Método que passa o foco do cursor para a caixa de Coordenada X na janela de translação.
	void focusTransX() {
		gtk_widget_grab_focus((GtkWidget*) editElmnt_trans_X);
	}

	//! Método que limpa as caixas de texto de escalonamento da janela de editar objeto.
	void limparTextoEscalonamento() {
		gtk_entry_set_text(editElmnt_escal_X, "1");
		gtk_entry_set_text(editElmnt_escal_Y, "1");
		gtk_entry_set_text(editElmnt_escal_Z, "1");
	}

	//! Método que passa o foco do cursor para a caixa de Coordenada X na janela de escalonamento.
	void focusEscalX() {
		gtk_widget_grab_focus((GtkWidget*) editElmnt_escal_X);
	}

	//! Método que limpa as caixas de texto de rotacao da janela de editar objeto.
	void limparTextoRotacao() {
		gtk_entry_set_text(editElmnt_rot_X, "0");
		gtk_entry_set_text(editElmnt_rot_Y, "0");
		gtk_entry_set_text(editElmnt_rot_Z, "0");
		gtk_entry_set_text(editElmnt_rot_angulo, "0");
		gtk_toggle_button_set_active((GtkToggleButton*) editElmnt_radio_0, TRUE);
		gtk_toggle_button_set_active((GtkToggleButton*) editElmnt_radio_1, FALSE);
		gtk_toggle_button_set_active((GtkToggleButton*) editElmnt_radio_2, FALSE);
		gtk_toggle_button_set_active((GtkToggleButton*) editElmnt_radio_eixo_0, TRUE);
		gtk_toggle_button_set_active((GtkToggleButton*) editElmnt_radio_eixo_1, FALSE);
		gtk_toggle_button_set_active((GtkToggleButton*) editElmnt_radio_eixo_2, FALSE);
	}

	//! Método que passa o foco do cursor para a caixa de valor do ângulo na janela de rotação.
	void focusRotAngulo() {
		gtk_widget_grab_focus((GtkWidget*) editElmnt_rot_angulo);
	}

	//! Método que restaura a janela de editar elementos ao seu estado original.
	void resetarJanelaEditElemento() {
		limparTextoTranslacao();
		limparTextoEscalonamento();
		limparTextoRotacao();
		gtk_notebook_set_current_page(editElmnt_Notebook, 0);
		focusTransX();
	}

	//! Metodo que retorna o tipo de transformação.
	/*!
		/return inteiro correspondendo a qual o tipo de transformação esta sendo aplicada.
	*/
	int getTipoTransformacao () {
		return gtk_notebook_get_current_page(editElmnt_Notebook);
	}

	//! Metodo que retorna o valor numérico contido na caixa de Translação em X.
	/*!
		/return a quantidade de translação em X.
	*/
	double getTransX() {
		try {
			return getFator(editElmnt_trans_X);
		} catch (int erro) {
			if (erro == -1) {
				//gtk_entry_set_text(editElmnt_trans_X, "0");
				throw -1;
			} else if (erro == -2) {
				return 0;
			}
		}
	}

	//! Metodo que retorna o valor numérico contido na caixa de Translação em Y.
	/*!
		/return a quantidade de translação em Y.
	*/
	double getTransY() {
		try {
			return getFator(editElmnt_trans_Y);
		} catch (int erro) {
			if (erro == -1) {
				//gtk_entry_set_text(editElmnt_trans_Y, "0");
				throw -1;
			} else if (erro == -2) {
				return 0;
			}
		}
	}

	//! Metodo que retorna o valor numérico contido na caixa de Translação em Z.
	/*!
		/return a quantidade de translação em Z.
	*/
	double getTransZ() {
		try {
			return getFator(editElmnt_trans_Z);
		} catch (int erro) {
			if (erro == -1) {
				//gtk_entry_set_text(editElmnt_trans_Z, "0");
				throw -1;
			} else if (erro == -2) {
				return 0;
			}
		}
	}

	//! Metodo que retorna o valor numérico contido na caixa de fator de Escala em X.
	/*!
		/return o fator de escala em X.
	*/
	double getEscalFatorX() {
		try {
			return getFator(editElmnt_escal_X);
		} catch (int erro) {
			if (erro == -1) {
				//gtk_entry_set_text(editElmnt_escal_X, "1");
				throw -1;
			} else if (erro == -2) {
				//gtk_entry_set_text(editElmnt_escal_X, "1");
				throw -2;
			}
		}
	}

	//! Metodo que retorna o valor numérico contido na caixa de fator de Escala em Y.
	/*!
		/return o fator de escala em Y.
	*/
	double getEscalFatorY() {
		try {
			return getFator(editElmnt_escal_Y);
		} catch (int erro) {
			if (erro == -1) {
				//gtk_entry_set_text(editElmnt_escal_Y, "1");
				throw -1;
			} else if (erro == -2) {
				//gtk_entry_set_text(editElmnt_escal_Y, "1");
				throw -2;
			}
		}
	}

	//! Metodo que retorna o valor numérico contido na caixa de fator de Escala em Z.
	/*!
		/return o fator de escala em Z.
	*/
	double getEscalFatorZ() {
		try {
			return getFator(editElmnt_escal_Z);
		} catch (int erro) {
			if (erro == -1) {
				//gtk_entry_set_text(editElmnt_escal_Z, "1");
				throw -1;
			} else if (erro == -2) {
				//gtk_entry_set_text(editElmnt_escal_Z, "1");
				throw -2;
			}
		}
	}

	//! Metodo que retorna o valor numérico contido na caixa de angulo de rotacao.
	/*!
		/return o angulo a ser rotacionado.
	*/
	double getRotAngulo() {
		try {
			return getFator(editElmnt_rot_angulo);
		} catch (int erro) {
			if (erro == -1) {
				//gtk_entry_set_text(editElmnt_rot_angulo, "1");
				throw -1;
			} else if (erro == -2) {
				//gtk_entry_set_text(editElmnt_rot_angulo, "1");
				throw -2;
			}
		}
	}

	//! Metodo que retorna o eixo de rotacao.
	/*!
		/return inteiro correspondendo à uma das três opções de eixo para a rotação (0 = X, 1 = Y, 2 = Z).
	*/
	int getEixoDeRotacao() {
		if (gtk_toggle_button_get_active((GtkToggleButton*) editElmnt_radio_eixo_0)) {
			return 0;
		} else if (gtk_toggle_button_get_active((GtkToggleButton*) editElmnt_radio_eixo_1)) {
			return 1;
		} else {
			return 2;
		}
	}

	//! Metodo que retorna a relatividade da rotacao.
	/*!
		/return inteiro correspondendo à uma das três opções de relatividade para a rotação.
	*/
	int getRelatividadeRotacao() {
		if (gtk_toggle_button_get_active((GtkToggleButton*) editElmnt_radio_0)) {
			return 0;
		} else if (gtk_toggle_button_get_active((GtkToggleButton*) editElmnt_radio_1)) {
			return 1;
		} else {
			return 2;
		}
	}

	//! Metodo que retorna o valor numérico contido na caixa de posição X na rotação relativa à um ponto.
	/*!
		/return a coordenada X desse ponto.
	*/
	double getRotRelativoAX() {
		try {
			return getFator(editElmnt_rot_X);
		} catch (int erro) {
			if (erro == -1) {
				//gtk_entry_set_text(editElmnt_rot_X, "1");
				throw -1;
			} else if (erro == -2) {
				return 0;
			}
		}
	}

	//! Metodo que retorna o valor numérico contido na caixa de posição Y na rotação relativa à um ponto.
	/*!
		/return a coordenada Y desse ponto.
	*/
	double getRotRelativoAY() {
		try {
			return getFator(editElmnt_rot_Y);
		} catch (int erro) {
			if (erro == -1) {
				//gtk_entry_set_text(editElmnt_rot_Y, "1");
				throw -1;
			} else if (erro == -2) {
				return 0;
			}
		}
	}

	//! Metodo que retorna o valor numérico contido na caixa de posição Z na rotação relativa à um ponto.
	/*!
		/return a coordenada Z desse ponto.
	*/
	double getRotRelativoAZ() {
		try {
			return getFator(editElmnt_rot_Z);
		} catch (int erro) {
			if (erro == -1) {
				//gtk_entry_set_text(editElmnt_rot_Z, "1");
				throw -1;
			} else if (erro == -2) {
				return 0;
			}
		}
	}

	//! Metodo que abre uma janela para escolher um arquivo.
	/*!
		/return O caminho para um arquivo.
	*/
	string selecionarArquivo() {
		string arquivo;
		GtkWidget *dialog;

		dialog = gtk_file_chooser_dialog_new ("Selecione um arquivo", window_Main, GTK_FILE_CHOOSER_ACTION_OPEN, "Cancelar", GTK_RESPONSE_CANCEL, "Selecionar", GTK_RESPONSE_ACCEPT, NULL);

		int res = gtk_dialog_run (GTK_DIALOG (dialog));
		if (res == GTK_RESPONSE_ACCEPT) {
			GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
			arquivo = gtk_file_chooser_get_filename (chooser);
		} else {
			throw -1;
		}

		gtk_widget_destroy (dialog);

		return arquivo;
	}

	//! Metodo que abre uma janela para salvar um arquivo.
	/*!
		/return O caminho para o arquivo que será salvo.
	*/
	string salvarArquivo() {
		string arquivo;
		GtkWidget *dialog;

		dialog = gtk_file_chooser_dialog_new ("Salvar arquivo", window_Main, GTK_FILE_CHOOSER_ACTION_SAVE, "Cancelar", GTK_RESPONSE_CANCEL, "Salvar", GTK_RESPONSE_ACCEPT, NULL);

		GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);

		gtk_file_chooser_set_do_overwrite_confirmation (chooser, TRUE);

		gtk_file_chooser_set_current_name (chooser, "NovoObjeto");

		int res = gtk_dialog_run (GTK_DIALOG (dialog));
		if (res == GTK_RESPONSE_ACCEPT) {
			arquivo = gtk_file_chooser_get_filename (chooser);
		} else {
			throw -1;
		}

		gtk_widget_destroy (dialog);

		return arquivo;
	}

};

#endif