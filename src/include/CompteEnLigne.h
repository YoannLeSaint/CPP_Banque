#pragma once

#include "Compte.h"
#include "Personne.h"

using namespace std;

class CompteEnLigne : public Compte {

private:

public:
    CompteEnLigne() = default;
    CompteEnLigne(Personne* holder, Personne* advisor, float amount);
    ~CompteEnLigne();


    void inlineConsult();
};