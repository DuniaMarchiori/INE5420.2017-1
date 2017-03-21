//! Método que é chamado ao fechar a janela principal.
/*!
	Finalza o programa quando a janela principal é fechada.
*/
extern "C" G_MODULE_EXPORT void Window_Main_destroy_cb(){
	controller->getView()->fecharPrograma();
}

//! Método que é chamado ao selecionar um elemtno da list box.
/*!
	Ativa o botão de deletar elemento.
*/
extern "C" G_MODULE_EXPORT void Elmnt_List_row_selected_cb (GtkListBox *box, GtkListBoxRow *row, gpointer user_data) {
	controller->getView()->setElmnt_Btn_DelSensitive(TRUE);
}

//! Método que é chamado ao pressionar o botão de Novo Elemento na janela principal.
/*!
	Mostra a janela de criação de elemento.
*/
extern "C" G_MODULE_EXPORT void Elmnt_Btn_Novo_clicked_cb(){
	controller->getView()->Elmnt_Btn_Novo_Clicado();
}

//! Método que é chamado ao pressionar o botão de Deletar um elemento.
/*!
	Manda deletar o elemento da display file e executa um update na tela.
*/
extern "C" G_MODULE_EXPORT void Elmnt_Btn_Del_clicked_cb(){
	try {
		int index = controller->getView()->deletarElemento();
		controller->getModel()->deletarElemento(index);
		controller->atualizaDesenho();
		controller->getView()->inserirTextoConsole("Elemento excluído.");
		controller->getView()->setElmnt_Btn_DelSensitive(FALSE);	
	} catch (int erro) {
		if (erro == 1) {
			controller->getView()->inserirTextoConsole("É preciso selecionar um elemento para ser deletado.");
		}
	}
	
}

//! Método que é chamado ao pressionar o botão "Cima".
/*!
	Move a window para cima baseado no fator.
*/
extern "C" G_MODULE_EXPORT void Pos_Btn_Cima_clicked_cb(){
	try {
		double fator = controller->getView()->getFatorMovimento();
		controller->getModel()->moverWindow(0,fator);
		controller->atualizaDesenho();
		controller->getView()->inserirTextoConsole("Movimentação para cima.");
	} catch (...){
		return;
	}
}


//! Método que é chamado ao pressionar o botão "Esquerda".
/*!
	Move a window para esquerda baseado no fator.
*/
extern "C" G_MODULE_EXPORT void Pos_Btn_Esq_clicked_cb(){
	try {
		double fator = controller->getView()->getFatorMovimento();
		controller->getModel()->moverWindow(-fator,0);
		controller->atualizaDesenho();
		controller->getView()->inserirTextoConsole("Movimentação para a esquerda.");
	} catch (...){
		return;
	}
}


//! Método que é chamado ao pressionar o botão "Direita".
/*!
	Move a window para direita baseado no fator.
*/
extern "C" G_MODULE_EXPORT void Pos_Btn_Dir_clicked_cb(){
	try {
		double fator = controller->getView()->getFatorMovimento();
		controller->getModel()->moverWindow(fator,0);
		controller->atualizaDesenho();
		controller->getView()->inserirTextoConsole("Movimentação para a direita.");
	} catch (...){
		return;
	}
}


//! Método que é chamado ao pressionar o botão "Baixo".
/*!
	Move a window para baixo baseado no fator.
*/
extern "C" G_MODULE_EXPORT void Pos_Btn_Baixo_clicked_cb(){
	try {
		double fator = controller->getView()->getFatorMovimento();
		controller->getModel()->moverWindow(0,-fator);
		controller->atualizaDesenho();
		controller->getView()->inserirTextoConsole("Movimentação para baixo.");
	} catch (...){
		return;
	}
}


//! Método que é chamado ao pressionar o botão "-" do zoom.
/*!
	Aumenta o tamanho da window baseado no fator.
*/
extern "C" G_MODULE_EXPORT void Zoom_Btn_Menos_clicked_cb(){
	try {
		double fator = controller->getView()->getFatorZoom();
		controller->getModel()->zoom(-fator);
		controller->atualizaDesenho();
		controller->getView()->inserirTextoConsole("Zoom para fora.");
	} catch (...){
		return;
	}
}

//! Método que é chamado ao pressionar o botão "+" do zoom.
/*!
	Diminui o tamanho da window baseado no fator.
*/
extern "C" G_MODULE_EXPORT void Zoom_Btn_Mais_clicked_cb(){
	try {
		double fator = controller->getView()->getFatorZoom();
		controller->getModel()->zoom(fator);
		controller->atualizaDesenho();
		controller->getView()->inserirTextoConsole("Zoom para dentro.");
	} catch (...){
		return;
	}
}

//! Método que é chamado quando o signal "configure event" é ativado.
/*!
	Cria uma nova surface a atualiza o desenho.
*/
extern "C" G_MODULE_EXPORT gboolean Viewport_DrawingArea_configure_event_cb (GtkWidget *widget, GdkEventConfigure *event, gpointer data){
	controller->getView()->nova_surface(widget);
	controller->atualizaDesenho();
	return TRUE;
}

//! Método que é chamado quando o signal "draw" é ativado.
/*!
	Chama o metodo modifica_surface
*/
extern "C" G_MODULE_EXPORT gboolean Viewport_DrawingArea_draw_cb (GtkWidget *widget, cairo_t *cr,  gpointer   data){
	controller->getView()->modifica_surface(cr);
	return FALSE;
}


//--------------------------------------------------------
// Métodos da janela de novo elemento


//! Método que é chamado ao pressionar o botão de Adicionar dentro da janela de novo elemento.
/*!
	Verifica qual tipo de objeto esta sendo criado, e manda cria-los na display file, exibindo mensagens dependendo do resultado da operação.
*/
extern "C" G_MODULE_EXPORT void NovoElmnt_Adicionar_clicked_cb() {
	
	string nome = controller->getView()->getNomeElemento();
	int tipo = controller->getView()->getTipoNovoElemento();
	switch (tipo) {
		case 0: { // A page 0 corresponde à aba de Ponto
			string coordX = controller->getView()->getCoordXNovoPonto();
			string coordY = controller->getView()->getCoordYNovoPonto();
			try {
				controller->getModel()->inserirNovoPonto(nome, coordX, coordY);
				controller->getView()->limparTextoNovoPonto();
				controller->getView()->adicionaElementoListbox(nome);
				controller->getView()->inserirTextoConsole("Novo ponto adicionado.");
			} catch (int erro) {
				if (erro == -1) {
					controller->getView()->inserirTextoConsole("ERRO: não é possível inserir elemento sem nome.");
				} else if (erro == -2) {
					controller->getView()->inserirTextoConsole("ERRO: coordenadas devem ser valores numéricos.");
				} else if (erro == -3) {
					controller->getView()->inserirTextoConsole("ERRO: não é possível inserir um ponto sem coordenadas.");
				}
			}
			
			break;
		} case 1: { // A page 1 corresponde à aba de Reta
			string coordIniX = controller->getView()->getCoordIniXNovaReta();
			string coordIniY = controller->getView()->getCoordIniYNovaReta();
			string coordFinX = controller->getView()->getCoordFinXNovaReta();
			string coordFinY = controller->getView()->getCoordFinYNovaReta();
		
			try {
				controller->getModel()->inserirNovaReta(nome, coordIniX, coordIniY, coordFinX, coordFinY);
				controller->getView()->limparTextoNovaReta();
				controller->getView()->adicionaElementoListbox(nome);
				controller->getView()->inserirTextoConsole("Nova reta adicionada.");
			} catch (int erro) {
				if (erro == -1) {
					controller->getView()->inserirTextoConsole("ERRO: não é possível inserir elemento sem nome.");
				} else if (erro == -2) {
					controller->getView()->inserirTextoConsole("ERRO: coordenadas devem ser valores numéricos.");
				} else if (erro == -3) {
					controller->getView()->inserirTextoConsole("ERRO: não é possível inserir reta sem dois pares de coordenadas.");
				}
			}
			
			break;
		} case 2: { // A page 2 corresponde à aba de Polígono
			ListaEnc<Coordenada*>* lista = controller->getView()->getListaCoordsPoligono();
			
			try {
				controller->getModel()->inserirNovoPoligono(nome, lista);
				controller->getView()->resetarListaCoordenadasPoligono();
				controller->getView()->limparTextoNovoPoligono();
				controller->getView()->adicionaElementoListbox(nome);
				controller->getView()->inserirTextoConsole("Novo poligono adicionado.");
			} catch (int erro) {
				if (erro == -1) {
					controller->getView()->inserirTextoConsole("ERRO: não é possível inserir elemento sem nome.");
				} else if (erro == -3) {
					controller->getView()->inserirTextoConsole("ERRO: não é possível inserir polígono sem coordenadas.");
				}
			}
			
			break;
		}
	}
	
	controller->atualizaDesenho();
	controller->getView()->setPoligono_Btn_DelSensitive(FALSE);
	controller->getView()->focusNome();
	
	/*
	string nome = gtk_entry_get_text(textoNomeElemento);
	switch (gtk_notebook_get_current_page(notebook)) {
		case 0: {
			// A page 0 corresponde à aba de Ponto
			string coordX = gtk_entry_get_text(textoPontoX);
			string coordY = gtk_entry_get_text(textoPontoY);
			int resultado = displayFile->inserirNovoPonto(nome, coordX, coordY);
			if(resultado == 1) {
				limparTextoNovoPonto();
				controller->getView()->inserirTextoConsole("Novo ponto adicionado.");
			} else if(resultado == -1) {
				controller->getView()->inserirTextoConsole("ERRO: não é possível inserir elemento sem nome.");
			} else if(resultado == -2) {
				controller->getView()->inserirTextoConsole("ERRO: coordenadas devem ser valores numéricos.");
			} else if(resultado == -3) {
				controller->getView()->inserirTextoConsole("ERRO: não é possível inserir ponto sem valor X ou Y.");
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
				controller->getView()->inserirTextoConsole("Nova reta adicionada.");
			} else if(resultado == -1) {
				controller->getView()->inserirTextoConsole("ERRO: não é possível inserir elemento sem nome.");
			} else if(resultado == -2) {
				controller->getView()->inserirTextoConsole("ERRO: coordenadas devem ser valores numéricos.");
			} else if(resultado == -3) {
				controller->getView()->inserirTextoConsole("ERRO: não é possível inserir reta sem dois pares de coordenadas.");
			}
			break;
			}
		case 2: {
			// A page 2 corresponde à aba de Polígono
			int resultado = displayFile->inserirNovoPoligono(nome, listaCoordsPoligono);
			if(resultado == 1) {
				limparTextoNovoPoligono();
				listaCoordsPoligono = new ListaEnc<Coordenada*>();
				controller->getView()->inserirTextoConsole("Novo poligono adicionado.");
			} else if(resultado == -1) {
				controller->getView()->inserirTextoConsole("ERRO: não é possível inserir elemento sem nome.");
			} else if(resultado == -3) {
				controller->getView()->inserirTextoConsole("ERRO: não é possível inserir polígono sem coordenadas.");
			}
			break;
			}
	}
	update_Surface();
	gtk_widget_set_sensitive (poligono_Btn_Del, FALSE); // botão de deletar coordenada é desativado
	gtk_widget_grab_focus((GtkWidget*) textoNomeElemento); // foco vai para a caixa de texto de nome do novo elemento
	*/
}


//! Método que é chamado ao pressionar o botão de nova coordenada na criação de um polígono.
/*!
	Adiciona uma nova coordenada à lista de coordenadas e à list box.
*/
extern "C" G_MODULE_EXPORT void NovoElmnt_Pol_Add_clicked_cb() {
	try {
		controller->getView()->inserirCoordListaEnc();
		controller->getView()->limparTextoCoordPoligono();
		controller->getView()->focusCoordPoligono();
	} catch (...){
		return;
	}
	/*
	string c = inserirCoordListaEnc();
	if ( !(c.empty()) )  {
		addToListBox(poligono_Listbox, c);
		gtk_entry_set_text(textoPoligonoX, "");
		gtk_entry_set_text(textoPoligonoY, "");
		// Dá foco à caixa de texto X
		gtk_widget_grab_focus((GtkWidget*) textoPoligonoX);
	}
	*/
}

//! Método que é chamado ao pressionar o botão de deletar coordenada na criação de um polígono.
/*!
	Remove a coordenada selecionada na list box de coordenadas do novo poligono.
*/
extern "C" G_MODULE_EXPORT void NovoElmnt_Pol_Del_clicked_cb(){
	controller->getView()->deletarCoordPoligono();
}

//! Método que é chamado ao selecionar uma coordenada da list box de criação de poligono.
/*!
	Ativa o botão de deletar coordenada.
*/
extern "C" G_MODULE_EXPORT void NovoElmnt_Listbox_Pol_row_selected_cb (GtkListBox *box, GtkListBoxRow *row, gpointer user_data) {
	controller->getView()->setPoligono_Btn_DelSensitive(TRUE);	
}


//! Método que é ativado ao fechar a janela de novo elemento.
/*!
	Restaura a janela para o seu estado inicial.
*/
extern "C" G_MODULE_EXPORT void Window_NovoElmnt_hide_cb(){
	controller->getView()->resetarJanelaNovoElemento();
}
