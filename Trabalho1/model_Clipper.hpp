#include "model_Ponto.hpp"
#include "model_Reta.hpp"
#include "model_Poligono.hpp"

#ifndef CLIPPER_HPP
#define CLIPPER_HPP

class Clipper {

private:
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

public:
	//! Método que clippa um ponto.
	/*!
        /param ponto O ponto que será clippado.
		/return o ponto clippado.
    */
	Ponto* clippingDePonto(Ponto* ponto) {
		return ponto; // Retorno apenas para que o programa compile
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
			//cout << "Meio a meio" << endl;
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



		//return reta; // Retorno apenas para que o programa compile
	}

	//! Método que clippa uma reta com o algoritmo Liang-Barsky.
	/*!
        /param reta A reta que será clippada.
		/return a reta clippada.
    */
	Reta* clippingDeRetaLB(Reta* reta) {
		return reta; // Retorno apenas para que o programa compile
	}

	//! Método que clippa um poligono.
	/*!
        /param poligono O poligono que será clippado.
		/return o poligono clippado.
    */
	Poligono* clippingDePoligono(Poligono* poligono) {
		return poligono; // Retorno apenas para que o programa compile
	}

};

#endif