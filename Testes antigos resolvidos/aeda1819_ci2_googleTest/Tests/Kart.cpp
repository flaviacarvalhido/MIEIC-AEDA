#include <cstdlib>
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
#include <time.h>
#include <string>
#include "Kart.h"

#include <algorithm>

using namespace std;

//To help build better array
string itos(int i){
    stringstream s;
    s << i;
    return s.str();
}

void CGrupo::criaGrupo()
{
    float cilindradas[4]  = {134,250,450,600};
    bool avariados[3]  = {true,false,false};

    srand (1);   //Criar Pistas e Karts de Teste
    for(int i=1;i<=50;i++){
        vector<CKart> frota;
        for(int j=1;j<=50;j++){
            frota.push_back(CKart(avariados[rand()% 3],
                                  ("KART - "+itos(i))+itos(j),(i-1)*50+j,cilindradas[(rand() % 4)]));
        }
        adicionaPista(CPista("Pista - "+itos(i),frota));
    }
}


vector <CKart> CPista::getKartsAvariados()
{
    vector<CKart> aux;
    for (vector<CKart>::iterator it = frotaKartsPista.begin() ; it != frotaKartsPista.end(); ++it) {
        if ((it)->getAvariado()) aux.push_back((*it));
    }
    return aux;
}

bool numberSort(CKart k1,CKart k2){
    if(k1.getNumero() > k2.getNumero()){
        return false;
    }
    return true;
}

//Exercicio 1 a)     
vector<CKart> CGrupo::ordenaKarts()
{
	vector<CKart> vord;
	for(unsigned int i=0;i<pistasG.size();i++){
	    vord.insert(vord.end(),pistasG[i].getFrotaActual().begin(),pistasG[i].getFrotaActual().end());
	}

	sort(vord.begin(),vord.end(),numberSort);

	return vord;
}

//Exercicio 1 b)  
int CGrupo::numAvariados(int cilind)
{
    int res=0;

    for(unsigned int i =0;i<pistasG.size();i++){
        for(unsigned int j=0;j<pistasG[i].getKartsAvariados().size();j++){
            if(pistasG[i].getKartsAvariados()[j].getCilindrada()==cilind)
                res+=1;
        }
    }
    return res;

}

//Exercicio 1 c)   
bool CPista::prepararCorrida(int numeroKarts, int cilind)
{
    int count=0;
    for(unsigned int i=0;i<frotaKartsPista.size();i++){
        if(frotaKartsPista[i].getCilindrada() == cilind && !frotaKartsPista[i].getAvariado()){
            count+=1;
            kartsLinhaPartida.push(frotaKartsPista[i]);
        }
        if(count==numeroKarts)break;
    }
    if(count < numeroKarts) return false;
    return true;
}

//Exercicio 1 d) 
int CPista::inicioCorrida()
{
    while(!kartsLinhaPartida.empty()){
        kartsEmProva.push_back(kartsLinhaPartida.front());
        kartsLinhaPartida.pop();
    }
    return kartsEmProva.size();
}

