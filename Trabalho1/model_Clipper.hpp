#include "model_Ponto.hpp"
#include "model_Reta.hpp"
#include "model_Poligono.hpp"

#ifndef CLIPPER_HPP
#define CLIPPER_HPP

class Clipper {

private:
	// Métodos auxiliares do CS

	//! Método que obtem o Region Code de uma dada coordenada.
	/*!
        /param coord A coordenada que se deseja saber o region code.
		/return um array de inteiros contendo o region code.
    */
	int* obterRegionCode(Coordenada* coord) {
		int* RC = new int[4];
		for (int i = 0; i < 4; i++) {
			RC[i] = 0;
		}

		if (coord->getX() < -1) {
			RC[3] = 1;
		} else if (coord->getX() > 1) {
			RC[2] = 1;
		}

		if (coord->getY() < -1) {
			RC[1] = 1;
		} else if (coord->getY() > 1) {
			RC[0] = 1;
		}

		return RC;
	}

	//! Método que diz se o AND logico entre duas region codes é 0000
	/*!
        /param RC1 Uma das Region Codes a ser comparada.
        /param RC2 A outra das Region Codes a ser comparada.
		/return true caso o AND logico entre elas seja 0000.
    */
	bool andLogicoRegionCodeZerado(int* RC1, int* RC2) {
		bool eZero = true;

		for (int i = 0; i < 4; i++) {
			if (RC1[i] == 1 && RC2[i] == 1){
				eZero = false;
			}
		}

		return eZero;
	}

	//! Método que diz se duas Region Codes são iguais.
	/*!
        /param RC1 Uma das Region Codes a ser comparada.
        /param RC2 A outra das Region Codes a ser comparada.
		/return true caso as duas sejam iguais.
    */
	bool comparaRegionCode(int* RC1, int* RC2) {
		bool eIgual = true;

		for (int i = 0; i < 4; i++) {
			if (RC1[i] != RC2[i]){
				eIgual = false;
			}
		}

		return eIgual;
	}

	//! Método auxiliar para o algoritmo de clipping de reta C-S.
	/*!
        /param RC a Region Code de uma das extremidades da reta.
        /param coord a coordenada da extremidade da reta.
        /param m é o coeficiente angular da reta.
		/return a coordenada clippada da extremidade da reta.
    */
	Coordenada* auxiliarCSClipping (int* RC, Coordenada* coord, double m) {
		Coordenada* novoPonto;
		bool xCalculado = false;
		bool yCalculado = false;
		double x = 0;
		double y = 0;
		double x2, y2;

		if (RC[0] == 1) {
			// Calcular Xtopo
			// x = x1 + 1/m . (yT - y1)
			x = coord->getX() + (1/m) * (1 - coord->getY());
			y2 = 1;
			xCalculado = true;
		} else if (RC[1] == 1) {
			// Calcular Xfundo
			// x = x1 + 1/m . (yF - y1)
			x = coord->getX() + (1/m) * ((-1) - coord->getY());
			y2 = -1;
			xCalculado = true;
		}

		if (RC[2] == 1) {
			// Calcular Ydir
			// y = m * (xD - x1) + y1
			y = m * (1 - coord->getX()) + coord->getY();
			x2 = 1;
			yCalculado = true;
		} else if (RC[3] == 1) {
			// Calcular Yesq
			// y = m * (xE - x1) + y1
			y = m * ((-1) - coord->getX()) + coord->getY();
			x2 = -1;
			yCalculado = true;
		}

		if (xCalculado != yCalculado) {
			if (xCalculado == true && x >= -1 && x <= 1) {
				novoPonto = new Coordenada(x, y2);
				return novoPonto;
			} else if (yCalculado == true && y >= -1 && y <= 1) {
				novoPonto = new Coordenada(x2, y);
				return novoPonto;
			} else {
				return NULL;
			}
		} else if (xCalculado && yCalculado) {
			if (x >= -1 && x <= 1) {
				novoPonto = new Coordenada(x, y2);
				return novoPonto;
			} else if (y >= -1 && y <= 1) {
				novoPonto = new Coordenada(x2, y);
				return novoPonto;
			}
		}
	}

	//! Método auxiliar para obter o valor maximo entre 3 variáveis.
	/*!
        /param a valor a ser comparado.
        /param b valor a ser comparado.
        /param c valor a ser comparado.
		/return o maior valor dentre eles.
    */
	double maximo (double a, double b, double c) {
		double max = (a < b) ? b : a;
		return ( (max < c) ? c : max );
	}

	//! Método auxiliar para obter o valor minimo entre 3 variáveis.
	/*!
        /param a valor a ser comparado.
        /param b valor a ser comparado.
        /param c valor a ser comparado.
		/return o menor valor dentre eles.
    */
	double minimo (double a, double b, double c) {
		double min = (a < b) ? a : b;
		return ( (min < c) ? min : c );
	}

	//! Método auxiliar para obter o clipping de um poligono nos eixos verticais.
	/*!
        /param coordAnterior A coordenada do ponto anterior ao ponto sendo analisado.
        /param coordAtual A coordenada sendo analisada.
        /param anteriorDentro valor booleano indicando se a coordenada anterior ao ponto analisado esta dentro ou fora da região.
        /param atualDentro valor booleano indicando se a coordenada do ponto sendo analisado esta dentro ou fora da região.
		/param limite variavel indicando qual o limite da window esta sendo analisado (-1 ou 1).
		/param poligonoClippado ponteiro para o poligono que esta sendo construido nesta clippagem.
    */
	void auxClippingPoligonoVertical(Coordenada* coordAnterior, Coordenada* coordAtual, bool anteriorDentro, bool atualDentro, double limite, Poligono* poligonoClippado) {
		if (anteriorDentro && atualDentro) {
			// Se a coordenada veio de dentro para dentro.
			// 	Ele se adiciona ao novo poligono.
			Coordenada* novaCoordenada = new Coordenada(coordAtual);
			poligonoClippado->adicionarCoordenadaNormal(novaCoordenada);
		} else if (anteriorDentro && !atualDentro){
			// Se a coordenada veio de dentro para fora.
			// 	Ela se altera baseado na reta formada entre ela e a coordenada anterior.
			Coordenada* novaCoordenada;

			// y – y0 = m (x – x0)
			// y = m (x - x0) + y0
			double m = (coordAtual->getY() - coordAnterior->getY()) / (coordAtual->getX() - coordAnterior->getX());
			double y = m * (limite - coordAtual->getX()) + coordAtual->getY();

			novaCoordenada = new Coordenada(limite, y);
			poligonoClippado->adicionarCoordenadaNormal(novaCoordenada);

		} else if (!anteriorDentro && atualDentro){
			// Se a coordenada veio de fora para dentro.
			// 	Ela cria uma nova coordenada baseado na reta formada entre ela e a coordenada anterior.
			// 	E então se adiciona ao poligono final.
			Coordenada* novaCoordenada;

			// y – y0 = m (x – x0)
			// y = m (x - x0) + y0
			double m = (coordAtual->getY() - coordAnterior->getY()) / (coordAtual->getX() - coordAnterior->getX());
			double y = m * (limite - coordAtual->getX()) + coordAtual->getY();

			novaCoordenada = new Coordenada(limite, y);
			poligonoClippado->adicionarCoordenadaNormal(novaCoordenada);
			novaCoordenada = new Coordenada(coordAtual);
			poligonoClippado->adicionarCoordenadaNormal(novaCoordenada);

		} // Se for de fora pra fora, a coordenada simplesmente é ignorada.
	}

	//! Método que realiza o clipping de poligonos na borda esquerda da window.
	/*!
        /param poligonoAClipar ponteiro para o poligono que sera clippado.
		/return o poligono clipado na borda esquerda da window.
    */
	Poligono* clippaPoligonoEsq(Poligono* poligonoAClipar) {
		Poligono* poligonoClippado = new Poligono();

		Elemento<Coordenada*>* elementoAtual = poligonoAClipar->getListaNormal()->getHead();
		Coordenada* coordAtual;

		Coordenada* coordAnterior = poligonoAClipar->getListaNormal()->getUltimoElemento()->getInfo();

		while (elementoAtual != NULL) {
			coordAtual = elementoAtual->getInfo();

			bool anteriorDentro = (coordAnterior->getX() >= -1);
			bool atualDentro = (coordAtual->getX() >= -1);

			auxClippingPoligonoVertical(anteriorDentro, atualDentro, -1, poligonoClippado, coordAnterior, coordAtual);

			coordAnterior = elementoAtual->getInfo();
			elementoAtual = elementoAtual->getProximo();
		}

		return poligonoClippado;
	}

	//! Método que realiza o clipping de poligonos na borda direita da window.
	/*!
        /param poligonoAClipar ponteiro para o poligono que sera clippado.
		/return o poligono clipado na borda direita da window.
    */
	Poligono* clippaPoligonoDir(Poligono* poligonoAClipar) {
		Poligono* poligonoClippado = new Poligono();

		Elemento<Coordenada*>* elementoAtual = poligonoAClipar->getListaNormal()->getHead();
		Coordenada* coordAtual;

		Coordenada* coordAnterior = poligonoAClipar->getListaNormal()->getUltimoElemento()->getInfo();

		while (elementoAtual != NULL) {
			coordAtual = elementoAtual->getInfo();

			bool anteriorDentro = (coordAnterior->getX() <= 1);
			bool atualDentro = (coordAtual->getX() <= 1);

			auxClippingPoligonoVertical(anteriorDentro, atualDentro, 1, poligonoClippado, coordAnterior, coordAtual);

			coordAnterior = elementoAtual->getInfo();
			elementoAtual = elementoAtual->getProximo();
		}

		return poligonoClippado;
	}

	//! Método auxiliar para obter o clipping de um poligono nos eixos horizontais.
	/*!
        /param coordAnterior A coordenada do ponto anterior ao ponto sendo analisado.
        /param coordAtual A coordenada sendo analisada.
        /param anteriorDentro valor booleano indicando se a coordenada anterior ao ponto analisado esta dentro ou fora da região.
        /param atualDentro valor booleano indicando se a coordenada do ponto sendo analisado esta dentro ou fora da região.
		/param limite variavel indicando qual o limite da window esta sendo analisado (-1 ou 1).
		/param poligonoClippado ponteiro para o poligono que esta sendo construido nesta clippagem.
    */
	void auxClippingPoligonoHorizontal(bool anteriorDentro, bool atualDentro, double limite, Poligono* poligonoClippado, Coordenada* coordAnterior, Coordenada* coordAtual) {
		if (anteriorDentro && atualDentro) {
			// Se a coordenada veio de dentro para dentro.
			// 	Ele se adiciona ao novo poligono.
			Coordenada* novaCoordenada = new Coordenada(coordAtual);
			poligonoClippado->adicionarCoordenadaNormal(novaCoordenada);
		} else if (anteriorDentro && !atualDentro){
			// Se a coordenada veio de dentro para fora.
			// 	Ela se altera baseado na reta formada entre ela e a coordenada anterior.
			Coordenada* novaCoordenada;

			// y – y0 = m (x – x0)
			// x = (y - y0) / m + x0
			double m = (coordAtual->getY() - coordAnterior->getY()) / (coordAtual->getX() - coordAnterior->getX());
			double x = ((limite - coordAtual->getY()) / m) + coordAtual->getX();

			novaCoordenada = new Coordenada(x, limite);
			poligonoClippado->adicionarCoordenadaNormal(novaCoordenada);

		} else if (!anteriorDentro && atualDentro){
			// Se a coordenada veio de fora para dentro.
			// 	Ela cria uma nova coordenada baseado na reta formada entre ela e a coordenada anterior.
			// 	E então se adiciona ao poligono final.
			Coordenada* novaCoordenada;

			// y – y0 = m (x – x0)
			// x = (y - y0) / m + x0
			double m = (coordAtual->getY() - coordAnterior->getY()) / (coordAtual->getX() - coordAnterior->getX());
			double x = ((limite - coordAtual->getY()) / m) + coordAtual->getX();

			novaCoordenada = new Coordenada(x, limite);
			poligonoClippado->adicionarCoordenadaNormal(novaCoordenada);
			novaCoordenada = new Coordenada(coordAtual);
			poligonoClippado->adicionarCoordenadaNormal(novaCoordenada);

		} // Se for de fora pra fora, a coordenada simplesmente é ignorada.
	}

	//! Método que realiza o clipping de poligonos na borda inferior da window.
	/*!
        /param poligonoAClipar ponteiro para o poligono que sera clippado.
		/return o poligono clipado na borda inferior da window.
    */
	Poligono* clippaPoligonoBaixo(Poligono* poligonoAClipar) {
		Poligono* poligonoClippado = new Poligono();

		Elemento<Coordenada*>* elementoAtual = poligonoAClipar->getListaNormal()->getHead();
		Coordenada* coordAtual;

		Coordenada* coordAnterior = poligonoAClipar->getListaNormal()->getUltimoElemento()->getInfo();

		while (elementoAtual != NULL) {
			coordAtual = elementoAtual->getInfo();

			bool anteriorDentro = (coordAnterior->getY() >= -1);
			bool atualDentro = (coordAtual->getY() >= -1);

			auxClippingPoligonoHorizontal(anteriorDentro, atualDentro, -1, poligonoClippado, coordAnterior, coordAtual);

			coordAnterior = elementoAtual->getInfo();
			elementoAtual = elementoAtual->getProximo();
		}

		return poligonoClippado;
	}

	//! Método que realiza o clipping de poligonos na borda superior da window.
	/*!
        /param poligonoAClipar ponteiro para o poligono que sera clippado.
		/return o poligono clipado na borda superior da window.
    */
	Poligono* clippaPoligonoCima(Poligono* poligonoAClipar) {
		Poligono* poligonoClippado = new Poligono();

		Elemento<Coordenada*>* elementoAtual = poligonoAClipar->getListaNormal()->getHead();
		Coordenada* coordAtual;

		Coordenada* coordAnterior = poligonoAClipar->getListaNormal()->getUltimoElemento()->getInfo();

		while (elementoAtual != NULL) {
			coordAtual = elementoAtual->getInfo();

			bool anteriorDentro = (coordAnterior->getY() <= 1);
			bool atualDentro = (coordAtual->getY() <= 1);

			auxClippingPoligonoHorizontal(anteriorDentro, atualDentro, 1, poligonoClippado, coordAnterior, coordAtual);

			coordAnterior = elementoAtual->getInfo();
			elementoAtual = elementoAtual->getProximo();
		}

		return poligonoClippado;
	}

public:
	//! Método que clippa um ponto.
	/*!
        /param ponto O ponto que será clippado.
		/return o ponto clippado.
    */
	Ponto* clippingDePonto(Ponto* ponto) {
		if (ponto->getCoordenadaNormal()->getX() < -1 || ponto->getCoordenadaNormal()->getX() > 1 || ponto->getCoordenadaNormal()->getY() < -1 || ponto->getCoordenadaNormal()->getY() > 1) {
			return NULL;
		}
		return ponto; // Ponto está dentro da window
	}

	//! Método que clippa uma reta com o algoritmo Cohen-Sutherland.
	/*!
        /param reta A reta que será clippada.
		/return a reta clippada.
    */
	Reta* clippingDeRetaCS(Reta* reta) {
		Reta* retaClippada;
		Coordenada* P1 = reta->getCoordenadaNormalInicial();
		Coordenada* P2 = reta->getCoordenadaNormalFinal();

		int* RCZero = new int[4];
		for (int i = 0; i < 4; i++) {
			RCZero[i] = 0;
		}

		int* RC1 = obterRegionCode(P1);
		int* RC2 = obterRegionCode(P2);

		if (comparaRegionCode(RC1, RC2) && comparaRegionCode(RC1, RCZero) ) {
			// Reta esta completamente contida na window.
			retaClippada = new Reta();
			retaClippada->setCoordenadaNormalInicial(new Coordenada(P1));
			retaClippada->setCoordenadaNormalFinal(new Coordenada(P2));
			return retaClippada;
		} else if (!andLogicoRegionCodeZerado(RC1, RC2)) {
			// Reta esta completamente fora da window.
			return NULL;
		} else {
			double m = (P2->getY() - P1->getY()) / (P2->getX() - P1->getX());
			Coordenada* novoP1 = NULL;
			Coordenada* novoP2 = NULL;

			if (comparaRegionCode(RC1, RCZero)) {
				novoP1 = new Coordenada(P1->getX(), P1->getY());
			} else {
				novoP1 = auxiliarCSClipping(RC1, P1, m);
			}

			if (comparaRegionCode(RC2, RCZero)) {
				novoP2 = new Coordenada(P2->getX(), P2->getY());
			} else {
				novoP2 = auxiliarCSClipping(RC2, P2, m);
			}

			if (novoP1 == NULL || novoP2 == NULL) {
				return NULL;
			} else {
				retaClippada = new Reta();
				retaClippada->setCoordenadaNormalInicial(novoP1);
				retaClippada->setCoordenadaNormalFinal(novoP2);

				return retaClippada;
			}
		}
	}

	//! Método que clippa uma reta com o algoritmo Liang-Barsky.
	/*!
        /param reta A reta que será clippada.
		/return a reta clippada.
    */

	Reta* clippingDeRetaLB(Reta* reta) {
		Reta* retaClippada;
		double p1, p2, p3, p4, q1, q2, q3, q4;
		double r1max = 0, r2max = 0, r1min = 1, r2min = 1, z1 = 0, z2 = 0;

		Coordenada* ini = reta->getCoordenadaNormalInicial();
		Coordenada* fin = reta->getCoordenadaNormalFinal();

		p1 = -(fin->getX() - ini->getX());
		p2 = fin->getX() - ini->getX();
		p3 = -(fin->getY() - ini->getY());
		p4 = fin->getY() - ini->getY();

		q1 = ini->getX() - (-1);
		q2 = 1 - ini->getX();
		q3 = ini->getY() - (-1);
		q4 = 1 - ini->getY();

		if ((p1 == 0 && q1 < 0) || (p2 == 0 && q2 < 0) || (p3 == 0 && q3 < 0) || (p4 == 0 && q4 < 0)) {
			return NULL;
		}

		if (p1 < 0) {
			r1max = q1/p1;

		} else if (p2 < 0) {
			r1max = q2/p2;

		}

		if (p3 < 0) {
			r2max = q3/p3;

		} else if (p4 < 0) {
			r2max = q4/p4;

		}

		if (p1 > 0){
			r1min = q1/p1;

		} else if (p2 > 0) {
			r1min = q2/p2;

		}

		if (p3 > 0) {
			r2min = q3/p3;

		} else if (p4 > 0) {
			r2min = q4/p4;

		}

		z1 = maximo(0.0, r1max, r2max);
		z2 = minimo(1.0, r1min, r2min);
		Coordenada* novoP1 = NULL;
		Coordenada* novoP2 = NULL;

		if (z1 > z2) { // A linha está completamente fora
			return NULL;
		}

		// A linha está total ou parcialmente visível
		if (z1 != 0) {
			novoP1 = new Coordenada( (ini->getX() + z1 * p2), (ini->getY() + z1 * p4) );

		} else {
			novoP1 = new Coordenada(ini->getX(), ini->getY());
		}

		if (z2 != 1) {
			novoP2 = new Coordenada( (ini->getX() + z2 * p2), (ini->getY() + z2 * p4) );

		} else {
			novoP2 = new Coordenada(fin->getX(), fin->getY());
		}

		retaClippada = new Reta();
		retaClippada->setCoordenadaNormalInicial(novoP1);
		retaClippada->setCoordenadaNormalFinal(novoP2);
		return retaClippada;
	}



	//! Método que clippa um poligono.
	/*!
        /param poligono O poligono que será clippado.
		/return o poligono clippado.
    */
	Poligono* clippingDePoligono(Poligono* poligono) {
		Poligono* poligonoClippado;
		Poligono* poligonoAux;

		poligonoClippado = clippaPoligonoEsq(poligono);
		if (poligonoClippado->getListaNormal()->getHead() == NULL) {
			return NULL;
		}

		poligonoAux = clippaPoligonoDir(poligonoClippado);
		free(poligonoClippado);
		poligonoClippado = poligonoAux;
		if (poligonoClippado->getListaNormal()->getHead() == NULL) {
			return NULL;
		}

		poligonoAux = clippaPoligonoBaixo(poligonoClippado);
		free(poligonoClippado);
		poligonoClippado = poligonoAux;
		if (poligonoClippado->getListaNormal()->getHead() == NULL) {
			return NULL;
		}

		poligonoAux = clippaPoligonoCima(poligonoClippado);
		free(poligonoClippado);
		poligonoClippado = poligonoAux;
		if (poligonoClippado->getListaNormal()->getHead() == NULL) {
			return NULL;
		}

		return poligonoClippado;
	}

};

#endif