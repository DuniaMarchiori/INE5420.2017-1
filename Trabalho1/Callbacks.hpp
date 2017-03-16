//! Método que é chamado ao fechar a janela principal.
/*!
	Finalza o programa quando a janela principal é fechada.
*/
extern "C" G_MODULE_EXPORT void Window_Main_destroy_cb(){
	gtk_main_quit();
}

//! Método que é chamado ao selecionar um elemtno da list box.
/*!
	Ativa o botão de deletar elemento.
*/
extern "C" G_MODULE_EXPORT void Elmnt_List_row_selected_cb (GtkListBox *box, GtkListBoxRow *row, gpointer user_data) {
	gtk_widget_set_sensitive (elmnt_Btn_Del, TRUE);	
}

//! Método que é chamado ao pressionar o botão de Novo Elemento na janela principal.
/*!
	Mostra a janela de criação de elemento.
*/
extern "C" G_MODULE_EXPORT void Elmnt_Btn_Novo_clicked_cb(){
	listaCoordsPoligono = new ListaEnc<Coordenada*>();
	gtk_widget_show(window_NovoElemento);
}

//! Método que é chamado ao pressionar o botão de Deletar um elemento.
/*!
	Manda deletar o elemento da display file e executa um update na tela.
*/
extern "C" G_MODULE_EXPORT void Elmnt_Btn_Del_clicked_cb(){
	displayFile->deletarElemento();
	update_Surface();
	console->inserirTexto("Elemento excluído.");
	gtk_widget_set_sensitive (elmnt_Btn_Del, FALSE);	
}

//! Método que é chamado ao pressionar o botão "Cima".
/*!
	Move a window para cima baseado no fator.
*/
extern "C" G_MODULE_EXPORT void Pos_Btn_Cima_clicked_cb(){
	double fator = 0;
	
	try {
		fator = stod(gtk_entry_get_text((GtkEntry*) pos_Txt_Fator));
	} catch (const invalid_argument& e) {
		return;
	}
	
	window->moverWindow(0,fator);
	update_Surface();
	console->inserirTexto("Movimentação para cima.");
}


//! Método que é chamado ao pressionar o botão "Esquerda".
/*!
	Move a window para esquerda baseado no fator.
*/
extern "C" G_MODULE_EXPORT void Pos_Btn_Esq_clicked_cb(){
	double fator = 0;
	
	try {
		fator = stod(gtk_entry_get_text((GtkEntry*) pos_Txt_Fator));
	} catch (const invalid_argument& e) {
		return;
	}
	
	window->moverWindow(-fator,0);
	update_Surface();
	console->inserirTexto("Movimentação para a esquerda.");
}


//! Método que é chamado ao pressionar o botão "Direita".
/*!
	Move a window para direita baseado no fator.
*/
extern "C" G_MODULE_EXPORT void Pos_Btn_Dir_clicked_cb(){
	double fator = 0;
	
	try {
		fator = stod(gtk_entry_get_text((GtkEntry*) pos_Txt_Fator));
	} catch (const invalid_argument& e) {
		return;
	}
	
	window->moverWindow(fator,0);
	update_Surface();
	console->inserirTexto("Movimentação para a direita.");
}


//! Método que é chamado ao pressionar o botão "Baixo".
/*!
	Move a window para baixo baseado no fator.
*/
extern "C" G_MODULE_EXPORT void Pos_Btn_Baixo_clicked_cb(){
	double fator = 0;
	
	try {
		fator = stod(gtk_entry_get_text((GtkEntry*) pos_Txt_Fator));
	} catch (const invalid_argument& e) {
		return;
	}
	
	window->moverWindow(0,-fator);
	update_Surface();
	console->inserirTexto("Movimentação para baixo.");
}


//! Método que é chamado ao pressionar o botão "-" do zoom.
/*!
	Aumenta o tamanho da window baseado no fator.
*/
extern "C" G_MODULE_EXPORT void Zoom_Btn_Menos_clicked_cb(){
	double fator = 0;
	
	try {
		fator = stod(gtk_entry_get_text((GtkEntry*) zoom_Txt_Fator));
	} catch (const invalid_argument& e) {
		return;
	}
	
	window->zoom(-fator);
	update_Surface();
	console->inserirTexto("Menos zoom.");
}

//! Método que é chamado ao pressionar o botão "+" do zoom.
/*!
	Diminui o tamanho da window baseado no fator.
*/
extern "C" G_MODULE_EXPORT void Zoom_Btn_Mais_clicked_cb(){
	double fator = 0;
	
	try {
		fator = stod(gtk_entry_get_text((GtkEntry*) zoom_Txt_Fator));
	} catch (const invalid_argument& e) {
		return;
	}
	
	window->zoom(fator);
	update_Surface();
	console->inserirTexto("Mais zoom.");
}

//! Método que é chamado quando o signal "configure event" é ativado.
/*!
	Cria uma nova surface a atualiza o desenho.
*/
extern "C" G_MODULE_EXPORT gboolean Viewport_DrawingArea_configure_event_cb (GtkWidget *widget, GdkEventConfigure *event, gpointer data){
	desenhista->nova_surface(widget);
	update_Surface();
	
	return TRUE;
}

//! Método que é chamado quando o signal "draw" é ativado.
/*!
	Chama o metodo modifica_surface
*/
extern "C" G_MODULE_EXPORT gboolean Viewport_DrawingArea_draw_cb (GtkWidget *widget, cairo_t *cr,  gpointer   data){

	desenhista->modifica_surface(cr);

	return FALSE;
}


//--------------------------------------------------------
// Métodos da janela de novo elemento


//! Método que é chamado ao pressionar o botão de Adicionar dentro da janela de novo elemento.
/*!
	Verifica qual tipo de objeto esta sendo criado, e manda cria-los na display file, exibindo mensagens dependendo do resultado da operação.
*/
extern "C" G_MODULE_EXPORT void NovoElmnt_Adicionar_clicked_cb() {
	string nome = gtk_entry_get_text(textoNomeElemento);
	switch (gtk_notebook_get_current_page(notebook)) {
		case 0: {
			// A page 0 corresponde à aba de Ponto
			string coordX = gtk_entry_get_text(textoPontoX);
			string coordY = gtk_entry_get_text(textoPontoY);
			int resultado = displayFile->inserirNovoPonto(nome, coordX, coordY);
			if(resultado == 1) {
				limparTextoNovoPonto();
				console->inserirTexto("Novo ponto adicionado.");
			} else if(resultado == -1) {
				console->inserirTexto("ERRO: não é possível inserir elemento sem nome.");
			} else if(resultado == -2) {
				console->inserirTexto("ERRO: coordenadas devem ser valores numéricos.");
			} else if(resultado == -3) {
				console->inserirTexto("ERRO: não é possível inserir ponto sem valor X ou Y.");
			}
			break;
			}
		case 1: {
			// A page 1 corresponde à aba de Reta
			string coordIniX = gtk_entry_get_text(textoRetaInicialX);
			string coordIniY = gtk_entry_get_text(textoRetaInicialY);
			string coordFinX = gtk_entry_get_text(textoRetaFinalX);
			string coordFinY = gtk_entry_get_text(textoRetaFinalY);
			int resultado = displayFile->inserirNovaReta(nome, coordIniX, coordIniY, coordFinX, coordFinY);
			if(resultado == 1) {
				limparTextoNovaReta();
				console->inserirTexto("Nova reta adicionada.");
			} else if(resultado == -1) {
				console->inserirTexto("ERRO: não é possível inserir elemento sem nome.");
			} else if(resultado == -2) {
				console->inserirTexto("ERRO: coordenadas devem ser valores numéricos.");
			} else if(resultado == -3) {
				console->inserirTexto("ERRO: não é possível inserir reta sem dois pares de coordenadas.");
			}
			break;
			}
		case 2: {
			// A page 2 corresponde à aba de Polígono
			int resultado = displayFile->inserirNovoPoligono(nome, listaCoordsPoligono);
			if(resultado == 1) {
				limparTextoNovoPoligono();
				listaCoordsPoligono = new ListaEnc<Coordenada*>();
				console->inserirTexto("Novo poligono adicionado.");
			} else if(resultado == -1) {
				console->inserirTexto("ERRO: não é possível inserir elemento sem nome.");
			} else if(resultado == -3) {
				console->inserirTexto("ERRO: não é possível inserir polígono sem coordenadas.");
			}
			break;
			}
	}
	update_Surface();
	gtk_widget_set_sensitive (poligono_Btn_Del, FALSE);
}


//! Método que é chamado ao pressionar o botão de nova coordenada na criação de um polígono.
/*!
	Adiciona uma nova coordenada à lista de coordenadas e à list box.
*/
extern "C" G_MODULE_EXPORT void NovoElmnt_Pol_Add_clicked_cb() {
	string c = inserirCoordListaEnc();
	if ( !(c.empty()) )  {
		addToListBox(poligono_Listbox, c);
		gtk_entry_set_text(textoPoligonoX, "");
		gtk_entry_set_text(textoPoligonoY, "");
		// Dá foco à caixa de texto X
		gtk_widget_grab_focus((GtkWidget*) textoPoligonoX);
	}
}

//! Método que é chamado ao pressionar o botão de deletar coordenada na criação de um polígono.
/*!
	Remove a coordenada selecionada na list box.
*/
extern "C" G_MODULE_EXPORT void NovoElmnt_Pol_Del_clicked_cb(){
	listaCoordsPoligono->retiraDaPosicao(getIndexElementoDeletado(poligono_Listbox));
	gtk_widget_set_sensitive (poligono_Btn_Del, FALSE);	
}

//! Método que é chamado ao selecionar uma coordenada da list box de criação de poligono.
/*!
	Ativa o botão de deletar coordenada.
*/
extern "C" G_MODULE_EXPORT void NovoElmnt_Listbox_Pol_row_selected_cb (GtkListBox *box, GtkListBoxRow *row, gpointer user_data) {

	gtk_widget_set_sensitive (poligono_Btn_Del, TRUE);	
}


//! Método que é ativado ao fechar a janela de novo elemento.
/*!
	Restaura a janela para o seu estado inicial.
*/
extern "C" G_MODULE_EXPORT void Window_NovoElmnt_hide_cb(){
	limparTextoNomeNovoElmnt();
	limparTextoNovoPonto();
	limparTextoNovaReta();
	limparTextoNovoPoligono();
	gtk_widget_set_sensitive (poligono_Btn_Del, FALSE);	
	gtk_notebook_set_current_page(notebook, 0);
}