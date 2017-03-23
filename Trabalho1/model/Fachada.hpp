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
	
	//! Método que manda a window se mover.
	/*!
        /param fatX O quanto a janela deve se mover em X.
        /param fatY O quanto a janela deve se mover em Y.
    */
	void moverWindow(double fatX, double fatY) {
		window->moverWindow(fatX, fatY);
	}

	//! Método que manda a window executar um zoom.
	/*!
        /param fator O quanto a janela deve dar zoom.
    */
	void zoom(double fator) {
		window->zoom(fator);
	}

	//! Método que realiza a transformada de viewport.
	/*!
        /param ponto uma coordenada do mundo que sera transformada.
        /param vpMax a coordenada vpMax da viewport.
		/return o ponto transformado.
    */
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
			return 1;
		} else {
			return -3;
		}
	}

	//! Método que deleta um elemento da display file.
	/*!
        /param index a posicao do elemento a ser deletado.
    */
	void deletarElemento(int index) {
		displayFile->deletarElemento(index);
	}

	//! Método que obtem um elemento da display file.
	/*!
        /param index a posicao do elemento a ser consultado.
		/return o elemento da display file na posicao especificada.
    */
	ElementoGrafico* getElementoNoIndice(int index) {
		displayFile->getElementoNoIndice(index);
	}
	
	//! Método que realiza a translação em um elemento grafico.
	/*!
        /param elem o elemento grafico que sera transladado.
		/param coord uma coordenada contendo a quantidade de translação que sera aplicada em X e Y.
    */
	void fazTranslacao(ElementoGrafico* elem, Coordenada* coord) {
		Tipo t = elem->getTipo();

		switch (t) {
			case PONTO:
				{
					Ponto* p = static_cast<Ponto*> (elem);
					Coordenada* nova = transformacao->transformaCoordenada(p->getCoordenada(), transformacao->novaMatrizTraslacao(coord->getX(), coord->getY()));
					p->setCoordenada(nova);
					break;
				}
			case RETA:
				{
					Reta* r = static_cast<Reta*> (elem);
					Coordenada* novaInicial = transformacao->transformaCoordenada(r->getPontoInicial(), transformacao->novaMatrizTraslacao(coord->getX(), coord->getY()));
					Coordenada* novaFinal = transformacao->transformaCoordenada(r->getPontoFinal(), transformacao->novaMatrizTraslacao(coord->getX(), coord->getY()));
					r->setPontoInicial(novaInicial);
					r->setPontoFinal(novaFinal);
					break;
				}
			case POLIGONO:
				{
					Poligono* p = static_cast<Poligono*> (elem);
					
					ListaEnc<Coordenada*>* listaCoord = p->getLista();
					Elemento<Coordenada*>* proxCoord = listaCoord->getHead();
					ListaEnc<Coordenada*>* listaNovasCoord = new ListaEnc<Coordenada*>();

					while (proxCoord != NULL) {
						Coordenada* coordPol = proxCoord->getInfo();
						Coordenada* coordTransformada = transformacao->transformaCoordenada(coordPol, transformacao->novaMatrizTraslacao(coord->getX(), coord->getY()));
						listaNovasCoord->adiciona(coordTransformada);
						proxCoord = proxCoord->getProximo();
					}
					p->setLista(listaNovasCoord);
					free(listaCoord);
					break;
				}
		}
	}

	//! Método que realiza o escalonamento de um elemento grafico.
	/*!
        /param elem o elemento grafico que sera escalonado.
		/param fator uma coordenada contendo a quantidade de escalonamento que sera aplicada em X e Y.
    */
	void fazEscalonamento(ElementoGrafico* elem, Coordenada* fator) {
		Tipo t = elem->getTipo();
		Coordenada* centro = elem->getCentroGeometrico();
		// Traslada para a origem e escalona
		double** resultado = transformacao->multiplicarMatrizes3x3(transformacao->novaMatrizTraslacao(-(centro->getX()), -(centro->getY())), transformacao->novaMatrizEscalonamento(fator->getX(), fator->getY()));
		// Translada para o lugar de antes
		resultado = transformacao->multiplicarMatrizes3x3(resultado, transformacao->novaMatrizTraslacao(centro->getX(), centro->getY()));

		switch (t) {
			case PONTO:
				{
					Ponto* p = static_cast<Ponto*> (elem);
					Coordenada* nova = transformacao->transformaCoordenada(p->getCoordenada(), resultado);
					p->setCoordenada(nova);
					break;
				}
			case RETA:
				{
					Reta* r = static_cast<Reta*> (elem);
					Coordenada* novaInicial = transformacao->transformaCoordenada(r->getPontoInicial(), resultado);
					Coordenada* novaFinal = transformacao->transformaCoordenada(r->getPontoFinal(), resultado);
					r->setPontoInicial(novaInicial);
					r->setPontoFinal(novaFinal);
					break;
				}
			case POLIGONO:
				{
					Poligono* p = static_cast<Poligono*> (elem);
					
					ListaEnc<Coordenada*>* listaCoord = p->getLista();
					Elemento<Coordenada*>* proxCoord = listaCoord->getHead();
					ListaEnc<Coordenada*>* listaNovasCoord = new ListaEnc<Coordenada*>();

					while (proxCoord != NULL) {
						Coordenada* coordPol = proxCoord->getInfo();
						Coordenada* coordTransformada = transformacao->transformaCoordenada(coordPol, resultado);
						listaNovasCoord->adiciona(coordTransformada);
						proxCoord = proxCoord->getProximo();
					}
					p->setLista(listaNovasCoord);
					free(listaCoord);
					break;
				}
		}
	}
	
	//! Método que realiza a rotação de um elemento grafico.
	/*!
        /param elem o elemento grafico que sera rotacionado.
		/param coord a rotação sera relativa a este ponto.
		/param angulo quantos graus o elemento sera rotacionado.
    */
	void fazRotacao(ElementoGrafico* elem, Coordenada* coord, double angulo) {
		Tipo t = elem->getTipo();
		// Traslada para o ponto arbitrário e rotaciona
		double** resultado = transformacao->multiplicarMatrizes3x3(transformacao->novaMatrizTraslacao(-(coord->getX()), -(coord->getY())), transformacao->novaMatrizRotacao(angulo));
		// Translada para o lugar de antes
		resultado = transformacao->multiplicarMatrizes3x3(resultado, transformacao->novaMatrizTraslacao(coord->getX(), coord->getY()));

		switch (t) {
			case PONTO:
				{
					Ponto* p = static_cast<Ponto*> (elem);
					Coordenada* nova = transformacao->transformaCoordenada(p->getCoordenada(), resultado);
					p->setCoordenada(nova);
					break;
				}
			case RETA:
				{
					Reta* r = static_cast<Reta*> (elem);
					Coordenada* novaInicial = transformacao->transformaCoordenada(r->getPontoInicial(), resultado);
					Coordenada* novaFinal = transformacao->transformaCoordenada(r->getPontoFinal(), resultado);
					r->setPontoInicial(novaInicial);
					r->setPontoFinal(novaFinal);
					break;
				}
			case POLIGONO:
				{
					Poligono* p = static_cast<Poligono*> (elem);
					
					ListaEnc<Coordenada*>* listaCoord = p->getLista();
					Elemento<Coordenada*>* proxCoord = listaCoord->getHead();
					ListaEnc<Coordenada*>* listaNovasCoord = new ListaEnc<Coordenada*>();

					while (proxCoord != NULL) {
						Coordenada* coordPol = proxCoord->getInfo();
						Coordenada* coordTransformada = transformacao->transformaCoordenada(coordPol, resultado);
						listaNovasCoord->adiciona(coordTransformada);
						proxCoord = proxCoord->getProximo();
					}
					p->setLista(listaNovasCoord);
					free(listaCoord);
					break;
				}
		}
	}
};

#endif