#ifndef POLIGONO_HPP
#define POLIGONO_HPP

#include "ElementoGrafico.hpp"
#include "Ponto.hpp"
#include "ListaEnc.hpp"

class Poligono: public ElementoGrafico {
	
private:
	ListaEnc<Ponto*> *lista;
	
public:
	Poligono() {
		lista = new ListaEnc<Ponto*>;
		setTipo(POLIGONO);
	}
	
	void adicionarPonto(Ponto* p) {
		lista->adiciona(p);
	}
	
	ListaEnc<Ponto*>* getLista() {
		return lista;
	}
};

#endif