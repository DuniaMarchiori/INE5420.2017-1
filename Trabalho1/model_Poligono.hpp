#ifndef POLIGONO_HPP
#define POLIGONO_HPP

#include "model_ElementoGrafico.hpp"
#include "model_Coordenada.hpp"
#include "ListaEnc.hpp"

class Poligono: public ElementoGrafico {

private:
	ListaEnc<Coordenada3D*> *listaMundo; /*!< Lista encadeada de coordenadas do polígono no mundo.*/
	ListaEnc<Coordenada3D*> *listaNormal; /*!< Lista encadeada de coordenadas do polígono normalizadas.*/
	bool preenchido; /*!< Valor que indica se este poligono é preenchido ou não.*/

public:
	//! Construtor
	Poligono() {
		listaMundo = new ListaEnc<Coordenada3D*>();
		listaNormal = new ListaEnc<Coordenada3D*>();
		preenchido = false;
		setNome("");
		setTipo(POLIGONO);
	}

	//! Construtor
	/*
		/param nome é o nome do polígono
	*/
	Poligono(string nome) {
		listaMundo = new ListaEnc<Coordenada3D*>();
		listaNormal = new ListaEnc<Coordenada3D*>();
		preenchido = false;
		setNome(nome);
		setTipo(POLIGONO);
	}

	//! Construtor
	/*
		/param nome é o nome do polígono
		/param novaLista é a lista de coordenadas do polígono
	*/
	Poligono(string nome, ListaEnc<Coordenada3D*> *novaLista) {
		setListaMundo(novaLista);
		preenchido = false;
		setNome(nome);
		setTipo(POLIGONO);
	}

	// Coordenadas no Mundo.


	//! Método que adiciona coordenadas do mundo ao polígono
    /*!
        Adiciona coordenadas à lista de coordenadas
        /param p é a coordenada a ser adicionada.
    */
	void adicionarCoordenadaMundo(Coordenada3D* p) {
		listaMundo->adiciona(p);
	}

	//! Método que modifica a lista de coordenadas do mundo do polígono
    /*!
        /param novaLista é a lista de coordenadas que substituirá a anterior.
    */
	void setListaMundo(ListaEnc<Coordenada3D*> *novaLista) {
		listaMundo = novaLista;
	}

	//! Método que retorna a lista de coordenadas do mundo do polígono
    /*!
        /return uma lista encadeada das coordenadas do polígono.
    */
	ListaEnc<Coordenada3D*>* getListaMundo() {
		return listaMundo;
	}

	//! Método que modifica a propriedade de preenchimento do poligono.
    /*!
        /param _preenchido deve ser true caso o poligono deva passar a ser preenchido.
    */
	void setPreenchido(bool _preenchido) {
		preenchido = _preenchido;
	}

	//! Método que retorna a propriedade de preenchimento do poligono.
    /*!
        /return true caso o poligono deva ser preenchido.
    */
	bool getPreenchido() {
		return preenchido;
	}

	// Coordenadas Normalizadas

	//! Método que adiciona coordenadas normalizadas ao polígono
    /*!
        Adiciona coordenadas à lista de coordenadas
        /param p é a coordenada a ser adicionada.
    */
	void adicionarCoordenadaNormal(Coordenada3D* p) {
		listaNormal->adiciona(p);
	}

	//! Método que modifica a lista de coordenadas normalizadas do polígono
    /*!
        /param novaLista é a lista de coordenadas que substituirá a anterior.
    */
	void setListaNormal(ListaEnc<Coordenada3D*> *novaLista) {
		listaNormal = novaLista;
	}

	//! Método que retorna a lista de coordenadas normalizadas do polígono
    /*!
        /return uma lista encadeada das coordenadas do polígono.
    */
	ListaEnc<Coordenada3D*>* getListaNormal() {
		return listaNormal;
	}


	//! Método que retorna o centro geométrico do polígono.
	/*!
		/return uma Coordenada que indica o centro geométrico do polígono.
	*/
	Coordenada3D* getCentroGeometrico() override{
		Coordenada3D* coord;

		if (listaMundo->listaVazia()) {
			coord = new Coordenada3D(-1, -1, -1); // Se não há pontos no polígono
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
};

#endif