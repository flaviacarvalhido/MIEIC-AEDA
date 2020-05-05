#include <iostream>
#include <vector>

using namespace std;

/**
 * Versao da classe generica Grafo usando a classe vector
 */

template <class N, class A> class Aresta;

template <class N, class A>
class No {
public:
	N info;
	vector< Aresta<N,A> > arestas;
	No(N inf) {
		info = inf;
	}
};

template <class N, class A>
class Aresta {
public:
	A valor;
	No<N,A> *destino;
	Aresta(No<N,A> *dest, A val) {
		valor = val;
		destino = dest;
	}
};

template <class N, class A> 
class Grafo { 
	vector< No<N,A> *> nos;
  public: 
    Grafo();
    ~Grafo();
    Grafo & inserirNo(const N &dados);
    Grafo & inserirAresta(const N &inicio, const N &fim, const A &val);
    Grafo & eliminarAresta(const N &inicio, const N &fim);
    A & valorAresta(const N &inicio, const N &fim);

    int numArestas(void) const;

    int numNos(void) const;

    void imprimir(std::ostream &os) const;
};

template <class N, class A> 
std::ostream & operator<<(std::ostream &out, const Grafo<N,A> &g);


// excecao NoRepetido
template <class N>
class NoRepetido
{
public:
   N info;
   NoRepetido(N inf) { info=inf; }
};
template <class N> 
std::ostream & operator<<(std::ostream &out, const NoRepetido<N> &no)
{ out << "No repetido: " << no.info; return out; }


template <class N>
class ArestaRepetida
{
public:
    N info1, info2;
    ArestaRepetida(N inf1, N inf2) { info1=inf1; info2=inf2; }
};
template <class N>
std::ostream & operator<<(std::ostream &out, const ArestaRepetida<N> &a)
{ out << "Aresta repetida: " << a.info1 << " , " << a.info2 ; return out; }

// excecao NoInexistente
template <class N>
class NoInexistente {
public:
	N info;
	NoInexistente(N inf) {
		info = inf;
	}
};

template <class N>
std::ostream & operator<<(std::ostream &out, const NoInexistente<N> &ni)
{ out << "No inexistente: " << ni.info; return out; }

template <class N>
class ArestaInexistente
{
public:
    N info1, info2;
    ArestaInexistente(N inf1, N inf2) { info1=inf1; info2=inf2; }
};
template <class N>
std::ostream & operator<<(std::ostream &out, const ArestaInexistente<N> &a)
{ out << "Aresta inexistente: " << a.info1 << " , " << a.info2 ; return out; }



template <class N, class A>
Grafo<N,A>::Grafo() {}

template <class N, class A>
Grafo<N,A>::~Grafo() {
    typename vector< No<N,A> *>::const_iterator it;
    for (it=nos.begin(); it!=nos.end(); it++)
        delete *it;
}

template <class N, class A>
int Grafo<N,A>::numArestas(void) const {
    int result=0;
    for (int i =0; i<nos.size();i++){
        result += nos[i]->arestas.size();
    }
    return result;
}

template <class N, class A>
int Grafo<N,A>::numNos(void) const {
    return nos.size();
}


template <class N, class A>
Grafo<N, A> & Grafo<N, A>::inserirNo(const N &dados) {

    typename vector<No<N,A>*>::const_iterator i;
    for(i=nos.begin();i!=nos.end();i++){
        if((*i)->info == dados) throw NoRepetido<N>(dados);
    }

    No<N,A> *n = new No<N,A>(dados);
    nos.push_back(n);
    return *this;
}

template <class N, class A>
Grafo<N,A> & Grafo<N,A>::inserirAresta(const N &inicio, const N &fim, const A &val) {
    bool foundExp=true;

    typename vector<No<N,A>*>::const_iterator i,j;
    typename vector<Aresta<N,A>>::const_iterator a;
    for(i=nos.begin();i!=nos.end();i++){
        if((*i)->info == inicio) {
            foundExp=false;
            break;
        }
    }
    if(foundExp){throw NoInexistente<N>(inicio);}
    foundExp=true;
    for(j=nos.begin();j!=nos.end();j++){
        if((*j)->info == fim) {
            foundExp = false;
            break;
        }
    }
    if(foundExp){throw NoInexistente<N>(fim);}
    foundExp=true;

    No<N,A> *noInicio_apt=*i;
    No<N,A> *noFim_apt=*j;

    for(a=(*i)->arestas.begin();a!=(*i)->arestas.end(); a++){
        if(a->destino->info == fim) throw ArestaRepetida<N> (inicio,fim);
    }

    Aresta<N,A> aresta1(noFim_apt, val);
    noInicio_apt -> arestas.push_back(aresta1);

    return *this;
}

template <class N, class A>
A & Grafo<N,A> :: valorAresta(const N &inicio, const N &fim){
    typename vector<No<N,A>*>::iterator it;
    typename vector<Aresta<N,A>>::iterator a;

    bool foundExp = true;

    for(it = nos.begin(); it != nos.end(); it++){
        if((*it)->info == inicio) {
            foundExp=false;
            break;
        }
    }
    if(foundExp){throw NoInexistente<N>(inicio);}
    foundExp=true;

    for(a = (*it)->arestas.begin();a!=(*it)->arestas.end();a++){
        if(a->destino->info == fim){
            foundExp=false;
            return a->valor;
        }
    }
    if(foundExp) throw ArestaInexistente<N>(inicio,fim);

}

template<class N,class A>
Grafo<N,A> & Grafo<N,A>::eliminarAresta(const N &inicio, const N &fim) {

    typename vector<No<N,A>*>::iterator it;
    typename vector<Aresta<N,A>>::iterator a;

    bool foundExp = true;

    for(it=nos.begin();it!=nos.end();it++){
        if((*it)->info == inicio) {
            foundExp=false;
            break;
        }
    }

    if(foundExp){throw NoInexistente<N>(inicio);}
    foundExp=true;

    for(a = (*it)->arestas.begin();a!=(*it)->arestas.end();a++){
        if(a->destino->info == fim){
            foundExp=false;
            (*it) -> arestas.erase(a);
            return *this;
        }
    }
    if(foundExp) throw ArestaInexistente<N>(inicio,fim);

}

template<class N,class A>
void Grafo<N,A>::imprimir(std::ostream &os) const {

    typename vector<No<N,A>*>::const_iterator it;
    typename vector<Aresta<N,A>>::const_iterator a;

    for(it=nos.begin();it!=nos.end();it++){
        os<<"( "<<(*it)->info;
        for(a=(*it)->arestas.begin();a!=(*it)->arestas.end();a++){
            os<<"[ "<<a->destino->info <<" "<<a->valor<<"] ";
        }
        os<<") ";
    }

}

template <class N, class A>
std::ostream & operator<<(std::ostream &out, const Grafo<N, A> &g)
{
    g.imprimir(out);
    return out;
}