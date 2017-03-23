#ifndef ELEMENTOGRAFICO_HPP
#define ELEMENTOGRAFICO_HPP

#include<string>
#include "model_Tipo.hpp"
//#include "Coordenada.hpp"

using std::string;

class ElementoGrafico {
	
private:
	string nome; /*!< Nome do elemento*/
	Tipo tipo; /*!< Tipo do elemento*/

public:
	//! Método que retorna o nome do elemento.
	/*!
		/return uma string que representa o nome do elemento.
	*/
	string getNome() {
		return nome;
	}
	
	//! Método que altera o nome do elemento.
	/*!
		/param s é uma string que representa o nome do elemento.
	*/
	void setNome(string s) {
		nome = s;
	}
	
	//! Método que retorna o tipo do elemento.
	/*!
		/return um Tipo que indica o tipo do elemento.
	*/
	Tipo getTipo() {
		return tipo;
	}
	
	//! Método que altera o tipo do elemento.
	/*!
		/param t é uma variável Tipo que representa o tipo do elemento.
	*/
	void setTipo(Tipo t) {
		tipo = t;
	}

	//! Método que retorna o centro geométrico do elemento.
	/*!
		/return uma Coordenada que indica o centro geométrico do elemento.
	*/
	virtual Coordenada* getCentroGeometrico() {}

};

#endif