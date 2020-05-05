
#include "veterinario.h"
#include <sstream>
using namespace std;

string Veterinario::getNome() const {
	return nome;
}

Veterinario::Veterinario(string nome, int cod) {
    this ->nome =nome;
    this -> codOrdem = cod;
}



