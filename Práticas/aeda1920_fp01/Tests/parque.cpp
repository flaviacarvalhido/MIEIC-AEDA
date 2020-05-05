#include "parque.h"
#include <vector>

using namespace std;


ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli) :lotacao(lot),numMaximoClientes(nMaxCli) {
    this -> vagas = lot;
}

unsigned int ParqueEstacionamento::getNumLugares() const {
    return lotacao;
}

unsigned int ParqueEstacionamento::getNumMaximoClientes() const {
    return numMaximoClientes;
}

int ParqueEstacionamento::posicaoCliente(const string &nome) const {
    for (int i=0;i<clientes.size();i++){
        if(clientes[i].nome == nome){
            return i;
        }
    }
    return -1;
}

bool ParqueEstacionamento::adicionaCliente(const string &nome) {
    if(posicaoCliente(nome)==-1 && clientes.size() < numMaximoClientes){
        InfoCartao i;
        i.nome = nome;
        i.presente = false;
        clientes.push_back(i);
        return true;
    }
    else{
        return false;
    }

}

bool ParqueEstacionamento::entrar(const string &nome) {
    if (posicaoCliente(nome) == -1 || clientes[posicaoCliente(nome)].presente == true || vagas == 0){
        return false;
    }else{
        vagas = vagas - 1;
        clientes[posicaoCliente(nome)].presente=true;
        return true;
    }
}

bool ParqueEstacionamento::retiraCliente(const string &nome) {
    int i = posicaoCliente(nome);
    if( i == -1 || clientes[i].presente == true){
        return false;
    }else{
        clientes.erase(clientes.begin()+i);
        return true;
    }
}

bool ParqueEstacionamento::sair(const string &nome) {
    if(posicaoCliente(nome) != -1 && clientes[posicaoCliente(nome)].presente == true){
        vagas = vagas +1;
        clientes[posicaoCliente(nome)].presente=false;
        return true;
    }
    return false;
}

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const {
    return lotacao-vagas;
}

unsigned int ParqueEstacionamento::getNumClientesAtuais() const {
    return clientes.size();
}





