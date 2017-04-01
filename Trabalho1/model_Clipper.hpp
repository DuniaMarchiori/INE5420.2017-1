#include "model_Ponto.hpp"
#include "model_Reta.hpp"
#include "model_Poligono.hpp"

#ifndef CLIPPER_HPP
#define CLIPPER_HPP

class Clipper {

private:
	
	
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
		return reta; // Retorno apenas para que o programa compile
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