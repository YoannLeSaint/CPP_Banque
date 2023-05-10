#include <string>
#include <iostream>
//#include <sqlite3>
#include <Personne.h>
#include <Operation.h>

#include "Compte.h"

using namespace std;

class BDD {
private:
    //sqlite3* p_db;
    string p_name;

    BDD() = default;

    void setName(string name);
    int callback_function(void *inutil, int argc, char** argv, char** columns);

public:
    BDD(string name);

    ~BDD() = default;

    void display();
    void addPersonne(Personne *p);
    void addCompte(Compte *account);



};



