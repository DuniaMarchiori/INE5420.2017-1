#include "Ponto.hpp"
#include "Reta.hpp"
#include "Poligono.hpp"

#include "Coordenada.hpp"


//extern "C" G_MODULE_EXPORT void btn_ok_clicked_cb(){ }

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

	return 0;
}
