#include "frota.h"
#include <string>

using namespace std;


void Frota::adicionaVeiculo(Veiculo *v1) {
    veiculos.push_back(v1);
}

int Frota::numVeiculos() const {
    return veiculos.size();
}

int Frota::menorAno() const {
    int value=0;
    if (veiculos.size()==0){return 0;}
    else{
        value = veiculos[0]->getAno();
        for (int i =1; i < veiculos.size();i++){
            if(veiculos[i]->getAno() < value){value=veiculos[i]->getAno();}
        }
    }
    return value;
}

ostream &operator<<(ostream &o, const Frota &f) {
    for (int i =0; i<f.veiculos.size(); i++){
        f.veiculos[i]->info();
    }
}

vector<Veiculo *> Frota::operator()(int anoM) const {
    vector <Veiculo *> result;
    for (int i = 0; i<veiculos.size();i++){
        if(veiculos[i]->getAno() == anoM){
            result.push_back(veiculos[i]);
        }
    }
    return result;
}

float Frota::totalImposto() const{
    float result;
    for(int i=0;i<veiculos.size();i++){
        result+=veiculos[i]->calcImposto();
    }
    return result;
}