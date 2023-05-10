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
    void setColumn(vector<string> column);
    int callback_function(void *inutil, int argc, char** argv, char** columns);

public:
    BDD(string name, string rqt_create, vector<string> column);

    ~BDD() = default;

    string getName();
    vector<string> getColumns();
    sqlite3* getDb();

    void display();
    void add(T *temp);
    int size();

    T operator[](int i);

};

#ifndef _WIN32
#include "../BDD.inl"
#endif