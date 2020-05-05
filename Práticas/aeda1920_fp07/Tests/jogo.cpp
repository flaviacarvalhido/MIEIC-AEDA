#include "jogo.h"
#include <sstream>


//a alterar
ostream &operator << (ostream &os, Circulo &c1)
{
    os << to_string(c1.pontuacao) << "-";
    if(c1.estado)os<<"true"<<"-";
    else os<<"false"<<"-";
    os<<to_string(c1.nVisitas)<<endl;
	return os;
}


//very hard
BinaryTree<Circulo> Jogo::inicia(int pos, int niv,vector<int> &pontos, vector<bool> &estados){
    Circulo c1(pontos[pos],estados[pos]);

    if(niv==0) return BinaryTree<Circulo>(c1);

    BinaryTree<Circulo> esq = inicia(2*pos+1,niv-1,pontos,estados);
    BinaryTree<Circulo> dir = inicia(2*pos+2,niv-1,pontos,estados);

    return BinaryTree<Circulo>(c1,esq,dir);
}

//a alterar
Jogo::Jogo(int niv, vector<int> &pontos, vector<bool> &estados)
{
    jogo=inicia(0,niv,pontos,estados);
}

//a alterar

string Jogo::escreveJogo()
{
    BTItrLevel<Circulo> it(jogo);
    stringstream res("");
    while(!it.isAtEnd()){
        res << it.retrieve();
        it.advance();
    }
    return res.str();

}

//a alterar
int Jogo::jogada()
{
    BTItrLevel<Circulo> it(jogo);
    int pontos=-1,pos=1;

    if(it.isAtEnd())return pontos;

    while(true){
        Circulo &c1 = it.retrieve();
        bool estado=c1.getEstado();

        int n;
        if(estado==false) n=pos; //diz se é o filho da esquerda ou direita
        else n=pos+1;

        c1.mudaEstado();
        c1.incNVisitas();

        pontos=c1.getPontuacao();

        int i=0;
        while(i<n && !it.isAtEnd()){ //itera pelo nivel t0do, até ao nivel seguinte na posição correta
            it.advance();
            i++;
        }

        if(!it.isAtEnd())pos+=n;    //incrementa pos para o nivel seguinte
        else break;
    }



    return pontos;
}


//a alterar
int Jogo::maisVisitado()
{
	BTItrLevel<Circulo> it(jogo);
	int visitas=0;

	it.advance();

	while(true){
	    if(visitas < it.retrieve().getNVisitas())visitas=it.retrieve().getNVisitas();

	    it.advance();

	    if(it.isAtEnd())return visitas;
	}
}

