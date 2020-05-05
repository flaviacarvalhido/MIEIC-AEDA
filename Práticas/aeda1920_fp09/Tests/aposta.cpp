#include "aposta.h"
#include <iostream>
#include <sstream>

using namespace std;

// a alterar
bool Aposta::contem(unsigned num) const
{
    for(auto it=numeros.begin();it!=numeros.end();it++){
        if(*it == num)return true;
    }
	return false;
}

//a alterar
void Aposta::geraAposta(const vector<unsigned> & valores, unsigned n)
{
    unordered_set<unsigned>num;
    int i=0;

    while(num.size() != n){
        num.insert(valores[i]);
        i++;
    }
    numeros=num;
}

//a alterar
unsigned Aposta::calculaCertos(const tabHInt & sorteio) const
{
    auto sorte=sorteio.begin();
    int count=0;

    for(auto it=numeros.begin();it!=numeros.end();it++){
        for(auto sorte=sorteio.begin();sorte!=numeros.end();sorte++)
            if(*it == *sorte) count++;

    }

    return count;
}

unsigned Aposta::somaNumeros() const
{
    unsigned soma = 0;
    for (tabHInt::const_iterator it = numeros.begin();
         it != numeros.end(); it ++ )
        soma +=* it;
    return soma;
}

unsigned Aposta::tamanho() const
{
    return numeros.size();
}



