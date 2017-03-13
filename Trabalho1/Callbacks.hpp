// Métodos da janela principal.

//  Método para fechar o programa quando a janela principal é fechada.
extern "C" G_MODULE_EXPORT void Window_Main_destroy_cb(){
	gtk_main_quit();
}

//  Métodos da região do Menu de Funções.

//  Métodos do menu de Elementos.

//  Método do botão de novo elemento.
extern "C" G_MODULE_EXPORT void Elmnt_Btn_Novo_clicked_cb(){
	gtk_widget_show(window_NovoElemento);
}

//  Método do botão de deletar elemento.
extern "C" G_MODULE_EXPORT void Elmnt_Btn_Del_clicked_cb(){
	GtkListBoxRow* row = gtk_list_box_get_selected_row ((GtkListBox*) elmnt_List);
	if (row != NULL) {
		int index = gtk_list_box_row_get_index(row);
		gtk_container_remove((GtkContainer*) elmnt_List, (GtkWidget*) row);
		displayFile->retiraDaPosicao(index);
	}
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
	// TODO verificação de campos nulos ou não-numéricos
	// TODO diferentes inserções para Retas e Poligonos

	// teste inicial pro método de inserir
	// Pega nome (mesmo comando para todos os desenhos)
	string nome = gtk_entry_get_text(textoNomeElemento);

	// Ponto simples ------------------
	// pega valores
	string numx = gtk_entry_get_text(textoPontoX);
	string numy = gtk_entry_get_text(textoPontoY);
	//cria novo objeto
	Coordenada* c = new Coordenada();
	c->setX(stod(numx));
	c->setY(stod(numy));
	Ponto *p = new Ponto(nome, c);
	//adiciona objeto na display file
	displayFile->adiciona(p);
	

	update_Surface();
}
