#ifndef POLIGONO_HPP
#define POLIGONO_HPP

#include "ElementoGrafico.hpp"
#include "Coordenada.hpp"
#include "ListaEnc.hpp"

class Poligono: public ElementoGrafico {
	
private:
	ListaEnc<Coordenada*> *lista;
	
public:
	Poligono() {
		lista = new ListaEnc<Coordenada*>;
		setTipo(POLIGONO);
	}
	
	void adicionarCoordenada(Coordenada* p) {
		lista->adiciona(p);
	}
	
	ListaEnc<Coordenada*>* getLista() {
		return lista;
	}
};

#endif