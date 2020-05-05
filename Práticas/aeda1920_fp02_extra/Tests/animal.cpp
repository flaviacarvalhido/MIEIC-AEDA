
#include "animal.h"
#include <sstream>
using namespace std;

/*
 * Classe Animal
 */
int Animal::maisJovem=1000;

string Animal::getNome() const {
	return nome;
}

Animal::Animal(string nome, int idade) {
    this -> nome = nome;
    this -> idade = idade;
    if (idade < maisJovem){this->maisJovem = idade;}
}

int Animal::getMaisJovem() {
    return maisJovem;
}

int Animal::getIdade() const {
    return idade;
}

Veterinario * Animal::getVet() {
    return vet;
}

string Animal::getInformacao() {
    string result;
    result += getNome() + ", " + to_string(getIdade()) + ", " + getVet()->getNome();
    return result;
}

void Animal::setVet(Veterinario *v) {
    this-> vet = v;
}


Cao::Cao(string nome, int idade, string raca):Animal(nome,idade) {
    this -> raca=raca;
}

bool Cao::eJovem() const {
    return (idade < 5);
}

string Cao::getInformacao() {
    return Animal::getInformacao() + ", " + raca;
}


Voador::Voador(int vmax, int amax) {
    this -> velocidade_max = vmax;
    this->altura_max=amax;
}

int Voador::getVMax() {
    return velocidade_max;
}

int Voador::getAMax() {
    return altura_max;
}


Morcego::Morcego(string nome, int idade, int vmax, int amax):Animal(nome,idade),Voador(vmax,amax) {}

bool Morcego::eJovem() const {
    return (idade < 4);
}

string Morcego::getInformacao() {
    return Animal::getInformacao() +  ", " + to_string(getVMax()) + ", " + to_string(getAMax());
}

