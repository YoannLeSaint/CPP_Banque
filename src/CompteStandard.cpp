#include "./include/CompteStandard.h"

CompteStandard::CompteStandard(Personne* holder, Personne* advisor, float amount) : Compte(holder, advisor, amount)
{
}

string CompteStandard::toString(){
    stringstream ss;
	ss << getHolder().toString() << " (Compte Standard) - " << getBalance() << "EUR" << endl;
	return ss.str();
}
