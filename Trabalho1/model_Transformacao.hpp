#include <math.h>
#include "model_Matriz.hpp"

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
			case PONTO:
				{
					Ponto* p = static_cast<Ponto*> (elem);
					Coordenada* nova = transformaCoordenada(p->getCoordenadaMundo(), matrizResultado);
					p->setCoordenadaMundo(nova);
					break;
				}
			case RETA:
				{
					Reta* r = static_cast<Reta*> (elem);
					Coordenada* novaInicial = transformaCoordenada(r->getCoordenadaMundoInicial(), matrizResultado);
					Coordenada* novaFinal = transformaCoordenada(r->getCoordenadaMundoFinal(), matrizResultado);
					r->setCoordenadaMundoInicial(novaInicial);
					r->setCoordenadaMundoFinal(novaFinal);
					break;
				}
			case POLIGONO:
				{
					Poligono* p = static_cast<Poligono*> (elem);

					ListaEnc<Coordenada*>* listaCoord = p->getListaMundo();
					Elemento<Coordenada*>* proxCoord = listaCoord->getHead();
					ListaEnc<Coordenada*>* listaNovasCoord = new ListaEnc<Coordenada*>();

					while (proxCoord != NULL) {
						Coordenada* coordPol = proxCoord->getInfo();
						Coordenada* coordTransformada = transformaCoordenada(coordPol, matrizResultado);
						listaNovasCoord->adiciona(coordTransformada);
						proxCoord = proxCoord->getProximo();
					}
					p->setListaMundo(listaNovasCoord);
					free(listaCoord);
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
		/return uma matriz de translação.
	*/
	Matriz<double>* novaMatrizTraslacao(double Dx, double Dy) {
		Matriz<double> *matriz= new Matriz<double>(3,3);
		
		for (int i = 0; i < 3; ++i) {
			matriz->setValor(i, i, 1);
		}

		matriz->setValor(2, 0, Dx);
		matriz->setValor(2, 1, Dy);
		return matriz;
	}

	//! Método que cria uma matriz de escalonamento em coordenadas homogêneas.
	/*!
		/param Sx é o valor de X do ponto para o qual será feita o escalonamento.
		/param Sy é o valor de Y do ponto para o qual será feita o escalonamento.
		/return uma matriz de escalonamento.
	*/
	Matriz<double>* novaMatrizEscalonamento(double Sx, double Sy) {
		Matriz<double> *matriz= new Matriz<double>(3,3);

		matriz->setValor(0, 0, Sx);
		matriz->setValor(1, 1, Sy);
		matriz->setValor(2, 2, 1);
		return matriz;
	}

	//! Método que cria uma matriz de rotação em coordenadas homogêneas.
	/*!
		/param angulo é o valor do ângulo para o qual será feita a rotação.
		/return uma matriz de rotação.
	*/
	Matriz<double>* novaMatrizRotacao(double angulo) {
		Matriz<double> *matriz= new Matriz<double>(3,3);
		
		double radianos = (angulo * M_PI/180.0);
		matriz->setValor(0, 0, cos (radianos));
		matriz->setValor(1, 1, cos (radianos));
		matriz->setValor(2, 2, 1);
		matriz->setValor(1, 0, (-1)*(sin (radianos)));
		matriz->setValor(0, 1, sin (radianos));
		return matriz;
	}

	//! Método que faz a transformação.
	/*!
		Faz a transformação sobre o ponto utilizando a matriz passada.
		/param coord é a Coordenada na qual será feita a transformação.
		/param matriz é a matriz de transformação.
		/return a coordenada depois de feita a transformação.
	*/
	Coordenada* transformaCoordenada(Coordenada* coord, Matriz<double>* matriz) {
		Coordenada* transformada;
		Matriz<double> *vetor= new Matriz<double>(1,3);
		
		vetor->setValor(0, 0, coord->getX());
		vetor->setValor(0, 1, coord->getY());
		vetor->setValor(0, 2, 1);
		Matriz<double>* resultado = vetor->multiplica(matriz);
		
		transformada = new Coordenada(resultado->getValor(0,0), resultado->getValor(0,1));
		free(vetor);
		free(resultado);
		return transformada;

	}

	//! Método que realiza a translação em um elemento grafico.
	/*!
        /param elem o elemento grafico que sera transladado.
		/param coord uma coordenada contendo a quantidade de translação que sera aplicada em X e Y.
    */
	void fazTranslacao(ElementoGrafico* elem, Coordenada* coord) {
		Matriz<double> *resultado = novaMatrizTraslacao(coord->getX(), coord->getY());
		fazTransformacaoMundo(elem, resultado);
		free(resultado);
	}

	//! Método que realiza o escalonamento de um elemento grafico.
	/*!
        /param elem o elemento grafico que sera escalonado.
		/param fator uma coordenada contendo a quantidade de escalonamento que sera aplicada em X e Y.
    */
	void fazEscalonamento(ElementoGrafico* elem, Coordenada* fator) {
		Coordenada* centro = elem->getCentroGeometrico();
		Matriz<double> *resultadoAux, *resultado, *translacaoOrigem, *escalonamento, *translacaoVolta;
		translacaoOrigem = novaMatrizTraslacao(-(centro->getX()), -(centro->getY()));
		escalonamento = novaMatrizEscalonamento(fator->getX(), fator->getY());
		translacaoVolta = novaMatrizTraslacao(centro->getX(), centro->getY());

		// Traslada para a origem e escalona
		resultadoAux = translacaoOrigem->multiplica(escalonamento);
		// Translada para o lugar de antes
		resultado = resultadoAux->multiplica(translacaoVolta);

		fazTransformacaoMundo(elem, resultado);

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
	void fazRotacao(ElementoGrafico* elem, Coordenada* coord, double angulo) {
		Matriz<double> *resultadoAux, *resultado, *translacaoAteCoord, *rotacao, *translacaoVoltaDeCoord;
		translacaoAteCoord = novaMatrizTraslacao(-(coord->getX()), -(coord->getY()));
		rotacao = novaMatrizRotacao(angulo);
		translacaoVoltaDeCoord = novaMatrizTraslacao(coord->getX(), coord->getY());

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
	}

	//! Método que calcula a matriz para a tranformação de sistemas de coordenadas normalizadas.
	Matriz<double>* matrizSistemaCoordenadasNormalizadas(double angulo, Coordenada* fator, Coordenada* centroWin) {
		Matriz<double> *resultadoAux, *resultado, *translacaoAteCentro, *rotacao, *translacaoVoltaDeCentro;
		translacaoAteCentro = novaMatrizTraslacao(-(centroWin->getX()), -(centroWin->getY()));
		rotacao = novaMatrizRotacao(-angulo);
		translacaoVoltaDeCentro = novaMatrizEscalonamento(fator->getX(), fator->getY());

		// Matriz de transformação
		// Traslada para o centro da window e rotaciona
		resultadoAux = translacaoAteCentro->multiplica(rotacao);
		// Escalona
		resultado = resultadoAux->multiplica(translacaoVoltaDeCentro);		

		free(resultadoAux);
		free(translacaoAteCentro);
		free(translacaoVoltaDeCentro);
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
			case PONTO:
				{
					Ponto* p = static_cast<Ponto*> (elem);
					Coordenada* nova = transformaCoordenada(p->getCoordenadaMundo(), matrizResultado);
					p->setCoordenadaNormal(nova);
					break;
				}
			case RETA:
				{
					Reta* r = static_cast<Reta*> (elem);
					Coordenada* novaInicial = transformaCoordenada(r->getCoordenadaMundoInicial(), matrizResultado);
					Coordenada* novaFinal = transformaCoordenada(r->getCoordenadaMundoFinal(), matrizResultado);
					r->setCoordenadaNormalInicial(novaInicial);
					r->setCoordenadaNormalFinal(novaFinal);
					break;
				}
			case POLIGONO:
				{
					Poligono* p = static_cast<Poligono*> (elem);

					ListaEnc<Coordenada*>* listaCoord = p->getListaMundo();
					Elemento<Coordenada*>* proxCoord = listaCoord->getHead();
					ListaEnc<Coordenada*>* listaNovasCoord = new ListaEnc<Coordenada*>();

					while (proxCoord != NULL) {
						Coordenada* coordPol = proxCoord->getInfo();
						Coordenada* coordTransformada = transformaCoordenada(coordPol, matrizResultado);
						listaNovasCoord->adiciona(coordTransformada);
						proxCoord = proxCoord->getProximo();
					}
					p->setListaNormal(listaNovasCoord);
					//free(listaCoord);
					break;
				}
		}
	}
	
};