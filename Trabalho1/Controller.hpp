#include <stdlib.h>

#include "view/View.hpp"
#include "model/Fachada.hpp"

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

class Controller {
	
private:
	View* view;
	Fachada* model;

public:

	Controller() {
		model = new Fachada();
		view = new View();
	}
	
	void inicializarView(int argc, char *argv[]){
		view->inicializarComponentes(argc, argv);
	}
	
	
	View* getView() {
		return view;
	}
	
	Fachada* getModel() {
		return model;
	}
	
	// Método que percorre a display file, faz a transformada de Viewport para cada elemento e depois os desenha.
	void atualizaDesenho() {
		view->clear_surface();
		
		Coordenada* viewportMax = view->getViewportMax();
		
		Elemento<ElementoGrafico*>* proxElemento = model->getHeadDisplayFile(); // primeiro elemento da display file
		while (proxElemento != NULL) {
			ElementoGrafico* elemento = proxElemento->getInfo();
			switch (elemento->getTipo()) {
				case PONTO: {
					Coordenada* coordTransformada = model->transformaViewport((static_cast<Ponto*> (elemento))->getCoordenada(), viewportMax);
					Ponto* pontoTransformado = new Ponto(elemento->getNome(), coordTransformada);
					view->desenhaPonto(pontoTransformado);
					free(pontoTransformado);
					break;
					
				} case RETA: {
					Coordenada* coordIniTransformada = model->transformaViewport((static_cast<Reta*> (elemento))->getPontoInicial(), viewportMax);
					Coordenada* coordFinTransformada = model->transformaViewport((static_cast<Reta*> (elemento))->getPontoFinal(), viewportMax);
					
					Reta* retaTransformada = new Reta(elemento->getNome(), coordIniTransformada, coordFinTransformada);
					view->desenhaReta(retaTransformada);
					free(retaTransformada);
					break;
					
				} case POLIGONO: {
					Poligono* poligonoTransformado = new Poligono(elemento->getNome());
					
					ListaEnc<Coordenada*>* listaCoord = (static_cast<Poligono*> (elemento))->getLista();
					Elemento<Coordenada*>* proxCoord = listaCoord->getHead();

					while (proxCoord != NULL) {
						Coordenada* coord = proxCoord->getInfo();
						Coordenada* coordTransformada = model->transformaViewport(coord, viewportMax);
						poligonoTransformado->adicionarCoordenada(coordTransformada);
						proxCoord = proxCoord->getProximo();
					}
					view->desenhaPoligono(poligonoTransformado);
					free(poligonoTransformado);
					break;
				}
			}
			proxElemento = proxElemento->getProximo();
		}
	}

	// Fazer transformações
	
};

#endif