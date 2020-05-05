#include "jogador.h"

//a alterar
void Jogador::adicionaAposta(const Aposta & ap)
{
    apostas.insert(ap);
}

//a alterar
unsigned Jogador::apostasNoNumero(unsigned num) const
{
    int count=0;
	for(auto it = apostas.begin();it!=apostas.end();it++){
	    if(it->contem(num))count++;
	}
	return count;
}

//a alterar
tabHAposta Jogador::apostasPremiadas(const tabHInt & sorteio) const
{
	tabHAposta money;
    for(auto it = apostas.begin();it!=apostas.end();it++){
        if(it->calculaCertos(sorteio) >= 3)money.insert(*it);
    }
	return money;
}
