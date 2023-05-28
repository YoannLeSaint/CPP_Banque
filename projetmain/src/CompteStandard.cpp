#include "./include/CompteStandard.h"

CompteStandard::CompteStandard(Personne* holder, Personne* advisor, float amount, int id) : Compte(holder, advisor, amount, id)
{
}

string CompteStandard::toString(){
    stringstream ss;
    if (getBalance() > 0){
        ss << getHolder()->toString() << " (Compte Standard) | +" << getBalance() << "EUR" << endl;
    } else {
        ss << getHolder()->toString() << " (Compte Standard) | " << getBalance() << "EUR" << endl;
    }
    return ss.str();
}

string CompteStandard::getValues(){
    stringstream ss;
    ss << getId() << ", 'Compte Standard', " << getHolder()->getIdClient() << ", " << getAdvisor()->getIdAdvisor() << ", " << getBalance();
    return ss.str();
}

string CompteStandard::columns(){
    string s;
    s = "'ID', 'Type', 'HolderId', 'AdvisorId', 'Balance'";
    return s;
}