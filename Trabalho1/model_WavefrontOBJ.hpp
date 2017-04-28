#ifndef OBJ_HPP
#define OBJ_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <sys/stat.h>

#include "model_Coordenada.hpp"
#include "model_ElementoGrafico.hpp"
#include "model_Ponto.hpp"
#include "model_Reta.hpp"
#include "model_Poligono.hpp"
//#include <CurvaBezier.cpp>
#include "model_CurvaBSpline.hpp"

using std::string;

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
	ListaEnc<Coordenada*>* percorreListaParaEncontrarVertices(ListaEnc<Coordenada*>* listaVertices, ListaEnc<int>* valores) {
		Elemento<int>* vertice = valores->getHead();
		ListaEnc<Coordenada*>* listaAux = new ListaEnc<Coordenada*>();

		while (vertice != NULL) {
			Coordenada* c = new Coordenada(listaVertices->elementoNoIndice( (vertice->getInfo()) -1));
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
	string verticeParaString(Coordenada* c) {
		quantidadeVertices++;
		string linha = "v " + std::to_string(c->getX()) + " " + std::to_string(c->getY());
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
	}

	//! Método que retorna um poligono como uma string no formato de wavefrontObj.
	/*!
		/param pol o Poligono que sera transformado em string
		/return a string contendo o poligono.
	*/
	string poligonoParaString(Poligono* pol) {
		string novaLinha = "l";

		ListaEnc<Coordenada*>* lista = pol->getListaMundo();
		Elemento<Coordenada*>* vertice = lista->getHead();

		while (vertice != NULL) {
			adicionaNoFimArquivo(verticeParaString(vertice->getInfo()), nomeArquivoFinal);
			novaLinha += " " + std::to_string(quantidadeVertices);
			vertice = vertice->getProximo();
		}

		return novaLinha;
	}

	//! Método que retorna uma curva como uma string no formato de wavefrontObj.
	/*!
		/param curva a Curva que sera transformada em string
		/return a string contendo a curva.
	*/
	string curvaParaString(CurvaBSpline* c) {
		string novaLinha = "curv";

		ListaEnc<Coordenada*>* lista = c->getListaMundo();
		Elemento<Coordenada*>* vertice = lista->getHead();

		while (vertice != NULL) {
			adicionaNoFimArquivo(verticeParaString(vertice->getInfo()), nomeArquivoFinal);
			novaLinha += " " + std::to_string(quantidadeVertices);
			vertice = vertice->getProximo();
		}

		return novaLinha;
	}

	//! Método que converte uma string em uma coordenada.
	/*!
		/param stream é a stream que contem a string.
		/return a coordenada contida na string.
	*/
	Coordenada* stringParaCoordenada(std::stringstream& stream) {
		int* valores = new int[2]();
		double parametro = 0;
		int quantidadeParametros = 0;
		string palavra;

		while (stream >> palavra) {

			if (quantidadeParametros < 2) { // x e y
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

		Coordenada* c = new Coordenada(valores[0], valores[1]);
		return c;
	}

	//! Método que converte uma string em um ponto.
	/*!
		/param é a stream que contem a string.
		/param nomeElemento é o nome desse ponto.
		/param listaVertices é a lista de todos os vertices do arquivo.
		/return o ponto contido na string.
	*/
	Ponto* stringParaPonto(std::stringstream& stream, string nomeElemento, ListaEnc<Coordenada*>* listaVertices) {
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

		Coordenada* c = new Coordenada(listaVertices->elementoNoIndice(vertice-1)); // porque os vértices no arquivo são indexados a partir do 1 e a lista é a partir do 0
		Ponto* p = new Ponto(nomeElemento, c);
		return p;
	}

	//! Método que converte uma string em uma reta.
	/*!
		/param nomeElemento é o nome dessa reta.
		/param valores É uma lista contendo quais pontos pertencem a reta.
		/param listaVertices é a lista de todos os vertices do arquivo.
		/return a reta contida na string.
	*/
	Reta* stringParaReta(string nomeElemento, ListaEnc<int>* valores, ListaEnc<Coordenada*>* listaVertices){
		Coordenada *cInicial, *cFinal;

		Elemento<int>* vertice = valores->getHead();
		cInicial = new Coordenada(listaVertices->elementoNoIndice( (vertice->getInfo()) -1));
		vertice = vertice->getProximo();
		cFinal = new Coordenada(listaVertices->elementoNoIndice( (vertice->getInfo()) -1));
		Reta* r = new Reta(nomeElemento, cInicial, cFinal);
		return r;
	}

	//! Método que converte uma string em um poligono.
	/*!
		/param nomeElemento é o nome desse poligono.
		/param valores É uma lista contendo quais pontos pertencem ao poligono.
		/param listaVertices é a lista de todos os vertices do arquivo.
		/return o poligono contido na string.
	*/
	Poligono* stringParaPoligono(string nomeElemento, ListaEnc<int>* valores, ListaEnc<Coordenada*>* listaVertices){
		ListaEnc<Coordenada*>* listaAuxPoligono = percorreListaParaEncontrarVertices(listaVertices, valores);
		Poligono* pol = new Poligono(nomeElemento, listaAuxPoligono);
		return pol;
	}

	//! Método que converte uma string em uma curva.
	/*!
		/param nomeElemento é o nome dessa curva.
		/param valores É uma lista contendo quais pontos pertencem a curva.
		/param listaVertices é a lista de todos os vertices do arquivo.
		/return a curva contida na string.
	*/
	CurvaBSpline* stringParaCurva(string nomeElemento, ListaEnc<int>* valores, ListaEnc<Coordenada*>* listaVertices){
		ListaEnc<Coordenada*>* listaAuxCurva =  percorreListaParaEncontrarVertices(listaVertices, valores);
		CurvaBSpline* cbs = new CurvaBSpline(nomeElemento, listaAuxCurva);
		return cbs;
	}

public:

	//! Construtor
	WavefrontOBJ () {
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
		ListaEnc<ElementoGrafico*>* listaRetorno = new ListaEnc<ElementoGrafico*>();
		ListaEnc<Coordenada*>* listaVertices = new ListaEnc<Coordenada*>();

		while ( std::getline(arquivo, linha) ) {

			numeroLinha++;

			// pegando só a primeira palavra da linha:
			std::stringstream stream(linha);
			string palavra;
			stream >> palavra;
			if (palavra == "v") { // é um vértice

				Coordenada* c;
				try {
					c = stringParaCoordenada(stream);
				} catch (int erro) {
					free(listaVertices);
					throw numeroLinha;
				}

				listaVertices->adiciona(c);

			} else if (palavra == "p") { // é um ponto

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
				while (stream >> palavra) {
					nomeElemento += palavra;
				}

			} else if (palavra != "#" && palavra != "") { // '#' indica comentário. se o que sobrar não foi um comentário, então é um comando inválido
				free(listaVertices);
				throw numeroLinha;
				// console "comando 'palavra' não é suportado pelo sistema."
			}

			// depois de inserir cada elemento na display file, atualiza a tela.
		}

		free(listaVertices);
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