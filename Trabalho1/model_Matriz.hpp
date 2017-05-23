#ifndef MATRIZ_HPP
#define MATRIZ_HPP

template<typename T>
class Matriz {

private:
	T** matriz; /*!< Matriz que armazena os dados.*/
	int nLinhas, nColunas; /*!< Número de linhas e colunas da matriz, respectivamente.*/
public:


	//! Construtor.
	/*!
		/param numLinhas o numero de linhas da matriz.
		/param numColunas o numero de colunas da matriz.
	*/
	Matriz(int numLinhas, int numColunas) {
		nLinhas = numLinhas;
		nColunas = numColunas;

		matriz = new T*[numLinhas]();
		for(int i = 0; i < numLinhas; ++i) {
			matriz[i] = new T[numColunas]();
		}
	}

	//! Método que retorna o numero de linhas da matriz.
	/*!
		/return o numero de linhas da matriz.
	*/
	int getNumLinhas() {
		return nLinhas;
	}

	//! Método que retorna o numero de colunas da matriz.
	/*!
		/return o numero de colunas da matriz.
	*/
	int getNumColunas() {
		return nColunas;
	}

	//! Método que retorna um valor da matriz.
	/*!
		/param x é a linha onde esta o valor na matriz.
		/param y é a coluna onde esta o valor na matriz.
		/return retona o valor na posição.
	*/
	T getValor(int x, int y) {
		return matriz[x][y];
	}

	//! Método que altera um valor da matriz.
	/*!
		/param x é a linha onde o valor sera alterado.
		/param y é a coluna onde o valor sera alterado.
		/param novoValor é o valor para o qual será feita a alteração.
	*/
	void setValor(int x, int y, T novoValor) {
		matriz[x][y] = novoValor;
	}

	//! Método que multiplica a matriz por outra.
	/*!
		/param matriz2 é a matriz com a qual será feita a multiplicação.
		/return a matriz resultante da multiplicação.
	*/
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

	//! Método que transpõe a matriz
	/*!
		/return a matriz transposta.
	*/
	Matriz* transposta() {
		Matriz<T>* matrizResultado = new Matriz<T>(this->getNumColunas(), this->getNumLinhas());

		for (int i = 0; i < this->getNumLinhas(); ++i) {
			for (int j = 0; j < this->getNumColunas(); ++j) {
				matrizResultado->setValor(j, i, this->getValor(i, j));
			}
		}
		
		return matrizResultado;	
	}

};

#endif