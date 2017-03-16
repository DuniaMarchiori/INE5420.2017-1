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