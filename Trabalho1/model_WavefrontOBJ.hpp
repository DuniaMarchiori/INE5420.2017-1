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

//#include <iostream>
class WavefrontOBJ {

private:

	string nomeArquivoCriado, nomeArquivoFinal, elementosSalvos;
	int indiceArquivos, quantidadeVertices;

	bool arquivoExiste(const std::string& nomeArquivo) {
		struct stat buf;
		return (stat(nomeArquivo.c_str(), &buf) != -1); // se retorna -1, então o arquivo não existe
	}

	// valores são os valores que correspondem aos indices dos vertices na lista de vertices. é retornado então a lista dos vertices que são correspondidos na lista de valores
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

	void adicionaNoFimArquivo(string linha, string nomeArquivo) {
		std::ofstream novoArquivo; // abre pra escrita
		novoArquivo.open(nomeArquivo.c_str(), std::ios::app); // app = append
		novoArquivo << linha << std::endl;
		novoArquivo.close();
	}

	string verticeParaString(Coordenada* c) {
		quantidadeVertices++;
		string linha = "v " + std::to_string(c->getX()) + " " + std::to_string(c->getY());
		return linha;
	}

	string pontoParaString(Ponto* ponto) {
		adicionaNoFimArquivo(verticeParaString(ponto->getCoordenadaMundo()), nomeArquivoFinal);

		string novaLinha = "p";		
		novaLinha += " " + std::to_string(quantidadeVertices);

		return novaLinha;
	}

	string retaParaString(Reta* reta) {
		string novaLinha = "l";

		adicionaNoFimArquivo(verticeParaString(reta->getCoordenadaMundoInicial()), nomeArquivoFinal);
		novaLinha += " " + std::to_string(quantidadeVertices);

		adicionaNoFimArquivo(verticeParaString(reta->getCoordenadaMundoFinal()), nomeArquivoFinal);
		novaLinha += " " + std::to_string(quantidadeVertices);

		return novaLinha;
	}

	string poligonoParaString(Poligono* pol) {
		quantidadeVertices++;
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

	string curvaParaString(CurvaBSpline* c) {
		quantidadeVertices++;
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

	Reta* stringParaReta(string nomeElemento, ListaEnc<int>* valores, ListaEnc<Coordenada*>* listaVertices){
		Coordenada *cInicial, *cFinal;

		Elemento<int>* vertice = valores->getHead();
		cInicial = new Coordenada(listaVertices->elementoNoIndice( (vertice->getInfo()) -1));
		vertice = vertice->getProximo();
		cFinal = new Coordenada(listaVertices->elementoNoIndice( (vertice->getInfo()) -1));
		Reta* r = new Reta(nomeElemento, cInicial, cFinal);
		return r;
	}

	Poligono* stringParaPoligono(string nomeElemento, ListaEnc<int>* valores, ListaEnc<Coordenada*>* listaVertices){
		ListaEnc<Coordenada*>* listaAuxPoligono = percorreListaParaEncontrarVertices(listaVertices, valores);
		Poligono* pol = new Poligono(nomeElemento, listaAuxPoligono);
		return pol;
	}

	CurvaBSpline* stringParaCurva(string nomeElemento, ListaEnc<int>* valores, ListaEnc<Coordenada*>* listaVertices){
		ListaEnc<Coordenada*>* listaAuxCurva =  percorreListaParaEncontrarVertices(listaVertices, valores);
		CurvaBSpline* cbs = new CurvaBSpline(nomeElemento, listaAuxCurva);
		return cbs;
	}

public:
	WavefrontOBJ () {
		//nomeArquivoCriado = "elementosSalvos";
		indiceArquivos = 1;
		quantidadeVertices = 0;
		//nomeArquivoFinal = nomeArquivoCriado + ".obj";
	}

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

	void criaNovoArquivo(string caminhoArquivo) {
		int pos = caminhoArquivo.find_last_of("/");
		if (pos != string::npos) {
			nomeArquivoCriado = caminhoArquivo.substr(pos + 1, caminhoArquivo.size() - 1);
		}

		int ponto = nomeArquivoCriado.find_last_of(".");
		if (ponto != string::npos) {
			nomeArquivoCriado = nomeArquivoCriado.substr(0, ponto);;
		} 

		nomeArquivoFinal = nomeArquivoCriado + ".obj";

		while (arquivoExiste(nomeArquivoFinal)) {
			nomeArquivoFinal = nomeArquivoCriado + "-"+ std::to_string(indiceArquivos) + ".obj";
			indiceArquivos++;
		}

		std::ofstream novoArquivo(nomeArquivoFinal.c_str()); 
		novoArquivo.close();
	}

	// tem que chamar criaNovoArquivo antes de rodar a displayfile
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
			}

			case RETA: {
				Reta* reta = (static_cast<Reta*> (elemento));
				elementosSalvos += retaParaString(reta) + "\n";
				break;
			}

			case POLIGONO: {
				Poligono* pol = (static_cast<Poligono*> (elemento));
				elementosSalvos += poligonoParaString(pol) + "\n";
				break;
			}

			case CURVA: {
				CurvaBSpline* curva = (static_cast<CurvaBSpline*> (elemento));
				elementosSalvos += curvaParaString(curva) + "\n";
				break;
			}
		}
	} 

	void salvaElementosNoArquivo() {
		adicionaNoFimArquivo("\n", nomeArquivoFinal); // cria uma linha em branco
		adicionaNoFimArquivo(elementosSalvos, nomeArquivoFinal);
		elementosSalvos = "";
		quantidadeVertices = 0;
	}

};

#endif