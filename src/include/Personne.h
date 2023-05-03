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

public:
    Personne() = default;
    Personne(int nothing);
    Personne(string firstname, string lastname, string adress);

    ~Personne() = default;

    string getFirstname();
    string getLastname();
    string getAdress();

    void setFirstname(string firstname);
    void setLastname(string Lastname);
    void setAdress(string adress);

    string toString();
};