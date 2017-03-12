#include <gtk/gtk.h>
#include <iostream>
#include <vector>

#include "Ponto.hpp"
#include "Reta.hpp"
#include "Poligono.hpp"

#include "Coordenada.hpp"

GtkWidget *window_Main;

GtkWidget *elmnt_List, *elmnt_Btn_Novo, *elmnt_Btn_Del;

GtkWidget *pos_Txt_Fator, *pos_Btn_Cima, *pos_Btn_Baixo, *pos_Btn_Esq, *pos_Btn_Dir;

GtkWidget *viewport_DrawingArea;
GtkWidget *window_NovoElemento;

// Main de testes básicos
int main(int argc, char *argv[]){
	
	Coordenada* c = new Coordenada();
	c->x = 5;
	c->setY(6);
	
	Coordenada* c2 = new Coordenada();
	c2->x = 7;
	c2->y = 8;
	
	
	Ponto* p = new Ponto(c);
	p->setNome("a");
	
	
	Reta* r = new Reta(c, c2);
	
	Poligono* pol = new Poligono();
	pol->adicionarCoordenada(c);

	GtkBuilder  *gtkBuilder;
	gtk_init(&argc, &argv);

	gtkBuilder = gtk_builder_new();
	gtk_builder_add_from_file(gtkBuilder, "janela.glade", NULL);

	window_Main = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Window_Main"));
	window_NovoElemento = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Window_NovoElmnt"));
	viewport_DrawingArea = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "Viewport_DrawingArea"));
	gtk_builder_connect_signals(gtkBuilder, NULL);
	gtk_widget_show(window_Main);
	gtk_main ();
	
	return 0;
}

#include "callbacks.hpp"
