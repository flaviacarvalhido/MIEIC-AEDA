//
// Created by Tiago on 16/11/2019.
//

#include <algorithm>
#include "AfterSalesService.h"

using namespace std;

int AfterSalesService::tableOrdinal = 0;

AfterSalesService::AfterSalesService(int toWrapQS) : toWrapQueueSize(toWrapQS) {

}

vector<Article*> AfterSalesService::getPresentsTable() const {
    return presentsTable;
}

queue<Article*> AfterSalesService::getToWrap() const {
    return toWrap;
}

queue<Article*> AfterSalesService::getToDeliver() const {
    return toDeliver;
}

/**
 *  Place presents on the presents table, assigning them a relative present number and a sequential number.
 *  Assumes all given presents are from the same client.
 */
void AfterSalesService::dropPresentsOnTable(vector<Article*> presents) {
    for(vector<Article*>::size_type i = 0; i<presents.size(); i++) {
        presents[i]->setPresentNumber(i+1);
        presents[i]->setArrivalNumber(++tableOrdinal);
        presentsTable.push_back(presents[i]);
    }
}

/**
 * Remove from the table all articles of a given client.
 */
vector<Article*> AfterSalesService::pickPresentsFromTable(long client) {
    vector <Article*>res;
    for(unsigned int i=0;i<presentsTable.size();i++){
        if(presentsTable[i]->getClient()==client){
            res.push_back(presentsTable[i]);
            presentsTable.erase(presentsTable.begin()+i);
            i--;  //very important when erasing in the middle of iterations
        }
    }
    return res;
}

bool compareArticlesForTake(Article* a1, Article* a2) {
    if (a1->getPresentNumber() + 2 < a2->getPresentNumber())
        return true;
    return a1->getArrivalNumber() < a2->getArrivalNumber();
}

/**
 * Sort the first 10 articles in the presents table:
 *   (i) give priority to articles that are NOT to be delivered at home (client is waiting);
 *  (ii) if two articles have (relative) present numbers differing more than 2,
 *       the one with lower present number should have priority (clients should not wait too much);
 * (iii) else, maintain article order in the table.
 */
bool sortingPres(Article*a1,Article*a2){
    if(a1->getDeliverHome()  &&  !a2->getDeliverHome())return false;
    else if(a2->getDeliverHome() && !a1->getDeliverHome())return true;
    else if(a1->getDeliverHome() && a2->getDeliverHome())return false;
    else if(!a1->getDeliverHome() && !a2->getDeliverHome()){
        if(a1->getPresentNumber() - a2->getPresentNumber() > 2)return false;
        else if(a2->getPresentNumber()-a1->getPresentNumber() > 2)return true;


    }
}

void AfterSalesService::sortArticles() {
    sort(presentsTable.begin(),presentsTable.begin()+10,sortingPres);

}

/**
 * Move the first presents in the table to the queue of presents to wrap, taking into account the size of the queue.
 */
void AfterSalesService::enqueueArticles() {

    //sortArticles();

    while(toWrap.size()<toWrapQueueSize && !presentsTable.empty()){
        toWrap.push(presentsTable[0]);
        presentsTable.erase(presentsTable.begin());
    }

}

/**
 * Process the first present to wrap. If it is an article to deliver home, the article is placed in the toDeliver queue.
 */
Article* AfterSalesService::wrapNext() {

    while(!toWrap.empty()) {
        Article *c = toWrap.front();
        toWrap.pop();

        if (c->getDeliverHome()) {
            toDeliver.push(c);
            return NULL;
        } else return c;
    }
    return nullptr;


}

