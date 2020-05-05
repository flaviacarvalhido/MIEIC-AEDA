#include "zoo.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
using namespace std;

/*
 * Classe Zoo
 */

int Zoo::numAnimais() const {
	return animais.size();
}

int Zoo::numVeterinarios() const {
	return veterinarios.size();
}

void Zoo::adicionaAnimal(Animal *a1) {
    animais.push_back(a1);
}

string Zoo::getInformacao() const {
    string result;
    for(int i = 0; i < animais.size(); i++){
        result += animais[i]->getInformacao() + "\n";
    }
    return result;
}

bool Zoo::animalJovem(string nomeA) {
    for (int i= 0; i<animais.size();i++){
        if (animais[i]->getNome() == nomeA){
            return animais[i]->eJovem();
        }
    }
    return false;
}

void Zoo::alocaVeterinarios(istream &isV) {
    string nome,cod;
    while(getline(isV,nome)){
        getline(isV,cod);
        Veterinario *v = new Veterinario( nome, stoi(cod));
        veterinarios.push_back(v);
    }

    int j=0;
    for(int i=0; i<animais.size();i++){

        for ( j;j<veterinarios.size();j++){
            animais[i] -> setVet(veterinarios[j]);
            break;
        }
        if(j==veterinarios.size()){j=0;}
    }
}

