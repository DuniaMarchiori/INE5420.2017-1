#ifndef POLIGONO_HPP
#define POLIGONO_HPP

#include "model_ElementoGrafico.hpp"
#include "model_Coordenada.hpp"
#include "ListaEnc.hpp"

class Curva: public ElementoGrafico {

private:
	ListaEnc<Coordenada*> *listaMundo; /*!< Lista encadeada de coordenadas da curva no mundo.*/
	ListaEnc<Coordenada*> *listaNormal; /*!< Lista encadeada de coordenadas da curva normalizadas.*/

public:
	//! Construtor
	Curva() {
		listaMundo = new ListaEnc<Coordenada*>();
		listaNormal = new ListaEnc<Coordenada*>();
		setNome("");
		//setTipo(POLIGONO);
	}

	//! Construtor
	/*
		/param nome é o nome da curva
	*/
	Curva(string nome) {
		listaMundo = new ListaEnc<Coordenada*>();
		listaNormal = new ListaEnc<Coordenada*>();
		setNome(nome);
		//setTipo(POLIGONO);
	}

	//! Construtor
	/*
		/param nome é o nome da curva
		/param novaLista é a lista de coordenadas da curva
	*/
	Curva(string nome, ListaEnc<Coordenada*> *novaLista) {
		setListaMundo(novaLista);
		setNome(nome);
		//setTipo(POLIGONO);
	}

	// Coordenadas no Mundo.

	//! Método que adiciona coordenadas do mundo à curva
    /*!
        Adiciona coordenadas à lista de coordenadas
        /param p é a coordenada a ser adicionada.
    */
	void adicionarCoordenadaMundo(Coordenada* p) {
		listaMundo->adiciona(p);
	}

	//! Método que modifica a lista de coordenadas do mundo da curva
    /*!
        /param novaLista é a lista de coordenadas que substituirá a anterior.
    */
	void setListaMundo(ListaEnc<Coordenada*> *novaLista) {
		listaMundo = novaLista;
	}

	//! Método que retorna a lista de coordenadas do mundo da curva
    /*!
        /return uma lista encadeada das coordenadas da curva.
    */
	ListaEnc<Coordenada*>* getListaMundo() {
		return listaMundo;
	}

	// Coordenadas Normalizadas

	//! Método que adiciona coordenadas normalizadas à curva
    /*!
        Adiciona coordenadas à lista de coordenadas
        /param p é a coordenada a ser adicionada.
    */
	void adicionarCoordenadaNormal(Coordenada* p) {
		listaNormal->adiciona(p);
	}

	//! Método que modifica a lista de coordenadas normalizadas da curva
    /*!
        /param novaLista é a lista de coordenadas que substituirá a anterior.
    */
	void setListaNormal(ListaEnc<Coordenada*> *novaLista) {
		listaNormal = novaLista;
	}

	//! Método que retorna a lista de coordenadas normalizadas da curva
    /*!
        /return uma lista encadeada das coordenadas da curva.
    */
	ListaEnc<Coordenada*>* getListaNormal() {
		return listaNormal;
	}


	//! Método que retorna o centro geométrico da curva.
	/*!
		/return uma Coordenada que indica o centro geométrico da curva.
	*/
	Coordenada* getCentroGeometrico() override{
		Coordenada* coord;

		if (listaMundo->listaVazia()) {
			coord = new Coordenada(-1, -1); // Se não há pontos na curva
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

	//! Método que retorna os pontos da curva.
	/*!
		/param segmentos em quantos segmentos a curva sera dividida.
		/return uma lista de coordenadas
	*/
	virtual ListaEnc<Coordenada*>* getCurvaFinal(int segmentos) {}

};

#endif