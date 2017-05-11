#ifndef PARCOORD_HPP
#define PARCOORD_HPP

class ParCoord {
private:
	int A; /*!< Primeiro inteiro.*/
	int B; /*!< Segundo inteiro.*/

public:

	//! Construtor.
	ParCoord(int _A, int _B) {
		A = _A;
		B = _B;
	}

	int getA() {
		return A;
	}

	int getB() {
		return B;
	}

};

#endif