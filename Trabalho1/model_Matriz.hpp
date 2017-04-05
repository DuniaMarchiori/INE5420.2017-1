#ifndef MATRIZ_HPP
#define MATRIZ_HPP

template<typename T>
class Matriz {

private:
	T** matriz; /*!< Matriz que armazena os dados.*/
	int nLinhas, nColunas;
public:


	//! Construtor.
	/*!
		/param numLinhas o numero de linhas da matriz.
		/param numColunas o numero de colunas da matriz.
	*/
	Matriz(int numLinhas, int numColunas) {
		nLinhas = numLinhas;
		nColunas = numColunas;

		matriz = new T*[numLinhas];
		for(int i = 0; i < numLinhas; ++i) {
			matriz[i] = new T[numColunas];
		}
	}

	//! Método que retorna o numero de linhas da matriz.
	int getNumLinhas() {
		return nLinhas;
	}

	//! Método que retorna o numero de colunas da matriz.
	int getNumColunas() {
		return nColunas;
	}

	//! Método que retorna um valor da matriz.
	/*!
		/param x é a posição x onde esta o valor na matriz.
		/param y é a posição y onde esta o valor na matriz.
	*/
	T getValor(int x, int y) {
		return matriz[x][y];
	}

	//! Método que altura um valor da matriz.
	/*!
		/param x é a posição em x onde o valor sera alterado.
		/param y é a posição em y onde o valor sera alterado.
	*/
	void setValor(int x, int y, T novoValor) {
		matriz[x][y] = novoValor;
	}

	Matriz* multiplica(Matriz* matriz2) {
		if (this->getNumColunas() == matriz2->getNumLinhas()) {
			Matriz<T>* matrizResultado = new Matriz<T>(this->getNumLinhas(), matriz2->getNumColunas());

			for (int i = 0; i < matrizResultado->getNumLinhas(); i++) {
				for (int j = 0; j < matrizResultado->getNumColunas(); j++) {
					T resultado = 0;
					for (int k = 0; k < this->getNumColunas(); k++) {
						
						resultado += this->getValor(i, k) * matriz2->getValor(k, j);
					}

					matrizResultado->setValor(i, j, resultado);
				}
			}

			return matrizResultado;
		} else {
			throw -1;
		}
	}

};

#endif