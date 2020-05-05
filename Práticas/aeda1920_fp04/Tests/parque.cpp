#include "parque.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <algorithm>
#include <vector>

using namespace std;



ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli):
	lotacao(lot), numMaximoClientes(nMaxCli) {
    numClientes = 0;
    vagas=lot; 
}

ParqueEstacionamento::~ParqueEstacionamento() {}

vector<InfoCartao> ParqueEstacionamento::getClientes() const { return clientes; }

unsigned int ParqueEstacionamento::getNumLugares() const { return lotacao; }

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const { return lotacao-vagas; }


// a imnplementar
int ParqueEstacionamento::posicaoCliente(const string &nome) const
{
    for(int i=0; i<clientes.size();i++){
        if(clientes[i].nome==nome){
            return i;
        }
    }
    return -1;
}

//a implementar
int ParqueEstacionamento::getFrequencia(const string &nome) const
{
    for(int i=0;i<clientes.size();i++){
        if(clientes[i].nome == nome){
            return clientes[i].frequencia;
        }
    }
    throw ClienteNaoExistente(nome);
}

// a alterar/atualizar ?
bool ParqueEstacionamento::adicionaCliente(const string & nome)
{
 	if ( numClientes == numMaximoClientes ) return false;
	if ( posicaoCliente(nome) != -1 ) return false;
	InfoCartao info;
	info.nome = nome;
    info.presente = false;
	clientes.push_back(info);
	numClientes++;
	return true;
}

// a alterar/atualizar ?
bool ParqueEstacionamento::retiraCliente(const string & nome)
{
	for (vector<InfoCartao>::iterator it = clientes.begin(); it != clientes.end(); it++)
		if ( it->nome == nome ) {
			if ( it->presente == false ) {
				clientes.erase(it);
				numClientes--;
				return true;
			}
			else return false;
		}
	return false;
}

// a alterar/atualizar ?
bool ParqueEstacionamento::entrar(const string & nome)
{
	if ( vagas == 0 ) return false;
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == true ) return false;
	clientes[pos].presente = true;
	vagas--;
	clientes[pos].frequencia +=1;
	return true;
}

// a alterar/atualizar ?
bool ParqueEstacionamento::sair(const string & nome)
{
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == false ) return false;
	clientes[pos].presente = false;
	vagas++;
	return true;
}

		
// a implementar
void ParqueEstacionamento::ordenaClientesPorFrequencia()
{
    insertionSort(clientes);
}

bool compNome(const InfoCartao &ic1, const InfoCartao &ic2) {
    return ic1.nome < ic2.nome;
}

// a implementar
void ParqueEstacionamento::ordenaClientesPorNome()
{
    sort(clientes.begin(),clientes.end(),compNome);
}


// a implementar
vector<string> ParqueEstacionamento::clientesGamaUso(int n1, int n2)
{
    vector<string> nomes;
    int inicio,fim;

    ordenaClientesPorFrequencia();
    for(int i =0;i<clientes.size();i++){
        if(clientes[i].frequencia == n1){
            inicio = i;
            break;
        }
        for(i;i<clientes.size();i++){
            if(clientes[i].frequencia == n2){
                fim=n2;
            }
        }
    }

    for(inicio;inicio<fim;inicio++){
        nomes.push_back(clientes[inicio].nome);
    }

    return nomes;
}


// a implementar
ostream & operator<<(ostream & os, const ParqueEstacionamento & pe)
{

    for(int i=0; i<pe.clientes.size();i++){
        os << pe.clientes[i].nome << ", " << pe.clientes[i].presente << ", " << to_string(pe.clientes[i].frequencia) << "\n";
    }

    return os;
}


// a implmentar
InfoCartao ParqueEstacionamento::getClienteAtPos(vector<InfoCartao>::size_type p) const
{
    InfoCartao info;
    int size=clientes.size();
    if(p>size-1 || p<0){throw PosicaoNaoExistente(p);}

    info = clientes[p];

    return info;
}


bool InfoCartao::operator==(const InfoCartao &ic1) const {
    if(nome==ic1.nome){return true;}
    return false;
}

bool InfoCartao::operator<(const InfoCartao &ic1) const {
    if(frequencia > ic1.frequencia)
        return true;
    else if(frequencia<ic1.frequencia){
        return false;
    }else{return nome<ic1.nome;}
}




