#include <math.h>

class Transformacao {

private:
	//! Método que multiplica duas matrizes.
	/*!
		Faz a multiplicação de duas matrizes com no máximo 3 linhas e 3 colunas.
		/param matriz1 é a matriz à esquerda da multiplicação.
		/param matriz2 é a matriz à direita da multiplicação.
		/param linhasMatriz1 é a quantidade de linhas da matriz1.
		/return a matriz resultante da multiplicação.
	*/
	double** multiplicarMatrizes(double** matriz1, double** matriz2, int linhasMatriz1) {
		//double matrizResultado[3][3] /*= new double[3][3]*/;
		double **matrizResultado = new double*[3];
		for(int i = 0; i < 3; ++i) {
			matrizResultado[i] = new double[3];
		}

		for (int i = 0; i < linhasMatriz1; ++i) {
			for (int j = 0; j < 3; ++j) {
				for (int k = 0; k < 3; ++k) {
					matrizResultado[i][j] += matriz1[i][k] * matriz2[k][j];
				}
			}
		}

		return matrizResultado;
	}

	//! Método que multiplica um vetor por uma matriz.
	/*!
		Faz a multiplicação de um vetor com no máximo 3 colunas e uma matriz 3x3.
		/param vetor é o vetor (à esquerda da multiplicação).
		/param matriz é a matriz à direita da multiplicação.
		/return a matriz resultante da multiplicação.
	*/
	double* multiplicarVetorPorMatriz(double** vetor, double** matriz) {
		double** matrizMult = multiplicarMatrizes(vetor, matriz, 1);
		return matrizMult[0];
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
	double** novaMatrizTraslacao(double Dx, double Dy) {
		double **matriz = new double*[3];
		for(int i = 0; i < 3; ++i) {
			matriz[i] = new double[3];
		}
		
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				if (i == j) {
					matriz[i][j] = 1;
				}			
			}
		}
		matriz[2][0] = Dx;
		matriz[2][1] = Dy;
		return matriz;
	}

	//! Método que cria uma matriz de escalonamento em coordenadas homogêneas.
	/*!
		/param Sx é o valor de X do ponto para o qual será feita o escalonamento.
		/param Sy é o valor de Y do ponto para o qual será feita o escalonamento.
		/return uma matriz de escalonamento.
	*/
	double** novaMatrizEscalonamento(double Sx, double Sy) {
		double **matriz = new double*[3];
		for(int i = 0; i < 3; ++i) {
			matriz[i] = new double[3];
		}

		matriz[0][0] = Sx;
		matriz[1][1] = Sy;
		matriz[2][2] = 1;
		return matriz;
	}

#include <stdio.h>
	//! Método que cria uma matriz de rotação em coordenadas homogêneas.
	/*!
		/param angulo é o valor do ângulo para o qual será feita a rotação.
		/return uma matriz de rotação.
	*/
	double** novaMatrizRotacao(double angulo) {
		double **matriz = new double*[3];
		for(int i = 0; i < 3; ++i) {
			matriz[i] = new double[3];
		}
		
		double radianos = (angulo * M_PI/180.0);
		matriz[0][0] = cos (radianos);
		matriz[1][1] = cos (radianos);
		matriz[2][2] = 1;
		matriz[1][0] = (-1)*(sin (radianos));
		matriz[0][1] = (sin (radianos));
		std::cout << matriz[1][0] << std::endl;
		std::cout << matriz[0][1] << std::endl;
		return matriz;
	}

	//! Método que multiplica duas matrizes 3x3.
	/*!
		/param matriz1 é a matriz à esquerda da multiplicação.
		/param matriz2 é a matriz à direita da multiplicação.
		/return a matriz resultante da multiplicação.
	*/
	double** multiplicarMatrizes3x3(double** matriz1, double** matriz2) {
		return multiplicarMatrizes(matriz1, matriz2, 3);
	}

	//! Método que faz a transformação.
	/*!
		Faz a transformação sobre o ponto utilizando a matriz passada.
		/param coord é a Coordenada na qual será feita a transformação.
		/param matriz é a matriz de transformação.
		/return a coordenada depois de feita a transformação.
	*/
	Coordenada* transformaCoordenada(Coordenada* coord, double** matriz) {
		Coordenada* transformada;
		double **vetor = new double*[1];
		for(int i = 0; i < 1; ++i) {
			vetor[i] = new double[3];
		}
		
		vetor[0][0] = coord->getX();
		vetor[0][1] = coord->getY();
		vetor[0][2] = 1;

		double* resultado = multiplicarVetorPorMatriz(vetor, matriz);
		transformada = new Coordenada(resultado[0], resultado[1]);
		return transformada;

	}
	
};