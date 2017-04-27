#include <stdlib.h>
#include <math.h>
#include "view_View.hpp"
#include "model_Fachada.hpp"

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

class Controller {

private:
	View* view; /*!< É a fachada da camada view.*/
	Fachada* model; /*!< É a fachada da camada model*/

public:

	//! Construtor
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

					Ponto* pontoClippado = model->clippingDePonto((static_cast<Ponto*> (elemento)));

					if (pontoClippado != NULL) {
						Coordenada* coordTransformada = model->transformaViewport(pontoClippado->getCoordenadaNormal(), viewportMax);

						view->desenhaPonto(coordTransformada);
						free(coordTransformada);
						//free(pontoClippado); // Cuidado
					}

					break;

				} case RETA: {

					Reta* retaClippada = NULL;
					switch (view->getTipoClippingReta()) {
						case 0: {
							retaClippada = model->clippingDeRetaCS((static_cast<Reta*> (elemento)));
							break;
						} case 1: {
							retaClippada = model->clippingDeRetaLB((static_cast<Reta*> (elemento)));
							break;
						}
					}

					if (retaClippada != NULL) {
						Coordenada* coordIniTransformada = model->transformaViewport(retaClippada->getCoordenadaNormalInicial(), viewportMax);
						Coordenada* coordFinTransformada = model->transformaViewport(retaClippada->getCoordenadaNormalFinal(), viewportMax);


						view->desenhaReta(coordIniTransformada, coordFinTransformada);
						free(coordIniTransformada);
						free(coordFinTransformada);
						//free(retaClippada); // Cuidado
					}
					break;

				} case POLIGONO: {

					bool ePreenchido = (static_cast<Poligono*> (elemento))->getPreenchido();
					Poligono* poligonoClippado = model->clippingDePoligono((static_cast<Poligono*> (elemento)));

					if (poligonoClippado != NULL) {
						//ListaEnc<Coordenada*>* listaCoord = (static_cast<Poligono*> (elemento))->getListaNormal();
						ListaEnc<Coordenada*>* listaCoord = poligonoClippado->getListaNormal();

						Elemento<Coordenada*>* proxCoord = listaCoord->getHead();

						ListaEnc<Coordenada*>* listaCoordTransformada = new ListaEnc<Coordenada*>();

						while (proxCoord != NULL) {
							Coordenada* coord = proxCoord->getInfo();
							Coordenada* coordTransformada = model->transformaViewport(coord, viewportMax);
							listaCoordTransformada->adiciona(coordTransformada);
							proxCoord = proxCoord->getProximo();
						}
						view->desenhaPoligono(listaCoordTransformada, ePreenchido);
						free(listaCoordTransformada);
						//free(poligonoClippado); // Cuidado
					}
					break;
				} case CURVA: {
					Curva* curva = (static_cast<Curva*> (elemento));

					Coordenada* proporcoesWindow = model->getProporcoesWindow();
					double maiorProporcao = fmax(proporcoesWindow->getX(), proporcoesWindow->getY());
					free(proporcoesWindow);

					double distMedia = curva->distanciaMediaDoCentro();
					int numSegmentos = (distMedia/maiorProporcao)*100;
					numSegmentos = fmax(2, fmin(numSegmentos, 2000)); // Mantém o numero no intervalo [2, 2000].

					ListaEnc<Coordenada*>* pontosCurva = curva->getCurvaFinal(numSegmentos); // Quantos segmentos baseado no zoom;
					ListaEnc<Reta*>* listaRetas;

					switch (view->getTipoClippingReta()) {
						case 0: {
							listaRetas = model->clippingDeCurvaCS(pontosCurva);
							break;
						} case 1: {
							listaRetas = model->clippingDeCurvaLB(pontosCurva);
							break;
						}
					}

					if (listaRetas != NULL) {

						Elemento<Reta*>* elementoLista = listaRetas->getHead();
						while (elementoLista != NULL) {
							Reta* retaAtual = elementoLista->getInfo();

							retaAtual->setCoordenadaNormalInicial(model->transformaViewport(retaAtual->getCoordenadaNormalInicial(), viewportMax));
							retaAtual->setCoordenadaNormalFinal(model->transformaViewport(retaAtual->getCoordenadaNormalFinal(), viewportMax));

							elementoLista = elementoLista->getProximo();
						}

						view->desenhaCurva(listaRetas);

						free(listaRetas);
					}

					free(pontosCurva);
				}
			}
			proxElemento = proxElemento->getProximo();
		}

		view->desenhaMargem();
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
		model->fazEscalonamento(elem, fator);
	}

	//! Método que realiza a rotação de um elemento grafico.
	/*!
        /param elem o elemento grafico que sera rotacionado.
		/param coord a rotação sera relativa a este ponto.
		/param angulo quantos graus o elemento sera rotacionado.
    */
	void fazRotacao(ElementoGrafico* elem, Coordenada* coord, double angulo) {
		model->fazRotacao(elem, coord, angulo);
	}

	//! Método que faz a tranformação de sistemas de coordenadas normalizadas em todo o mundo.
	void descricaoSCN() {
		model->sistemaCoordenadasNormalizadas();
	}

	//! Método que faz a tranformação de sistemas de coordenadas normalizadas em um elemento.
	/*!
		/param elem é o elemento que será feita a transformação.
	*/
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
					descricaoSCN(elemento);
					//view->limparTextoTranslacao();
					view->focusTransX();
					view->inserirTextoConsole("Elemento transladado.");
					free(c);
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
					descricaoSCN(elemento);
					//view->limparTextoEscalonamento();
					view->focusEscalX();
					view->inserirTextoConsole("Elemento escalonado.");
					free(c);
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
						descricaoSCN(elemento);
						view->inserirTextoConsole("Elemento rotacionado ao redor da origem.");
						view->focusRotAngulo();
						free(c);
						//view->limparTextoRotacao();
						break;

					case 1: // Opção de rotação em relação ao centro do elemento
						c = new Coordenada(elemento->getCentroGeometrico());
						fazRotacao(elemento, c, angulo);
						descricaoSCN(elemento);
						view->inserirTextoConsole("Elemento rotacionado ao redor de si mesmo.");
						view->focusRotAngulo();
						free(c);
						//view->limparTextoRotacao();
						break;

					case 2: // Opção de rotação em relação a um ponto qualquer
						try {
							c = new Coordenada(view->getRotRelativoAX(), view->getRotRelativoAY());
							fazRotacao(elemento, c, angulo);
							descricaoSCN(elemento);
							view->inserirTextoConsole("Elemento rotacionado em relação a um ponto.");
							view->focusRotAngulo();
							free(c);
							//view->limparTextoRotacao();
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

		//descricaoSCN();
		atualizaDesenho();
	}

	//! Método que fecha o programa.
	void janelaPrincipalDestroy() {
		view->fecharPrograma();
	}

	//! Método que é chamado ao selecionar um elemento na list box de elementos.
	void selecionaElementoListBox() {
		view->setMenuBar_Salvar_Elemento_ObjSensitive(TRUE);
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
			view->setMenuBar_Salvar_Elemento_ObjSensitive(FALSE);
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

	//! Método que redesenha os elementos quando o tipo de clipping de reta é alterado.
	void clippingAlterado() {
		descricaoSCN();
		atualizaDesenho();
	}
	
	//! Método que carrega um arquivo .obj.
	void carregarObj() {
		try {
			string path = view->selecionarArquivo(); // Retorna tipo: \home\blabla\abc\arquivo.obj
			model->carregaOBJ(path);
			descricaoSCN();
			atualizaDesenho();
		} catch (...) { // Caso o usuário cancele a operação e feche a janela de escolher
			return;
		}
	}
	
	//! Método que salva um elemento em .obj.
	void salvarElementoObj() {
		try {
			string path = view->salvarArquivo(); // Retorna tipo: \home\blabla\abc\arquivo
			int index = view->getIndexLinhaElementosSelecionada();
			ElementoGrafico* elemento = model->getElementoNoIndice(index);
			model->salvaElementoParaOBJ(path, elemento);
			view->inserirTextoConsole("Elemento salvo.");
		} catch (...) { // Caso o usuário cancele a operação e feche a janela de escolher
			return;
		}
	}
	
	//! Método que salva o mundo em .obj.
	void salvarMundoObj() {
		try {
			string path = view->salvarArquivo(); // Retorna tipo: \home\blabla\abc\arquivo
			model->salvaMundoParaOBJ(path);
			view->inserirTextoConsole("Mundo salvo.");
		} catch (...) { // Caso o usuário cancele a operação e feche a janela de escolher
			return;
		}
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
					Ponto* p =model->inserirNovoPonto(nome, coordX, coordY);
					view->limparTextoNovoPonto();
					view->adicionaElementoListbox(nome, "Ponto");
					descricaoSCN(p);
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
					Reta* r = model->inserirNovaReta(nome, coordIniX, coordIniY, coordFinX, coordFinY);
					view->limparTextoNovaReta();
					view->adicionaElementoListbox(nome, "Reta");
					descricaoSCN(r);
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
					Poligono* pol = model->inserirNovoPoligono(nome, lista, view->poligonoPreenchido());
					view->resetarListaCoordenadasPoligono();
					view->limparTextoNovoPoligono();
					view->adicionaElementoListbox(nome, "Polígono");
					view->setPoligono_Btn_DelSensitive(FALSE);
					descricaoSCN(pol);
					view->inserirTextoConsole("Novo poligono adicionado.");
				} catch (int erro) {
					if (erro == -1) {
						view->inserirTextoConsole("ERRO: não é possível inserir elemento sem nome.");
					} else if (erro == -3) {
						view->inserirTextoConsole("ERRO: não é possível inserir polígono sem coordenadas.");
					}
				}

				break;
			} case 3: { // A page 3 corresponde à aba de Curva
				ListaEnc<Coordenada*>* lista = view->getListaCoordsCurva();

				try {
					if (view->getTipoCurva() == 0) { // 0 corresponde a opção de curva de Bézier
						CurvaBezier* cb = model->inserirNovaCurvaBezier(nome, lista);
						descricaoSCN(cb);
					} else {
						CurvaBSpline* cb = model->inserirNovaCurvaBSpline(nome, lista);
						descricaoSCN(cb);
					}

					view->resetarListaCoordenadasCurva();
					view->limparTextoNovaCurva();
					view->adicionaElementoListbox(nome, "Curva");
					view->setCurva_Btn_DelSensitive(FALSE);
					view->inserirTextoConsole("Nova curva adicionada.");
				} catch (int erro) {
					if (erro == -1) {
						view->inserirTextoConsole("ERRO: não é possível inserir elemento sem nome.");
					} else if (erro == -3) {
						if (view->getTipoCurva() == 0) { // 0 corresponde a opção de curva de Bézier
							view->inserirTextoConsole("ERRO: a curva deve ter 3*n + 1 coordenadas, com n > 0.");
						} else {
							view->inserirTextoConsole("ERRO: a curva deve ter pelo menos 4 coordenadas.");
						}
						
					}
				}

				break;
			}
		}

		//descricaoSCN();
		atualizaDesenho();
		view->focusNome();
	}

	//! Método que adiciona uma coordenada ao poligono sendo criado.
	void addNovaCoordenadaPoligono() {
		try {
			view->inserirCoordListaEncPoligono();
			view->limparTextoCoordPoligono();
			view->focusCoordPoligono();
		} catch (...){
			return;
		}
	}

	//! Método que remove a coordenada selecionada na criação de poligono.
	void delCoordenadaPoligono() {
		view->deletarCoordPoligono();
	}

	//! Método que é chamado ao selecionar um elemento na list box de elementos.
	void selecionaListBoxPoligono() {
		view->setPoligono_Btn_DelSensitive(TRUE);
	}

	//! Método que adiciona uma coordenada à curva sendo criado.
	void addNovaCoordenadaCurva() {
		try {
			view->inserirCoordListaEncCurva();
			view->limparTextoCoordCurva();
			view->focusCoordCurva();
		} catch (...){
			return;
		}
	}

	//! Método que remove a coordenada selecionada na criação de curva.
	void delCoordenadaCurva() {
		view->deletarCoordCurva();
	}

	//! Método que é chamado ao selecionar um elemento na list box de elementos.
	void selecionaListBoxCurva() {
		view->setCurva_Btn_DelSensitive(TRUE);
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