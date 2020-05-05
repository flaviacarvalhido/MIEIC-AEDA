#include <iostream>
#include <string>
#include <fstream>
#include "dicionario.h"
#include "bst.h"

using namespace std;

BST<PalavraSignificado> Dicionario::getPalavras() const {
	return palavras;
}

//a alterar
bool PalavraSignificado::operator < (const PalavraSignificado &ps1) const {
     return true;
}

//a alterar
void Dicionario::lerDicionario(ifstream &fich)
{
    string word,meaning;

    while(!fich.eof()){
        getline(fich,word);
        getline(fich,meaning);
        palavras.insert(PalavraSignificado(word,meaning));
    }

}

//a alterar
string Dicionario::consulta(string palavra) const
{
    BSTItrIn<PalavraSignificado> it(palavras);
    string antes="a",depois="z",siga,sigd;


    while(!it.isAtEnd()){
        if(it.retrieve().getPalavra() == palavra)return it.retrieve().getSignificado();

        if(it.retrieve().getPalavra() < palavra && antes < it.retrieve().getPalavra()){
            antes=it.retrieve().getPalavra();
            siga=it.retrieve().getSignificado();
            continue;
        }

        if(it.retrieve().getPalavra() > palavra && depois > it.retrieve().getPalavra()){
            depois=it.retrieve().getPalavra();
            sigd=it.retrieve().getSignificado();
            continue;
        }
        it.advance();
    }
    throw PalavraNaoExiste(palavra,antes,siga,depois,sigd);
}

//a alterar
bool Dicionario::corrige(string palavra, string significado)
{
    BSTItrIn<PalavraSignificado> it(palavras);

    while(!it.isAtEnd()){
        if(it.retrieve().getPalavra() == palavra){
            PalavraSignificado p1=it.retrieve();
            palavras.remove(p1);
            p1.setSignificado(significado);
            palavras.insert(p1);
            return true;
        }

        it.advance();
    }

    palavras.insert(PalavraSignificado(palavra,significado));
    return false;
}

//a alterar
void Dicionario::imprime() const
{
    BSTItrIn<PalavraSignificado> it(palavras);

    while(!it.isAtEnd()){
        cout << it.retrieve().getPalavra() << endl << it.retrieve().getSignificado() <<endl;
        it.advance();
    }

}

