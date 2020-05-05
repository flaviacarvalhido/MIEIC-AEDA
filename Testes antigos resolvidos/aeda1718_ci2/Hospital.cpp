
#include "Hospital.h"

#include <algorithm>
#include <stack>
#include <iostream>



Hospital::Hospital(unsigned trayC):trayCapacity(trayC)
{ }

void Hospital::addDoctor(const Doctor &d1) {
    doctors.push_back(d1);
}

list<Doctor> Hospital::getDoctors() const {
    return doctors;
}

void Hospital::addTrays(stack<Patient> tray1) {
    letterTray.push_back(tray1);
}

list<stack<Patient> > Hospital::getTrays() const {
    return letterTray;
}



unsigned Hospital::numPatients(string medicalSpecialty) const
{
    unsigned int res=0;

    for(_List_const_iterator<Doctor> it = doctors.begin(); it != doctors.end(); it++){
        if(it->getMedicalSpecialty() == medicalSpecialty){
            res+=it->getPatients().size();
        }
    }
    return res;
}

bool sortingDocs(Doctor d1, Doctor d2){
    if(d1.getPatients().size()>d2.getPatients().size())return false;
    else if(d1.getPatients().size()<d2.getPatients().size())return true;
    else if(d1.getPatients().size()==d2.getPatients().size()){
        if(d1.getMedicalSpecialty()>d2.getMedicalSpecialty())return false;
        else if(d1.getMedicalSpecialty()<d2.getMedicalSpecialty())return true;
        else if(d1.getMedicalSpecialty()==d2.getMedicalSpecialty()){
            if(d1.getCode()>d2.getCode())return false;
            else if(d1.getCode()<d2.getCode())return true;
        }
    }
    return false;
}


void Hospital::sortDoctors() {
    doctors.sort(sortingDocs);
}



bool Hospital::addDoctor(unsigned codM1, string medicalSpecialty1) {
    Doctor d1(codM1,medicalSpecialty1);

    int count=0;
    for(_List_const_iterator<Doctor> it = doctors.begin();it!=doctors.end();it++){
        if(it->getMedicalSpecialty()==medicalSpecialty1)count++;
    }

    if(count < 3){
        doctors.push_back(d1);
        return true;
    }
    return false;

}



queue<Patient> Hospital::removeDoctor(unsigned codM1) {

    bool found=false;

    for(_List_const_iterator<Doctor> it =doctors.begin();it!=doctors.end();it++){
        if(it->getCode()==codM1){
            doctors.erase(it);
            return it->getPatients();
        }
    }

    throw DoctorInexistent();

}


bool Hospital::putInLessBusyDoctor(unsigned cod1, string medicalSpecialty1) {

    vector<Doctor> docs;
    Patient p1(cod1,medicalSpecialty1);

    for(_List_iterator<Doctor> it=doctors.begin();it!=doctors.end();it++){
        if(it->getMedicalSpecialty()==medicalSpecialty1){
            docs.push_back(*it);
        }
    }

    if(docs.size()==0)return false;

    int indexmin = 0;

    for(unsigned int i=1;i<docs.size();i++){
        if(docs[indexmin].getPatients().size()>docs[i].getPatients().size()){
            indexmin=i;
        }
    }

    for(auto it=doctors.begin();it!=doctors.end();it++){
        if(it->getCode()==docs[indexmin].getCode()){
            it->addPatient(p1);
            break;
        }
    }
    return true;
}



void Hospital::processPatient(unsigned codM1) {
    bool found=false,assigned=false;
    stack<Patient> newTray;
    Patient pat;

    for(auto it=doctors.begin();it!=doctors.end();it++){
        if(it->getCode()==codM1 && it->getPatients().size()!=0){
            pat = it->removeNextPatient();
            found=true;
            break;
        }
    }

    if(!found){
        return;
    }else{
        for(auto it=letterTray.begin();it!=letterTray.end();it++){
            if(it->size()==trayCapacity){
                continue;
            }else{
                it->push(pat);
                return;
            }
        }
        newTray.push(pat);
        letterTray.push_back(newTray);
    }
}


unsigned Hospital::removePatients(unsigned codP1) {

    unsigned int res=0;
    auto it = letterTray.begin();       //importante!! repor iterador!!

    while(it!=letterTray.end()){

        if(it->top().getCode()==codP1){
            it->pop();
            res++;
        }
        if(it->size()==0){
            it=letterTray.erase(it);
        }else {
            it++;
        }
    }

    return res;

}
