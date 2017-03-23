#ifndef POLIGONO_HPP
#define POLIGONO_HPP

#include "model_ElementoGrafico.hpp"
#include "model_Coordenada.hpp"
#include "ListaEnc.hpp"

class Poligono: public ElementoGrafico {
	
private:
	ListaEnc<Coordenada*> *lista; /*!< Lista encadeada de coordenadas do polígono.*/
	
public:
	//! Construtor
	/*
		/param nome é o nome do polígono
	*/
	Poligono(string nome) {
		lista = new ListaEnc<Coordenada*>();
		setNome(nome);
		setTipo(POLIGONO);
	}

	//! Construtor
	/*
		/param nome é o nome do polígono
		/param novaLista é a lista de coordenadas do polígono
	*/
	Poligono(string nome, ListaEnc<Coordenada*> *novaLista) {
		setLista(novaLista);
		setNome(nome);
		setTipo(POLIGONO);
	}
	
	//! Método que adiciona coordenadas ao polígono
    /*!
        Adiciona coordenadas à lista de coordenadas
        /param p é a coordenada a ser adicionada.
    */
	void adicionarCoordenada(Coordenada* p) {
		lista->adiciona(p);
	}

	//! Método que modifica a lista de coordenadas do polígono
    /*!
        /param novaLista é a lista de coordenadas a ser adicionada.
    */
	void setLista(ListaEnc<Coordenada*> *novaLista) {
		lista = novaLista;
	}
	
	//! Método que retorna a lista de coordenadas do polígono
    /*!
        /return uma lista encadeada das coordenadas do polígono.
    */
	ListaEnc<Coordenada*>* getLista() {
		return lista;
	}

	//! Método que retorna o centro geométrico do polígono.
	/*!
		/return uma Coordenada que indica o centro geométrico do polígono.
	*/
	Coordenada* getCentroGeometrico() override{
		Coordenada* coord;

		if (lista->listaVazia()) {
			coord = new Coordenada(-1, -1); // Se não há pontos no polígono
		} else {
			int n = 0;
			double somaX = 0, somaY = 0;
			Elemento<Coordenada*>* proxCoord = lista->getHead(); 

			while (proxCoord != NULL) {
				++n;
				somaX += proxCoord->getInfo()->getX();
				somaY += proxCoord->getInfo()->getY();
				proxCoord = proxCoord->getProximo();
			}

			coord = new Coordenada( (somaX/n),(somaY/n) );
		}

		return coord;
	}
};

#endif