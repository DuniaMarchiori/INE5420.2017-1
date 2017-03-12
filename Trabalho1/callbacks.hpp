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