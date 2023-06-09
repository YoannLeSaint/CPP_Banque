#include "./include/CompteEnLigne.h"


CompteEnLigne::CompteEnLigne(Personne* holder, Personne* advisor, float amount) : Compte(holder, advisor, amount){}

string CompteEnLigne::toString(){
    stringstream ss;
    if (getBalance() > 0){
        ss << getHolder().toString() << " (Compte en Ligne) | +" << getBalance() << "EUR" << endl;
    } else {
        ss << getHolder().toString() << " (Compte en Ligne) | " << getBalance() << "EUR" << endl;
    }
    return ss.str();
}