#ifndef DISPLAYFILE_HPP
#define DISPLAYFILE_HPP

#include "ListaEnc.hpp"
#include "model_ElementoGrafico.hpp"
#include "model_Ponto.hpp"
#include "model_Reta.hpp"
#include "model_Poligono.hpp"
#include "model_Curva.hpp"

class DisplayFile {
	
private:
	ListaEnc<ElementoGrafico*> *displayFile; /*!< Lista encadeada de Elementos Graficos representando a display file.*/
	
public:
	
	//! Construtor
	DisplayFile () {
		displayFile = new ListaEnc<ElementoGrafico*>();
	}
	
	//! Método que retorna o primeiro elemento do display file.
    /*!
        /return O primeiro elemento da lista encadeada do display file.
    */
	Elemento<ElementoGrafico*>* getHead() {
		return displayFile->getHead();
	}

	void insereElementoGrafico(ElementoGrafico* elemento) {
		displayFile->adiciona(elemento);
	}
	
	//! Método que insere um ponto no display file.
    /*!
        /param p o ponto a ser adicionado à display file.
    */
	void inserirNovoPonto(Ponto* p) {
		displayFile->adiciona(p);
	}

	//! Método que insere uma reta no display file.
    /*!
        /param r a reta a ser adicionada à display file.
    */
	void inserirNovaReta(Reta* r) {
		displayFile->adiciona(r);
	}

	//! Método que insere um poligono no display file.
    /*!
        /param pol o polinomio a ser adicionado à display file.
    */
	void inserirNovoPoligono(Poligono* pol) {
		displayFile->adiciona(pol);
	}

	//! Método que insere uma curva na display file.
    /*!
        /param c é a curva a ser adicionada à display file.
    */
	void inserirNovaCurva(Curva* c) {
		displayFile->adiciona(c);
	}
	
	//! Método que deleta um elemento da display file.
    /*!
		/param index é o indice onde o elemento que sera deletado se encontra.
    */
	void deletarElemento(int index) {
		displayFile->retiraDaPosicao(index);
	}

	//! Método que obtem um elemento da display file.
    /*!
		/param index é o indice onde o elemento que sera consultado se encontra.
		/return o elemento no indice.
    */
	ElementoGrafico* getElementoNoIndice(int index) {
		displayFile->elementoNoIndice(index);
	}
	
};

#endif