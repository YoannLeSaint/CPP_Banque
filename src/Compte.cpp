#include "./include/Compte.h"


// Constructeurs
Compte::Compte(Personne* holder, Personne* advisor, float amount) {
    this->p_holder = *holder;
    this->p_advisor = *advisor;
    this->p_balance = amount;

    cout << "Salut" << endl;
}

Compte::Compte() {
    cout << "yo" << endl;
}


// Destructeur
Compte::~Compte()
{
}

void Compte::deposit(float amount) {
    this->p_balance += amount;
}

void Compte::withdraw(float amount) {
    this->p_balance -= amount;
}

float Compte::ConsultBalance() {
    return this->p_balance;
}

vector<Operation> Compte::consultOperations() {
    return this->p_historic;
}

vector<Operation> Compte::consultDebit() {
    vector<Operation> res;

    for (Operation ope : this->p_historic)
    {
        if (ope.getSum() < 0)
            res.push_back(ope);
    }

    return res;
}

vector<Operation> Compte::consultCredit() {
    vector<Operation> res;

    for (Operation ope : this->p_historic)
    {
        if (ope.getSum() > 0)
            res.push_back(ope);
    }

    return res;
}

// Getters
Personne Compte::getHolder() {
    return this->p_holder;
}

Personne Compte::getAdvisor() {
    return this->p_advisor;
}

vector<Operation> Compte::getHistoric() {
    return this->p_historic;
}

float Compte::getBalance() {
    return this->p_balance;
}

// Setters
void Compte::setHolder(Personne* holder) {
    this->p_holder = *holder;
}

void Compte::setAdvisor(Personne* advisor) {
    this->p_advisor = *advisor;
}

void Compte::setHistoric(vector<Operation> historic) {
    this->p_historic = historic;
}

void Compte::setBalance(float balance) {
    this->p_balance = balance;
}
