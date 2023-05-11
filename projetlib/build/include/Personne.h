#pragma once

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Personne{

private:
    string p_firstname;
    string p_lastname;
    string p_adress;
    int p_idClient;
    int p_idAdvisor;

public:
    Personne() = default;
    Personne(int idClient, int idAdvisor);
    Personne(string firstname, string lastname, string adress, int idClient, int idAdvisor);

    ~Personne() = default;

    string getFirstname();
    string getLastname();
    string getAdress();
    int getIdClient();
    int getIdAdvisor();

    void setFirstname(string firstname);
    void setLastname(string Lastname);
    void setAdress(string adress);
    void setIdClient(int idClient);
    void setIdAdvisor(int idAdvisor);

    string toString();
    string columns();
    string getValuesClient();
    string getValuesAdvisor();
};