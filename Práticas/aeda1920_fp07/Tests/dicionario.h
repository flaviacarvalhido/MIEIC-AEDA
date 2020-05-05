#ifndef _DIC
#define _DIC
#include <string>
#include <fstream>
#include "bst.h"


class PalavraSignificado {
      string palavra;
      string significado;
public:
       PalavraSignificado(string p, string s): palavra(p), significado(s) {}
       string getPalavra() const { return palavra; }
       string getSignificado() const { return significado; }
       void setSignificado(string sig) { this->significado=sig; }
       bool operator < (const PalavraSignificado &ps1) const;
};

class Dicionario
{
      BST<PalavraSignificado> palavras;
public:
      Dicionario(): palavras(PalavraSignificado("","")){};
      BST<PalavraSignificado> getPalavras() const;
      void lerDicionario(ifstream &fich);
      string consulta(string palavra) const;
      bool corrige(string palavra, string significado);
      void imprime() const;
};

// a alterar
class PalavraNaoExiste
{
    string palavra,antes,siga,depois,sigd;
public:
    PalavraNaoExiste(string palavra,string antes, string siga, string depois, string sigd):palavra(palavra),antes(antes),siga(siga),depois(depois),sigd(sigd){};
	string getPalavraAntes() const { return antes; }
	string getSignificadoAntes() const { return siga; }
	string getPalavraApos() const { return depois; }
	string getSignificadoApos() const { return sigd; }
};


#endif
