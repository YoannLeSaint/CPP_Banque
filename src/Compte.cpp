#include "./include/Compte.h"


// Constructeurs
Compte::Compte(Personne* holder, Personne* advisor, float amount) {
    this->p_holder = *holder;
    this->p_advisor = *advisor;
    this->p_balance = amount;
}

// Destructeur
Compte::~Compte()
{
    for (int i = this->p_historic.size()-1; i >= 0; i--)
    {
        delete &this->p_historic[i];
    }
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

void Compte::addMovement(float sum)
{
    stringstream name, date;
    time_t now = time(0);

    name << "operation" << this->p_historic.size()+1;
    date << localtime(&now)->tm_mday << "/" << localtime(&now)->tm_mon+1 << "/" << localtime(&now)->tm_year+1900;
    date << " " << localtime(&now)->tm_hour << ":" << localtime(&now)->tm_min << ":" << localtime(&now)->tm_sec;
    Operation* ope = new Operation(date.str(), name.str(), sum);

    this->p_historic.push_back(*ope);
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
