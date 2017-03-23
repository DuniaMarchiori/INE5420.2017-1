#include <stdlib.h>

#include <stdio.h>

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

	void fazTranslacao(ElementoGrafico* elem, Coordenada* coord) {
		model->fazTranslacao(elem, coord);
	}

	void fazEscalonamento(ElementoGrafico* elem, Coordenada* fator) {
		/*Coordenada* centro = elem->getCentroGeometrico();
		fazTranslacaoParaOrigem(elem);*/
		model->fazEscalonamento(elem, fator);
		//fazTranslacao(elem, centro);
	}

	void fazRotacao(ElementoGrafico* elem, Coordenada* coord, double angulo) {
		/*Coordenada* coordNegativa = new Coordenada( -(coord->getX()), -(coord->getY()) );
		fazTranslacao(elem, coordNegativa);*/
		model->fazRotacao(elem, coord, angulo);
		/*fazTranslacao(elem, coord);
		free(coordNegativa);*/
	}

	void editarElementoGrafico() {
		int index = view->getIndexLinhaElementosSelecionada();
		ElementoGrafico* elemento = model->getElementoNoIndice(index);
		Coordenada* c;
		
		switch (view->getTipoTransformacao()) {
			case 0: // Aba da translação
				try {
					c = new Coordenada(view->getTransX(), view->getTransY());
					fazTranslacao(elemento, c);
					view->limparTextoTranslacao();
					view->focusTransX();
					view->inserirTextoConsole("Elemento transladado.");
				} catch (int erro) {
					if (erro == -1) {
						view->inserirTextoConsole("ERRO: Você deve inserir um valor numérico como quantidade de translação.");
					}
				}
				break;

			case 1: // Aba do escalonamento
				try {
					c = new Coordenada(view->getEscalFatorX(), view->getEscalFatorY());
					fazEscalonamento(elemento, c);
					view->limparTextoEscalonamento();
					view->focusEscalX();
					view->inserirTextoConsole("Elemento escalonado.");
				} catch (int erro) {
					if (erro == -1) {
						view->inserirTextoConsole("ERRO: Você deve inserir um valor numérico como fator de escalonamento.");
					} else if (erro == -2){
						view->inserirTextoConsole("ERRO: Você deve inserir um valor diferente de 0 como fator de escalonamento.");
					}
				}
				break;

			case 2: // Aba da rotação
				double angulo;
				try {
					angulo = view->getRotAngulo();
				} catch (int erro) {
					if (erro == -1) {
						view->inserirTextoConsole("ERRO: Você deve inserir um valor numérico como ângulo de rotação.");
						break;
					} else if(erro == -2) {
						view->inserirTextoConsole("ERRO: Você deve inserir um valor diferente de 0 como ângulo de rotação.");
						break;
					}
				}
				switch(view->getRelatividadeRotacao()) {
					case 0: // Opção de rotação em relação à origem
						c = new Coordenada(0, 0);
						fazRotacao(elemento, c, angulo);
						view->inserirTextoConsole("Elemento rotacionado ao redor da origem.");
						view->focusRotAngulo();
						view->limparTextoRotacao();
						break;

					case 1: // Opção de rotação em relação ao centro do elemento
						c = new Coordenada(elemento->getCentroGeometrico()->getX(), elemento->getCentroGeometrico()->getY());
						fazRotacao(elemento, c, angulo);
						view->inserirTextoConsole("Elemento rotacionado ao redor de si mesmo.");
						view->focusRotAngulo();
						view->limparTextoRotacao();
						break;

					case 2: // Opção de rotação em relação a um ponto qualquer
						try {
							c = new Coordenada(view->getRotRelativoAX(), view->getRotRelativoAY());
							fazRotacao(elemento, c, angulo);
							view->inserirTextoConsole("Elemento rotacionado em relação a um ponto.");
							view->focusRotAngulo();
							view->limparTextoRotacao();
							break;
						} catch (int erro) {
							if (erro == -1) {
								view->inserirTextoConsole("ERRO: Você deve inserir um valor numérico como ponto de referência para a rotação.");
								break;
							}						
						}
				}
				break;
		}

		atualizaDesenho();

	}

	// Métodos chamados pela interface de usuário

	void janelaPrincipalDestroy() {
		view->fecharPrograma();
	}

	void selecionaElementoListBox() {
		view->setElmnt_Btn_DelSensitive(TRUE);
		view->setElmnt_Btn_EditSensitive(TRUE);
	}

	void botaoNovoElemento() {
		view->elmnt_Btn_Novo_Clicado();
	}

	void botaoEditarElemento() {
		view->elmnt_Btn_Edit_Clicado();
	}

	void botaoDeletarElemento() {
		try {
			int index = view->deletarElemento();
			model->deletarElemento(index);
			atualizaDesenho();
			view->inserirTextoConsole("Elemento excluído.");
			view->setElmnt_Btn_DelSensitive(FALSE);
			view->setElmnt_Btn_EditSensitive(FALSE);
		} catch (int erro) {
			if (erro == 1) {
				view->inserirTextoConsole("É preciso selecionar um elemento para ser deletado.");
			}
		}
	}

	void botaoMovimentoCima() {
		try {
			double fator = view->getFatorMovimento();
			model->moverWindow(0,fator);
			atualizaDesenho();
			view->inserirTextoConsole("Movimentação para cima.");
		} catch (...){
			return;
		}
	}

	void botaoMovimentoEsquerda() {
		try {
			double fator = view->getFatorMovimento();
			model->moverWindow(-fator,0);
			atualizaDesenho();
			view->inserirTextoConsole("Movimentação para a esquerda.");
		} catch (...){
			return;
		}
	}

	void botaoMovimentoDireita() {
		try {
			double fator = view->getFatorMovimento();
			model->moverWindow(fator,0);
			atualizaDesenho();
			view->inserirTextoConsole("Movimentação para a direita.");
		} catch (...){
			return;
		}
	}

	void botaoMovimentoBaixo() {
		try {
			double fator = view->getFatorMovimento();
			model->moverWindow(0,-fator);
			atualizaDesenho();
			view->inserirTextoConsole("Movimentação para baixo.");
		} catch (...){
			return;
		}
	}

	void botaoZoomMenos() {
		try {
			double fator = view->getFatorZoom();
			model->zoom(-fator);
			atualizaDesenho();
			view->inserirTextoConsole("Zoom para fora.");
		} catch (...){
			return;
		}
	}

	void botaoZoomMais() {
		try {
			double fator = view->getFatorZoom();
			model->zoom(fator);
			atualizaDesenho();
			view->inserirTextoConsole("Zoom para dentro.");
		} catch (...){
			return;
		}
	}

	void drawingAreaConfigure(GtkWidget *widget) {
		view->nova_surface(widget);
		atualizaDesenho();
	}

	void drawingAreaDraw(cairo_t *cr) {
		view->modifica_surface(cr);
	}

	void addNovoElemento() {
		string nome = view->getNomeElemento();
		int tipo = view->getTipoNovoElemento();
		switch (tipo) {
			case 0: { // A page 0 corresponde à aba de Ponto
				string coordX = view->getCoordXNovoPonto();
				string coordY = view->getCoordYNovoPonto();
				try {
					model->inserirNovoPonto(nome, coordX, coordY);
					view->limparTextoNovoPonto();
					view->adicionaElementoListbox(nome);
					view->inserirTextoConsole("Novo ponto adicionado.");
				} catch (int erro) {
					if (erro == -1) {
						view->inserirTextoConsole("ERRO: não é possível inserir elemento sem nome.");
					} else if (erro == -2) {
						view->inserirTextoConsole("ERRO: coordenadas devem ser valores numéricos.");
					} else if (erro == -3) {
						view->inserirTextoConsole("ERRO: não é possível inserir um ponto sem coordenadas.");
					}
				}

				break;
			} case 1: { // A page 1 corresponde à aba de Reta
				string coordIniX = view->getCoordIniXNovaReta();
				string coordIniY = view->getCoordIniYNovaReta();
				string coordFinX = view->getCoordFinXNovaReta();
				string coordFinY = view->getCoordFinYNovaReta();

				try {
					model->inserirNovaReta(nome, coordIniX, coordIniY, coordFinX, coordFinY);
					view->limparTextoNovaReta();
					view->adicionaElementoListbox(nome);
					view->inserirTextoConsole("Nova reta adicionada.");
				} catch (int erro) {
					if (erro == -1) {
						view->inserirTextoConsole("ERRO: não é possível inserir elemento sem nome.");
					} else if (erro == -2) {
						view->inserirTextoConsole("ERRO: coordenadas devem ser valores numéricos.");
					} else if (erro == -3) {
						view->inserirTextoConsole("ERRO: não é possível inserir reta sem dois pares de coordenadas.");
					}
				}

				break;
			} case 2: { // A page 2 corresponde à aba de Polígono
				ListaEnc<Coordenada*>* lista = view->getListaCoordsPoligono();

				try {
					model->inserirNovoPoligono(nome, lista);
					view->resetarListaCoordenadasPoligono();
					view->limparTextoNovoPoligono();
					view->adicionaElementoListbox(nome);
					view->inserirTextoConsole("Novo poligono adicionado.");
				} catch (int erro) {
					if (erro == -1) {
						view->inserirTextoConsole("ERRO: não é possível inserir elemento sem nome.");
					} else if (erro == -3) {
						view->inserirTextoConsole("ERRO: não é possível inserir polígono sem coordenadas.");
					}
				}

				break;
			}
		}

		atualizaDesenho();
		view->setPoligono_Btn_DelSensitive(FALSE);
		view->focusNome();
	}

	void addNovaCoordenadaPolinomio() {
		try {
			view->inserirCoordListaEnc();
			view->limparTextoCoordPoligono();
			view->focusCoordPoligono();
		} catch (...){
			return;
		}
	}

	void delCoordenadaPolinomio() {
		view->deletarCoordPoligono();
	}

	void selecionaCoordenadaListBox() {
		view->setPoligono_Btn_DelSensitive(TRUE);
	}

	void janelaNovoElementoHide() {
		view->resetarJanelaNovoElemento();
	}
	
	void fecharJanelaEdicao() {
		view->resetarJanelaEditElemento();
	}

};

#endif