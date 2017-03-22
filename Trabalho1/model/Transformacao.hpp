#include <math.h>

class Transformacao {

private:
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

	double* multiplicarVetorPorMatriz(double** vetor, double** matriz) {
		double** matrizMult = multiplicarMatrizes(vetor, matriz, 1);
		return matrizMult[1];
	}

public:
	/*Transformacao();
	~Transformacao();*/
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

	double** novaMatrizEscalonamento(double Sx, double Sy) {
		double **matriz = new double*[3];
		for(int i = 0; i < 3; ++i) {
			matriz[i] = new double[3];
		}

		matriz[0][0] = Sx;
		matriz[1][1] = Sx;
		matriz[2][2] = 1;
		return matriz;
	}

	double** novaMatrizRotacao(double angulo) {
		double **matriz = new double*[3];
		for(int i = 0; i < 3; ++i) {
			matriz[i] = new double[3];
		}
		
		matriz[0][0] = cos (angulo);
		matriz[1][1] = matriz[0][0];
		matriz[2][2] = 1;
		matriz[1][0] = sin (angulo);
		matriz[0][1] = -(matriz[1][0]);
		return matriz;
	}

	double** multiplicarMatrizes3x3(double** matriz1, double** matriz2) {
		return multiplicarMatrizes(matriz1, matriz2, 3);
	}

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