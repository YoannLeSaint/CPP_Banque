#include "./include/CompteStandard.h"

CompteStandard::CompteStandard(Personne* holder, Personne* advisor, float amount) : Compte(holder, advisor, amount)
{
}

string CompteStandard::toString(){
    stringstream ss;
    if (getBalance() > 0){
        ss << getHolder().toString() << " (Compte Standard) | +" << getBalance() << "EUR" << endl;
    } else {
        ss << getHolder().toString() << " (Compte Standard) | " << getBalance() << "EUR" << endl;
    }
    return ss.str();
}
