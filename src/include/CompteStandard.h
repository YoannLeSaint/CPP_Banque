#pragma once
#include <sstream>
#include "Compte.h"
#include "Personne.h"

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
