#ifndef OBJETO3D_HPP
#define OBJETO3D_HPP

#include "model_ElementoGrafico.hpp"
#include "model_Coordenada.hpp"
#include "model_Aresta.hpp"
#include "ListaEnc.hpp"

class Objeto3D: public ElementoGrafico {

private:
	ListaEnc<Coordenada3D*> *listaCoordMundo; /*!< Lista encadeada de coordenadas do objeto3d no mundo.*/
	ListaEnc<Aresta*> *listaArestasMundo; /*!< Lista encadeada das arestas do objeto3d no mundo.*/

	ListaEnc<Coordenada3D*> *listaCoordNormal; /*!< Lista encadeada de coordenadas do objeto3d no mundo.*/
	ListaEnc<Aresta*> *listaArestasNormal; /*!< Lista encadeada das arestas do objeto3d no mundo.*/

public:
	//! Construtor
	Objeto3D() {
		listaCoordMundo = new ListaEnc<Coordenada3D*>();
		listaArestasMundo = new ListaEnc<Aresta*>();

		listaCoordNormal = new ListaEnc<Coordenada3D*>();
		listaArestasNormal = new ListaEnc<Aresta*>();

		setNome("");
		setTipo(OBJETO3D);
	}

	//! Construtor
	Objeto3D(string nome) {
		listaCoordMundo = new ListaEnc<Coordenada3D*>();
		listaArestasMundo = new ListaEnc<Aresta*>();

		listaCoordNormal = new ListaEnc<Coordenada3D*>();
		listaArestasNormal = new ListaEnc<Aresta*>();

		setNome(nome);
		setTipo(OBJETO3D);
	}

	//! Construtor
	Objeto3D(string nome, ListaEnc<Coordenada3D*>* listaCoord, ListaEnc<Aresta*>* listaAresta) {
		listaCoordMundo = listaCoord;
		listaArestasMundo = listaAresta;

		listaCoordNormal = new ListaEnc<Coordenada3D*>();
		listaArestasNormal = new ListaEnc<Aresta*>();

		setNome(nome);
		setTipo(OBJETO3D);
	}

	//! Método que modifica a lista de coordenadas do mundo do objeto3d
    /*!
        /param novaLista é a lista de coordenadas que substituirá a anterior.
    */
	void setListaCoordMundo(ListaEnc<Coordenada3D*> *novaLista) {
		listaCoordMundo = novaLista;
	}

	//! Método que adiciona novas coordenadas à lista de coordenadas do mundo do objeto3d
    /*!
        /param listaCoordsNovas é a lista de coordenadas que serão adicionadas.
    */
	void appendListaCoordMundo(ListaEnc<Coordenada3D*> *listaCoordsNovas) {
		Elemento<Coordenada3D*>* elemento = listaCoordsNovas->getHead();

		while(elemento != NULL) {
			listaCoordMundo->adiciona(elemento->getInfo());
			elemento = elemento->getProximo();
		}
	}

	//! Método que retorna a lista de coordenadas do mundo do objeto3d
    /*!
        /return uma lista encadeada das coordenadas do objeto3d.
    */
	ListaEnc<Coordenada3D*>* getListaCoordMundo() {
		return listaCoordMundo;
	}

	//! Método que modifica a lista de arestas do mundo do objeto3d
    /*!
        /param novaLista é a lista de arestas que substituirá a anterior.
    */
	void setListaArestaMundo(ListaEnc<Aresta*> *novaLista) {
		listaArestasMundo = novaLista;
	}

	//! Método que adiciona novas arestas à lista de arestas do mundo do objeto3d
    /*!
        /param listaArestasNovas é a lista de arestas que serão adicionadas.
    */
	void appendListaArestaMundo(ListaEnc<Aresta*> *listaArestasNovas) {
		Elemento<Aresta*>* elemento = listaArestasNovas->getHead();

		while(elemento != NULL) {
			listaArestasMundo->adiciona(elemento->getInfo());
			elemento = elemento->getProximo();
		}
	}

	//! Método que retorna a lista de arestas do mundo do objeto3d
    /*!
        /return uma lista encadeada das arestas do objeto3d.
    */
	ListaEnc<Aresta*>* getListaArestaMundo() {
		return listaArestasMundo;
	}

	//! Método que modifica a lista de coordenadas normais do objeto3d
    /*!
        /param novaLista é a lista de coordenadas que substituirá a anterior.
    */
	void setListaCoordNormal(ListaEnc<Coordenada3D*> *novaLista) {
		listaCoordNormal = novaLista;
	}

	//! Método que retorna a lista de coordenadas normais do objeto3d
    /*!
        /return uma lista encadeada das coordenadas do objeto3d.
    */
	ListaEnc<Coordenada3D*>* getListaCoordNormal() {
		return listaCoordNormal;
	}

	//! Método que modifica a lista de arestas com as coordenadas normais do objeto3d
    /*!
        /param novaLista é a lista de arestas que substituirá a anterior.
    */
	void setListaArestaNormal(ListaEnc<Aresta*> *novaLista) {
		listaArestasNormal = novaLista;
	}

	//! Método que retorna a lista de arestas com as coordenadas normais do objeto3d
    /*!
        /return uma lista encadeada das arestas do objeto3d.
    */
	ListaEnc<Aresta*>* getListaArestaNormal() {
		return listaArestasNormal;
	}

	//! Método que retorna o centro geométrico do polígono.
	/*!
		/return uma Coordenada que indica o centro geométrico do polígono.
	*/
	Coordenada3D* getCentroGeometrico() override{
		Coordenada3D* coord;

		if (listaCoordMundo->listaVazia()) {
			throw -1; // Se não há pontos no polígono
		} else {
			int n = 0;
			double somaX = 0, somaY = 0, somaZ = 0;
			Elemento<Coordenada3D*>* proxCoord = listaCoordMundo->getHead();

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