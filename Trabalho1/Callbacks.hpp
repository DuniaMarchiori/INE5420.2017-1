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
extern "C" G_MODULE_EXPORT void Pos_Btn_Top_Esq_clicked_cb(){
	controller->botaoPosTopEsq();
}

//! Método que é chamado ao pressionar o botão de girar a window no sentido horário.
/*!
	Roda a window no sentido anti-horário.
*/
extern "C" G_MODULE_EXPORT void Pos_Btn_Top_Dir_clicked_cb(){
	controller->botaoPosTopDir();
}

//! Método que é chamado ao pressionar o botão "Cima".
/*!
	Move a window para cima baseado no fator.
*/
extern "C" G_MODULE_EXPORT void Pos_Btn_Cima_clicked_cb(){
	controller->botaoPosCima();
}


//! Método que é chamado ao pressionar o botão "Esquerda".
/*!
	Move a window para esquerda baseado no fator.
*/
extern "C" G_MODULE_EXPORT void Pos_Btn_Esq_clicked_cb(){
	controller->botaoPosEsq();
}


//! Método que é chamado ao pressionar o botão "Direita".
/*!
	Move a window para direita baseado no fator.
*/
extern "C" G_MODULE_EXPORT void Pos_Btn_Dir_clicked_cb(){
	controller->botaoPosDir();
}


//! Método que é chamado ao pressionar o botão "Baixo".
/*!
	Move a window para baixo baseado no fator.
*/
extern "C" G_MODULE_EXPORT void Pos_Btn_Baixo_clicked_cb(){
	controller->botaoPosBaixo();
}


//! Método que é chamado ao pressionar o radio button do tipo de clippagem C-S.
/*!
	Redesenha todos os elementos, utilizando clipping C-S.
*/
extern "C" G_MODULE_EXPORT void Pos_Radio_0_clicked_cb(){
	controller->movWindowAlterado();
}

//! Método que é chamado ao pressionar o radio button do tipo de clippagem L-B.
/*!
	Redesenha todos os elementos, utilizando clipping L-B.
*/
extern "C" G_MODULE_EXPORT void Pos_Radio_1_clicked_cb(){
	controller->movWindowAlterado();
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

//! Método que é chamado ao pressionar o radio button do tipo de clippagem C-S.
/*!
	Redesenha todos os elementos, utilizando clipping C-S.
*/
extern "C" G_MODULE_EXPORT void Clipping_Radio_0_clicked_cb(){
	controller->clippingAlterado();
}

//! Método que é chamado ao pressionar o radio button do tipo de clippagem L-B.
/*!
	Redesenha todos os elementos, utilizando clipping L-B.
*/
extern "C" G_MODULE_EXPORT void Clipping_Radio_1_clicked_cb(){
	controller->clippingAlterado();
}

//! Método que é chamado ao pressionar o botao do menu bar de carregar um .obj.
/*!
	Carrega um elemento em formato .obj.
*/
extern "C" G_MODULE_EXPORT void MenuBar_Carregar_Obj_activate_cb(){
	controller->carregarObj();
}

//! Método que é chamado ao pressionar o botao do menu bar de salvar elemento em .obj.
/*!
	Carrega um elemento em formato .obj.
*/
extern "C" G_MODULE_EXPORT void MenuBar_Salvar_Obj_Elemento_activate_cb(){
	controller->salvarElementoObj();
}

//! Método que é chamado ao pressionar o botao do menu bar de salvar o mundo em .obj.
/*!
	Carrega um elemento em formato .obj.
*/
extern "C" G_MODULE_EXPORT void MenuBar_Salvar_Obj_Mundo_activate_cb(){
	controller->salvarMundoObj();
}

//! Método que é chamado ao pressionar o botao do menu bar de salvar o mundo em .obj.
/*!
	Carrega um elemento em formato .obj.
*/
extern "C" G_MODULE_EXPORT void MenuBar_Window_Resetar_activate_cb(){
	controller->resetarWindow();
}



//----------------------------------------------------------------------------------------------------
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
	controller->addNovaCoordenadaPoligono();
}

//! Método que é chamado ao pressionar o botão de deletar coordenada na criação de um polígono.
/*!
	Remove a coordenada selecionada na list box de coordenadas do novo poligono.
*/
extern "C" G_MODULE_EXPORT void NovoElmnt_Pol_Del_clicked_cb(){
	controller->delCoordenadaPoligono();
}

//! Método que é chamado ao selecionar uma coordenada da list box de criação de poligono.
/*!
	Ativa o botão de deletar coordenada.
*/
extern "C" G_MODULE_EXPORT void NovoElmnt_Listbox_Pol_row_selected_cb (GtkListBox *box, GtkListBoxRow *row, gpointer user_data) {
	controller->selecionaListBoxPoligono();
}

//! Método que é chamado ao pressionar o botão de nova coordenada na criação de uma curva.
/*!
	Adiciona uma nova coordenada à lista de coordenadas e à list box.
*/
extern "C" G_MODULE_EXPORT void NovoElmnt_Curv_Add_clicked_cb() {
	controller->addNovaCoordenadaCurva();
}

//! Método que é chamado ao pressionar o botão de deletar coordenada na criação de uma curva.
/*!
	Remove a coordenada selecionada na list box de coordenadas da nova curva.
*/
extern "C" G_MODULE_EXPORT void NovoElmnt_Curv_Del_clicked_cb(){
	controller->delCoordenadaCurva();
}

//! Método que é chamado ao selecionar uma coordenada da list box de criação de curvas.
/*!
	Ativa o botão de deletar coordenada.
*/
extern "C" G_MODULE_EXPORT void NovoElmnt_Listbox_Curv_row_selected_cb (GtkListBox *box, GtkListBoxRow *row, gpointer user_data) {
	controller->selecionaListBoxCurva();
}

//! Método que é chamado ao pressionar o botão de nova coordenada na criação de um Objeto3D.
/*!
	Adiciona uma nova coordenada à lista de coordenadas e à list box.
*/
extern "C" G_MODULE_EXPORT void NovoElmnt_Obj_Coord_Add_clicked_cb() {
	controller->addNovaCoordenadaObjeto3D();
}

//! Método que é chamado ao pressionar o botão de deletar coordenada na criação de um Objeto3D.
/*!
	Remove a coordenada selecionada na list box de coordenadas do novo Objeto3D.
*/
extern "C" G_MODULE_EXPORT void NovoElmnt_Obj_Coord_Del_clicked_cb(){
	controller->delCoordenadaObjeto3D();
}

//! Método que é chamado ao pressionar o botão de nova aresta na criação de um Objeto3D.
/*!
	Adiciona uma nova aresta à lista de arestas e à list box.
*/
extern "C" G_MODULE_EXPORT void NovoElmnt_Obj_Aresta_Add_clicked_cb() {
	controller->addNovaArestaObjeto3D();
}

//! Método que é chamado ao pressionar o botão de deletar aresta na criação de um Objeto3D.
/*!
	Remove a aresta selecionada na list box de aresta do novo Objeto3D.
*/
extern "C" G_MODULE_EXPORT void NovoElmnt_Obj_Aresta_Del_clicked_cb(){
	controller->delArestaObjeto3D();
}

//! Método que é chamado ao selecionar uma coordenada da list box de criação de Objeto3D.
/*!
	Ativa o botão de deletar coordenada.
*/
extern "C" G_MODULE_EXPORT void NovoElmnt_Obj_Coord_Listbox_row_selected_cb (GtkListBox *box, GtkListBoxRow *row, gpointer user_data) {
	controller->selecionaListBoxObjeto3DCoord();
}

//! Método que é chamado ao selecionar uma aresta da list box de criação de Objeto3D.
/*!
	Ativa o botão de deletar aresta.
*/
extern "C" G_MODULE_EXPORT void NovoElmnt_Obj_Aresta_Listbox_row_selected_cb (GtkListBox *box, GtkListBoxRow *row, gpointer user_data) {
	controller->selecionaListBoxObjeto3DAresta();
}

//! Método que é ativado ao fechar a janela de novo elemento.
/*!
	Restaura a janela para o seu estado inicial.
*/
extern "C" G_MODULE_EXPORT void Window_NovoElmnt_hide_cb(){
	controller->janelaNovoElementoHide();
}



//------------------------------------------------------------------------------------------
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