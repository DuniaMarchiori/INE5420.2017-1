#ifndef CONSOLE_HPP
#define CONSOLE_HPP

class Console: public ElementoGrafico {
	
private:
	GtkTextView* caixaTexto;
	GtkTextBuffer *buffer;

public:

	Console(GtkTextView* _caixaTexto) {
		caixaTexto = _caixaTexto;
		buffer = gtk_text_view_get_buffer (caixaTexto);
	}
	
	void inserirTexto(const gchar *texto) {
		// -1 indica que é para adicionar o texto todo
		GtkTextIter* iter = new GtkTextIter();

		gtk_text_buffer_insert_at_cursor(buffer, g_strconcat(texto, "\n", NULL), -1);
		//gtk_text_buffer_get_iter_at_line(buffer, iter, gtk_text_buffer_get_line_count(buffer));
		gtk_text_buffer_get_end_iter(buffer, iter);
		gtk_text_view_scroll_to_iter(caixaTexto, iter, 0.0, TRUE, 0.5, 1);
		
		free(iter);
	}
	
};

#endif