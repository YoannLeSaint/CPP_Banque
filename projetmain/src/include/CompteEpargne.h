#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <Personne.h>
#include <Operation.h>
#include "Compte.h"

using namespace std;

class CompteEpargne : public Compte
{
private:
    float p_interest;

public:
    CompteEpargne() = default;
    CompteEpargne(Personne* holder, Personne* advisor, float amount, float interest, int id);
    ~CompteEpargne() = default;
    string toString();
    string getValues();
    string columns();
};
