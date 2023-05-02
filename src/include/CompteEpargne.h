#pragma once
#include <iostream>
#include <string>
#include "Compte.h"
#include "Personne.h"
#include "Operation.h"

using namespace std;

class CompteEpargne : public Compte
{
private:
    float p_interest;

public:
    CompteEpargne() = default;
    CompteEpargne(Personne* holder, Personne* advisor, float amount, float interest);
    ~CompteEpargne();
};
