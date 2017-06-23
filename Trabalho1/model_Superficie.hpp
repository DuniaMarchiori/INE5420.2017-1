#ifndef SUPERFICIE_HPP
#define SUPERFICIE_HPP

#include "model_ElementoGrafico.hpp"
#include "model_Coordenada.hpp"
#include "model_Matriz.hpp"
#include "model_ForwardDifferences.hpp"

class Superficie: public ElementoGrafico {

private:
	Matriz<Coordenada3D*>* pontosMundo; /*!< Pontos de controle no mundo*/
	Matriz<Coordenada3D*>* pontosNormais; /*!< Pontos de controle normalizados*/
	Matriz<double>* mbs; /*! Matriz do método B-Spline*/
	Matriz<double>* matrizS; /*! Matriz S para criação da superfície.*/
	Matriz<double>* matrizT; /*! Matriz T para criação da superfície.*/
	ForwardDifferences* fwdDiff;
	Matriz<double>* DDx;
	Matriz<double>* DDy;
	Matriz<double>* DDz;

	void inicializaMatrizesST(double s, double t) {
		matrizS = new Matriz<double>(4, 4);
		matrizS->setValor(0, 0, pow(s, 3));
		matrizS->setValor(0, 1, pow(s, 2));
		matrizS->setValor(0, 2, s);
		matrizS->setValor(0, 3, 1);

		matrizT = new Matriz<double>(4, 4);
		matrizT->setValor(0, 0, pow(t, 3));
		matrizT->setValor(0, 1, pow(t, 2));
		matrizT->setValor(0, 2, t);
		matrizT->setValor(0, 3, 1);
	}

	double multiplicacaoMatrizesSuperficie(Matriz<double>* matrizG) {
		Matriz<double> *auxiliar, *mbTransposta, *tTransposta, *mb;
		mb = fwdDiff->inicializaMatrizMbezier();
		mbTransposta = mb->transposta();
		tTransposta = matrizT->transposta();
		double retorno;

		//s* m * pontos * m transposta * t transposta
		auxiliar = matrizS->multiplica(mb);
		auxiliar = auxiliar->multiplica(matrizG);
		auxiliar = auxiliar->multiplica(mbTransposta);
		auxiliar = auxiliar->multiplica(tTransposta);
		retorno = auxiliar->getValor(0, 0);

		free(mb);
		free(mbTransposta);
		free(tTransposta);
		free(auxiliar);
		free(matrizG);

		return retorno;
	}

	double multiplicacaoMatrizesX(Matriz<Coordenada3D*>* matrizRetalho) {
		Matriz<double>* matrizX = new Matriz<double>(4,4);
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				matrizX->setValor(i, j, matrizRetalho->getValor(i, j)->getX());
			}
		}

		/*string teste = "matrizX: ";
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				teste += to_string(matrizX->getValor(i,j)) + " | ";
			}
			teste += "\n";
		}
		std::cout << teste << std::endl;*/


		return multiplicacaoMatrizesSuperficie(matrizX);
	}

	double multiplicacaoMatrizesY(Matriz<Coordenada3D*>* matrizRetalho) {
		Matriz<double>* matrizY = new Matriz<double>(4,4);
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				matrizY->setValor(i, j, matrizRetalho->getValor(i, j)->getY());
			}
		}

		return multiplicacaoMatrizesSuperficie(matrizY);
	}

	double multiplicacaoMatrizesZ(Matriz<Coordenada3D*>* matrizRetalho) {
		Matriz<double>* matrizZ = new Matriz<double>(4,4);
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				matrizZ->setValor(i, j, matrizRetalho->getValor(i, j)->getZ());
			}
		}

		return multiplicacaoMatrizesSuperficie(matrizZ);
	}

	Matriz<double>* multiplicacaoCoeficientes(Matriz<double>* matrizG) {
		Matriz<double> *auxiliar, *mbsTransposta, *retorno;
		mbsTransposta = mbs->transposta();

		// mbs * g * msbTransposta
		auxiliar = mbs->multiplica(matrizG);
		retorno = auxiliar->multiplica(mbsTransposta);

		free(mbsTransposta);
		free(auxiliar);
		free(matrizG);

		return retorno;
	}

	Matriz<double>* coeficientesX(Matriz<Coordenada3D*>* matrizRetalho) {
		Matriz<double>* matrizX = new Matriz<double>(4,4);
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				matrizX->setValor(i, j, matrizRetalho->getValor(i, j)->getX());
			}
		}

		return multiplicacaoCoeficientes(matrizX);
	}

	Matriz<double>* coeficientesY(Matriz<Coordenada3D*>* matrizRetalho) {
		Matriz<double>* matrizY = new Matriz<double>(4,4);
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				matrizY->setValor(i, j, matrizRetalho->getValor(i, j)->getY());
			}
		}

		return multiplicacaoCoeficientes(matrizY);
	}

	Matriz<double>* coeficientesZ(Matriz<Coordenada3D*>* matrizRetalho) {
		Matriz<double>* matrizZ = new Matriz<double>(4,4);
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				matrizZ->setValor(i, j, matrizRetalho->getValor(i, j)->getZ());
			}
		}

		return multiplicacaoCoeficientes(matrizZ);
	}

	Matriz<double>* criaMatrizDD(Matriz<double>* eDeltaS, Matriz<double>* c, Matriz<double>* eDeltaT) {
		Matriz<double> *retorno, *auxiliar, *eDeltaTTransposta;
		eDeltaTTransposta = eDeltaT->transposta();

		auxiliar = eDeltaS->multiplica(c);
		retorno = auxiliar->multiplica(eDeltaTTransposta);

		free(auxiliar);
		free(eDeltaTTransposta);

		return retorno;
	}

	void atualizaMatrizesDD() {
		double valorDDx = 0, valorDDy = 0, valorDDz = 0;

		for (int i = 0; i < (DDx->getNumLinhas() - 1); ++i) { // "número de linhas - 1"  porque a última linha não é modificada
			for (int j = 0; j < DDx->getNumColunas(); ++j) {
				valorDDx = DDx->getValor(i, j) + DDx->getValor(i+1, j);
				valorDDy = DDy->getValor(i, j) + DDy->getValor(i+1, j);
				valorDDz = DDz->getValor(i, j) + DDz->getValor(i+1, j);

				DDx->setValor(i, j, valorDDx);
				DDy->setValor(i, j, valorDDy);
				DDz->setValor(i, j, valorDDz);
			}
		}
	}

public:
	//! Construtor
	Superficie() {
		pontosMundo = new Matriz<Coordenada3D*>(4, 4);
		pontosNormais = new Matriz<Coordenada3D*>(4, 4);
		setNome("");
		setTipo(SUPERFICIE);
		fwdDiff = new ForwardDifferences();
	}

	//! Construtor
	/*
		/param nome é o nome da superfície
	*/
	Superficie(string nome) {
		pontosMundo = new Matriz<Coordenada3D*>(4, 4);
		pontosNormais = new Matriz<Coordenada3D*>(4, 4);
		setNome(nome);
		setTipo(SUPERFICIE);
		fwdDiff = new ForwardDifferences();
	}

	//! Construtor
	/*
		/param nome é o nome da superfície
		/param pontosSuperficie é a matriz de pontos de controle da superfície
	*/
	Superficie(string nome, Matriz<Coordenada3D*>* pontosSuperficie) {
		setPontosMundo(pontosSuperficie);
		pontosNormais = new Matriz<Coordenada3D*>(pontosSuperficie->getNumLinhas(), pontosSuperficie->getNumColunas());
		setNome(nome);
		setTipo(SUPERFICIE);
		fwdDiff = new ForwardDifferences();
	}

	// Coordenadas no Mundo.

	//! Método que modifica a matriz de coordenadas do mundo da superfície
    /*!
        /param pontosSuperficie é a matriz de coordenadas que substituirá a anterior.
    */
	void setPontosMundo(Matriz<Coordenada3D*>* pontosSuperficie) {
		pontosMundo = pontosSuperficie;
	}

	//! Método que retorna a matriz de coordenadas do mundo da superfície
    /*!
        /return uma matriz das coordenadas da superfície.
    */
	Matriz<Coordenada3D*>* getPontosMundo() {
		return pontosMundo;
	}

	// Coordenadas Normalizadas

	//! Método que modifica a matriz de coordenadas normais da superfície
    /*!
        /param novosPontos é a matriz de coordenadas que substituirá a anterior.
    */
	void setPontosNormais(Matriz<Coordenada3D*>* pontosSuperficie) {
		pontosNormais = pontosSuperficie;
	}

	//! Método que retorna a matriz de coordenadas normais da superfície
    /*!
        /return uma matriz das coordenadas da superfície.
    */
	Matriz<Coordenada3D*>* getPontosNormais() {
		return pontosNormais;
	}

	//! Método que retorna o centro geométrico da superfície.
	/*!
		/return uma Coordenada que indica o centro geométrico da superfície.
	*/
	Coordenada3D* getCentroGeometrico() override {
		Coordenada3D* coord;

		int n = pontosMundo->getNumLinhas() * pontosMundo->getNumColunas();
		double somaX = 0, somaY = 0, somaZ = 0;

		for (int i = 0; i < pontosMundo->getNumLinhas(); i++) {
			for (int j = 0; j < pontosMundo->getNumColunas(); j++) {
				Coordenada3D* coordAtual = pontosMundo->getValor(i, j);
				somaX += coordAtual->getX();
				somaY += coordAtual->getY();
				somaZ += coordAtual->getZ();
			}
		}

		coord = new Coordenada3D( (somaX/n), (somaY/n), (somaZ/n) );

		return coord;
	}

	//! Método que retorna a distancia média dos pontos ao centro geométrico da superfície.
	/*!
		/return a distância média dos pontos até o centro da superfície
	*/
	double distanciaMediaDoCentro() {
		Coordenada3D* centro = getCentroGeometrico();

		double distMedia;
		double soma = 0;
		int n = pontosMundo->getNumLinhas() * pontosMundo->getNumColunas();

		for (int i = 0; i < pontosMundo->getNumLinhas(); i++) {
			for (int j = 0; j < pontosMundo->getNumColunas(); j++) {
				Coordenada3D* coordAtual = pontosMundo->getValor(i, j);
				soma += sqrt(pow((coordAtual->getX() - centro->getX()), 2) + pow((coordAtual->getY() - centro->getY()), 2) + pow((coordAtual->getZ() - centro->getZ()), 2));
			}
		}

		distMedia = soma / n;

		free(centro);
		return distMedia;
	}

	//! Método que retorna quantos retalhos há na superfície.
	/*!
		/return o número de retalhos da superfície.
	*/
	int getNumRetalhos() {
		int retalhosNaVertical = (pontosMundo->getNumLinhas() - 3);
		int retalhosNaHorizontal = (pontosMundo->getNumColunas() - 3);
		return (retalhosNaHorizontal * retalhosNaVertical);
	}

	//! Método que retorna um dos retalhos da superfície.
	/*!
		/param n O número do retalho desejado. (Começando por 0)
		/return O enésimo retalho.
	*/
	Matriz<Coordenada3D*>* getRetalhoN(int n) {
		if (n < 0 || n > getNumRetalhos()) {
			throw -1;
		}

		int linhaInicial = floor(n / (pontosMundo->getNumColunas() - 3));
		int colunaInicial = n % (pontosMundo->getNumColunas() - 3);

		Matriz<Coordenada3D*>* retalho = new Matriz<Coordenada3D*>(4,4);

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				Coordenada3D* coordIJRetalho = pontosNormais->getValor((linhaInicial + i), (colunaInicial + j));
				retalho->setValor(i, j, new Coordenada3D(coordIJRetalho));
			}
		}

		return retalho;
	}

	//! Método que retorna uma lista de listas de coordenadas.
	/*!
		/param numSegmentosT O número de segmentos em t
		/param numSegmentosS O número de segmentos em s
		/return uma lista de listas das coordenadas de cada curva.
	*/
	ListaEnc<ListaEnc<Coordenada3D*>*>* getSuperficieFinal(int numSegmentosT, int numSegmentosS) {
		double passoT = 1.0/(double)numSegmentosT;
		double passoS = 1.0/(double)numSegmentosS;
		ListaEnc<ListaEnc<Coordenada3D*>*>* listaFinal = new ListaEnc<ListaEnc<Coordenada3D*>*>();
		ListaEnc<Coordenada3D*>* novaLista = new ListaEnc<Coordenada3D*>();
		double x, y, z;

		mbs = fwdDiff-> inicializaMatrizMbs();

		for (int i = 0; i < getNumRetalhos(); ++i) {
			Matriz<Coordenada3D*>* retalhoAtual = getRetalhoN(i);

			double passoSAcumulado = 0, passoTAcumulado = 0;
			for (double s = 0; s <= numSegmentosS; s++) {

				for (double t = 0; t <= numSegmentosT; t++) {
					inicializaMatrizesST(passoSAcumulado, passoTAcumulado);
					/*std::cout << passoSAcumulado << std::endl;
					std::cout << passoTAcumulado << std::endl;*/
					x = multiplicacaoMatrizesX(retalhoAtual);
					y = multiplicacaoMatrizesY(retalhoAtual);
					z = multiplicacaoMatrizesZ(retalhoAtual);

					Coordenada3D* coord = new Coordenada3D(x, y, z);
					novaLista->adiciona(coord);

					passoTAcumulado += passoT;
					free(matrizS);
					free(matrizT);
				}

				listaFinal->adiciona(novaLista);
				novaLista = new ListaEnc<Coordenada3D*>();
				passoSAcumulado += passoS;
				passoTAcumulado = 0;
			}

			passoSAcumulado = 0, passoTAcumulado = 0;
			novaLista = new ListaEnc<Coordenada3D*>();

			for (double t = 0; t <= numSegmentosT; t++) {

				for (double s = 0; s <= numSegmentosS; s++) {
					inicializaMatrizesST(passoSAcumulado, passoTAcumulado);
					x = multiplicacaoMatrizesX(retalhoAtual);
					y = multiplicacaoMatrizesY(retalhoAtual);
					z = multiplicacaoMatrizesZ(retalhoAtual);

					Coordenada3D* coord = new Coordenada3D(x, y, z);
					novaLista->adiciona(coord);

					passoSAcumulado += passoS;
					free(matrizS);
					free(matrizT);
				}

				listaFinal->adiciona(novaLista);
				novaLista = new ListaEnc<Coordenada3D*>();
				passoTAcumulado += passoT;
				passoSAcumulado = 0;
			}

			free(retalhoAtual);
		}

		free(mbs);
		return listaFinal;
	}

	//! Método que retorna uma lista de listas de coordenadas.
	/*!
		/param numSegmentosT O número de segmentos em t
		/param numSegmentosS O número de segmentos em s
		/return uma lista de listas das coordenadas de cada curva.
	*/
	ListaEnc<ListaEnc<Coordenada3D*>*>* getSuperficieFinalForwardDifferences(int numSegmentosT, int numSegmentosS) {
		double passoT = 1.0/(double)numSegmentosT;
		double passoS = 1.0/(double)numSegmentosS;

		ListaEnc<ListaEnc<Coordenada3D*>*>* listaFinal = new ListaEnc<ListaEnc<Coordenada3D*>*>();
		ListaEnc<Coordenada3D*>* novaLista = new ListaEnc<Coordenada3D*>();

		Matriz<double>* eDeltaS;
		Matriz<double>* eDeltaT;
		
		mbs = fwdDiff-> inicializaMatrizMbs();

		for (int i = 0; i < getNumRetalhos(); ++i) {
			Matriz<Coordenada3D*>* retalhoAtual = getRetalhoN(i);

			eDeltaS = fwdDiff->criaMatrizE(passoS);
			eDeltaT = fwdDiff->criaMatrizE(passoT);

			Matriz<double>* cx = coeficientesX(retalhoAtual);
			Matriz<double>* cy = coeficientesY(retalhoAtual);
			Matriz<double>* cz = coeficientesZ(retalhoAtual);

			DDx = criaMatrizDD(eDeltaS, cx, eDeltaT);
			DDy = criaMatrizDD(eDeltaS, cy, eDeltaT);
			DDz = criaMatrizDD(eDeltaS, cz, eDeltaT);

			double x, dx,d2x, d3x, y, dy, d2y, d3y, z, dz, d2z, d3z;

			for (double t = 0; t < numSegmentosT; t++) {

				x   = DDx->getValor(0, 0);
				dx  = DDx->getValor(0, 1);
				d2x = DDx->getValor(0, 2);
				d3x = DDx->getValor(0, 3);

				y   = DDy->getValor(0, 0);
				dy  = DDy->getValor(0, 1);
				d2y = DDy->getValor(0, 2);
				d3y = DDy->getValor(0, 3);

				z   = DDz->getValor(0, 0);
				dz  = DDz->getValor(0, 1);
				d2z = DDz->getValor(0, 2);
				d3z = DDz->getValor(0, 3);

				fwdDiff->desenhaCurvaFwdDiff(numSegmentosS, x, dx, d2x, d3x, y, dy, d2y, d3y, z, dz, d2z, d3z, novaLista);
				listaFinal->adiciona(novaLista);
				novaLista = new ListaEnc<Coordenada3D*>();

				atualizaMatrizesDD();
			}

			free(DDx);
			free(DDy);
			free(DDz);
			Matriz<double>* DDxAux = criaMatrizDD(eDeltaS, cx, eDeltaT);
			Matriz<double>* DDyAux = criaMatrizDD(eDeltaS, cy, eDeltaT);
			Matriz<double>* DDzAux = criaMatrizDD(eDeltaS, cz, eDeltaT);
			DDx = DDxAux->transposta();
			DDy = DDyAux->transposta();
			DDz = DDzAux->transposta();

			//novaLista = new ListaEnc<Coordenada3D*>();
			for (double s = 0; s < numSegmentosS; s++) {

				x   = DDx->getValor(0, 0);
				dx  = DDx->getValor(0, 1);
				d2x = DDx->getValor(0, 2);
				d3x = DDx->getValor(0, 3);

				y   = DDy->getValor(0, 0);
				dy  = DDy->getValor(0, 1);
				d2y = DDy->getValor(0, 2);
				d3y = DDy->getValor(0, 3);

				z   = DDz->getValor(0, 0);
				dz  = DDz->getValor(0, 1);
				d2z = DDz->getValor(0, 2);
				d3z = DDz->getValor(0, 3);

				fwdDiff->desenhaCurvaFwdDiff(numSegmentosT, x, dx, d2x, d3x, y, dy, d2y, d3y, z, dz, d2z, d3z, novaLista);

				listaFinal->adiciona(novaLista);
				novaLista = new ListaEnc<Coordenada3D*>();

				atualizaMatrizesDD();
			}

			free(eDeltaS);
			free(eDeltaT);
			free(cx);
			free(cy);
			free(cz);
			free(DDx);
			free(DDy);
			free(DDz);
			free(DDxAux);
			free(DDyAux);
			free(DDzAux);

			free(retalhoAtual);
		}

		free(mbs);
		return listaFinal;
	}
};

#endif