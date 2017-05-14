#ifndef OBJ_HPP
#define OBJ_HPP

#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include <sys/stat.h>

#include "model_Coordenada3D.hpp"
#include "model_ElementoGrafico.hpp"
#include "model_Ponto.hpp"
#include "model_Reta.hpp"
#include "model_Poligono.hpp"
//#include <CurvaBezier.cpp>
#include "model_CurvaBSpline.hpp"
#include "model_Objeto3D.hpp"
#include "model_Aresta.hpp"

using std::string;

/*!
	Implementação básica de Wavefront Obj, apenas com pontos, retas, poligonos e curvas (b-spline).
	Não interpreta arquivos de material.
*/
class WavefrontOBJ {

private:
	string caminho; /*!< O caminho do arquivo sendo editado no momento*/
	string nomeArquivoCriado; /*!< É apenas o nome do arquivo final*/
	string nomeArquivoFinal; /*!< É o nome do arquivo final com caminho e extensão*/
	string elementosSalvos; /*!< A parte do arquivo que contém a declaração dos elementos*/
	int indiceArquivos; /*!< Conta quantos arquivos possuem o mesmo nome*/
	int	quantidadeVertices; /*!< Variavel que armazena quantos vertices ja foram criados nesse .obj*/

	//! Método que diz se um arquivo existe.
	/*!
		/param nomeArquivo o caminho para o arquivo
		/return retorna -1 quando o arquivo não existe.
	*/
	bool arquivoExiste(const std::string& nomeArquivo) {
		struct stat buf;
		return (stat(nomeArquivo.c_str(), &buf) != -1); // se retorna -1, então o arquivo não existe
	}

	//! Método que percorre a lista de valores criando uma lista de coordenadas.
	/*!
		/param listaVertices A lista de todos os vertices
		/param valores É uma lista contendo quais pontos pertencem ao elemento.
		/return retorna os vertices do elemento.
	*/
	ListaEnc<Coordenada3D*>* percorreListaParaEncontrarVertices(ListaEnc<Coordenada3D*>* listaVertices, ListaEnc<int>* valores) {
		Elemento<int>* vertice = valores->getHead();
		ListaEnc<Coordenada3D*>* listaAux = new ListaEnc<Coordenada3D*>();

		while (vertice != NULL) {
			Coordenada3D* c = new Coordenada3D(listaVertices->elementoNoIndice( (vertice->getInfo()) -1));
			listaAux->adiciona(c);
			vertice = vertice->getProximo();
		}

		return listaAux;
	}

	//! Método que adiciona uma string no final do arquivo.
	/*!
		/param linha a string que sera adicionada ao final do arquivo.
		/param nomeArquivo é o caminho completo até o arquivo.
	*/
	void adicionaNoFimArquivo(string linha, string nomeArquivo) {
		std::ofstream novoArquivo; // abre pra escrita
		novoArquivo.open(nomeArquivo.c_str(), std::ios::app); // app = append
		novoArquivo << linha << std::endl;
		novoArquivo.close();
	}

	//! Método que retorna uma coordenada como uma string no formato de wavefrontObj.
	/*!
		/param c a Coordenada que sera transformada em string
		/return a string contendo a coordenada.
	*/
	string verticeParaString(Coordenada3D* c) {
		quantidadeVertices++;
		string linha = "v " + std::to_string(c->getX()) + " " + std::to_string(c->getY()) + " " + std::to_string(c->getZ());
		return linha;
	}

	//! Método que retorna um ponto como uma string no formato de wavefrontObj.
	/*!
		/param ponto o Ponto que sera transformado em string
		/return a string contendo o ponto.
	*/
	string pontoParaString(Ponto* ponto) {
		
		adicionaNoFimArquivo(verticeParaString(ponto->getCoordenadaMundo()), nomeArquivoFinal);

		string novaLinha = "p";
		novaLinha += " " + std::to_string(quantidadeVertices);

		return novaLinha;
		
		return NULL;
	}

	//! Método que retorna uma reta como uma string no formato de wavefrontObj.
	/*!
		/param reta a Reta que sera transformada em string
		/return a string contendo a reta.
	*/
	string retaParaString(Reta* reta) {
		
		string novaLinha = "l";

		adicionaNoFimArquivo(verticeParaString(reta->getCoordenadaMundoInicial()), nomeArquivoFinal);
		novaLinha += " " + std::to_string(quantidadeVertices);

		adicionaNoFimArquivo(verticeParaString(reta->getCoordenadaMundoFinal()), nomeArquivoFinal);
		novaLinha += " " + std::to_string(quantidadeVertices);

		return novaLinha;
		
		return NULL;
	}

	//! Método que retorna um poligono como uma string no formato de wavefrontObj.
	/*!
		/param pol o Poligono que sera transformado em string
		/return a string contendo o poligono.
	*/
	string poligonoParaString(Poligono* pol) {
		
		string novaLinha = "l";

		ListaEnc<Coordenada3D*>* lista = pol->getListaMundo();
		Elemento<Coordenada3D*>* vertice = lista->getHead();

		while (vertice != NULL) {
			adicionaNoFimArquivo(verticeParaString(vertice->getInfo()), nomeArquivoFinal);
			novaLinha += " " + std::to_string(quantidadeVertices);
			vertice = vertice->getProximo();
		}

		return novaLinha;
		
		return NULL;
	}

	//! Método que retorna uma curva como uma string no formato de wavefrontObj.
	/*!
		/param curva a Curva que sera transformada em string
		/return a string contendo a curva.
	*/
	string curvaParaString(CurvaBSpline* c) {
		
		string novaLinha = "curv";

		ListaEnc<Coordenada3D*>* lista = c->getListaMundo();
		Elemento<Coordenada3D*>* vertice = lista->getHead();

		while (vertice != NULL) {
			adicionaNoFimArquivo(verticeParaString(vertice->getInfo()), nomeArquivoFinal);
			novaLinha += " " + std::to_string(quantidadeVertices);
			vertice = vertice->getProximo();
		}

		return novaLinha;
		
		return NULL;
	}

	//! Método que retorna um objeto 3D como uma string no formato de wavefrontObj.
	/*!
		/param objeto é o Objeto3D que sera transformada em string
		/return a string contendo o objeto.
	*/
	string objeto3DParaString(Objeto3D* objeto) {
		return "# TODO objeto3DParaString()";
	}

	//! Método que converte uma string em uma coordenada.
	/*!
		/param stream é a stream que contem a string.
		/return a coordenada contida na string.
	*/
	Coordenada3D* stringParaCoordenada(std::stringstream& stream) {
		int* valores = new int[3]();
		double parametro = 0;
		int quantidadeParametros = 0;
		string palavra;

		while (stream >> palavra) {

			if (quantidadeParametros < 3) { // x, y e z
				try {
					parametro = std::stod(palavra);
					valores[quantidadeParametros] = parametro;
				} catch (...) {
					throw -1;
					// console "linha numeroLinha contém vértice com parâmetros inválidos
				}
				quantidadeParametros++;

			} else {
				throw -2;
				// console "linha numeroLinha contém vértice com mais de 2 parâmetros"
			}
		}

		Coordenada3D* c = new Coordenada3D(valores[0], valores[1], valores[2]);
		return c;
	}

	//! Método que converte uma string em um ponto.
	/*!
		/param é a stream que contem a string.
		/param nomeElemento é o nome desse ponto.
		/param listaVertices é a lista de todos os vertices do arquivo.
		/return o ponto contido na string.
	*/
	Ponto* stringParaPonto(std::stringstream& stream, string nomeElemento, ListaEnc<Coordenada3D*>* listaVertices) {
		
		string palavra;
		int vertice, quantidadeParametros = 0;

		while (stream >> palavra) {
			if (quantidadeParametros < 1) { // 1 vértice
				try {
					vertice = std::stoi(palavra);
				} catch (...) {
					throw -1;
					// console "linha numeroLinha contém ponto com parâmetros inválidos
				}
				quantidadeParametros++;
			} else {
				// console "linha numeroLinha contém ponto com mais de 1 vértice
				throw -2;
			}
		}

		Coordenada3D* c = new Coordenada3D(listaVertices->elementoNoIndice(vertice-1)); // porque os vértices no arquivo são indexados a partir do 1 e a lista é a partir do 0
		Ponto* p = new Ponto(nomeElemento, c);
		return p;
		
		return NULL;
	}

	//! Método que converte uma string em uma reta.
	/*!
		/param nomeElemento é o nome dessa reta.
		/param valores É uma lista contendo quais pontos pertencem a reta.
		/param listaVertices é a lista de todos os vertices do arquivo.
		/return a reta contida na string.
	*/
	Reta* stringParaReta(string nomeElemento, ListaEnc<int>* valores, ListaEnc<Coordenada3D*>* listaVertices) {
		
		Coordenada3D *cInicial, *cFinal;

		Elemento<int>* vertice = valores->getHead();
		cInicial = new Coordenada3D(listaVertices->elementoNoIndice( (vertice->getInfo()) -1));
		vertice = vertice->getProximo();
		cFinal = new Coordenada3D(listaVertices->elementoNoIndice( (vertice->getInfo()) -1));
		Reta* r = new Reta(nomeElemento, cInicial, cFinal);
		return r;
		
		return NULL;
	}

	//! Método que converte uma string em um poligono.
	/*!
		/param nomeElemento é o nome desse poligono.
		/param valores É uma lista contendo quais pontos pertencem ao poligono.
		/param listaVertices é a lista de todos os vertices do arquivo.
		/return o poligono contido na string.
	*/
	Poligono* stringParaPoligono(string nomeElemento, ListaEnc<int>* valores, ListaEnc<Coordenada3D*>* listaVertices) {
		
		ListaEnc<Coordenada3D*>* listaAuxPoligono = percorreListaParaEncontrarVertices(listaVertices, valores);
		Poligono* pol = new Poligono(nomeElemento, listaAuxPoligono);
		return pol;
		
		return NULL;
	}

	//! Método que converte uma string em uma curva.
	/*!
		/param nomeElemento é o nome dessa curva.
		/param valores É uma lista contendo quais pontos pertencem a curva.
		/param listaVertices é a lista de todos os vertices do arquivo.
		/return a curva contida na string.
	*/
	CurvaBSpline* stringParaCurva(string nomeElemento, ListaEnc<int>* valores, ListaEnc<Coordenada3D*>* listaVertices) {
		
		ListaEnc<Coordenada3D*>* listaAuxCurva =  percorreListaParaEncontrarVertices(listaVertices, valores);
		CurvaBSpline* cbs = new CurvaBSpline(nomeElemento, listaAuxCurva);
		return cbs;
		
	}

	ListaEnc<Aresta*>* stringParaFaceDeObjeto(ListaEnc<Coordenada3D*>* listaCoordenadas) {
		ListaEnc<Aresta*>* face = new ListaEnc<Aresta*>();

		Elemento<Coordenada3D*>* elementoInicial = listaCoordenadas->getHead();
		Elemento<Coordenada3D*>* elementoFinal;

		if (listaCoordenadas->getSize() == 1)
		{
			Aresta* novaAresta = new Aresta(elementoInicial->getInfo(), elementoInicial->getInfo());
			face->adiciona(novaAresta);

		} else {
			while(elementoInicial != NULL) {
				elementoFinal = elementoInicial->getProximo();
				if (elementoFinal != NULL) {
					Aresta* novaAresta = new Aresta(elementoInicial->getInfo(), elementoFinal->getInfo());
					face->adiciona(novaAresta);
				}
				elementoInicial = elementoInicial->getProximo();
			}

			elementoInicial = listaCoordenadas->getUltimoElemento();
			elementoFinal = listaCoordenadas->getHead();
			Aresta* novaAresta = new Aresta(elementoInicial->getInfo(), elementoFinal->getInfo());
			face->adiciona(novaAresta);
		}

		return face;
	}

public:

	//! Construtor
	WavefrontOBJ(){
		indiceArquivos = 1;
		quantidadeVertices = 0;
		caminho = "";
		nomeArquivoCriado = "";
		nomeArquivoFinal = "";
	}

	//! Método que carrega um obj.
	/*!
		/param nomeArquivo é o caminho completo para o arquivo.
		/return uma lista dos elementos graficos contidos nesse arquivo obj.
	*/
	ListaEnc<ElementoGrafico*>* carregarOBJ(string nomeArquivo) {
		std::ifstream arquivo(nomeArquivo);
		string linha, nomeElemento = "";
		int numeroLinha = 0;
		bool primeiraFace = true; // para auxilio com objetos3d
		Objeto3D* novoObjeto3D = NULL;
		ListaEnc<ElementoGrafico*>* listaRetorno = new ListaEnc<ElementoGrafico*>();
		ListaEnc<Coordenada3D*>* listaVertices = new ListaEnc<Coordenada3D*>();

		while ( std::getline(arquivo, linha) ) {

			numeroLinha++;

			// pegando só a primeira palavra da linha:
			std::stringstream stream(linha);
			string palavra;
			stream >> palavra;
			if (palavra == "v") { // é um vértice
				primeiraFace = true; // para controle de objetos3D

				Coordenada3D* c;
				try {
					c = stringParaCoordenada(stream);
				} catch (int erro) {
					free(listaVertices);
					throw numeroLinha;
				}

				listaVertices->adiciona(c);

			} else if (palavra == "p") { // é um ponto
				primeiraFace = true; // para controle de objetos3D

				if (nomeElemento != "") { // se foi passado um nome para esse elemento
					Ponto* p;
					try {
						p = stringParaPonto(stream, nomeElemento, listaVertices);
					} catch (int erro) {
						free(listaVertices);
						throw numeroLinha;
					}

					listaRetorno->adiciona(p);
					nomeElemento = "";

				} else { // não foi passado um nome válido para esse elemento
					free(listaVertices);
					throw numeroLinha;
					// console "nao é possivel adicionar um elemento sem nome"
				}

			} else if (palavra == "l") { // pode ser uma reta ou um polígono
				primeiraFace = true; // para controle de objetos3D

				ListaEnc<int>* valores = new ListaEnc<int>();
				int parametro = 0, quantidadeParametros = 0;

				if (nomeElemento != "") { // se foi passado um nome para esse elemento
					while (stream >> palavra) {
						try {
							parametro = std::stoi(palavra);
							valores->adiciona(parametro);
						} catch (...) {
							free(valores);
							free(listaVertices);
							throw numeroLinha;
							// console "linha numeroLinha contém line com parâmetros inválidos
						}
						quantidadeParametros++;
					}

					if (quantidadeParametros == 2) { // dois vértices indica uma reta
						Reta* r = stringParaReta(nomeElemento, valores, listaVertices);
						listaRetorno->adiciona(r);
						nomeElemento = "";

					} else if (quantidadeParametros > 2) { // mais de dois vértices indica um polígono
						Poligono* pol = stringParaPoligono(nomeElemento, valores, listaVertices);
						listaRetorno->adiciona(pol);
						nomeElemento = "";

					} else { // menos de dois vértices
						free(valores);
						free(listaVertices);
						throw numeroLinha;
						// console "linha numeroLinha deve conter pelo menos dois vertices"
					}
				} else { // não foi passado um nome válido para esse elemento
					free(valores);
					free(listaVertices);
					throw numeroLinha;
					// console "nao é possivel adicionar um elemento sem nome"
				}

				free(valores);

			} else if (palavra == "curv") { // é uma curva
				primeiraFace = true; // para controle de objetos3D

				ListaEnc<int>* valores = new ListaEnc<int>();
				int parametro = 0, quantidadeParametros = 0;

				if (nomeElemento != "") { // se foi passado um nome para esse elemento
					while (stream >> palavra) {
						try {
							parametro = std::stoi(palavra);
							valores->adiciona(parametro);
						} catch (...) {
							free(valores);
							free(listaVertices);
							throw numeroLinha;
							// console "linha numeroLinha contém curva com parâmetros inválidos
						}
						quantidadeParametros++;
					}
					if (quantidadeParametros >= 3) { // faz uma curva b-spline (precisa ter mais que 3 vértices)
						CurvaBSpline* cbs = stringParaCurva(nomeElemento, valores, listaVertices);
						listaRetorno->adiciona(cbs);
						nomeElemento = "";

					} else { // curva não tem no mínimo 3 vértices
						free(valores);
						free(listaVertices);
						throw numeroLinha;
						// console "linha numeroLinha deve conter pelo menos tres vertices"
					}
				} else { // não foi passado um nome válido para esse elemento
					free(valores);
					free(listaVertices);
					throw numeroLinha;
					// console "nao é possivel adicionar um elemento sem nome"
				}
				free(valores);

			} else if (palavra == "o") { // é o nome de um elemento
				primeiraFace = true; // para controle de objetos3D

				while (stream >> palavra) {
					nomeElemento += palavra;
				}

			} else if(palavra == "f") {
				if (primeiraFace) {
					if (novoObjeto3D != NULL) {
						listaRetorno->adiciona(novoObjeto3D);
					}

					if (nomeElemento != "") { // se foi passado um nome para esse elemento
						novoObjeto3D = new Objeto3D(nomeElemento);
						nomeElemento = "";
					} else { // não foi passado um nome válido para esse elemento
						free(listaVertices);
						throw numeroLinha;
					}
					primeiraFace = false;
				}

				ListaEnc<int>* valores = new ListaEnc<int>();
				int parametro = 0;

				while (stream >> palavra) {
						try {
							parametro = std::stoi(palavra);
							valores->adiciona(parametro);
						} catch (...) {
							free(valores);
							free(listaVertices);
							throw numeroLinha;
						}
				}

				//adiciona nova face no novoObjeto3D

				ListaEnc<Coordenada3D*>* listaCoordenadas = percorreListaParaEncontrarVertices(listaVertices, valores);
				ListaEnc<Aresta*>* listaArestas = stringParaFaceDeObjeto(listaCoordenadas);

				// append dessas duas listas no novoObjeto
				novoObjeto3D->appendListaCoordMundo(listaCoordenadas);
				novoObjeto3D->appendListaArestaMundo(listaArestas);


			}else if (palavra != "#" && palavra != "") { // '#' indica comentário. se o que sobrar não foi um comentário, então é um comando inválido
				free(listaVertices);
				throw numeroLinha;
				// console "comando 'palavra' não é suportado pelo sistema."
			}

			// depois de inserir cada elemento na display file, atualiza a tela.
		}

		free(listaVertices);

		//adiciona o último objeto3D
		listaRetorno->adiciona(novoObjeto3D);

		return listaRetorno;
	}

	//! Método que cria um arquivo.
	/*!
		/param caminhoArquivo é o caminho do novo arquivo, junto de seu nome.
	*/
	void criaNovoArquivo(string caminhoArquivo) {
		int pos = caminhoArquivo.find_last_of("/");
		if (pos != string::npos) {
			nomeArquivoCriado = caminhoArquivo.substr(pos + 1, caminhoArquivo.size() - 1);
			caminho = caminhoArquivo.substr(0, pos + 1);
		}

		int ponto = nomeArquivoCriado.find_last_of(".");
		if (ponto != string::npos) {
			nomeArquivoCriado = nomeArquivoCriado.substr(0, ponto);;
		}

		nomeArquivoFinal = caminho + nomeArquivoCriado + ".obj";

		while (arquivoExiste(nomeArquivoFinal)) {
			nomeArquivoFinal = caminho + nomeArquivoCriado + "-"+ std::to_string(indiceArquivos) + ".obj";
			indiceArquivos++;
		}

		std::ofstream novoArquivo(nomeArquivoFinal.c_str());
		novoArquivo.close();
		indiceArquivos = 1;
	}

	//! Método que salva um elemento grafico no arquivo.
	/*!
		/param elemento é o elemento que será salvo.
	*/
	void salvaVerticesNoArquivo(ElementoGrafico* elemento) {

		// case para tipo de elemento. dependendo do tipo, chama o metodo coorespondente ParaString
		// chama adicionaNoFimArquivo passando a string criada pelo metodo anterior e nomeArquivoFinal
		string nome = "o ";
		nome += elemento->getNome();
		elementosSalvos += nome + "\n";

		switch (elemento->getTipo()) {
			case PONTO: {
				Ponto* ponto = (static_cast<Ponto*> (elemento));
				elementosSalvos += pontoParaString(ponto) + "\n";
				break;
			} case RETA: {
				Reta* reta = (static_cast<Reta*> (elemento));
				elementosSalvos += retaParaString(reta) + "\n";
				break;
			} case POLIGONO: {
				Poligono* pol = (static_cast<Poligono*> (elemento));
				elementosSalvos += poligonoParaString(pol) + "\n";
				break;
			} case CURVA: {
				CurvaBSpline* curva = (static_cast<CurvaBSpline*> (elemento));
				elementosSalvos += curvaParaString(curva) + "\n";
				break;
			} case OBJETO3D: {
				Objeto3D* objeto = (static_cast<Objeto3D*> (elemento));
				elementosSalvos += objeto3DParaString(objeto) + "\n";
				break;
			}
		}
	}

	//! Método que salva os elementos no arquivo.
	void salvaElementosNoArquivo() {
		adicionaNoFimArquivo("\n", nomeArquivoFinal); // cria uma linha em branco
		adicionaNoFimArquivo(elementosSalvos, nomeArquivoFinal);
		elementosSalvos = "";
		quantidadeVertices = 0;
	}

};

#endif