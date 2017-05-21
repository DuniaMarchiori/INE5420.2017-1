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
	Superficie(string nome) {
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
	Superficie(string nome, Matriz<Coordenada3D*>* pontosSuperficie) {
		setPontosMundo(pontosSuperficie);
		pontosNormais = new Matriz<Coordenada3D*>(pontosSuperficie->getNumLinhas(), pontosSuperficie->getNumColunas());
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

	//! Método que retorna a distancia média dos pontos ao centro geométrico da superfície.
	/*!
		/return a distância média dos pontos até o centro da superfície
	*/
	double distanciaMediaDoCentro() {
		Coordenada3D* centro = getCentroGeometrico();

		double distMedia;
		double soma = 0;
		int n = pontosMundo->getNumLinhas() * pontosMundo->getNumColunas();

		for (int i = 0; i < pontosMundo->getNumLinhas(); i++) {
			for (int j = 0; j < pontosMundo->getNumColunas(); j++) {
				Coordenada3D* coordAtual = pontosMundo->getValor(i, j);
				soma += sqrt(pow((coordAtual->getX() - centro->getX()), 2) + pow((coordAtual->getY() - centro->getY()), 2) + pow((coordAtual->getZ() - centro->getZ()), 2));
			}
		}

		distMedia = soma / n;

		free(centro);
		return distMedia;
	}

	//! Método que retorna quantos retalhos há na superfície.
	/*!
		/return o número de retalhos da superfície.
	*/
	int getNumRetalhos() {
		int retalhosNaVertical = (pontosMundo->getNumLinhas() - 3);
		int retalhosNaHorizontal = (pontosMundo->getNumColunas() - 3);
		return (retalhosNaHorizontal * retalhosNaVertical);
	}

	//! Método que retorna um dos retalhos da superfície.
	/*!
		/param n O número do retalho desejado. (Começando por 0)
		/return O enésimo retalho.
	*/
	Matriz<Coordenada3D*>* getRetalhoN(int n) {
		if (n < 0 || n > getNumRetalhos()) {
			throw -1;
		}

		int linhaInicial = floor(n / (pontosMundo->getNumColunas() - 3));
		int colunaInicial = n % (pontosMundo->getNumColunas() - 3);

		Matriz<Coordenada3D*>* retalho = new Matriz<Coordenada3D*>(4,4);

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				Coordenada3D* coordIJRetalho = pontosNormais->getValor((linhaInicial + i), (colunaInicial + j));
				retalho->setValor(i, j, coordIJRetalho);
			}
		}

		return retalho;
	}

	//! Método que retorna uma lista de listas de coordenadas.
	/*!
		/param numSegmentosT O número de segmentos em t
		/param numSegmentosS O número de segmentos em s
		/return uma lista de listas das coordenadas de cada curva.
	*/
	ListaEnc<ListaEnc<Coordenada3D*>*>* getListaCoords(int numSegmentosT, int numSegmentosS) {
		double passoT = 1.0/(double)numSegmentosT;
		double passoS = 1.0/(double)numSegmentosS;

		// Imagino que o que a gente obtenha seja:
		// Uma lista (A) de listas (B) de coordenadas. No caso, cada lista "B" de coordenadas são os pontos que devem ser ligados em retas de cada curva e a lista "A" são diversas listas pois existem diversas curvas.

		// Tu vai precisar iterar por cada retalho eu acho, aí ja fiz um método que conta quantos retalhos tem, e outro que te devolve o retalho N, aí da pra fazer um "for" e ir percorrendo cada retalho. (getNumRetalhos() e getRetalhoN())
		// Um detalhe: O método que retorna o retalho N retorna o retalho N da matriz normalizada, não sei se é esse que precisa, se precisar do outro só mudar. a linha 155
	}
};

#endif