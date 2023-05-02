#include "./include/CompteEpargne.h"

CompteEpargne::CompteEpargne(Personne* holder, Personne* advisor, float amount, float interest) : Compte(holder, advisor, amount) {
    this->p_interest = interest;
}

CompteEpargne::~CompteEpargne()
{
}
