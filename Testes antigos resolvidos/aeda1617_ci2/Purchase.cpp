//
// Created by Tiago on 16/11/2019.
//

#include "Purchase.h"
#include <stack>

using namespace std;

Purchase::Purchase(long cli) : client (cli) {
}

long Purchase::getClient() const {
    return client;
}

list< stack<Article*> > Purchase::getBags() const {
    return bags;
}

/**
 * Create an Article associated with the client of this purchase.
 */
Article* Purchase::createArticle(long barCode, bool present, bool deliverHome) {
    Article a(client, barCode);
    a.setPresent(present);
    a.setDeliverHome(deliverHome);

    return new Article(a);
}

/**
 * Add an Article to the bags of this purchase. A new bag is added when the last bag is full.
 */
void Purchase::putInBag(Article* article) {
    bool found=false;
    stack<Article*> newBag;
    for(auto a=bags.begin();a!=bags.end();a++){
        if(a->size()==BAG_SIZE){
            continue;
        }else{
            found = true;
            a->push(article);
        }
    }

    if(!found){
        newBag.push(article);
        bags.push_back(newBag);
    }
}

/**
 * Pop from the bags all articles that are presents.
 * All other articles are pushed back into the bags where they were, maintaining order.
 */
vector<Article*> Purchase::popPresents() {
    stack <Article*> temp,temp2,noPress;
    vector<Article*>press;
    for(auto a=bags.begin();a!=bags.end();a++){
        temp=*a;
        while(!temp.empty()) {
            if (temp.top()->getPresent()) {
                press.push_back(temp.top());
                temp.pop();
            } else {
                temp2.push(temp.top());
                temp.pop();
            }
        }

        while(!temp2.empty()){
            noPress.push(temp2.top());
            temp2.pop();
        }

        *a=noPress;

        noPress=temp2;
    }

    return press;
}

