#ifndef SUPERFICIE_HPP
#define SUPERFICIE_HPP

#include "model_ElementoGrafico.hpp"
#include "model_Coordenada.hpp"
#include "model_Matriz.hpp"

class Superficie: public ElementoGrafico {

private:
	Matriz<Coordenada3D*>* pontosMundo; /*!< Pontos de controle no mundo*/
	Matriz<Coordenada3D*>* pontosNormais; /*!< Pontos de controle normalizados*/

public:
	//! Construtor
	Superficie() {
		pontosMundo = new Matriz<Coordenada3D*>(4, 4);
		pontosNormais = new Matriz<Coordenada3D*>(4, 4);
		setNome("");
		setTipo(SUPERFICIE);
	}

	//! Construtor
	/*
		/param nome é o nome da superfície
	*/
	Poligono(string nome) {
		pontosMundo = new Matriz<Coordenada3D*>(4, 4);
		pontosNormais = new Matriz<Coordenada3D*>(4, 4);
		setNome(nome);
		setTipo(SUPERFICIE);
	}

	//! Construtor
	/*
		/param nome é o nome da superfície
		/param pontosSuperficie é a matriz de pontos de controle da superfície
	*/
	Poligono(string nome, Matriz<Coordenada3D*>* pontosSuperficie) {
		setPontosMundo(pontosSup);
		pontosNormais = new Matriz<Coordenada3D*>(4, 4);
		setNome(nome);
		setTipo(SUPERFICIE);
	}

	// Coordenadas no Mundo.

	//! Método que modifica a matriz de coordenadas do mundo da superfície
    /*!
        /param pontosSuperficie é a matriz de coordenadas que substituirá a anterior.
    */
	void setPontosMundo(Matriz<Coordenada3D*>* pontosSuperficie) {
		pontosMundo = pontosSuperficie;
	}

	//! Método que retorna a matriz de coordenadas do mundo da superfície
    /*!
        /return uma matriz das coordenadas da superfície.
    */
	Matriz<Coordenada3D*>* getPontosMundo() {
		return pontosMundo;
	}

	// Coordenadas Normalizadas

	//! Método que modifica a matriz de coordenadas normais da superfície
    /*!
        /param novosPontos é a matriz de coordenadas que substituirá a anterior.
    */
	void setPontosNormais(Matriz<Coordenada3D*>* pontosSuperficie) {
		pontosNormais = pontosSuperficie;
	}

	//! Método que retorna a matriz de coordenadas normais da superfície
    /*!
        /return uma matriz das coordenadas da superfície.
    */
	Matriz<Coordenada3D*>* getPontosNormais() {
		return pontosNormais;
	}


	//! Método que retorna o centro geométrico da superfície.
	/*!
		/return uma Coordenada que indica o centro geométrico da superfície.
	*/
	Coordenada3D* getCentroGeometrico() override {
		Coordenada3D* coord;

		int n = pontosMundo->getNumLinhas() * pontosMundo->getNumColunas();
		double somaX = 0, somaY = 0, somaZ = 0;
		
		for (int i = 0; i < pontosMundo->getNumLinhas(); i++) {
			for (int j = 0; j < pontosMundo->getNumColunas(); j++) {
				Coordenada3D* coordAtual = pontosMundo->getValor(i, j);
				somaX += coordAtual->getX();
				somaY += coordAtual->getY();
				somaZ += coordAtual->getZ();
			}
		}

		coord = new Coordenada3D( (somaX/n), (somaY/n), (somaZ/n) );

		return coord;
	}
};

#endif