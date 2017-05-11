#include <math.h>
#include <iostream>

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "model_Coordenada3D.hpp"
#include "model_Poligono.hpp"
#include "ListaEnc.hpp"

class Window {

private:
	Coordenada3D* VRP;
	double angX, angY, angZ;
	double altura, largura;
	//Coordenada3D *vetorFrente, *vetorDireita, *vetorCima;

public:
	//! Construtor
	/*!

	*/
	Window(Coordenada3D* pos, double alt, double larg, double _angX, double _angY, double _angZ) {
		VRP = pos;
		altura = alt;
		largura = larg;
		angX = _angX;
		angY = _angY;
		angZ = _angZ;
		//vetorFrente = new Coordenada3D(0, 0, 1);
		//vetorDireita = new Coordenada3D(1, 0, 0);
		//vetorCima = new Coordenada3D(0, 1, 0);
		//atualizarVetores();
	}

	//! Método que retorna a altura da window.
	/*!
		/return altura da window.
	*/
	double getAltura() {
		return altura;
	}

	//! Método que retorna a largura da window.
	/*!
		/return largura da window.
	*/
	double getLargura() {
		return largura;
	}

	//! Método que retorna a posição da VRP.
	/*!
		/return a coordenada VRP da window.
	*/
	Coordenada3D* getVRP() {
		return VRP;
	}

	//! Método que altera a VRP.
	void setVRP(Coordenada3D* novaVRP) {
		free(VRP);
		VRP = novaVRP;
	}

	double getAnguloX() {
		return angX;
	}

	double getAnguloY() {
		return angY;
	}

	double getAnguloZ() {
		return angZ;
	}

	void rotacionarX(double fator) {
		angX += fator;
		while (angX >= 360) {
			angX -= 360;
		}
		while (angX < 0) {
			angX += 360;
		}
		//atualizarVetores();
	}

	void rotacionarY(double fator) {
		angY += fator;
		while (angY >= 360) {
			angY -= 360;
		}
		while (angY < 0) {
			angY += 360;
		}
		//atualizarVetores();
	}

	void rotacionarZ(double fator) {
		angZ += fator;
		while (angZ >= 360) {
			angZ -= 360;
		}
		while (angZ < 0) {
			angZ += 360;
		}
		//atualizarVetores();
	}

	//! Método que move a window pelos eixos do mundo.
	void zoom(double fator) {
		altura -= altura * (fator/100);
		largura -= largura * (fator/100);
	}
	
	//! Método que move a window pelos eixos do mundo.
	void moverWindow(double fatX, double fatY, double fatZ) {
		setVRP(new Coordenada3D( (VRP->getX() + fatX), (VRP->getY() + fatY),(VRP->getZ() + fatZ) ));
		/*
		double movX, movY, movZ;

		Coordenada3D* movDir = new Coordenada3D(vetorDireita->getX() * fatX, vetorDireita->getY() * fatX, vetorDireita->getZ() * fatX);
		Coordenada3D* movCima = new Coordenada3D(vetorCima->getX() * fatY, vetorCima->getY() * fatY, vetorCima->getZ() * fatY);
		Coordenada3D* movFrente = new Coordenada3D(vetorFrente->getX() * fatZ, vetorFrente->getY() * fatZ, vetorFrente->getZ() * fatZ);

		movX = movDir->getX() + movCima->getX() + movFrente->getX();
		movY = movDir->getY() + movCima->getY() + movFrente->getY();
		movZ = movDir->getZ() + movCima->getZ() + movFrente->getZ();
		setVRP(new Coordenada3D( (VRP->getX() + movX), (VRP->getY() + movY),(VRP->getZ() + movZ) ));

		free(movDir);
		free(movCima);
		free(movFrente);
		*/
	}

	/*
	void atualizarVetores() {
		double angXRad = angX * M_PI / 180;
		double angYRad = angY * M_PI / 180;
		double angZRad = angZ * M_PI / 180;
		free(vetorFrente);
		free(vetorDireita);
		free(vetorCima);

		vetorFrente = new Coordenada3D(sin(angYRad), -sin(-angXRad) * cos(angYRad), cos(-angXRad) * cos(angYRad));

		vetorDireita = new Coordenada3D(-cos(-angZRad) * cos(angYRad), -sin(-angZRad), sin(angYRad) * cos(-angZRad));

		vetorCima = new Coordenada3D(-sin(angZRad), cos(angZRad) * cos(angXRad), cos(angZRad) * sin(angXRad));

		std::cout << "aX:" << angX << " aY:" << angY << " aZ:" << angZ << std::endl;
		std::cout << "Forward: " << vetorFrente->getX() << ", " << vetorFrente->getY() << ", " << vetorFrente->getZ() << std::endl;
		std::cout << "Right: " << vetorDireita->getX() << ", " << vetorDireita->getY() << ", " << vetorDireita->getZ() << std::endl;
		std::cout << "Up: " << vetorCima->getX() << ", " << vetorCima->getY() << ", " << vetorCima->getZ() << std::endl;
		std::cout << std::endl;
	}
	*/
};

#endif
