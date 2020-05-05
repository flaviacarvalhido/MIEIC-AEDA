/*
 * jogo.cpp
 */

#include "jogo.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;


unsigned int Jogo::numPalavras(string frase)
{
  if ( frase.length() == 0 ) return 0;

  unsigned n=1;
  size_t pos = frase.find(' ');
  while (pos != string::npos) {
    frase = frase.substr(pos+1);
    pos = frase.find(' ');
    n++;
  }
  return n;
}

// a implementar
Jogo::Jogo()
{
}

// a implementar
Jogo::Jogo(list<Crianca>& lc2)
{
    this->criancas = lc2;
}

// a implementar
void Jogo::insereCrianca(const Crianca &c1)
{
    criancas.push_back(c1);
}

// a implementar
list<Crianca> Jogo::getCriancasJogo() const
{
    list<Crianca> res;
    res=criancas;
    return res;
}

// a implementar
string Jogo::escreve() const
{
    string res;

    for(_List_const_iterator<Crianca> it = criancas.begin(); it != criancas.end(); it++){
        res += it->escreve() + "\n";
    }

    return res;
}

// a implementar
Crianca& Jogo::perdeJogo(string frase)
{
    /*
    int palavras = numPalavras(frase),iter,count=0;

    while(criancas.size() > palavras){palavras=palavras-criancas.size();}
    iter = palavras;

    _List_const_iterator<Crianca> it;
    for(it = criancas.begin(); it != criancas.end(); it++){
        count+=1;
        if(count==iter){
            break;
        }
    }



    return (Crianca &)(*it);
     */


    list<Crianca> remove = criancas;
    int num = numPalavras(frase) ;

    list<Crianca>::iterator it = remove.begin();
    list<Crianca>::iterator ite = remove.end();

    while (remove.size()  > 1)
    {
        int livra = (remove.size() % num) - 1;
        for(int i = 0; i < livra; i++)
        {
            it++;
            if (it == ite)
                it = remove.begin();
        }
        remove.erase(it);
    }

    return *it;
}

// a implementar
list<Crianca>& Jogo::inverte()
{
    criancas.reverse();
    return criancas;
}

// a implementar
list<Crianca> Jogo::divide(unsigned id)
{
    list<Crianca> res;

    for(_List_const_iterator<Crianca> it = criancas.begin(); it != criancas.end(); it++){
        if(it->getIdade() > id){
            res.push_back(*it);
            criancas.remove(*it);
            it++;
        }
    }

    return res;
}

// a implementar
void Jogo::setCriancasJogo(const list<Crianca>& l1)
{
    this->criancas=l1;
}

// a implementar
bool Jogo::operator==(Jogo& j2)
{
    if(criancas == j2.criancas){
        return true;
    }
	return false;
}

// a implementar
list<Crianca> Jogo::baralha() const
{
    //srand(time(NULL));

    list<Crianca> res;
    list<Crianca>::const_iterator it1 = criancas.begin(), it2;
    list<Crianca>::const_iterator ite = criancas.end();

    while(it1 != ite)
    {
        int pos = rand() % criancas.size();
        it2 = res.begin();
        advance(it2, pos);
        res.insert(it2, (*it1));
        it1++;
    }

    return res;
}
