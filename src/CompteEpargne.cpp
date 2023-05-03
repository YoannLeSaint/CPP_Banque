#include "./include/CompteEpargne.h"

CompteEpargne::CompteEpargne(Personne* holder, Personne* advisor, float amount, float interest) : Compte(holder, advisor, amount) {
    this->p_interest = interest;
}

string CompteEpargne::toString(){
    stringstream ss;
	ss << getHolder().toString() << " (Compte Epargne) - " << getBalance() << "EUR" << endl;
	return ss.str();
}
