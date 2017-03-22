#ifndef FACHADA_HPP
#define FACHADA_HPP

#include "Coordenada.hpp"
#include "ElementoGrafico.hpp"
#include "DisplayFile.hpp"
#include "Window.hpp"
#include "Viewport.hpp"
#include "Tipo.hpp"
#include "Ponto.hpp"
#include "Reta.hpp"
#include "Poligono.hpp"
#include "Transformacao.hpp"

class Fachada {

private:
	Window* window;
	Viewport* viewport;
	DisplayFile* displayFile;
	Transformacao* transformacao;

	//! Método que verifica a validade de um nome.
    /*!
        Verifica se um nome é valido para um Elemento Grafico.
        /param nome É nome que será validado.
		/return Retorna true se o nome é valido.
    */
	bool nomeValido(string nome){
		if ( !(nome.empty()) ) {	
			return true;
		} else {
			return false;
		}
	}

public:

	Fachada () {
		Coordenada* windowInfEsq = new Coordenada(0,0);
		Coordenada* windowSupDir = new Coordenada(200,200);
		window = new Window(windowInfEsq, windowSupDir);
		viewport = new Viewport();
		displayFile = new DisplayFile();
		transformacao = new Transformacao();
	}

	void moverWindow(double fatX, double fatY) {
		window->moverWindow(fatX, fatY);
	}

	void zoom(double fator) {
		window->zoom(fator);
	}

	Coordenada* transformaViewport(Coordenada* ponto, Coordenada* vpMax) {
		return viewport->transformaViewport(ponto, window, vpMax);
	}

	//! Método que retorna o primeiro elemento do display file.
    /*!
        /return O primeiro elemento da lista encadeada do display file.
    */
	Elemento<ElementoGrafico*>* getHeadDisplayFile() {
		return displayFile->getHead();
	}

	//! Método que insere um ponto no display file.
    /*!
		Verifica se o nome e as coordenadas são válidas e então cria um ponto tanto no display file quanto uma referência para ele na list box.
        /param nome O nome do novo ponto.
		/param coordX A coordenada em X desse ponto.
		/param coordY A coordenada em Y desse ponto.
		/return Um valor inteiro com o resultado da operação.
    */
	void inserirNovoPonto(string nome, string coordX, string coordY) {
		if (!nomeValido(nome)) {
			throw -1;
		}
		
		// Se os campos de coordenada não estão em branco
		if ( !(coordX.empty()) && !(coordY.empty()) ) {
			// Cria novo objeto
			Coordenada* c = new Coordenada();
			
			// Verifica se os campos são números
			try {
				// stod = string to double
				c->setX(stod(coordX));
				c->setY(stod(coordY));
			} catch (...) {
				throw -2;
			}

			Ponto *p = new Ponto(nome, c);
			// Adiciona objeto na display file
			displayFile->inserirNovoPonto(p);
			//addToListBox(nome);
		} else {
			throw -3;
		}
	}

	//! Método que insere uma reta no display file.
    /*!
		Verifica se o nome e as coordenadas são válidas e então cria uma reta tanto no display file quanto uma referência para ele na list box.
        /param nome O nome da nova reta.
		/param coordIniX A coordenada inicial em X dessa reta.
		/param coordIniY A coordenada inicial em Y dessa reta.
		/param coordFinX A coordenada final em X dessa reta.
		/param coordFinY A coordenada final em Y dessa reta.
		/return Um valor inteiro com o resultado da operação.
    */
	void inserirNovaReta(string nome, string coordIniX, string coordIniY, string coordFinX, string coordFinY) {
		if (!nomeValido(nome)) {
			throw -1;
		}

		// Se os campos de coordenada não estão em branco
		if ( !(coordIniX.empty()) && !(coordIniY.empty()) && !(coordFinX.empty()) && !(coordFinY.empty()) ) { 
			// Cria novo objeto
			Coordenada* cI = new Coordenada();
			Coordenada* cF = new Coordenada();

			// Verifica se os campos são números
			try {
				// stod = string to double
				cI->setX(stod(coordIniX));
				cI->setY(stod(coordIniY));

				cF->setX(stod(coordFinX));
				cF->setY(stod(coordFinY));
			} catch (...) {
				throw -2;
			}

			Reta *r = new Reta(nome, cI, cF);
			// Adiciona objeto na display file
			displayFile->inserirNovaReta(r);
			//addToListBox(nome);
		} else {
			throw -3;
		}
	}

	//! Método que insere um poligono no display file.
    /*!
		Verifica se o nome e as coordenadas são válidas e então cria um ponto tanto no display file quanto uma referência para ele na list box.
        /param nome O nome do novo ponto.
		/param listaCoordsPoligono Uma lista de coordenadas que contém todos os pontos do poligono.
		/return Um valor inteiro com o resultado da operação.
    */
	int inserirNovoPoligono(string nome, ListaEnc<Coordenada*>* listaCoordsPoligono) {
		if (!nomeValido(nome)) {
			return -1;
		}
		
		if ( !(listaCoordsPoligono->listaVazia()) ) {
			Poligono *pol = new Poligono(nome, listaCoordsPoligono);
			displayFile->inserirNovoPoligono(pol);
			//addToListBox(nome);
			return 1;
		} else {
			return -3;
		}
	}

	void deletarElemento(int index) {
		displayFile->deletarElemento(index);
	}
	
	/*Coordenada* transformaCoordenada(Coordenada* coord, double matriz) {
		transformacao->transformaCoordenada(coord, matriz);
	}

	double multiplicarMatrizes3x3(double matriz1, double matriz2) {
		transformacao->multiplicarMatrizes3x3(matriz1, matriz2);
	}

	double novaMatrizTraslacao(double Dx, double Dy) {
		transformacao->novaMatrizTraslacao(Dx, Dy);
	}

	double novaMatrizEscalonamento(double Sx, double Sy) {
		transformacao->novaMatrizEscalonamento(Sx, Sy);
	}

	double novaMatrizRotacao(double angulo) {
		transformacao->novaMatrizRotacao(angulo);
	}*/
	void fazTranslacao(ElementoGrafico* elem, Coordenada* coord) {
		Tipo t = elem->getTipo();

		switch (t) {
			case PONTO:
				{
					Ponto* p = static_cast<Ponto*> (elem);
					Coordenada* novaC = transformacao->transformaCoordenada(p->getCoordenada(), transformacao->novaMatrizTraslacao(coord->getX(), coord->getY()));
					p->setCoordenada(novaC);
					break;
				}
		}
	}
};

#endif