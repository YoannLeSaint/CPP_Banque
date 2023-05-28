#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <chrono>
#include <typeinfo>
#include <thread>
#include <Personne.h>
#include <Operation.h>
#include "RecurrentOperation.h"
using namespace std;

class Compte
{
private:
    Personne* p_holder;
    Personne* p_advisor;
    vector<Operation*> p_historic;
    vector<RecurrentOperation> p_recurrentOperations;
    float p_balance;
    int p_id;

protected:
    // Constructeurs
    Compte() = default;
    Compte(Personne* holder, Personne* advisor, float amount, int id);

    // Getters
    vector<Operation*> getHistoric();
    float getBalance();

    // Setters
    void setHolder(Personne* holder);
    void setHistoric(vector<Operation*> historic);
    void setBalance(float balance);
    void setRecurrentOperations(vector<RecurrentOperation> recurrentOperations);
    void setId(int id);

public:
    // Destructeur
    ~Compte() = default;

    // Getters
    Personne* getHolder();
    Personne* getAdvisor();
    vector<RecurrentOperation>* getRecurrentOperations();
    int getId();

    // Setters
    void setAdvisor(Personne* advisor);

    // Méthodes
    void deposit(float amount);
    void withdraw(float amount);
    float ConsultBalance();
    vector<Operation*> consultOperations();
    vector<Operation*> consultDebit();
    vector<Operation*> consultCredit();
    void addMovement(float sum);
    virtual string toString() = 0;
    virtual string getValues() = 0;
    virtual string columns() = 0;
    void executeRecurrence(RecurrentOperation* ope);
    void addRecurrentOperation();
};