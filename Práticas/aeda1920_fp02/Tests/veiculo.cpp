#include "veiculo.h"
#include <iostream>

using namespace std;

Veiculo::Veiculo(string mc, int m, int a) {
    this -> marca = mc;
    this -> ano = a;
    this -> mes = m;
}

string Veiculo::getMarca() const {
    return marca;
}

int Veiculo::info() const {
    cout << marca;
    cout << mes;
    cout << ano;
    return 3;
}

int Veiculo::getAno() const {
    return ano;
}

bool Veiculo::operator<(const Veiculo &v) const {
    if(ano < v.ano){
        return true;
    }

    if(ano == v.ano){
        if(mes < v.mes) {
            return true;
        }
    }

    return false;
}

Motorizado::Motorizado(string mc, int m, int a, string c, int cil) : Veiculo(mc,m,a){
    this -> combustivel = c;
    this -> cilindrada = cil;
}

string Motorizado::getCombustivel() const {
    return combustivel;
}

int Motorizado::info() const {
    int r = Veiculo::info();
    cout << combustivel;
    cout << cilindrada;
    return r+2;
}

float Motorizado::calcImposto() const {
    float result;
    if (getCombustivel()=="gasolina"){
        if(cilindrada <= 1000 ){
            if (getAno() >1995){result=14.56;}
            else{result = 8.10;}
        }
        else if(cilindrada > 1000 && cilindrada <= 1300){
            if (getAno() >1995){result=29.06;}
            else{result = 14.56;}
        }
        else if(cilindrada >1300 && cilindrada <= 1750){
            if (getAno() >1995){result=45.15;}
            else{result = 22.65;}
        }
        else if(cilindrada > 1750 && cilindrada <= 2600){
            if (getAno() >1995){result=113.98;}
            else{result = 54.89;}
        }
        else if(cilindrada > 2600 && cilindrada <= 3500){
            if (getAno() >1995){result=181.17;}
            else{result = 87.13;}
        }else{
            if (getAno() >1995){result=320.89;}
            else{result = 148.37;}
        }
    }
    else{
        if(cilindrada <= 1500 ){
            if (getAno() >1995){result=14.56;}
            else{result = 8.10;}
        }
        else if(cilindrada > 1500 && cilindrada <= 2000){
            if (getAno() >1995){result=29.06;}
            else{result = 14.56;}
        }
        else if(cilindrada >2000 && cilindrada <= 3000){
            if (getAno() >1995){result=45.15;}
            else{result = 22.65;}
        }
        else {
            if (getAno() > 1995) { result = 113.98;}
            else { result = 54.89;}
        }
    }

    return result;
}

Automovel::Automovel(string mc, int m, int a, string c, int cil) : Motorizado(mc, m, a, c, cil) {}

int Automovel::info() const {
    return Motorizado::info();
}

float Automovel::calcImposto() const {

    return Motorizado::calcImposto();
}

Camiao::Camiao(string mc, int m, int a, string c, int cil, int cm) : Motorizado(mc,m,a,c,cil){
    this -> carga_maxima = cm;
}

int Camiao::info() const {
    int r = Motorizado::info();
    cout << carga_maxima;
    return r+1;
}

float Camiao::calcImposto() const {

    return Motorizado::calcImposto();
}

Bicicleta::Bicicleta(string mc, int m, int a, string t) : Veiculo(mc,m,a){
    this -> tipo = t;
}

int Bicicleta::info() const {
    int r=Veiculo::info();
    cout << tipo;
    return r+1;
}

float Bicicleta::calcImposto() const {
    return 0;
}
