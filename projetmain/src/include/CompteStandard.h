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
    CompteStandard(Personne* holder, Personne* advisor, float amount);
    ~CompteStandard() = default;

    string toString();
};
