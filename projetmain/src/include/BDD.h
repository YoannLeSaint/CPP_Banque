#include <string>
#include <iostream>
#include <vector>
#include <Personne.h>
#include <Operation.h>
#include <sstream>

#ifdef _WIN32
#include <winsqlite/winsqlite3.h>
#else
#include <sqlite3.h>
#endif

#include "Compte.h"
#include "CompteEnLigne.h"
#include "CompteEpargne.h"
#include "CompteStandard.h"

using namespace std;

template <class T>
class BDD {
private:
    sqlite3* p_db;
    string p_name;
    vector<string> p_column;

    BDD() = default;

    void setName(string name);
    int callback_function(void *inutil, int argc, char** argv, char** columns);

public:
    // Tags
    struct tagPersonne{};
    struct tagCompte{};

    BDD(string name, string rqt_create);

    ~BDD() = default;

    string getName();
    sqlite3* getDb();

    void display();
    void add(string temp, string column);
    void del(int id);
    void updateId(string col, int newId, int oldId);
    vector<unique_ptr<T>> getAll(vector<unique_ptr<Personne>>* clientsList, vector<unique_ptr<Personne>>* advisorsList, tagPersonne);
    vector<unique_ptr<T>> getAll(vector<unique_ptr<Personne>>* clientsList, vector<unique_ptr<Personne>>* advisorsList, tagCompte);
    int size();
};

#ifndef _WIN32
#include "../BDD.inl"
#endif