//! Método que é chamado ao fechar a janela principal.
/*!
	Finalza o programa quando a janela principal é fechada.
*/
extern "C" G_MODULE_EXPORT void Window_Main_destroy_cb(){
	controller->janelaPrincipalDestroy();
}

//! Método que é chamado ao selecionar um elemtno da list box.
/*!
	Ativa o botão de deletar elemento.
*/
extern "C" G_MODULE_EXPORT void Elmnt_List_row_selected_cb (GtkListBox *box, GtkListBoxRow *row, gpointer user_data) {
	controller->selecionaElementoListBox();
}

//! Método que é chamado ao pressionar o botão de Novo Elemento na janela principal.
/*!
	Mostra a janela de criação de elemento.
*/
extern "C" G_MODULE_EXPORT void Elmnt_Btn_Novo_clicked_cb(){
	controller->botaoNovoElemento();
}

//! Método que é chamado ao pressionar o botão de Deletar um elemento.
/*!
	Manda deletar o elemento da display file e executa um update na tela.
*/
extern "C" G_MODULE_EXPORT void Elmnt_Btn_Del_clicked_cb(){
	controller->botaoDeletarElemento();
}

//! Método que é chamado ao pressionar o botão de Editar um elemento.
/*!
	Abre a janela de editar elemento grafico.
*/
extern "C" G_MODULE_EXPORT void Elmnt_Btn_Edit_clicked_cb() {
	controller->botaoEditarElemento();
}

//! Método que é chamado ao pressionar o botão de girar a window no sentido anti-horário.
/*!
	Roda a window no sentido anti-horário.
*/
extern "C" G_MODULE_EXPORT void Pos_Btn_Rot_Esq_clicked_cb(){
	controller->botaoGirarWindowEsquerdo();
}

//! Método que é chamado ao pressionar o botão de girar a window no sentido horário.
/*!
	Roda a window no sentido anti-horário.
*/
extern "C" G_MODULE_EXPORT void Pos_Btn_Rot_Dir_clicked_cb(){
	controller->botaoGirarWindowDireito();
}

//! Método que é chamado ao pressionar o botão "Cima".
/*!
	Move a window para cima baseado no fator.
*/
extern "C" G_MODULE_EXPORT void Pos_Btn_Cima_clicked_cb(){
	controller->botaoMovimentoCima();
}


//! Método que é chamado ao pressionar o botão "Esquerda".
/*!
	Move a window para esquerda baseado no fator.
*/
extern "C" G_MODULE_EXPORT void Pos_Btn_Esq_clicked_cb(){
	controller->botaoMovimentoEsquerda();
}


//! Método que é chamado ao pressionar o botão "Direita".
/*!
	Move a window para direita baseado no fator.
*/
extern "C" G_MODULE_EXPORT void Pos_Btn_Dir_clicked_cb(){
	controller->botaoMovimentoDireita();
}


//! Método que é chamado ao pressionar o botão "Baixo".
/*!
	Move a window para baixo baseado no fator.
*/
extern "C" G_MODULE_EXPORT void Pos_Btn_Baixo_clicked_cb(){
	controller->botaoMovimentoBaixo();
}


//! Método que é chamado ao pressionar o botão "-" do zoom.
/*!
	Aumenta o tamanho da window baseado no fator.
*/
extern "C" G_MODULE_EXPORT void Zoom_Btn_Menos_clicked_cb(){
	controller->botaoZoomMenos();
}

//! Método que é chamado ao pressionar o botão "+" do zoom.
/*!
	Diminui o tamanho da window baseado no fator.
*/
extern "C" G_MODULE_EXPORT void Zoom_Btn_Mais_clicked_cb(){
	controller->botaoZoomMais();
}

//! Método que é chamado quando o signal "configure event" é ativado.
/*!
	Cria uma nova surface a atualiza o desenho.
*/
extern "C" G_MODULE_EXPORT gboolean Viewport_DrawingArea_configure_event_cb (GtkWidget *widget, GdkEventConfigure *event, gpointer data){
	controller->drawingAreaConfigure(widget);
	return TRUE;
}

//! Método que é chamado quando o signal "draw" é ativado.
/*!
	Chama o metodo modifica_surface
*/
extern "C" G_MODULE_EXPORT gboolean Viewport_DrawingArea_draw_cb (GtkWidget *widget, cairo_t *cr,  gpointer   data){
	controller->drawingAreaDraw(cr);
	return FALSE;
}



//--------------------------------------------------------------
// Métodos da janela de novo elemento


//! Método que é chamado ao pressionar o botão de Adicionar dentro da janela de novo elemento.
/*!
	Verifica qual tipo de objeto esta sendo criado, e manda cria-los na display file, exibindo mensagens dependendo do resultado da operação.
*/
extern "C" G_MODULE_EXPORT void NovoElmnt_Adicionar_clicked_cb() {
	controller->addNovoElemento();
}


//! Método que é chamado ao pressionar o botão de nova coordenada na criação de um polígono.
/*!
	Adiciona uma nova coordenada à lista de coordenadas e à list box.
*/
extern "C" G_MODULE_EXPORT void NovoElmnt_Pol_Add_clicked_cb() {
	controller->addNovaCoordenadaPolinomio();
}

//! Método que é chamado ao pressionar o botão de deletar coordenada na criação de um polígono.
/*!
	Remove a coordenada selecionada na list box de coordenadas do novo poligono.
*/
extern "C" G_MODULE_EXPORT void NovoElmnt_Pol_Del_clicked_cb(){
	controller->delCoordenadaPolinomio();
}

//! Método que é chamado ao selecionar uma coordenada da list box de criação de poligono.
/*!
	Ativa o botão de deletar coordenada.
*/
extern "C" G_MODULE_EXPORT void NovoElmnt_Listbox_Pol_row_selected_cb (GtkListBox *box, GtkListBoxRow *row, gpointer user_data) {
	controller->selecionaCoordenadaListBox();
}


//! Método que é ativado ao fechar a janela de novo elemento.
/*!
	Restaura a janela para o seu estado inicial.
*/
extern "C" G_MODULE_EXPORT void Window_NovoElmnt_hide_cb(){
	controller->janelaNovoElementoHide();
}



//--------------------------------------------------------------
// Métodos da janela de editar elementos

//! Método que é chamado ao pressionar o botão de aplicar na janela de edição de elementos.
/*!
	Abre a janela de edição de elemento.
*/
extern "C" G_MODULE_EXPORT void EditElmnt_Aplicar_clicked_cb() {
	controller->editarElementoGrafico();
}

//! Método que é ativado ao fechar a janela de editar elemento.
/*!
	Restaura a janela para o seu estado inicial.
*/
extern "C" G_MODULE_EXPORT void Window_EditElmnt_hide_cb() {
	controller->fecharJanelaEdicao();
}