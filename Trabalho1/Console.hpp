#ifndef CONSOLE_HPP
#define CONSOLE_HPP

class Console: public ElementoGrafico {
	
private:
	GtkTextView* caixaTexto; /*!< Referência para a caixa de texto da interface de usuário*/
	GtkTextBuffer *buffer; /*!< Guarda o texto para ser mostrada na caixa de texto*/

public:

	//! Construtor
	/*
		/param _caixaTexto Um ponteiro para a caixa de texto onde este console se mostrará.
	*/
	Console(GtkTextView* _caixaTexto) {
		caixaTexto = _caixaTexto;
		buffer = gtk_text_view_get_buffer (caixaTexto);
	}
	
	//! Método que adiciona novas mensagens.
    /*!
        Adiciona uma nova linha ao console com uma mensagem nova.
        /param text O texto que sera adicionado ao console.
    */
	void inserirTexto(const gchar *texto) {
		// -1 indica que é para adicionar o texto todo
		GtkTextIter* iter = new GtkTextIter();

		gtk_text_buffer_insert_at_cursor(buffer, g_strconcat(texto, "\n", NULL), -1);
		gtk_text_buffer_get_end_iter(buffer, iter);
		gtk_text_view_scroll_to_iter(caixaTexto, iter, 0.0, TRUE, 0.5, 1);
		
		free(iter);
	}
	
};

#endif