#ifndef CURVA_HPP
#define CURVA_HPP

#include "model_ElementoGrafico.hpp"
#include "model_Coordenada.hpp"
#include "ListaEnc.hpp"
#include <math.h>

class Curva: public ElementoGrafico {

protected:
	ListaEnc<Coordenada3D*> *listaMundo; /*!< Lista encadeada de coordenadas da curva no mundo.*/
	ListaEnc<Coordenada3D*> *listaNormal; /*!< Lista encadeada de coordenadas da curva normalizadas.*/

public:
	//! Construtor
	Curva() {
		listaMundo = new ListaEnc<Coordenada3D*>();
		listaNormal = new ListaEnc<Coordenada3D*>();
		setNome("");
		setTipo(CURVA);
	}

	//! Construtor
	/*
		/param nome é o nome da curva
	*/
	Curva(string nome) {
		listaMundo = new ListaEnc<Coordenada3D*>();
		listaNormal = new ListaEnc<Coordenada3D*>();
		setNome(nome);
		setTipo(CURVA);
	}

	//! Construtor
	/*
		/param nome é o nome da curva
		/param novaLista é a lista de coordenadas da curva
	*/
	Curva(string nome, ListaEnc<Coordenada3D*> *novaLista) {
		setListaMundo(novaLista);
		setNome(nome);
		setTipo(CURVA);
	}

	// Coordenadas no Mundo.

	//! Método que adiciona coordenadas do mundo à curva
    /*!
        Adiciona coordenadas à lista de coordenadas
        /param p é a coordenada a ser adicionada.
    */
	void adicionarCoordenadaMundo(Coordenada3D* p) {
		listaMundo->adiciona(p);
	}

	//! Método que modifica a lista de coordenadas do mundo da curva
    /*!
        /param novaLista é a lista de coordenadas que substituirá a anterior.
    */
	void setListaMundo(ListaEnc<Coordenada3D*> *novaLista) {
		listaMundo = novaLista;
	}

	//! Método que retorna a lista de coordenadas do mundo da curva
    /*!
        /return uma lista encadeada das coordenadas da curva.
    */
	ListaEnc<Coordenada3D*>* getListaMundo() {
		return listaMundo;
	}

	// Coordenadas Normalizadas

	//! Método que adiciona coordenadas normalizadas à curva
    /*!
        Adiciona coordenadas à lista de coordenadas
        /param p é a coordenada a ser adicionada.
    */
	void adicionarCoordenadaNormal(Coordenada3D* p) {
		listaNormal->adiciona(p);
	}

	//! Método que modifica a lista de coordenadas normalizadas da curva
    /*!
        /param novaLista é a lista de coordenadas que substituirá a anterior.
    */
	void setListaNormal(ListaEnc<Coordenada3D*> *novaLista) {
		listaNormal = novaLista;
	}

	//! Método que retorna a lista de coordenadas normalizadas da curva
    /*!
        /return uma lista encadeada das coordenadas da curva.
    */
	ListaEnc<Coordenada3D*>* getListaNormal() {
		return listaNormal;
	}

	//! Método que retorna o centro geométrico da curva.
	/*!
		/return uma Coordenada que indica o centro geométrico da curva.
	*/
	Coordenada3D* getCentroGeometrico() override{
		Coordenada3D* coord;

		if (listaMundo->listaVazia()) {
			coord = new Coordenada3D(-1, -1, -1); // Se não há pontos na curva
		} else {
			int n = 0;
			double somaX = 0, somaY = 0, somaZ = 0;
			Elemento<Coordenada3D*>* proxCoord = listaMundo->getHead();

			while (proxCoord != NULL) {
				n++;
				somaX += proxCoord->getInfo()->getX();
				somaY += proxCoord->getInfo()->getY();
				somaZ += proxCoord->getInfo()->getZ();
				proxCoord = proxCoord->getProximo();
			}

			coord = new Coordenada3D( (somaX/n), (somaY/n), (somaZ/n) );
		}

		return coord;
	}

	//! Método que retorna a distancia média dos pontos ao centro geométrico da curva.
	/*!
		/return a distância média dos pontos até o centro da curva
	*/
	double distanciaMediaDoCentro() {
		Coordenada3D* centro = getCentroGeometrico();

		double distMedia;
		double soma = 0;
		int n = 0;

		Elemento<Coordenada3D*>* proxCoord = listaMundo->getHead();

		while (proxCoord != NULL) {
			Coordenada3D* coordAtual = proxCoord->getInfo();
			soma += sqrt(pow((coordAtual->getX() - centro->getX()), 2) + pow((coordAtual->getY() - centro->getY()), 2) + pow((coordAtual->getZ() - centro->getZ()), 2));
			n++;

			proxCoord = proxCoord->getProximo();
		}

		distMedia = soma / n;

		free(centro);
		return distMedia;
	}






	//! Método que retorna os pontos da curva.
	/*!
		/param segmentos em quantos segmentos a curva sera dividida.
		/return uma lista de coordenadas
	*/
	virtual ListaEnc<Coordenada3D*>* getCurvaFinal(int segmentos) {}

};

#endif