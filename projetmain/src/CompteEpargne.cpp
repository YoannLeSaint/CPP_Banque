#include "./include/CompteEpargne.h"

CompteEpargne::CompteEpargne(Personne* holder, Personne* advisor, float amount, float interest, int id) : Compte(holder, advisor, amount, id) {
    this->p_interest = interest;
}

string CompteEpargne::toString(){
    stringstream ss;
    if (getBalance() > 0){
        ss << getHolder()->toString() << " (Compte Epargne) | +" << getBalance() << "EUR" << endl;
    } else {
        ss << getHolder()->toString() << " (Compte Epargne) | " << getBalance() << "EUR" << endl;
    }
    return ss.str();
}

string CompteEpargne::getValues(){
    stringstream ss;
    ss << getId() << ", 'Compte Epargne', " << getHolder()->getIdClient() << ", " << getAdvisor()->getIdAdvisor() << ", " << getBalance() << ", " << this->p_interest;
    return ss.str();
}

string CompteEpargne::columns(){
    string s;
    s = "'ID', 'Type', 'HolderId', 'AdvisorId', 'Balance', 'Interest'";
    return s;
}