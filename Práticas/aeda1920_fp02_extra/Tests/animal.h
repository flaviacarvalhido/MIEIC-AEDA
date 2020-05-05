
#ifndef SRC_ANIMAL_H_
#define SRC_ANIMAL_H_

#include "veterinario.h"
#include <string>
using namespace std;


class Animal {
protected:
	string nome;
	int idade;
	Veterinario *vet;
	static int maisJovem;
public:
	Animal(string nome, int idade);
	void setVet(Veterinario *v);
	virtual ~Animal(){};
	string getNome() const;
	int getIdade() const;
	Veterinario * getVet();
	virtual string getInformacao();
	static int getMaisJovem();
    virtual bool eJovem()const=0;  //função puramente virtual para redifinição nas classes derivadas
};


class Cao: public Animal {
	string raca;
public:
	Cao(string nome, int idade, string raca);
    bool eJovem()const;
    string getInformacao();
};


class Voador {
	int velocidade_max;
	int altura_max;
public:
	Voador(int vmax, int amax);
    virtual ~Voador(){};
    int getVMax();
    int getAMax();
};


class Morcego: public Animal, public Voador {
public:
	Morcego(string nome, int idade, int vmax, int amax);
	bool eJovem()const;
    string getInformacao();

};


#endif /* SRC_ANIMAL_H_ */
