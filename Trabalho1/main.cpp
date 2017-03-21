#include <gtk/gtk.h>

#include "Controller.hpp"

Controller* controller;

// !Método inicial
int main(int argc, char *argv[]) {
	
	controller = new Controller();
	controller->inicializarView(argc, argv);
	return 0;
	
}

#include "Callbacks.hpp"