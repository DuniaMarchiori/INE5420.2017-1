#include <math.h>

#include "model_Matriz.hpp"

#ifndef TRANSFORMACAO_HPP
#define TRANSFORMACAO_HPP

class Transformacao {

private:

	//! Método que faz transformações em coordenadas de mundo de um elemento.
	/*!
		Faz as transformações usando a matriz passada.
		/param elem é o elemento gráfico que será feita a transformação.
		/param matrizResultado é a matriz utilizada para fazer a transformação.
	*/
	void fazTransformacaoMundo(ElementoGrafico* elem, Matriz<double>* matrizResultado) {
		Tipo t = elem->getTipo();

		switch (t) {
			case PONTO: {
				Ponto* p = static_cast<Ponto*> (elem);
				Coordenada3D* nova = transformaCoordenada(p->getCoordenadaMundo(), matrizResultado);
				p->setCoordenadaMundo(nova);
				break;
			} case RETA: {
				Reta* r = static_cast<Reta*> (elem);
				Coordenada3D* novaInicial = transformaCoordenada(r->getCoordenadaMundoInicial(), matrizResultado);
				Coordenada3D* novaFinal = transformaCoordenada(r->getCoordenadaMundoFinal(), matrizResultado);
				r->setCoordenadaMundoInicial(novaInicial);
				r->setCoordenadaMundoFinal(novaFinal);
				break;
			} case POLIGONO: {
				Poligono* p = static_cast<Poligono*> (elem);
				ListaEnc<Coordenada3D*>* listaCoord = p->getListaMundo();
				Elemento<Coordenada3D*>* proxCoord = listaCoord->getHead();
				ListaEnc<Coordenada3D*>* listaNovasCoord = new ListaEnc<Coordenada3D*>();
				while (proxCoord != NULL) {
					Coordenada3D* coordPol = proxCoord->getInfo();
					Coordenada3D* coordTransformada = transformaCoordenada(coordPol, matrizResultado);
					listaNovasCoord->adiciona(coordTransformada);
					proxCoord = proxCoord->getProximo();
				}

				p->setListaMundo(listaNovasCoord);

				free(listaCoord);
				break;
			} case CURVA: {
				Curva* c = static_cast<Curva*> (elem);

				ListaEnc<Coordenada3D*>* listaCoord = c->getListaMundo();
				Elemento<Coordenada3D*>* proxCoord = listaCoord->getHead();
				ListaEnc<Coordenada3D*>* listaNovasCoord = new ListaEnc<Coordenada3D*>();

				while (proxCoord != NULL) {
					Coordenada3D* coordCurva = proxCoord->getInfo();
					Coordenada3D* coordTransformada = transformaCoordenada(coordCurva, matrizResultado);
					listaNovasCoord->adiciona(coordTransformada);
					proxCoord = proxCoord->getProximo();
				}
				c->setListaMundo(listaNovasCoord);
				free(listaCoord);
				break;
			} case OBJETO3D: {
				Objeto3D* obj = static_cast<Objeto3D*> (elem);

				ListaEnc<Coordenada3D*>* listaCoord = obj->getListaCoordMundo();
				Elemento<Coordenada3D*>* proxCoord = listaCoord->getHead();
				while (proxCoord != NULL) {
					Coordenada3D* coordObj = proxCoord->getInfo();
					Coordenada3D* coordTransformada = transformaCoordenada(coordObj, matrizResultado);
					coordObj->setX(coordTransformada->getX());
					coordObj->setY(coordTransformada->getY());
					coordObj->setZ(coordTransformada->getZ());
					proxCoord = proxCoord->getProximo();
				}
				break;
			} case SUPERFICIE: {
				Superficie* s = static_cast<Superficie*> (elem);

				Matriz<Coordenada3D*>* matrizPontos = s->getPontosMundo();
				int altura = matrizPontos->getNumLinhas();
				int largura = matrizPontos->getNumColunas();
				for (int i = 0; i < altura; i++) {
					for (int j = 0; j < largura; j++) {
						Coordenada3D* coordSup = matrizPontos->getValor(i, j);
						Coordenada3D* coordTransformada = transformaCoordenada(coordSup, matrizResultado);
						matrizPontos->setValor(i, j, coordTransformada);
					}
				}

				break;
			}
		}
	}

public:
	/*Transformacao();
	~Transformacao();*/

	//! Método que cria uma matriz de translação em coordenadas homogêneas.
	/*!
		/param Dx é o valor de X do ponto para o qual será feita a translação.
		/param Dy é o valor de Y do ponto para o qual será feita a translação.
		/param Dz é o valor de Z do ponto para o qual será feita a translação.
		/return uma matriz de translação.
	*/
	Matriz<double>* novaMatrizTranslacao(double Dx, double Dy, double Dz) {
		Matriz<double> *matriz= new Matriz<double>(4,4);

		for (int i = 0; i < 4; ++i) {
			matriz->setValor(i, i, 1);
		}

		matriz->setValor(3, 0, Dx);
		matriz->setValor(3, 1, Dy);
		matriz->setValor(3, 2, Dz);
		return matriz;
	}

	//! Método que cria uma matriz de escalonamento em coordenadas homogêneas.
	/*!
		/param Sx é o valor de X do ponto para o qual será feita o escalonamento.
		/param Sy é o valor de Y do ponto para o qual será feita o escalonamento.
		/param Sz é o valor de Z do ponto para o qual será feita o escalonamento.
		/return uma matriz de escalonamento.
	*/
	Matriz<double>* novaMatrizEscalonamento(double Sx, double Sy, double Sz) {
		Matriz<double> *matriz= new Matriz<double>(4,4);

		matriz->setValor(0, 0, Sx);
		matriz->setValor(1, 1, Sy);
		matriz->setValor(2, 2, Sz);
		matriz->setValor(3, 3, 1);
		return matriz;
	}

	//! Método que cria uma matriz de rotação em coordenadas homogêneas.
	/*!
		/param angulo é o valor do ângulo para o qual será feita a rotação.
		/return uma matriz de rotação.
	*/
	/*Matriz<double>* novaMatrizRotacao(double angulo) {
		/*
		Matriz<double> *matriz= new Matriz<double>(3,3);

		double radianos = (angulo * M_PI/180.0);
		matriz->setValor(0, 0, cos (radianos));
		matriz->setValor(1, 1, cos (radianos));
		matriz->setValor(2, 2, 1);
		matriz->setValor(1, 0, (-1)*(sin (radianos)));
		matriz->setValor(0, 1, sin (radianos));
		return matriz;
		*/

		/*Matriz<double>* matriz= new Matriz<double>(4,4);

		for (int i = 0; i < 4; ++i) {
			matriz->setValor(i, i, 1);
		}

		return matriz;
	}*/

	//! Método que cria uma matriz de rotação no eixo X.
	/*!
		/param angulo é o valor do ângulo para o qual será feita a rotação.
		/return uma matriz de rotação em X.
	*/
	Matriz<double>* novaMatrizRotacaoX(double angulo) {
		Matriz<double> *matriz= new Matriz<double>(4,4);

		double radianos = (angulo * M_PI/180.0);
		matriz->setValor(0, 0, 1);
		matriz->setValor(1, 1, cos(radianos));
		matriz->setValor(1, 2, sin(radianos));
		matriz->setValor(2, 1, -1 * sin(radianos));
		matriz->setValor(2, 2, cos(radianos));
		matriz->setValor(3, 3, 1);

		return matriz;
	}

	//! Método que cria uma matriz de rotação no eixo Y.
	/*!
		/param angulo é o valor do ângulo para o qual será feita a rotação.
		/return uma matriz de rotação em Y.
	*/
	Matriz<double>* novaMatrizRotacaoY(double angulo) {
		Matriz<double> *matriz= new Matriz<double>(4,4);

		double radianos = (angulo * M_PI/180.0);
		matriz->setValor(0, 0, cos(radianos));
		matriz->setValor(0, 2, -1 * sin(radianos));
		matriz->setValor(1, 1, 1);
		matriz->setValor(2, 0, sin(radianos));
		matriz->setValor(2, 2, cos(radianos));
		matriz->setValor(3, 3, 1);

		return matriz;
	}

	//! Método que cria uma matriz de rotação no eixo Z.
	/*!
		/param angulo é o valor do ângulo para o qual será feita a rotação.
		/return uma matriz de rotação em Z.
	*/
	Matriz<double>* novaMatrizRotacaoZ(double angulo) {
		Matriz<double> *matriz= new Matriz<double>(4,4);

		double radianos = (angulo * M_PI/180.0);
		matriz->setValor(0, 0, cos(radianos));
		matriz->setValor(0, 1, sin(radianos));
		matriz->setValor(1, 0, -1 * sin(radianos));
		matriz->setValor(1, 1, cos(radianos));
		matriz->setValor(2, 2, 1);
		matriz->setValor(3, 3, 1);

		return matriz;
	}

	//! Método que faz a transformação.
	/*!
		Faz a transformação sobre o ponto utilizando a matriz passada.
		/param coord é a Coordenada na qual será feita a transformação.
		/param matriz é a matriz de transformação.
		/return a coordenada depois de feita a transformação.
	*/
	Coordenada3D* transformaCoordenada(Coordenada3D* coord, Matriz<double>* matriz) {
		Coordenada3D* transformada;
		Matriz<double> *vetor= new Matriz<double>(1,4);
		vetor->setValor(0, 0, coord->getX());
		vetor->setValor(0, 1, coord->getY());
		vetor->setValor(0, 2, coord->getZ());
		vetor->setValor(0, 3, 1);
		Matriz<double>* resultado = vetor->multiplica(matriz);

		transformada = new Coordenada3D(resultado->getValor(0,0), resultado->getValor(0,1), resultado->getValor(0,2));
		free(vetor);
		free(resultado);
		return transformada;
	}

	//! Método que realiza a translação em um elemento grafico.
	/*!
        /param elem o elemento grafico que sera transladado.
		/param coord é uma coordenada contendo a quantidade de translação que sera aplicada em X, Y e Z.
    */
	void fazTranslacao(ElementoGrafico* elem, Coordenada3D* coord) {
		Matriz<double> *resultado = novaMatrizTranslacao(coord->getX(), coord->getY(), coord->getZ());
		fazTransformacaoMundo(elem, resultado);
		free(resultado);
	}

	//! Método que realiza o escalonamento de um elemento grafico.
	/*!
        /param elem o elemento grafico que sera escalonado.
		/param fator é uma coordenada contendo a quantidade de escalonamento que sera aplicada em X, Y e Z.
    */
	void fazEscalonamento(ElementoGrafico* elem, Coordenada3D* fator) {
		Coordenada3D* centro = elem->getCentroGeometrico();
		Matriz<double> *resultadoAux, *resultado, *translacaoOrigem, *escalonamento, *translacaoVolta;
		translacaoOrigem = novaMatrizTranslacao(-(centro->getX()), -(centro->getY()), -(centro->getZ()));
		escalonamento = novaMatrizEscalonamento(fator->getX(), fator->getY(), fator->getZ());
		translacaoVolta = novaMatrizTranslacao(centro->getX(), centro->getY(), -centro->getZ());

		// Traslada para a origem e escalona
		resultadoAux = translacaoOrigem->multiplica(escalonamento);
		// Translada para o lugar de antes
		resultado = resultadoAux->multiplica(translacaoVolta);

		fazTransformacaoMundo(elem, resultado);

		free(centro);
		free(resultado);
		free(resultadoAux);
		free(translacaoVolta);
		free(translacaoOrigem);
		free(escalonamento);
	}

	//! Método que realiza a rotação de um elemento grafico.
	/*!
        /param elem o elemento grafico que sera rotacionado.
		/param coord a rotação sera relativa a este ponto.
		/param angulo quantos graus o elemento sera rotacionado.
    */
	//void fazRotacao(ElementoGrafico* elem, Coordenada* coord, double angulo) {
		/*
		Matriz<double> *resultadoAux, *resultado, *translacaoAteCoord, *rotacao, *translacaoVoltaDeCoord;
		translacaoAteCoord = novaMatrizTranslacao(-(coord->getX()), -(coord->getY()));
		rotacao = novaMatrizRotacao(angulo);
		translacaoVoltaDeCoord = novaMatrizTranslacao(coord->getX(), coord->getY());

		// Traslada para o ponto arbitrário e rotaciona
		resultadoAux = translacaoAteCoord->multiplica(rotacao);
		// Translada para o lugar de antes
		resultado = resultadoAux->multiplica(translacaoVoltaDeCoord);

		fazTransformacaoMundo(elem, resultado);

		free(resultado);
		free(resultadoAux);
		free(translacaoAteCoord);
		free(translacaoVoltaDeCoord);
		free(rotacao);
		*/
	//}

	//! Método que diz o angulo em que um vetor se encontra em relação ao eixo X.
	/*!
		/param coord é um ponto que indica um vetor
		/return o angulo entre o vetor e o eixo X
	*/
	double getAnguloX(Coordenada3D* coord) {
		if (coord->getZ() == 0) {
			if (coord->getY() > 0) {
				return 90;
			} else {
				return -90;
			}
		} else {
			double angulo = atan(coord->getY()/coord->getZ());
			angulo = (angulo * 180.0) / M_PI;
			return angulo;
		}
	}

	//! Método que diz o angulo em que um vetor se encontra em relação ao eixo Y.
	/*!
		/param coord é um ponto que indica um vetor
		/return o angulo entre o vetor e o eixo Y
	*/
	double getAnguloY(Coordenada3D* coord) {
		if (coord->getZ() == 0) {
			if (coord->getX() > 0) {
				return 90;
			} else {
				return -90;
			}
		} else {
			double angulo = atan(coord->getX()/coord->getZ());
			angulo = (angulo * 180.0) / M_PI;
			return angulo;
		}
	}

	//! Método que diz o angulo em que um vetor se encontra em relação ao eixo Z.
	/*!
		/param coord é um ponto que indica um vetor
		/return o angulo entre o vetor e o eixo X
	*/
	double getAnguloZ(Coordenada3D* coord) {
		if (coord->getX() == 0) {
			if (coord->getY() > 0) {
				return 90;
			} else {
				return -90;
			}
		} else {
			double angulo = atan(coord->getY()/coord->getX());
			angulo = (angulo * 180.0) / M_PI;
			return angulo;
		}
	}

	//! Método que realiza a rotação de um elemento grafico.
	/*!
        /param elem o elemento grafico que sera rotacionado.
		/param coord a rotação sera relativa a este ponto.
		/param angulo quantos graus o elemento sera rotacionado.
		/param eixo inteiro representando o eixo a ser rotacionado (X = 0, Y = 1, Z = 2).
    */
	void fazRotacao(ElementoGrafico* elem, Coordenada3D* coord, double angulo, int eixo) {
		Matriz<double> *resultadoAux, *resultado, *translacaoAteCoord, *rotacao, *translacaoVoltaDeCoord;

		// Passo 1
		translacaoAteCoord = novaMatrizTranslacao(-(coord->getX()), -(coord->getY()), -(coord->getZ()));

		// Passo 2
		rotacao = novaMatrizRotacaoX(getAnguloX(coord));
		resultadoAux = translacaoAteCoord->multiplica(rotacao);
		free(rotacao);

		// Passo 3
		rotacao = novaMatrizRotacaoZ(getAnguloZ(coord));
		resultadoAux = resultadoAux->multiplica(rotacao);
		free(rotacao);

		// Passo 4
		switch (eixo) {
			case 0: {
				rotacao = novaMatrizRotacaoX(angulo);
				break;
			} case 1: {
				rotacao = novaMatrizRotacaoY(angulo);
				break;
			} case 2: {
				rotacao = novaMatrizRotacaoZ(angulo);
				break;
			}
		}
		resultadoAux = resultadoAux->multiplica(rotacao);
		free(rotacao);

		// Passo 5
		rotacao = novaMatrizRotacaoZ(-getAnguloZ(coord));
		resultadoAux = resultadoAux->multiplica(rotacao);
		free(rotacao);

		// Passo 6
		rotacao = novaMatrizRotacaoX(-getAnguloX(coord));
		resultadoAux = resultadoAux->multiplica(rotacao);
		free(rotacao);

		// Passo 7
		translacaoVoltaDeCoord = novaMatrizTranslacao((coord->getX()), (coord->getY()), (coord->getZ()));
		resultado = resultadoAux->multiplica(translacaoVoltaDeCoord);

		fazTransformacaoMundo(elem, resultado);

		free(resultado);
		free(resultadoAux);
		free(translacaoAteCoord);
		free(translacaoVoltaDeCoord);
	}

	//! Método que realiza a rotação de um elemento grafico.
	/*!
        /param elem o elemento grafico que sera rotacionado.
		/param coord a rotação sera relativa a este ponto.
		/param angulo quantos graus o elemento sera rotacionado.
		/param eixo inteiro representando o eixo a ser rotacionado (X = 0, Y = 1, Z = 2).
    */
	void fazRotacaoEixo(ElementoGrafico* elem, Coordenada3D* coord, double angulo, int eixo) {
		Matriz<double> *translacaoAteCoord, *rotacao, *translacaoVoltaDeCoord, *resultado;
		translacaoAteCoord = novaMatrizTranslacao(-(coord->getX()), -(coord->getY()), -(coord->getZ()));

		switch (eixo) {
			case 0: {
				rotacao = novaMatrizRotacaoX(angulo);
				break;
			} case 1: {
				rotacao = novaMatrizRotacaoY(angulo);
				break;
			} case 2: {
				rotacao = novaMatrizRotacaoZ(angulo);
				break;
			}
		}

		resultado = translacaoAteCoord->multiplica(rotacao);

		translacaoVoltaDeCoord = novaMatrizTranslacao((coord->getX()), (coord->getY()), (coord->getZ()));
		resultado = resultado->multiplica(translacaoVoltaDeCoord);

		fazTransformacaoMundo(elem, resultado);

		free(resultado);
		free(translacaoAteCoord);
		free(translacaoVoltaDeCoord);
		free(rotacao);
	}

	//! Método que calcula a matriz para a tranformação de sistemas de coordenadas normalizadas.
	/*!
		/param angulo é o angulo da window.
		/param fator é o fator de escalonamento.
		/param centroWin é a coordenada que indica o centro da window.
		/return a matriz para a transformação de sistemas de coordenadas normalizadas.
	*/
	Matriz<double>* matrizSistemaCoordenadasNormalizadas(double angulo, Coordenada* fator, Coordenada3D* centroWin) {
		Matriz<double> *resultadoAux, *resultado, *translacaoAteCentro, *rotacao, *escalonamento;
		//translacaoAteCentro = novaMatrizTranslacao(-(centroWin->getX()), -(centroWin->getY()), 0);
		translacaoAteCentro = novaMatrizTranslacao(0, 0, 0); // Window esta em 0,0,0 após o calculo da Perspectiva, por isso não transladamos -VRP aqui.
		rotacao = novaMatrizRotacaoZ(-angulo);
		escalonamento = novaMatrizEscalonamento(fator->getX(), fator->getY(), 1);

		// Matriz de transformação
		// Traslada para o centro da window e rotaciona
		resultadoAux = translacaoAteCentro->multiplica(rotacao);
		// Escalona
		resultado = resultadoAux->multiplica(escalonamento);

		free(resultadoAux);
		free(translacaoAteCentro);
		free(escalonamento);
		free(rotacao);

		return resultado;
	}

	//! Método que faz transformações em coordenadas normalizadas de um elemento.
	/*!
		Faz as transformações usando a matriz passada.
		/param elem é o elemento gráfico que será feita a transformação.
		/param matrizResultado é a matriz utilizada para fazer a transformação.
	*/
	void fazTransformacaoNormalizada(ElementoGrafico* elem, Matriz<double>* matrizResultado) {
		Tipo t = elem->getTipo();

		switch (t) {
			case PONTO: {
				Ponto* p = static_cast<Ponto*> (elem);
				Coordenada3D* nova = transformaCoordenada(p->getCoordenadaNormal(), matrizResultado);
				p->setCoordenadaNormal(nova);
				break;
			} case RETA: {
				Reta* r = static_cast<Reta*> (elem);
				Coordenada3D* novaInicial = transformaCoordenada(r->getCoordenadaNormalInicial(), matrizResultado);
				Coordenada3D* novaFinal = transformaCoordenada(r->getCoordenadaNormalFinal(), matrizResultado);
				r->setCoordenadaNormalInicial(novaInicial);
				r->setCoordenadaNormalFinal(novaFinal);
				break;
			} case POLIGONO: {
				Poligono* p = static_cast<Poligono*> (elem);

				ListaEnc<Coordenada3D*>* listaCoord = p->getListaNormal();
				Elemento<Coordenada3D*>* proxCoord = listaCoord->getHead();
				ListaEnc<Coordenada3D*>* listaNovasCoord = new ListaEnc<Coordenada3D*>();

				while (proxCoord != NULL) {
					Coordenada3D* coordPol = proxCoord->getInfo();
					Coordenada3D* coordTransformada = transformaCoordenada(coordPol, matrizResultado);
					listaNovasCoord->adiciona(coordTransformada);
					proxCoord = proxCoord->getProximo();
				}
				p->setListaNormal(listaNovasCoord);
				//free(listaCoord);
				break;
			} case CURVA: {
				Curva* c = static_cast<Curva*> (elem);

				ListaEnc<Coordenada3D*>* listaCoord = c->getListaNormal();
				Elemento<Coordenada3D*>* proxCoord = listaCoord->getHead();
				ListaEnc<Coordenada3D*>* listaNovasCoord = new ListaEnc<Coordenada3D*>();

				while (proxCoord != NULL) {
					Coordenada3D* coordCurva = proxCoord->getInfo();
					Coordenada3D* coordTransformada = transformaCoordenada(coordCurva, matrizResultado);
					listaNovasCoord->adiciona(coordTransformada);
					proxCoord = proxCoord->getProximo();
				}
				c->setListaNormal(listaNovasCoord);
				break;
			} case OBJETO3D: {
				Objeto3D* obj = static_cast<Objeto3D*> (elem);

				ListaEnc<Coordenada3D*>* listaCoord = obj->getListaCoordNormal();
				Elemento<Coordenada3D*>* proxCoord = listaCoord->getHead();
				while (proxCoord != NULL) {
					Coordenada3D* coordObj = proxCoord->getInfo();
					Coordenada3D* coordTransformada = transformaCoordenada(coordObj, matrizResultado);
					coordObj->setX(coordTransformada->getX());
					coordObj->setY(coordTransformada->getY());
					coordObj->setZ(coordTransformada->getZ());
					proxCoord = proxCoord->getProximo();
				}
				break;
			} case SUPERFICIE: {
				Superficie* s = static_cast<Superficie*> (elem);

				Matriz<Coordenada3D*>* matrizPontos = s->getPontosNormais();
				int altura = matrizPontos->getNumLinhas();
				int largura = matrizPontos->getNumColunas();
				for (int i = 0; i < altura; i++) {
					for (int j = 0; j < largura; j++) {
						Coordenada3D* coordSup = matrizPontos->getValor(i, j);
						Coordenada3D* coordTransformada = transformaCoordenada(coordSup, matrizResultado);
						matrizPontos->setValor(i, j, coordTransformada);
					}
				}

				break;
			}
		}
	}

	Matriz<double>* getMatrizProjecaoParalelaOrtogonal(Coordenada3D* vrp, double anguloX, double anguloY) {
		// fazer matriz translação * rotacaoX * rotacaoY
		Matriz<double> *resultado, *auxiliar, *rotacao;

		auxiliar = novaMatrizTranslacao(-(vrp->getX()), -(vrp->getY()), -(vrp->getZ()));
		rotacao = novaMatrizRotacaoX(-anguloX);
		resultado = auxiliar->multiplica(rotacao);

		auxiliar = novaMatrizRotacaoY(-anguloY);
		resultado = resultado->multiplica(auxiliar);

		//auxiliar = novaMatrizRotacaoZ(-anguloZ);
		//resultado = resultado->multiplica(auxiliar);

		/*
		string teste = "";
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
			teste += to_string(resultado->getValor(i,j)) + " | ";
			}
			teste += "\n";
		}
		std::cout << teste << std::endl;
		*/

		return resultado;
	}

	Matriz<double>* getMatrizProjecaoPerspectiva(Coordenada3D* vrp, double anguloX, double anguloY, double distanciaCOP) {
		// fazer matriz translação * rotacaoX * rotacaoY
		Matriz<double> *resultado, *auxiliar, *rotacao;

		auxiliar = novaMatrizTranslacao(-(vrp->getX()), -(vrp->getY()), -(vrp->getZ()));
		rotacao = novaMatrizRotacaoX(-anguloX);
		resultado = auxiliar->multiplica(rotacao);

		auxiliar = novaMatrizRotacaoY(-anguloY);
		resultado = resultado->multiplica(auxiliar);

		// translada a distância do COP em Z
		auxiliar = novaMatrizTranslacao(0,0, distanciaCOP);
		resultado = resultado->multiplica(auxiliar);

		return resultado;
	}

	//! Método que faz transformações em coordenadas normalizadas de um elemento.
	/*!
		Faz as transformações usando a matriz passada.
		/param elem é o elemento gráfico que será feita a transformação.
		/param matrizResultado é a matriz utilizada para fazer a transformação.
	*/
	void fazProjecao(ElementoGrafico* elem, Matriz<double>* matrizResultado) {
		Tipo t = elem->getTipo();

		switch (t) {
			case PONTO: {
				Ponto* p = static_cast<Ponto*> (elem);
				Coordenada3D* nova = transformaCoordenada(p->getCoordenadaMundo(), matrizResultado);
				p->setCoordenadaNormal(nova);
				break;
			} case RETA: {
				Reta* r = static_cast<Reta*> (elem);
				Coordenada3D* novaInicial = transformaCoordenada(r->getCoordenadaMundoInicial(), matrizResultado);
				Coordenada3D* novaFinal = transformaCoordenada(r->getCoordenadaMundoFinal(), matrizResultado);
				r->setCoordenadaNormalInicial(novaInicial);
				r->setCoordenadaNormalFinal(novaFinal);
				break;
			} case POLIGONO: {
				Poligono* p = static_cast<Poligono*> (elem);

				ListaEnc<Coordenada3D*>* listaCoord = p->getListaMundo();
				Elemento<Coordenada3D*>* proxCoord = listaCoord->getHead();
				ListaEnc<Coordenada3D*>* listaNovasCoord = new ListaEnc<Coordenada3D*>();

				while (proxCoord != NULL) {
					Coordenada3D* coordPol = proxCoord->getInfo();
					Coordenada3D* coordTransformada = transformaCoordenada(coordPol, matrizResultado);
					listaNovasCoord->adiciona(coordTransformada);
					proxCoord = proxCoord->getProximo();
				}
				p->setListaNormal(listaNovasCoord);
				//free(listaCoord);
				break;
			} case CURVA: {
				Curva* c = static_cast<Curva*> (elem);

				ListaEnc<Coordenada3D*>* listaCoord = c->getListaMundo();
				Elemento<Coordenada3D*>* proxCoord = listaCoord->getHead();
				ListaEnc<Coordenada3D*>* listaNovasCoord = new ListaEnc<Coordenada3D*>();

				while (proxCoord != NULL) {
					Coordenada3D* coordCurva = proxCoord->getInfo();
					Coordenada3D* coordTransformada = transformaCoordenada(coordCurva, matrizResultado);
					listaNovasCoord->adiciona(coordTransformada);
					proxCoord = proxCoord->getProximo();
				}
				c->setListaNormal(listaNovasCoord);
				break;
			} case OBJETO3D: {
				Objeto3D* obj = static_cast<Objeto3D*> (elem);

				ListaEnc<Coordenada3D*>* listaCoord = obj->getListaCoordMundo();
				Elemento<Coordenada3D*>* proxCoord = listaCoord->getHead();
				ListaEnc<Coordenada3D*>* listaNovasCoords = new ListaEnc<Coordenada3D*>();
				while (proxCoord != NULL) {
					Coordenada3D* coordObj = proxCoord->getInfo();
					Coordenada3D* coordTransformada = transformaCoordenada(coordObj, matrizResultado);
					listaNovasCoords->adiciona(coordTransformada);
					proxCoord = proxCoord->getProximo();
				}
				obj->setListaCoordNormal(listaNovasCoords);
				ListaEnc<Aresta*>* listaAresta = obj->getListaArestaMundo();
				Elemento<Aresta*>* proxAresta = listaAresta->getHead();
				ListaEnc<Aresta*>* listaNovasArestas = new ListaEnc<Aresta*>();
				while (proxAresta != NULL) {
					Aresta* arestaAtual = proxAresta->getInfo();
					Coordenada3D *CoordMundoA, *CoordMundoB, *CoordNormalA, *CoordNormalB;
					CoordMundoA = arestaAtual->getCoordA();
					CoordMundoB = arestaAtual->getCoordB();
					int indiceCoordA = obj->getListaCoordMundo()->posicao(CoordMundoA);
					int indiceCoordB = obj->getListaCoordMundo()->posicao(CoordMundoB);
					CoordNormalA = obj->getListaCoordNormal()->elementoNoIndice(indiceCoordA);
					CoordNormalB = obj->getListaCoordNormal()->elementoNoIndice(indiceCoordB);
					Aresta* novaAresta = new Aresta(CoordNormalA, CoordNormalB);
					listaNovasArestas->adiciona(novaAresta);
					proxAresta = proxAresta->getProximo();
				}
				obj->setListaArestaNormal(listaNovasArestas);

				break;
			} case SUPERFICIE: {
				Superficie* s = static_cast<Superficie*> (elem);

				Matriz<Coordenada3D*>* matrizPontos = s->getPontosMundo();
				Matriz<Coordenada3D*>* novaMatrizPontos = s->getPontosNormais();

				int altura = matrizPontos->getNumLinhas();
				int largura = matrizPontos->getNumColunas();
				for (int i = 0; i < altura; i++) {
					for (int j = 0; j < largura; j++) {
						Coordenada3D* coordSup = matrizPontos->getValor(i, j);
						Coordenada3D* coordTransformada = transformaCoordenada(coordSup, matrizResultado);
						novaMatrizPontos->setValor(i, j, coordTransformada);
					}
				}

				break;
			}
		}
	}

	void fazProjecaoPerspectiva(ElementoGrafico* elem, double distanciaCOP) {
		Tipo t = elem->getTipo();

		switch (t) {
			case PONTO: {
				Ponto* p = static_cast<Ponto*> (elem);
				Coordenada3D* coord = p->getCoordenadaNormal();
				Coordenada3D* nova = new Coordenada3D( (coord->getX()/ (coord->getZ()/distanciaCOP)) , (coord->getY()/ (coord->getZ()/distanciaCOP)) , distanciaCOP);
				p->setCoordenadaNormal(nova);
				break;
			} case RETA: {
				Reta* r = static_cast<Reta*> (elem);
				Coordenada3D* coordIni = r->getCoordenadaNormalInicial();
				Coordenada3D* coordFin = r->getCoordenadaNormalFinal();
				Coordenada3D* novaInicial = new Coordenada3D( (coordIni->getX()/ (coordIni->getZ()/distanciaCOP)) , (coordIni->getY()/ (coordIni->getZ()/distanciaCOP)) , distanciaCOP);
				Coordenada3D* novaFinal = new Coordenada3D( (coordFin->getX()/ (coordFin->getZ()/distanciaCOP)) , (coordFin->getY()/ (coordFin->getZ()/distanciaCOP)) , distanciaCOP);
				r->setCoordenadaNormalInicial(novaInicial);
				r->setCoordenadaNormalFinal(novaFinal);
				break;
			} case POLIGONO: {
				Poligono* p = static_cast<Poligono*> (elem);

				ListaEnc<Coordenada3D*>* listaCoord = p->getListaNormal();
				Elemento<Coordenada3D*>* proxCoord = listaCoord->getHead();
				ListaEnc<Coordenada3D*>* listaNovasCoord = new ListaEnc<Coordenada3D*>();

				while (proxCoord != NULL) {
					Coordenada3D* coordPol = proxCoord->getInfo();
					Coordenada3D* coordTransformada = new Coordenada3D( (coordPol->getX()/ (coordPol->getZ()/distanciaCOP)) , (coordPol->getY()/ (coordPol->getZ()/distanciaCOP)) , distanciaCOP);
					listaNovasCoord->adiciona(coordTransformada);
					proxCoord = proxCoord->getProximo();
				}
				p->setListaNormal(listaNovasCoord);
				//free(listaCoord);
				break;
			} case CURVA: {
				Curva* c = static_cast<Curva*> (elem);

				ListaEnc<Coordenada3D*>* listaCoord = c->getListaNormal();
				Elemento<Coordenada3D*>* proxCoord = listaCoord->getHead();
				ListaEnc<Coordenada3D*>* listaNovasCoord = new ListaEnc<Coordenada3D*>();

				while (proxCoord != NULL) {
					Coordenada3D* coordCurva = proxCoord->getInfo();
					Coordenada3D* coordTransformada = new Coordenada3D( (coordCurva->getX()/ (coordCurva->getZ()/distanciaCOP)) , (coordCurva->getY()/ (coordCurva->getZ()/distanciaCOP)) , distanciaCOP);
					listaNovasCoord->adiciona(coordTransformada);
					proxCoord = proxCoord->getProximo();
				}
				c->setListaNormal(listaNovasCoord);
				break;
			} case OBJETO3D: {
				Objeto3D* obj = static_cast<Objeto3D*> (elem);

				ListaEnc<Coordenada3D*>* listaCoord = obj->getListaCoordNormal();
				Elemento<Coordenada3D*>* proxCoord = listaCoord->getHead();
				while (proxCoord != NULL) {
					Coordenada3D* coordObj = proxCoord->getInfo();
					Coordenada3D* coordTransformada = new Coordenada3D( (coordObj->getX()/ (coordObj->getZ()/distanciaCOP)), (coordObj->getY()/ (coordObj->getZ()/distanciaCOP)) , distanciaCOP);
					coordObj->setX(coordTransformada->getX());
					coordObj->setY(coordTransformada->getY());
					coordObj->setZ(coordTransformada->getZ());
					proxCoord = proxCoord->getProximo();
				}
				break;
			} case SUPERFICIE: {
				Superficie* s = static_cast<Superficie*> (elem);

				Matriz<Coordenada3D*>* matrizPontos = s->getPontosNormais();
				int altura = matrizPontos->getNumLinhas();
				int largura = matrizPontos->getNumColunas();

				for (int i = 0; i < altura; i++) {
					for (int j = 0; j < largura; j++) {
						Coordenada3D* coordSup = matrizPontos->getValor(i, j);
						Coordenada3D* coordTransformada = new Coordenada3D( (coordSup->getX()/ (coordSup->getZ()/distanciaCOP)), (coordSup->getY()/ (coordSup->getZ()/distanciaCOP)) , distanciaCOP);
						matrizPontos->setValor(i, j, coordTransformada);
					}
				}

				break;
			}
		}
	}

};

#endif