// Métodos da janela principal.

//  Método para fechar o programa quando a janela principal é fechada.
extern "C" G_MODULE_EXPORT void Window_Main_destroy_cb(){
	gtk_main_quit();
}

//  Métodos da região do Menu de Funções.

//  Métodos do menu de Elementos.

//  Método do botão de novo elemento.
extern "C" G_MODULE_EXPORT void Elmnt_Btn_Novo_clicked_cb(){
	listaCoordsPoligono = new ListaEnc<Coordenada*>();
	gtk_widget_show(window_NovoElemento);
}

//  Método do botão de deletar elemento.
extern "C" G_MODULE_EXPORT void Elmnt_Btn_Del_clicked_cb(){
	displayFile->retiraDaPosicao(getIndexElementoDeletado(elmnt_List));
	update_Surface();
	inserirTextoConsole("Elemento excluído.");
}

//  Método do botão de mover a window para Cima.
extern "C" G_MODULE_EXPORT void Pos_Btn_Cima_clicked_cb(){
	double fator = 0;
	
	try {
		fator = stod(gtk_entry_get_text((GtkEntry*) pos_Txt_Fator));
	} catch (const invalid_argument& e) {
		return;
	}
	
	window->moverWindow(0,fator);
	update_Surface();
	inserirTextoConsole("Movimentação para cima.");
}

//  Método do botão de mover a window para Esquerda.
extern "C" G_MODULE_EXPORT void Pos_Btn_Esq_clicked_cb(){
	double fator = 0;
	
	try {
		fator = stod(gtk_entry_get_text((GtkEntry*) pos_Txt_Fator));
	} catch (const invalid_argument& e) {
		return;
	}
	
	window->moverWindow(-fator,0);
	update_Surface();
	inserirTextoConsole("Movimentação para a esquerda.");
}

//  Método do botão de mover a window para Direita.
extern "C" G_MODULE_EXPORT void Pos_Btn_Dir_clicked_cb(){
	double fator = 0;
	
	try {
		fator = stod(gtk_entry_get_text((GtkEntry*) pos_Txt_Fator));
	} catch (const invalid_argument& e) {
		return;
	}
	
	window->moverWindow(fator,0);
	update_Surface();
	inserirTextoConsole("Movimentação para a direita.");
}

//  Método do botão de mover a window para Baixo.
extern "C" G_MODULE_EXPORT void Pos_Btn_Baixo_clicked_cb(){
	double fator = 0;
	
	try {
		fator = stod(gtk_entry_get_text((GtkEntry*) pos_Txt_Fator));
	} catch (const invalid_argument& e) {
		return;
	}
	
	window->moverWindow(0,-fator);
	update_Surface();
	inserirTextoConsole("Movimentação para baixo.");
}

//  Método do botão de menor zoom.
extern "C" G_MODULE_EXPORT void Zoom_Btn_Menos_clicked_cb(){
	double fator = 0;
	
	try {
		fator = stod(gtk_entry_get_text((GtkEntry*) zoom_Txt_Fator));
	} catch (const invalid_argument& e) {
		return;
	}
	
	window->zoom(-fator);
	update_Surface();
	inserirTextoConsole("Menos zoom.");
}

//  Método do botão de mais zoom.
extern "C" G_MODULE_EXPORT void Zoom_Btn_Mais_clicked_cb(){
	double fator = 0;
	
	try {
		fator = stod(gtk_entry_get_text((GtkEntry*) zoom_Txt_Fator));
	} catch (const invalid_argument& e) {
		return;
	}
	
	window->zoom(fator);
	update_Surface();
	inserirTextoConsole("Mais zoom.");
}

//--------------------------------------------------------
// Métodos da viewport

// Método configure-event
extern "C" G_MODULE_EXPORT gboolean Viewport_DrawingArea_configure_event_cb (GtkWidget *widget, GdkEventConfigure *event, gpointer data){

	if (surface) {
		cairo_surface_destroy (surface);
	}

	surface = gdk_window_create_similar_surface (gtk_widget_get_window (widget),
												CAIRO_CONTENT_COLOR,
												gtk_widget_get_allocated_width (widget),
												gtk_widget_get_allocated_height (widget));

	clear_surface ();
	return TRUE;
}

// Método do draw da viewport
extern "C" G_MODULE_EXPORT gboolean Viewport_DrawingArea_draw_cb (GtkWidget *widget, cairo_t   *cr,  gpointer   data){
	
	cairo_set_source_surface (cr, surface, 0, 0);
	cairo_paint (cr);

	return FALSE;
}

//--------------------------------------------------------
// Métodos da janela de novo elemento

// Botão que adiciona um novo elemento
extern "C" G_MODULE_EXPORT void NovoElmnt_Adicionar_clicked_cb() {
	inserirNovoElemento();
	update_Surface();
	inserirTextoConsole("Novo elemento adicionado.");
}

// Botão que adiciona uma nova coordenada no poligono
extern "C" G_MODULE_EXPORT void NovoElmnt_Pol_Add_clicked_cb() {
	string c = inserirCoordListaEnc();
	if ( !(c.empty()) )  {
		addToListBox(poligono_Listbox, c);
	}
}

// Botão que deleta uma coordenada do poligono
extern "C" G_MODULE_EXPORT void NovoElmnt_Pol_Del_clicked_cb(){
	listaCoordsPoligono->retiraDaPosicao(getIndexElementoDeletado(poligono_Listbox));
}

extern "C" G_MODULE_EXPORT void Window_NovoElmnt_hide_cb(){
	limparTextoNomeNovoElmnt();
	limparTextoNovoPonto();
	limparTextoNovaReta();
	limparTextoNovoPoligono();
	gtk_notebook_set_current_page(notebook, 0);
	free(listaCoordsPoligono);
}
