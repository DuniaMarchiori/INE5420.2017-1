#include "Ponto.hpp"
#include "Reta.hpp"
#include "Poligono.hpp"


//extern "C" G_MODULE_EXPORT void btn_ok_clicked_cb(){ }

// Main de testes básicos
int main(int argc, char *argv[]){
	Ponto* p = new Ponto(5,6);
	p->setNome("a");
	
	Ponto* p2 = new Ponto(7,8);
	p->setNome("B");
	
	Reta* r = new Reta(p, p2);
	
	Poligono* pol = new Poligono();
	pol->adicionarPonto(p);

	return 0;
}
