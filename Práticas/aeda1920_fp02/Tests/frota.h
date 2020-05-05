#ifndef FROTA_H_
#define FROTA_H_

#include <vector>
#include "veiculo.h"
using namespace std;

class Frota {
	vector<Veiculo *> veiculos;
public:
	friend ostream & operator<<(ostream & o, const Frota & f);
    void adicionaVeiculo(Veiculo *v1);
    int numVeiculos() const; // retorna o nº de veículos no vector veiculos
    int menorAno() const; // retorna o menor ano dos veículos presentes no vetor veículos; retorna 0 se não existir nenhum veículo
    vector<Veiculo *> operator () (int anoM) const;
    float totalImposto() const;
};

#endif /*FROTA_H_*/
