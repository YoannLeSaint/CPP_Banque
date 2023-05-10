#include "./include/BDD.h"

BDD::BDD(string name, string rqt_create) {
    this->setName(name);
    char* errorMsg = 0
    //const char* rqt_create = (const char*)"CREATE TABLE truc IF NOT EXISTS  (" \
    //       "nom TEXT NOT NULL," \
    //       "description TEXT NOT NULL);";

    // 1er 0  -> premier argument du callback
    // 2eme 0 -> erreur
rqt_create    rc = sqlite3_exec(p_db, , rt00, 0, &errorMsg);

    if (rc != SQLITE_OK) {
        // Error handling
        cerr << "Erreur a l'execution de la BDD : " << errorMsg << endl;
    }
    else cout << "Table bien creee." << endl;

}

int BDD::callback_function(void *inutil, int argc, char** argv, char** columns){
    cout << endl;
    for (int i=0; i<argc; i++){
        cout << columns[i] << " ->\t" << argv[i] << endl;
    }
    return 0;
}

void BDD::display()
{
    jh
}

void BDD::addPersonne(Personne *p){
    
}

void BDD::addCompte(Compte *account)
{
    
}


// Getters


// Setters
void BDD::setName(string name)
{
    this->p_name = name;
}