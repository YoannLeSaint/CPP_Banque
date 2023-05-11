#pragma once
#include <sstream>
#include <string>
#include <Personne.h>
#include "Compte.h"

using namespace std;

class CompteEnLigne : public Compte {

private:

public:
    CompteEnLigne() = default;
    CompteEnLigne(Personne* holder, Personne* advisor, float amount, int id);
    ~CompteEnLigne() = default;


    void inlineConsult();
    string toString();
    string getValues();
    string columns();
};