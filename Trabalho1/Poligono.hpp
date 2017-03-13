#ifndef POLIGONO_HPP
#define POLIGONO_HPP

#include "ElementoGrafico.hpp"
#include "Coordenada.hpp"
#include "ListaEnc.hpp"

class Poligono: public ElementoGrafico {
	
private:
	ListaEnc<Coordenada*> *lista; /*!< Lista encadeada de coordenadas do polígono.*/
	
public:
	//! Construtor
	Poligono(string nome) {
		lista = new ListaEnc<Coordenada*>();
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
	
	//! Método que retorna a lista de coordenadas do polígono
    /*!
        /return uma lista encadeada das coordenadas do polígono.
    */
	ListaEnc<Coordenada*>* getLista() {
		return lista;
	}
};

#endif