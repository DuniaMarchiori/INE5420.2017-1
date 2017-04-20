// Copyright [2017] <Dúnia Marchiori e Vinicius Steffani Schweitzer>

#include "Controller.hpp"

Controller* controller;

//! Método inicial
int main(int argc, char *argv[]) {
	
	controller = new Controller();
	controller->inicializarView(argc, argv);
	return 0;
	
}

#include "Callbacks.hpp"