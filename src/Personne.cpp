#include "./include/Personne.h"


Personne::Personne(string firstname, string lastname, string adress){
    this-> p_firstname = firstname;
    this-> p_lastname = lastname;
    this-> p_adress = adress;
}

Personne::Personne(){
    string firstname, lastname, adress;
    cout << "Enter firstname:\t";
    cin >> firstname;
    cout << endl;

    cout << "Enter lastname:\t";
    cin >> lastname;
    cout << endl;

    cout << "Enter adress:\t";
    cin >> adress;
    cout << endl;

    Personne(firstname, lastname, adress);
}

string Personne::getFirstname(){ return this-> p_firstname; }
string Personne::getLastname(){  return this-> p_lastname;  }
string Personne::getAdress(){    return this-> p_adress;    }

void Personne::setFirstname(string firstname){
    this-> p_firstname = firstname;
}
void Personne::setLastname(string lastname){
    this-> p_lastname = lastname;
}
void Personne::setAdress(string adress){
    this-> p_adress = adress;
}


string Personne::toString(){
    stringstream ss;
	ss << "-> " << getFirstname() << " " << getLastname() << " :" << endl;
    ss << "_t" << getAdress() << endl;
	return ss.str();
}