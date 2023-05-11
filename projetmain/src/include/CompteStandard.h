#pragma once
#include <sstream>
#include <Personne.h>
#include "Compte.h"

class CompteStandard : public Compte
{
private:
    //

protected:
    //

public:
    CompteStandard() = default;
    CompteStandard(Personne* holder, Personne* advisor, float amount, int id);
    ~CompteStandard() = default;

    string toString();
    string getValues();
    string columns();
};
