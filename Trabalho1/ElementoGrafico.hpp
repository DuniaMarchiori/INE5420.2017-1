#ifndef ELEMENTOGRAFICO_HPP
#define ELEMENTOGRAFICO_HPP

#include<string>
#include "Tipo.hpp"

using std::string;

class ElementoGrafico {
	
private:
	string nome;
	Tipo tipo;

public:
	string getNome() {
		return nome;
	}
	
	void setNome(string s) {
		nome = s;
	}
	
	Tipo getTipo() {
		return tipo;
	}
	
	void setTipo(Tipo t) {
		tipo = t;
	}
};

#endif