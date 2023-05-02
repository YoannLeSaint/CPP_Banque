#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "Personne.h"
#include "Operation.h"
using namespace std;

class Compte
{
private:
    Personne p_holder;
    Personne p_advisor;
    vector<Operation> p_historic;
    float p_balance;

protected:
    // Getters
    vector<Operation> getHistoric();
    float getBalance();

    // Setters
    void setHolder(Personne* holder);
    void setAdvisor(Personne* advisor);
    void setHistoric(vector<Operation> historic);
    void setBalance(float balance);

public:
    // Constructeurs
    Compte() = default;
    Compte(Personne* holder, Personne* advisor, float amount);

    // Destructeur
    ~Compte();

    // Getters
    Personne getHolder();
    Personne getAdvisor();

    // Méthodes
    void deposit(float amount);
    void withdraw(float amount);
    float ConsultBalance();
    vector<Operation> consultOperations();
    vector<Operation> consultDebit();
    vector<Operation> consultCredit();
};