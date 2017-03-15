#ifndef DISPLAYFILE_HPP
#define DISPLAYFILE_HPP

#include<string>

#include "ListaEnc.hpp"
#include "Coordenada.hpp"
#include "ElementoGrafico.hpp"

using namespace std;

class DisplayFile {
	
private:
	ListaEnc<ElementoGrafico*> *displayFile;
	GtkListBox* elmnt_List;
	
	void addToListBox(string nome) {
		GtkWidget* label = gtk_label_new(nome.c_str());
		gtk_container_add((GtkContainer*) elmnt_List, label);
		gtk_widget_show_all((GtkWidget*) elmnt_List);
	}
	
	bool nomeValido(string nome){
		if ( !(nome.empty()) ) {	
			return true;
		} else {
			return false;
		}
	}
	
public:
	
	// Rever esse metodo, ele só existe por causa do update_surface, que deveria ir pro Desenhista.
	Elemento<ElementoGrafico*>* getHead() {
		return displayFile->getHead();
	}

	DisplayFile (GtkListBox* listBox) {
		elmnt_List = listBox;
		displayFile = new ListaEnc<ElementoGrafico*>();
	}
	
	int inserirNovoPonto(string nome, string coordX, string coordY) {
		if (!nomeValido(nome)) {
			return -1;
		}
		
		/// Se os campos de coordenada não estão em branco
		if ( !(coordX.empty()) && !(coordY.empty()) ) {
			// Cria novo objeto
			Coordenada* c = new Coordenada();
			
			// Verifica se os campos são números
			try {
				// stod = string to double
				c->setX(stod(coordX));
				c->setY(stod(coordY));
			} catch (...) {
				return -2;
			}

			Ponto *p = new Ponto(nome, c);
			// Adiciona objeto na display file
			displayFile->adiciona(p);
			addToListBox(nome);
			return 1;
		} else {
			return -3;
		}
	}

	int inserirNovaReta(string nome, string coordIniX, string coordIniY, string coordFinX, string coordFinY) {
		if (!nomeValido(nome)) {
			return -1;
		}

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
			} catch (...) {
				return -2;
			}

			Reta *r = new Reta(nome, cI, cF);
			// Adiciona objeto na display file
			displayFile->adiciona(r);
			addToListBox(nome);
			return 1;
		} else {
			return -3;
		}
		
	}

	int inserirNovoPoligono(string nome, ListaEnc<Coordenada*>* listaCoordsPoligono) {
		if (!nomeValido(nome)) {
			return -1;
		}
		
		if ( !(listaCoordsPoligono->listaVazia()) ) {
			Poligono *pol = new Poligono(nome, listaCoordsPoligono);
			displayFile->adiciona(pol);
			addToListBox(nome);
			listaCoordsPoligono = new ListaEnc<Coordenada*>();
			return 1;
		} else {
			return -3;
		}
	}

	/* Devido a parametros diferentes, deve-se usar os metodos especificos para adicionar elementos, o switch deve ser feito no botão de adicionar elemento
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
			console->inserirTexto("ERRO: não é possível inserir elemento sem nome.");
		}
	}
	*/
	
	void deletarElemento() {
		GtkListBoxRow* row = gtk_list_box_get_selected_row (elmnt_List);
		if (row != NULL) {
			int index = gtk_list_box_row_get_index(row);
			gtk_container_remove((GtkContainer*) elmnt_List, (GtkWidget*) row);
			
			displayFile->retiraDaPosicao(index);
		}
	}
	
	// Método para testes
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

	
};

#endif