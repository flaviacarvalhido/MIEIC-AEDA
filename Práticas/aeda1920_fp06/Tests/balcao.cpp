#include <queue>
#include <cstdlib>
#include "balcao.h"
#include "exceptions.h"

using namespace std;

//a alterar
Cliente::Cliente() {
    this->numPresentes = 1+rand()%((5+1)-1);
}

//a alterar
int Cliente::getNumPresentes() const {
    return numPresentes;
}

//a alterar
Balcao::Balcao(int te): tempo_embrulho(te) {
    this->tempo_atual = 0;
    this->prox_chegada = 1+rand() % ((20-1)+1);
    this->prox_saida=0;
    this->clientes_atendidos=0;
}

//a alterar
void Balcao:: proximoEvento()
{
    if(!clientes.empty()){
        if(prox_chegada>prox_saida){
            tempo_atual=prox_saida;
            saida();
        }else{
            tempo_atual=prox_chegada;
            chegada();
        }
    }else{
        tempo_atual=prox_chegada;
        chegada();
    }
}

//a alterar
void Balcao::chegada()
{
    Cliente c;

    clientes.push(c);

    prox_chegada=tempo_atual+1+rand()%((20-1)+1);

    if(clientes.size() == 1){
        prox_saida=tempo_atual + c.getNumPresentes()*tempo_embrulho;
    }

    cout << "tempo:" << tempo_atual <<endl << "chegou novo cliente com " << c.getNumPresentes() << " presentes"<<endl;

}

//a alterar
void Balcao::saida()
{

    clientes_atendidos+=1;

    Cliente c=getProxCliente();
    clientes.pop();
    if(!clientes.empty())
        prox_saida=tempo_atual + clientes.front().getNumPresentes()*tempo_embrulho;
    else
        prox_saida=0;

    //cout << tempo_atual << endl << c.getNumPresentes() << endl;
}


int Balcao::getTempoAtual() const { return tempo_atual; }

int Balcao::getProxChegada() const { return prox_chegada; }

//a alterar
ostream & operator << (ostream & out, const Balcao & b1)
{
     out << "Clientes atendidos: " << b1.clientes_atendidos << endl << "Clientes em espera: " << b1.clientes.size() << endl;
     return out;
}

//a alterar
int Balcao::getTempoEmbrulho() const {
	return tempo_embrulho;
}

//a alterar
int Balcao::getProxSaida() const {
	return prox_saida;
}

//a alterar
int Balcao::getClientesAtendidos() const {
	return clientes_atendidos;
}

//a alterar
Cliente & Balcao::getProxCliente() {
    if(clientes.empty()){
        throw FilaVazia();
    }
    else{
        return clientes.front();
    }
}

      
