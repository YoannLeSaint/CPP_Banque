#include "Personne.h"

Personne::Personne(string firstname, string lastname, string adress, int idClient, int idAdvisor){
    this->p_firstname = firstname;
    this->p_lastname = lastname;
    this->p_adress = adress;
    this->p_idClient = idClient;
    this->p_idAdvisor = idAdvisor;
}

Personne::Personne(int idClient, int idAdvisor){
    string firstname, lastname, adress;
    cout << "Enter firstname:\t";
    cin >> firstname;
    cout << endl;

    cout << "Enter lastname:\t\t";
    cin >> lastname;
    cout << endl;

    cout << "Enter adress:\t\t";
    cin.ignore();
    getline(cin, adress);
    cout << endl;

    *this = Personne(firstname, lastname, adress, idClient, idAdvisor);
}

string Personne::getFirstname(){ return this-> p_firstname; }
string Personne::getLastname(){  return this-> p_lastname;  }
string Personne::getAdress(){    return this-> p_adress;    }
int Personne::getIdClient(){     return this-> p_idClient;  }
int Personne::getIdAdvisor(){    return this-> p_idAdvisor; }

void Personne::setFirstname(string firstname){
    this-> p_firstname = firstname;
}
void Personne::setLastname(string lastname){
    this-> p_lastname = lastname;
}
void Personne::setAdress(string adress){
    this-> p_adress = adress;
}

void Personne::setIdClient(int idClient){
    this-> p_idClient = idClient;
}

void Personne::setIdAdvisor(int idAdvisor){
    this-> p_idAdvisor = idAdvisor;
}


string Personne::toString(){
    stringstream ss;
	ss << "-> " << getFirstname() << " " << getLastname() << " : " << getAdress();
	return ss.str();
}

string Personne::columns()
{
    string s = "'ID', 'Firstname', 'Lastname', 'Address'";
    return s;
}

string Personne::getValuesClient()
{
    stringstream ss;
    ss << getIdClient() << ", '" << getFirstname() << "', '" << getLastname() << "', '" << getAdress() << "'";
    return ss.str();
}

string Personne::getValuesAdvisor()
{
    stringstream ss;
    ss << getIdAdvisor() << ", '" << getFirstname() << "', '" << getLastname() << "', '" << getAdress() << "'";
    return ss.str();
}