#ifndef DISPLAYFILE_HPP
#define DISPLAYFILE_HPP

#include "ListaEnc.hpp"
//#include "Coordenada.hpp"
#include "ElementoGrafico.hpp"

class DisplayFile {
	
private:

	ListaEnc<ElementoGrafico*> *displayFile; /*!< Lista encadeada de Elementos Graficos representando a display file.*/
	//GtkListBox* elmnt_List; /*!< Um GtkListBox para poder mostrar a display file ao usuário.*/
	
	//! Método que adiciona uma nova entrada na list box.
    /*!
        Adiciona uma nova entrada à list box que se pode interagir.
        /param nome É nome que será mostrado na list box.
    */
	/*void addToListBox(string nome) {
		GtkWidget* label = gtk_label_new(nome.c_str());
		gtk_container_add((GtkContainer*) elmnt_List, label);
		gtk_widget_show_all((GtkWidget*) elmnt_List);
	}*/
	
public:
	
	//! Construtor
	/*
		/param listBox É uma referência para a listBox que mostrará a display file.
	*/
	DisplayFile () {
		//elmnt_List = listBox;
		displayFile = new ListaEnc<ElementoGrafico*>();
	}
	
	//! Método que retorna o primeiro elemento do display file.
    /*!
        /return O primeiro elemento da lista encadeada do display file.
    */
	Elemento<ElementoGrafico*>* getHead() {
		return displayFile->getHead();
	}
	
	//! Método que insere um ponto no display file.
    /*!
		Verifica se o nome e as coordenadas são válidas e então cria um ponto tanto no display file quanto uma referência para ele na list box.
        /param nome O nome do novo ponto.
		/param coordX A coordenada em X desse ponto.
		/param coordY A coordenada em Y desse ponto.
		/return Um valor inteiro com o resultado da operação.
    */
	void inserirNovoPonto(Ponto* p) {
		// string nome, string coordX, string coordY
		/*if (!nomeValido(nome)) {
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

			Ponto *p = new Ponto(nome, c);*/
			// Adiciona objeto na display file
			displayFile->adiciona(p);
			//addToListBox(nome);
			/*return 1;
		} else {
			return -3;
		}*/
	}

	//! Método que insere uma reta no display file.
    /*!
		Verifica se o nome e as coordenadas são válidas e então cria uma reta tanto no display file quanto uma referência para ele na list box.
        /param nome O nome da nova reta.
		/param coordIniX A coordenada inicial em X dessa reta.
		/param coordIniY A coordenada inicial em Y dessa reta.
		/param coordFinX A coordenada final em X dessa reta.
		/param coordFinY A coordenada final em Y dessa reta.
		/return Um valor inteiro com o resultado da operação.
    */
	void inserirNovaReta(Reta* r) {
		// string nome, string coordIniX, string coordIniY, string coordFinX, string coordFinY
		/*if (!nomeValido(nome)) {
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

			Reta *r = new Reta(nome, cI, cF);*/
			// Adiciona objeto na display file
			displayFile->adiciona(r);
			//addToListBox(nome);
			/*return 1;
		} else {
			return -3;
		}*/
		
	}

	//! Método que insere um poligono no display file.
    /*!
		Verifica se o nome e as coordenadas são válidas e então cria um ponto tanto no display file quanto uma referência para ele na list box.
        /param nome O nome do novo ponto.
		/param listaCoordsPoligono Uma lista de coordenadas que contém todos os pontos do poligono.
		/return Um valor inteiro com o resultado da operação.
    */
	void inserirNovoPoligono(Poligono* pol) {
		// string nome, ListaEnc<Coordenada*>* listaCoordsPoligono
		/*if (!nomeValido(nome)) {
			return -1;
		}
		
		if ( !(listaCoordsPoligono->listaVazia()) ) {
			Poligono *pol = new Poligono(nome, listaCoordsPoligono);*/
			displayFile->adiciona(pol);
			//addToListBox(nome);
			/*return 1;
		} else {
			return -3;
		}*/
	}
	
	//! Método que deleta um elemento da display file.
    /*!
		Verifica qual objeto esta selecionado e o deleta tanto da display file quanto da list box.
    */
	void deletarElemento(int index) {
		/*GtkListBoxRow* row = gtk_list_box_get_selected_row (elmnt_List);
		if (row != NULL) {
			int index = gtk_list_box_row_get_index(row);
			gtk_container_remove((GtkContainer*) elmnt_List, (GtkWidget*) row);*/
			
			displayFile->retiraDaPosicao(index);
		//}
	}

	ElementoGrafico* getElementoNoIndice(int index) {
		displayFile->elementoNoIndice(index);
	}
	
	//! Método que imprime a display file. (Para testes)
    /*!
		Este metodo é somente para ser utilizado em testes.
    */
	/*void exibeDisplayFile() {
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
	}*/
};

#endif