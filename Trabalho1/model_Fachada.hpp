#ifndef FACHADA_HPP
#define FACHADA_HPP

#include "model_Coordenada.hpp"
#include "model_ElementoGrafico.hpp"
#include "model_DisplayFile.hpp"
#include "model_Window.hpp"
#include "model_Viewport.hpp"
#include "model_Tipo.hpp"
#include "model_Ponto.hpp"
#include "model_Reta.hpp"
#include "model_Poligono.hpp"
#include "model_Transformacao.hpp"

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

	void fazTransformacaoMundo(ElementoGrafico* elem, double** matrizResultado) {
		Tipo t = elem->getTipo();

		switch (t) {
			case PONTO:
				{
					Ponto* p = static_cast<Ponto*> (elem);
					Coordenada* nova = transformacao->transformaCoordenada(p->getCoordenadaMundo(), matrizResultado);
					p->setCoordenadaMundo(nova);
					break;
				}
			case RETA:
				{
					Reta* r = static_cast<Reta*> (elem);
					Coordenada* novaInicial = transformacao->transformaCoordenada(r->getCoordenadaMundoInicial(), matrizResultado);
					Coordenada* novaFinal = transformacao->transformaCoordenada(r->getCoordenadaMundoFinal(), matrizResultado);
					r->setCoordenadaMundoInicial(novaInicial);
					r->setCoordenadaMundoFinal(novaFinal);
					break;
				}
			case POLIGONO:
				{
					Poligono* p = static_cast<Poligono*> (elem);
					
					ListaEnc<Coordenada*>* listaCoord = p->getListaMundo();
					Elemento<Coordenada*>* proxCoord = listaCoord->getHead();
					ListaEnc<Coordenada*>* listaNovasCoord = new ListaEnc<Coordenada*>();

					while (proxCoord != NULL) {
						Coordenada* coordPol = proxCoord->getInfo();
						Coordenada* coordTransformada = transformacao->transformaCoordenada(coordPol, matrizResultado);
						listaNovasCoord->adiciona(coordTransformada);
						proxCoord = proxCoord->getProximo();
					}
					p->setListaMundo(listaNovasCoord);
					free(listaCoord);
					break;
				}
		}
	}

	void fazTransformacaoNormalizada(ElementoGrafico* elem, double** matrizResultado) {
		Tipo t = elem->getTipo();

		switch (t) {
			case PONTO:
				{
					Ponto* p = static_cast<Ponto*> (elem);
					Coordenada* nova = transformacao->transformaCoordenada(p->getCoordenadaMundo(), matrizResultado);
					p->setCoordenadaNormal(nova);
					break;
				}
			case RETA:
				{
					Reta* r = static_cast<Reta*> (elem);
					Coordenada* novaInicial = transformacao->transformaCoordenada(r->getCoordenadaMundoInicial(), matrizResultado);
					Coordenada* novaFinal = transformacao->transformaCoordenada(r->getCoordenadaMundoFinal(), matrizResultado);
					r->setCoordenadaNormalInicial(novaInicial);
					r->setCoordenadaNormalFinal(novaFinal);
					break;
				}
			case POLIGONO:
				{
					Poligono* p = static_cast<Poligono*> (elem);
					
					ListaEnc<Coordenada*>* listaCoord = p->getListaMundo();
					Elemento<Coordenada*>* proxCoord = listaCoord->getHead();
					ListaEnc<Coordenada*>* listaNovasCoord = new ListaEnc<Coordenada*>();

					while (proxCoord != NULL) {
						Coordenada* coordPol = proxCoord->getInfo();
						Coordenada* coordTransformada = transformacao->transformaCoordenada(coordPol, matrizResultado);
						listaNovasCoord->adiciona(coordTransformada);
						proxCoord = proxCoord->getProximo();
					}
					p->setListaNormal(listaNovasCoord);
					free(listaCoord);
					break;
				}
		}
	}

public:

	Fachada () {
		Coordenada* centroWindow = new Coordenada(0,0);
		window = new Window(centroWindow);
		viewport = new Viewport();
		displayFile = new DisplayFile();
		transformacao = new Transformacao();
	}
	
	void rotacionarWindow(double graus) {
		window->rotacionarWindow(graus);
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
		double** resultado = transformacao->novaMatrizTraslacao(coord->getX(), coord->getY());
		fazTransformacaoMundo(elem, resultado);
	}

	//! Método que realiza o escalonamento de um elemento grafico.
	/*!
        /param elem o elemento grafico que sera escalonado.
		/param fator uma coordenada contendo a quantidade de escalonamento que sera aplicada em X e Y.
    */
	void fazEscalonamento(ElementoGrafico* elem, Coordenada* fator) {
		Coordenada* centro = elem->getCentroGeometrico();
		// Traslada para a origem e escalona
		double** resultado = transformacao->multiplicarMatrizes3x3(transformacao->novaMatrizTraslacao(-(centro->getX()), -(centro->getY())), transformacao->novaMatrizEscalonamento(fator->getX(), fator->getY()));
		// Translada para o lugar de antes
		resultado = transformacao->multiplicarMatrizes3x3(resultado, transformacao->novaMatrizTraslacao(centro->getX(), centro->getY()));

		fazTransformacaoMundo(elem, resultado);
	}
	
	//! Método que realiza a rotação de um elemento grafico.
	/*!
        /param elem o elemento grafico que sera rotacionado.
		/param coord a rotação sera relativa a este ponto.
		/param angulo quantos graus o elemento sera rotacionado.
    */
	void fazRotacao(ElementoGrafico* elem, Coordenada* coord, double angulo) {
		// Traslada para o ponto arbitrário e rotaciona
		double** resultado = transformacao->multiplicarMatrizes3x3(transformacao->novaMatrizTraslacao(-(coord->getX()), -(coord->getY())), transformacao->novaMatrizRotacao(angulo));
		// Translada para o lugar de antes
		resultado = transformacao->multiplicarMatrizes3x3(resultado, transformacao->novaMatrizTraslacao(coord->getX(), coord->getY()));

		fazTransformacaoMundo(elem, resultado);		
	}

	void sistemaCoordenadasNormalizadas() {
		double angulo = -(0);
		Coordenada* fator = new Coordenada(1, 1);

		// Matriz de transformação
		// Traslada para o centro da window e rotaciona
		double** resultado = transformacao->multiplicarMatrizes3x3(transformacao->novaMatrizTraslacao(-(window->getCentro()->getX()), -(window->getCentro()->getY())), transformacao->novaMatrizRotacao(angulo));
		// Escalona
		resultado = transformacao->multiplicarMatrizes3x3(resultado, transformacao->novaMatrizEscalonamento(fator->getX(), fator->getY()));

		// Faz a transformação em todo o mundo
		Elemento<ElementoGrafico*>* elementoLista = displayFile->getHead();
		while (elementoLista != NULL) {
			fazTransformacaoNormalizada(elementoLista->getInfo(), resultado);
			elementoLista = elementoLista->getProximo();
		}
	}

	void sistemaCoordenadasNormalizadas(ElementoGrafico* elem) {
		double angulo = -(0);
		Coordenada* fator = new Coordenada(1, 1);

		// Matriz de transformação
		// Traslada para o centro da window e rotaciona
		double** resultado = transformacao->multiplicarMatrizes3x3(transformacao->novaMatrizTraslacao(-(window->getCentro()->getX()), -(window->getCentro()->getY())), transformacao->novaMatrizRotacao(angulo));
		// Escalona
		resultado = transformacao->multiplicarMatrizes3x3(resultado, transformacao->novaMatrizEscalonamento(fator->getX(), fator->getY()));

		fazTransformacaoNormalizada(elem, resultado);
	}
};

#endif