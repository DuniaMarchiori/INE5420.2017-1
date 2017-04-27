#ifndef FACHADA_HPP
#define FACHADA_HPP

#include <string>

#include "model_Matriz.hpp"
#include "model_WavefrontOBJ.hpp"
#include "model_Tipo.hpp"

#include "model_Coordenada.hpp"
#include "model_ElementoGrafico.hpp"

#include "model_Ponto.hpp"
#include "model_Reta.hpp"
#include "model_Poligono.hpp"
#include "model_Curva.hpp"
#include "model_CurvaBezier.hpp"
#include "model_CurvaBSpline.hpp"

#include "model_Window.hpp"
#include "model_DisplayFile.hpp"

#include "model_Viewport.hpp"
#include "model_Transformacao.hpp"
#include "model_Clipper.hpp"

class Fachada {

private:
	Window* window; /*!< É a window.*/
	Viewport* viewport; /*!< É a viewport.*/
	DisplayFile* displayFile; /*!< É a display file*/
	Transformacao* transformacao; /*!< É um objeto da classe Tranformacao*/
	Clipper* clipper; /*!< É um objeto da classe Clipper*/
	WavefrontOBJ* obj;

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

	//! Construtor
	Fachada () {
		Coordenada* centroWindow = new Coordenada(0,0);
		window = new Window(centroWindow, 100, 100);
		viewport = new Viewport();
		displayFile = new DisplayFile();
		transformacao = new Transformacao();
		clipper = new Clipper();
		obj = new WavefrontOBJ();
	}

	//! Método que rotaciona a window.
	/*!
        /param graus indica quantos graus a window deve rotacionar.
    */
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
        /param fator é o  quanto a janela deve dar zoom.
    */
	void zoom(double fator) {
		window->zoom(fator);
	}

	//! Método que clippa um ponto.
	/*!
        /param ponto O ponto que será clippado.
		/return o ponto clippado.
    */
	Ponto* clippingDePonto(Ponto* ponto) {
		return clipper->clippingDePonto(ponto);
	}

	//! Método que clippa uma reta com o algoritmo Cohen-Sutherland.
	/*!
        /param reta A reta que será clippada.
		/return a reta clippada.
    */
	Reta* clippingDeRetaCS(Reta* reta) {
		return clipper->clippingDeRetaCS(reta);
	}

	//! Método que clippa uma reta com o algoritmo Liang-Barsky.
	/*!
        /param reta A reta que será clippada.
		/return a reta clippada.
    */
	Reta* clippingDeRetaLB(Reta* reta) {
		return clipper->clippingDeRetaLB(reta);
	}
	
	//! Método que clippa um poligono.
	/*!
        /param poligono O poligono que será clippado.
		/return o poligono clippado.
    */
	Poligono* clippingDePoligono(Poligono* poligono) {
		return clipper->clippingDePoligono(poligono);
	}
	
	
	
	
	
	
	//! Método que clippa uma curva, com clipping de retas Cohen-Sutherland.
	/*!
        /param pontosCurva São os pontos que serão ligador para formar a curva.
		/return a lista de retas depois do clipping.
    */
	ListaEnc<Reta*>* clippingDeCurvaCS(ListaEnc<Coordenada*>* pontosCurva) {
		return clipper->clippingDeCurvaCS(pontosCurva);
	}
	
	//! Método que clippa uma curva, com clipping de retas Liang-Barsky.
	/*!
        /param pontosCurva São os pontos que serão ligador para formar a curva.
		/return a lista de retas depois do clipping.
    */
	ListaEnc<Reta*>* clippingDeCurvaLB(ListaEnc<Coordenada*>* pontosCurva) {
		return clipper->clippingDeCurvaLB(pontosCurva);
	}
	
	
	
	
	
	//! Método que realiza a transformada de viewport.
	/*!
        /param ponto uma coordenada do mundo que sera transformada.
        /param vpMax a coordenada vpMax da viewport.
		/return o ponto transformado.
    */
	Coordenada* transformaViewport(Coordenada* ponto, Coordenada* vpMax) {
		return viewport->transformaViewport(ponto, vpMax);
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
		/return retorna o ponto que foi inserido.
    */
	Ponto* inserirNovoPonto(string nome, string coordX, string coordY) {
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
			return p;
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
		/return retorna a reta que foi inserida.
    */
	Reta* inserirNovaReta(string nome, string coordIniX, string coordIniY, string coordFinX, string coordFinY) {
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
			return r;
		} else {
			throw -3;
		}
	}

	//! Método que insere um poligono no display file.
    /*!
		Verifica se o nome e as coordenadas são válidas e então cria um poligono tanto no display file quanto uma referência para ele na list box.
        /param nome O nome do novo poligono.
		/param listaCoordsPoligono Uma lista de coordenadas que contém todos os pontos do poligono.
		/param preenchido True caso o poligono deva ser preenchido.
		/return retorna o polígono que foi inserido.
    */
	Poligono* inserirNovoPoligono(string nome, ListaEnc<Coordenada*>* listaCoordsPoligono, bool preenchido) {
		if (!nomeValido(nome)) {
			throw -1;
		}

		if ( !(listaCoordsPoligono->listaVazia()) ) {
			Poligono *pol = new Poligono(nome, listaCoordsPoligono);
			pol->setPreenchido(preenchido);
			displayFile->inserirNovoPoligono(pol);
			return pol;
		} else {
			throw -3;
		}
	}

	//! Método que insere uma curva de Bézier na display file.
    /*!
		Verifica se o nome e as coordenadas são válidas.
        /param nome O nome da nova curva.
		/param listaCoordCurva Uma lista de coordenadas que contém todos os pontos da curva.
		/return retorna a curva que foi inserida.
    */
	CurvaBezier* inserirNovaCurvaBezier(string nome, ListaEnc<Coordenada*>* listaCoordCurva) {
		if (!nomeValido(nome)) {
			throw -1;
		}

		if ( (listaCoordCurva->getSize()%3 == 1) && listaCoordCurva->getSize() > 3) {
			CurvaBezier* cb = new CurvaBezier(nome, listaCoordCurva);
			displayFile->inserirNovaCurva(cb);
			return cb;
		} else {
			throw -3;
		}
	}
	
	//! Método que insere uma curva B-Spline na display file.
    /*!
		Verifica se o nome e as coordenadas são válidas.
        /param nome O nome da nova curva.
		/param listaCoordCurva Uma lista de coordenadas que contém todos os pontos da curva.
		/return retorna a curva que foi inserida.
    */
	CurvaBSpline* inserirNovaCurvaBSpline(string nome, ListaEnc<Coordenada*>* listaCoordCurva) {
		if (!nomeValido(nome)) {
			throw -1;
		}

		if ( listaCoordCurva->getSize() > 3) {
			CurvaBSpline* cb = new CurvaBSpline(nome, listaCoordCurva);
			displayFile->inserirNovaCurva(cb);
			return cb;
		} else {
			throw -3;
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
		transformacao->fazTranslacao(elem, coord);
	}

	//! Método que realiza o escalonamento de um elemento grafico.
	/*!
        /param elem o elemento grafico que sera escalonado.
		/param fator uma coordenada contendo a quantidade de escalonamento que sera aplicada em X e Y.
    */
	void fazEscalonamento(ElementoGrafico* elem, Coordenada* fator) {
		transformacao->fazEscalonamento(elem, fator);
	}

	//! Método que realiza a rotação de um elemento grafico.
	/*!
        /param elem o elemento grafico que sera rotacionado.
		/param coord a rotação sera relativa a este ponto.
		/param angulo quantos graus o elemento sera rotacionado.
    */
	void fazRotacao(ElementoGrafico* elem, Coordenada* coord, double angulo) {
		transformacao->fazRotacao(elem, coord, angulo);
	}

	//! Método que faz a tranformação de sistemas de coordenadas normalizadas em todo o mundo.
	void sistemaCoordenadasNormalizadas() {
		double angulo = window->getAngulo();
		Coordenada* fator = new Coordenada( (2/window->getLargura()), (2/window->getAltura()) );
		Matriz<double>* resultado = transformacao->matrizSistemaCoordenadasNormalizadas(angulo, fator, window->getCentro());

		// Faz a transformação em todo o mundo
		Elemento<ElementoGrafico*>* elementoLista = displayFile->getHead();
		while (elementoLista != NULL) {
			transformacao->fazTransformacaoNormalizada(elementoLista->getInfo(), resultado);
			elementoLista = elementoLista->getProximo();
		}

		free(fator);
		free(resultado);
	}

	//! Método que faz a tranformação de sistemas de coordenadas normalizadas em um elemento.
	/*!
		/param elem o elemento que será feita a transformação.
	*/
	void sistemaCoordenadasNormalizadas(ElementoGrafico* elem) {
		double angulo = window->getAngulo();
		Coordenada* fator = new Coordenada( (2/window->getLargura()), (2/window->getAltura()) );
		Matriz<double>* resultado = transformacao->matrizSistemaCoordenadasNormalizadas(angulo, fator, window->getCentro());

		transformacao->fazTransformacaoNormalizada(elem, resultado);

		free(fator);
		free(resultado);
	}
	
	//! Método que devolve a largura e altura da window.
	/*!
		/return coordenada com a altura e largura da window.
	*/
	Coordenada* getProporcoesWindow() {
		return new Coordenada(window->getLargura(), window->getAltura());
	}

	void salvaElementoParaOBJ(ElementoGrafico* elemento) {
		obj->criaNovoArquivo();
		obj->salvaVerticesNoArquivo(elemento);
		obj->salvaElementosNoArquivo();
	}

	void salvaMundoParaOBJ() {
		obj->criaNovoArquivo();
		Elemento<ElementoGrafico*>* elementoLista = displayFile->getHead();
		while (elementoLista != NULL) {
			obj->salvaVerticesNoArquivo(elementoLista->getInfo());
			elementoLista = elementoLista->getProximo();
		}
		obj->salvaElementosNoArquivo();
	}

	void carregaOBJ(std::string nomeArquivo) {
		ListaEnc<ElementoGrafico*>* lista = obj->carregarOBJ(nomeArquivo);
		displayFile->insereLista(lista);
	}
	
};

#endif
