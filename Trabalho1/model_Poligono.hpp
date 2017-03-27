#ifndef POLIGONO_HPP
#define POLIGONO_HPP

#include "model_ElementoGrafico.hpp"
#include "model_Coordenada.hpp"
#include "ListaEnc.hpp"

class Poligono: public ElementoGrafico {

private:
	ListaEnc<Coordenada*> *listaMundo; /*!< Lista encadeada de coordenadas do polígono no mundo.*/
	ListaEnc<Coordenada*> *listaNormal; /*!< Lista encadeada de coordenadas do polígono normalizadas.*/

public:
	//! Construtor
	/*
		/param nome é o nome do polígono
	*/
	Poligono(string nome) {
		listaMundo = new ListaEnc<Coordenada*>();
		listaNormal = new ListaEnc<Coordenada*>();
		setNome(nome);
		setTipo(POLIGONO);
	}

	//! Construtor
	/*
		/param nome é o nome do polígono
		/param novaLista é a lista de coordenadas do polígono
	*/
	Poligono(string nome, ListaEnc<Coordenada*> *novaLista) {
		setListaMundo(novaLista);
		setNome(nome);
		setTipo(POLIGONO);
	}

	// Coordenadas no Mundo.


	//! Método que adiciona coordenadas do mundo ao polígono
    /*!
        Adiciona coordenadas à lista de coordenadas
        /param p é a coordenada a ser adicionada.
    */
	void adicionarCoordenadaMundo(Coordenada* p) {
		listaMundo->adiciona(p);
	}

	//! Método que modifica a lista de coordenadas do mundo do polígono
    /*!
        /param novaLista é a lista de coordenadas que substituirá a anterior.
    */
	void setListaMundo(ListaEnc<Coordenada*> *novaLista) {
		listaMundo = novaLista;
	}

	//! Método que retorna a lista de coordenadas do mundo do polígono
    /*!
        /return uma lista encadeada das coordenadas do polígono.
    */
	ListaEnc<Coordenada*>* getListaMundo() {
		return listaMundo;
	}

	// Coordenadas Normalizadas

	//! Método que adiciona coordenadas normalizadas ao polígono
    /*!
        Adiciona coordenadas à lista de coordenadas
        /param p é a coordenada a ser adicionada.
    */
	void adicionarCoordenadaNormal(Coordenada* p) {
		listaNormal->adiciona(p);
	}

	//! Método que modifica a lista de coordenadas normalizadas do polígono
    /*!
        /param novaLista é a lista de coordenadas que substituirá a anterior.
    */
	void setListaNormal(ListaEnc<Coordenada*> *novaLista) {
		listaNormal = novaLista;
	}

	//! Método que retorna a lista de coordenadas normalizadas do polígono
    /*!
        /return uma lista encadeada das coordenadas do polígono.
    */
	ListaEnc<Coordenada*>* getListaNormal() {
		return listaNormal;
	}


	//! Método que retorna o centro geométrico do polígono.
	/*!
		/return uma Coordenada que indica o centro geométrico do polígono.
	*/
	Coordenada* getCentroGeometrico() override{
		Coordenada* coord;

		if (listaMundo->listaVazia()) {
			coord = new Coordenada(-1, -1); // Se não há pontos no polígono
		} else {
			int n = 0;
			double somaX = 0, somaY = 0;
			Elemento<Coordenada*>* proxCoord = listaMundo->getHead();

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