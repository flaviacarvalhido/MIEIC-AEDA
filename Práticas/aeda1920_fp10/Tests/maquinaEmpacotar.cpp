#include "maquinaEmpacotar.h"
#include <sstream>


MaquinaEmpacotar::MaquinaEmpacotar(int capCaixas): capacidadeCaixas(capCaixas)
{}

unsigned MaquinaEmpacotar::numCaixasUsadas() {
	return caixas.size();
}

unsigned MaquinaEmpacotar::addCaixa(Caixa& cx) {
	caixas.push(cx);
	return caixas.size();
}

HEAP_OBJS MaquinaEmpacotar::getObjetos() const {
	return this->objetos;
}

HEAP_CAIXAS MaquinaEmpacotar::getCaixas() const {
	return this->caixas;
}


// a alterar
unsigned MaquinaEmpacotar::carregaPaletaObjetos(vector<Objeto> &objs) {
	int count=0;
	vector<Objeto> remaining;

    for(unsigned int i=0; i<objs.size();i++){
	    if(objs[i].getPeso() <= capacidadeCaixas){
	        count +=1;
            objetos.push(objs[i]);
            continue;
	    }
	    remaining.push_back(objs[i]);
	}
    objs=remaining;



    return count;
}

// a alterar
Caixa MaquinaEmpacotar::procuraCaixa(Objeto& obj) {
    //resolução stor
    //estrutura temporaria para guardar caixas retiradas da fila
    vector<Caixa> temp;

    //procura caixa mais cheia, ainda com espaco para obj
    while ( !caixas.empty() )
    {
        Caixa cx = caixas.top();
        caixas.pop();
        if ( cx.getCargaLivre() >= obj.getPeso() ) {

            for (unsigned i=0; i<temp.size(); i++) //repoe na fila de caixas as caixas retiradas da frente.
                caixas.push(temp[i]);
            return cx;
        }
        else temp.push_back(cx); //coloca as caixas nao utilizadas num vetor temporario
    }
    for (unsigned i=0; i<temp.size(); i++) //repoe as caixas nao utilizadas de volta, caso nenhuma sirva
        caixas.push(temp[i]);

    return Caixa(capacidadeCaixas); //e retorna uma nova caixa


    /*
    HEAP_CAIXAS remaining;
    Caixa f;
    bool found=false;
	for(unsigned int i=0;i<caixas.size();i++){
	    if(obj.getPeso() <= caixas.top().getCargaLivre() && !found){
	        found=true;
	        f=caixas.top();
	        caixas.pop();
	        continue;
	    }
	    remaining.push(caixas.top());
	    caixas.pop();
	}

	caixas=remaining;

	if(!found){
	    Caixa cx(obj.getPeso());
	    addCaixa(cx);
        return cx;
	}

	return f;
    */
}

// a alterar
unsigned MaquinaEmpacotar::empacotaObjetos() {


    while(!objetos.empty()){
        Objeto o=objetos.top();
        objetos.pop();
        Caixa c1 = procuraCaixa(o);
        c1.addObjeto(o);
        caixas.push(c1);
    }

    return caixas.size();

}

// a alterar
string MaquinaEmpacotar::imprimeObjetosPorEmpacotar() const {
	if(objetos.empty())return "Nao ha objetos!";

	HEAP_OBJS objtemp = objetos;

	stringstream s;
	while(!objtemp.empty()){
	    s << objtemp.top();
	    objtemp.pop();
	}
	return s.str();
}

// a alterar
Caixa MaquinaEmpacotar::caixaMaisObjetos() const {
	Caixa cx;
	return cx;
}



