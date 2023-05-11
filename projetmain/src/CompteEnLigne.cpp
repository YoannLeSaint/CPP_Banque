#include "./include/CompteEnLigne.h"


CompteEnLigne::CompteEnLigne(Personne* holder, Personne* advisor, float amount, int id) : Compte(holder, advisor, amount, id){}

string CompteEnLigne::toString(){
    stringstream ss;
    if (getBalance() > 0){
        ss << this->getHolder()->toString() << " (Compte en Ligne) | +" << getBalance() << "EUR" << endl;
    } else {
        ss << this->getHolder()->toString() << " (Compte en Ligne) | " << getBalance() << "EUR" << endl;
    }
    return ss.str();
}

string CompteEnLigne::getValues(){
    stringstream ss;
    ss << getId() << ", 'Compte en Ligne', " << getHolder()->getIdClient() << ", " << getAdvisor()->getIdAdvisor() << ", " << getBalance();
    return ss.str();
}

string CompteEnLigne::columns(){
    string s;
    s = "'ID', 'Type', 'HolderId', 'AdvisorId', 'Balance'";
    return s;
}