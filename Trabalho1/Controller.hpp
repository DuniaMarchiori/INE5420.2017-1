#include <stdlib.h>

#include <stdio.h>

#include "view_View.hpp"
#include "model_Fachada.hpp"

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

	//! Método que inicializa a interface grafica.
	void inicializarView(int argc, char *argv[]){
		view->inicializarComponentes(argc, argv);
	}

	//! Método que percorre a display file, faz a transformada de Viewport para cada elemento e depois os desenha.
	void atualizaDesenho() {
		view->clear_surface();

		Coordenada* viewportMax = view->getViewportMax();

		Elemento<ElementoGrafico*>* proxElemento = model->getHeadDisplayFile(); // primeiro elemento da display file
		while (proxElemento != NULL) {
			ElementoGrafico* elemento = proxElemento->getInfo();
			switch (elemento->getTipo()) {
				case PONTO: {
					Coordenada* coordTransformada = model->transformaViewport((static_cast<Ponto*> (elemento))->getCoordenadaNormal(), viewportMax);
					Ponto* pontoTransformado = new Ponto(elemento->getNome(), coordTransformada);
					view->desenhaPonto(pontoTransformado);
					free(pontoTransformado);
					break;

				} case RETA: {
					Coordenada* coordIniTransformada = model->transformaViewport((static_cast<Reta*> (elemento))->getCoordenadaNormalInicial(), viewportMax);
					Coordenada* coordFinTransformada = model->transformaViewport((static_cast<Reta*> (elemento))->getCoordenadaNormalFinal(), viewportMax);

					Reta* retaTransformada = new Reta(elemento->getNome(), coordIniTransformada, coordFinTransformada);
					view->desenhaReta(retaTransformada);
					free(retaTransformada);
					break;

				} case POLIGONO: {
					Poligono* poligonoTransformado = new Poligono(elemento->getNome());

					ListaEnc<Coordenada*>* listaCoord = (static_cast<Poligono*> (elemento))->getListaNormal();
					Elemento<Coordenada*>* proxCoord = listaCoord->getHead();

					while (proxCoord != NULL) {
						Coordenada* coord = proxCoord->getInfo();
						Coordenada* coordTransformada = model->transformaViewport(coord, viewportMax);
						poligonoTransformado->adicionarCoordenadaMundo(coordTransformada);
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

	//! Método que realiza a translação em um elemento grafico.
	/*!
        /param elem o elemento grafico que sera transladado.
		/param coord uma coordenada contendo a quantidade de translação que sera aplicada em X e Y.
    */
	void fazTranslacao(ElementoGrafico* elem, Coordenada* coord) {
		model->fazTranslacao(elem, coord);
	}

	//! Método que realiza o escalonamento de um elemento grafico.
	/*!
        /param elem o elemento grafico que sera escalonado.
		/param fator uma coordenada contendo a quantidade de escalonamento que sera aplicada em X e Y.
    */
	void fazEscalonamento(ElementoGrafico* elem, Coordenada* fator) {
		/*Coordenada* centro = elem->getCentroGeometrico();
		fazTranslacaoParaOrigem(elem);*/
		model->fazEscalonamento(elem, fator);
		//fazTranslacao(elem, centro);
	}

	//! Método que realiza a rotação de um elemento grafico.
	/*!
        /param elem o elemento grafico que sera rotacionado.
		/param coord a rotação sera relativa a este ponto.
		/param angulo quantos graus o elemento sera rotacionado.
    */
	void fazRotacao(ElementoGrafico* elem, Coordenada* coord, double angulo) {
		/*Coordenada* coordNegativa = new Coordenada( -(coord->getX()), -(coord->getY()) );
		fazTranslacao(elem, coordNegativa);*/
		model->fazRotacao(elem, coord, angulo);
		/*fazTranslacao(elem, coord);
		free(coordNegativa);*/
	}

	void descricaoSCN() {
		model->sistemaCoordenadasNormalizadas();
	}

	void descricaoSCN(ElementoGrafico* elem) {
		model->sistemaCoordenadasNormalizadas(elem);
	}

	//! Método encarregado de decidir qual operação de transformação sera feita.
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

		descricaoSCN();
		atualizaDesenho();

	}

	//! Método que fecha o programa.
	void janelaPrincipalDestroy() {
		view->fecharPrograma();
	}

	//! Método que é chamado ao selecionar um elemento na list box de elementos.
	void selecionaElementoListBox() {
		view->setElmnt_Btn_DelSensitive(TRUE);
		view->setElmnt_Btn_EditSensitive(TRUE);
	}

	//! Método que abre a janela de novo elemento.
	void botaoNovoElemento() {
		view->elmnt_Btn_Novo_Clicado();
	}

	//! Método que abre a janela de editar elemento.
	void botaoEditarElemento() {
		view->elmnt_Btn_Edit_Clicado();
	}

	//! Método que deleta um elemento.
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


	//! Método que gira a window no sentido anti-horário.
	void botaoGirarWindowEsquerdo() {
		try {
			double fator = view->getFatorPosicao();
			model->rotacionarWindow(fator);
			descricaoSCN();
			atualizaDesenho();
			view->inserirTextoConsole("Window rotacionada");
		} catch (...){
			return;
		}
	}

	//! Método que gira a window no sentido horário.
	void botaoGirarWindowDireito() {
		try {
			double fator = view->getFatorPosicao();
			model->rotacionarWindow(-1 * fator);
			descricaoSCN();
			atualizaDesenho();
			view->inserirTextoConsole("Window rotacionada");
		} catch (...){
			return;
		}
	}


	//! Método que movimenta a window para cima.
	void botaoMovimentoCima() {
		try {
			double fator = view->getFatorPosicao();
			model->moverWindow(0,fator);
			descricaoSCN();
			atualizaDesenho();
			view->inserirTextoConsole("Movimentação para cima.");
		} catch (...){
			return;
		}
	}

	//! Método que movimenta a window para esquerda.
	void botaoMovimentoEsquerda() {
		try {
			double fator = view->getFatorPosicao();
			model->moverWindow(-fator,0);
			descricaoSCN();
			atualizaDesenho();
			view->inserirTextoConsole("Movimentação para a esquerda.");
		} catch (...){
			return;
		}
	}

	//! Método que movimenta a window para direita.
	void botaoMovimentoDireita() {
		try {
			double fator = view->getFatorPosicao();
			model->moverWindow(fator,0);
			descricaoSCN();
			atualizaDesenho();
			view->inserirTextoConsole("Movimentação para a direita.");
		} catch (...){
			return;
		}
	}

	//! Método que movimenta a window para baixo.
	void botaoMovimentoBaixo() {
		try {
			double fator = view->getFatorPosicao();
			model->moverWindow(0,-fator);
			descricaoSCN();
			atualizaDesenho();
			view->inserirTextoConsole("Movimentação para baixo.");
		} catch (...){
			return;
		}
	}

	//! Método que realiza zoom out na window.
	void botaoZoomMenos() {
		try {
			double fator = view->getFatorZoom();
			model->zoom(-fator);
			descricaoSCN();
			atualizaDesenho();
			view->inserirTextoConsole("Zoom para fora.");
		} catch (...){
			return;
		}
	}

	//! Método que realiza zoom in na window.
	void botaoZoomMais() {
		try {
			double fator = view->getFatorZoom();
			model->zoom(fator);
			descricaoSCN();
			atualizaDesenho();
			view->inserirTextoConsole("Zoom para dentro.");
		} catch (...){
			return;
		}
	}

	//! Método que é chamado ao signal de configure da janela principal.
	void drawingAreaConfigure(GtkWidget *widget) {
		view->nova_surface(widget);
		descricaoSCN();
		atualizaDesenho();
	}

	//! Método que é chamado ao signal de draw da janela principal.
	void drawingAreaDraw(cairo_t *cr) {
		view->modifica_surface(cr);
	}

	//! Método que adiciona um novo elemento.
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
					view->adicionaElementoListbox(nome, "Ponto");
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
					view->adicionaElementoListbox(nome, "Reta");
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
					view->adicionaElementoListbox(nome, "Polígono");
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

		descricaoSCN();
		atualizaDesenho();
		view->setPoligono_Btn_DelSensitive(FALSE);
		view->focusNome();
	}

	//! Método que adiciona uma coordenada ao poligono sendo criado.
	void addNovaCoordenadaPolinomio() {
		try {
			view->inserirCoordListaEnc();
			view->limparTextoCoordPoligono();
			view->focusCoordPoligono();
		} catch (...){
			return;
		}
	}

	//! Método que remove a coordenada selecionada na criação de poligono.
	void delCoordenadaPolinomio() {
		view->deletarCoordPoligono();
	}

	//! Método que é chamado ao selecionar um elemento na list box de elementos.
	void selecionaCoordenadaListBox() {
		view->setPoligono_Btn_DelSensitive(TRUE);
	}

	//! Método que é chamado ao fechar a janela de novo elemento.
	void janelaNovoElementoHide() {
		view->resetarJanelaNovoElemento();
	}

	//! Método que é chamado ao fechar a janela de editar elemento.
	void fecharJanelaEdicao() {
		view->resetarJanelaEditElemento();
	}

};

#endif