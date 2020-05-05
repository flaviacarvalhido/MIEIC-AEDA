
#include "Doctor.h"
#include <algorithm>
#include "iostream"


Patient::Patient() {}

Patient::Patient(unsigned codP, string mS): codeP(codP), medicalSpecialty(mS)
{}

string Patient::getMedicalSpecialty() const {
    return medicalSpecialty;
}

unsigned Patient::getCode() const {
    return codeP;
}

Doctor::Doctor(unsigned codM, string mS): codeM(codM), medicalSpecialty(mS)
{}


Doctor::Doctor(unsigned codM, string mS, queue<Patient> patients1): codeM(codM), medicalSpecialty(mS), patients(patients1)
{}

unsigned Doctor::getCode() const {
    return codeM;
}

string Doctor::getMedicalSpecialty() const {
    return medicalSpecialty;
}

queue<Patient> Doctor::getPatients() const {
    return patients;
}

void Doctor::addPatient(const Patient &p1)  {
    patients.push(p1);
}

Patient Doctor::removeNextPatient() {
    if (!patients.empty()) {
        Patient p1 = patients.front();
        patients.pop();
        return p1;
    }
    else throw PatientInexistent();
}




void Doctor::moveToFront(unsigned codP1) {
    queue<Patient> pat,var=patients,front,back;
    bool found=false;


    while(var.size()!=0){
        if(var.front().getCode()!=codP1 && !found){
            front.push(var.front());
            var.pop();
        }else if(var.front().getCode()==codP1){
            pat.push(var.front());
            found =true;
            var.pop();
        }else{
            back.push(var.front());
            var.pop();
        }
    }

    while(front.size()!=0){
        pat.push(front.front());
        front.pop();
    }
    while(back.size()!=0){
        pat.push(back.front());
        back.pop();
    }

    if(found)patients=pat;
}

void Doctor::operator=(const Doctor &d1) {
    codeM = d1.getCode();
    medicalSpecialty = d1.getMedicalSpecialty();
}

void Patient::operator=(const Patient &p1) {
    codeP = p1.getCode();
    medicalSpecialty = p1.getMedicalSpecialty();
}
