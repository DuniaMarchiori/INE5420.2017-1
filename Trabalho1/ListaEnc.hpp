// Copyright [2015] <Dúnia Marchiori>

#ifndef LISTAENC_HPP
#define LISTAENC_HPP

#include "Elemento.hpp"
template<typename T>
    /*!
        Uma classe que implementa uma lista encadeada
    */
class ListaEnc {
 public:
    //! Construtor
    /*!
        Inicializa o tamanho da lista como -1 e o primeiro elemento como NULL
    */
	ListaEnc() {
	  size = -1;
	  head = NULL;
	}
	//! Destrutor
    /*!
        Destrói a lista
        \sa destroiLista
    */
	~ListaEnc() {
	    destroiLista();
	}
	// Início
	//! Método que adiciona um elemento no inicio da lista
    /*!
        Adiciona o dado passado no início da lista
        \param dado é o dado a ser adicionado
    */
	void adicionaNoInicio(const T& dado) {
	   Elemento<T>* novo = new Elemento<T>(dado, head);
	   if (novo == NULL) throw -1;
	   head = novo;
	   size++;
	}
	//! Método que retira um elemento do início da lista
    /*!
        Retira o primeiro elemento da lista
        \return retorna o elemento retirado
        \sa listaVazia
    */
	T retiraDoInicio() {
	    if (listaVazia()) throw -1;
	    Elemento<T>* saiu = head;
	    T volta = saiu->getInfo();
	    head = saiu->getProximo();
	    size--;
	    free(saiu);
	    return volta;
	}
	//! Método que elimina o primeiro elemento no início da lista
    /*!
        Libera a memória ocupada pelo elemento no início da lista
        \sa listaVazia
    */
	void eliminaDoInicio() {
	    if (listaVazia()) throw -1;
	    Elemento<T>* saiu = head;
	    head = saiu->getProximo();
	    size--;
	    free(saiu);
	}
	// Posição
	//! Método que adiciona um dado na posição indicada
	/*!
	    Adiciona um elemento na posição fornecida
	    \param dado é o elemento a ser adicionado
	    \pos é a posição em que o dado vai ser adicionado
	    \sa adicionaNoInicio
	*/
	void adicionaNaPosicao(const T& dado, int pos) {
	    if (pos > size + 1) throw -1;
	    if (pos == 0) {
	        adicionaNoInicio(dado);
	    } else {
	        Elemento<T>* novo = new Elemento<T>(dado, NULL);
	        if (novo == NULL) throw -1;
	        Elemento<T>* anterior = head;
	        for (int i = 0; i < pos - 1; i++) {
	            anterior = anterior->getProximo();
	        }
	        novo->setProximo(anterior->getProximo());
	        anterior->setProximo(novo);
	        size++;
	   }
	}
	//! Método que retorna a posição que está determinado elemento
	/*!
	    Indica a posição do dado fornecido
	    \param dado é o elemento que a posição deve ser encontrada
	    \return retorna um inteiro que é a posição do elemento
	    \sa listaVazia
	*/
	int posicao(const T& dado) const {
	    if (listaVazia()) throw -1;
	    Elemento<T>* elemAux = head;
	    T aux = elemAux->getInfo();
	    for (int i = 0; i <= size; i++) {
	         if (aux == dado) return i;
	         if (elemAux->getProximo() == NULL) throw -1;
	         elemAux = elemAux->getProximo();
	         aux = elemAux->getInfo();
	    }
	}
	//! Método que mostra a posição de memória do dado
	/*!
	    Indica a posição de memória do elemento fornecido
	    \dado é o elemento que a posição de memória deverá ser retornado
	    \return retorna a posição de memória do dado
	*/
	T* posicaoMem(const T& dado) const {
	    if (listaVazia()) throw -1;
	    Elemento<T>* elemAux = head;
	    T aux = elemAux->getInfo();
	    for (int i = 0; i <= size; i++) {
	         if (aux == dado) return elemAux;
	         if (elemAux->getProximo() == NULL) throw -1;
	         elemAux = elemAux->getProximo();
	         aux = elemAux->getInfo();
	    }
	}
	//! Método que verifica se a lista contém determinado elemento
	/*!
	    Indica se um elemento está contido na lista
	    \param dado é o elemento a ser verificado
	    \return retorna um boolean se o dado está ou não contido na lista
	    \sa listaVazia
	*/
	bool contem(const T& dado) {
	    if (listaVazia()) throw -1;
	    Elemento<T>* elemAux = head;
	    T aux = elemAux->getInfo();
	    for (int i = 1; i <= size+1; i++) {
	         if (aux == dado) return true;
	         if (elemAux->getProximo() == NULL) return false;
	         elemAux = elemAux->getProximo();
	         aux = elemAux->getInfo();
	    }
	}
	//! Método que retira um elemento da posição indicada
	/*!
	    Retira da lista o elemento na posição fornecida
	    \param pos é a posição que o elemento deve ser retirado
	    \return retorna o dado retirado
	    \sa listaVazia
	*/
	T retiraDaPosicao(int pos) {
	    if (listaVazia()) throw -1;
	    if (pos > size) throw -1;
	    if (pos == 0) {
	        retiraDoInicio();
	    } else {
	        Elemento<T>* anterior = head;
	        for (int i = 0; i < pos - 1; i++) {
	            anterior = anterior->getProximo();
	        }
	        Elemento<T>* eliminar = anterior->getProximo();
	        T volta = eliminar->getInfo();
	        anterior->setProximo(eliminar->getProximo());
	        size--;
	        free(eliminar);
	        return volta;
	   }
	}
	// Fim
	//! Método que adiciona o dado no fim da lista
	/*!
	    Adiciona o elemento fornecido no fim da lista
	    \param dado é o dado a ser adicionado
	    \sa listaVazia, adicionaNoInicio
	*/
	void adiciona(const T& dado) {
	    if (listaVazia()) {
	        adicionaNoInicio(dado);
	    } else {
	        Elemento<T>* anterior = head;
	        Elemento<T>* novo = new Elemento<T>(dado, NULL);
	        if (novo == NULL) throw -1;
	        while (anterior->getProximo() != NULL) {
	            anterior = anterior->getProximo();
	        }
	        anterior->setProximo(novo);
	        size++;
	   }
	}
	//! Método que retira do fim da lista
	/*!
	    Retira o último elemento da lista
	    \return retorna o dado retirado
	    \sa listaVazia
	*/
	T retira() {
	    if (listaVazia()) throw -1;
	    Elemento<T>* anterior;
	    Elemento<T>* atual = head;
	    while (atual->getProximo() != NULL) {
	        anterior = atual;
	        atual = atual->getProximo();
	    }
	    anterior->setProximo(NULL);
	    T volta = atual->getInfo();
	    free(atual);
	    size--;
	    return volta;
	}
	// Específico
	//! Método que retira um elemento específico
	/*!
	    Retira o elemento fornecido
	    \param dado é o dado que vai ser retirado da lista
	    \return retorna o dado retirado
	    \sa listaVazia, retiraDaPosicao
	*/
	T retiraEspecifico(const T& dado) {
	     if (listaVazia()) throw -1;
	     Elemento<T>* aux = head;
	     for (int i = 0; i < size; i++) {
	        if (igual(dado, aux->getInfo())) {
	            return retiraDaPosicao(i);
	        }
	        aux = aux->getProximo();
	     }
	     throw -1;
	}
	//! Método que adiciona os elementos na lista em ordem
	/*!
	   O elemento é adicionado em ordem na lista
	   \param data é o elemento a ser adicionado
	   \sa listaVazia, adicionaNoInicio, adicionaNaPosicao
	*/
	void adicionaEmOrdem(const T& data) {
	    if (listaVazia()) return adicionaNoInicio(data);
	    Elemento<T>* atual = head;
	    int pos = 1;
	    while (atual->getProximo() != NULL && maior(data, atual->getInfo())) {
	        atual = atual->getProximo();
	        pos++;
	    }
	    if (maior(data, atual->getInfo())) adicionaNaPosicao(data, pos + 1);
	    else
	        adicionaNaPosicao(data, pos);
	}
	//! Método que indica se a lista está vazia
	/*!
	    Mostra se a lista está vazia
	    \return retorna um boolean que indica se a lista está vazia
	*/
	bool listaVazia() const {
	    return (size == -1);
	}
	//! Método que indica se um dado é igual a outro
	/*!
	    Mostra se dois dados são iguais
	    \return retorna um boolean que indica se os dados são iguais
	*/
	bool igual(T dado1, T dado2) {
	    return (dado1 == dado2);
	}
	//! Método que indica se um dado é maior que outro
	/*!
	    Mostra se o primeiro dado é maior que outro
	    \return retorna um boolean que indica se um dado é maior que outro
	*/
	bool maior(T dado1, T dado2) {
	    return (dado1 > dado2);
	}
	//! Método que indica se um dado é menor que outro
	/*!
	    Mostra se o primeiro dado é menor que outro
	    \return retorna um boolean que indica se um dado é menor que outro
	*/
	bool menor(T dado1, T dado2) {
	    return (dado1 < dado2);
	}
	//! Método que destrói a lista
	/*!
	    Destrói a lista
	*/
	void destroiLista() {
	    while (!listaVazia()) {
	        eliminaDoInicio();
	    }
	}
    //! Método que retorna o primeiro elemento da lista
    /*
        Retorna o primeiro dado da lista
        \return retorna o primeiro dado da lista
    */
	T primeiroElemento() {
	    return head->getInfo();
	}

 private:
	Elemento<T>* head; /*!< Guarda o primeiro elemento da lista */
	int size; /*!< Inteiro que guarda o tamanho da lista */
};

#endif