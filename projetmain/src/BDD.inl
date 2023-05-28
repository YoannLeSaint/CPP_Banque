#ifdef _WIN32
#include "./include/BDD.h"
#endif

template <class T>
BDD<T>::BDD(string name, string rqt_create) {
    this->setName(name);
    char* errorMsg = 0;
    int rc = 0;

    rc = sqlite3_open("BDD.db", &p_db);

    if (rc != SQLITE_OK)
        cerr << "BDD.db could not be opened : " << errorMsg << endl;

    rc = sqlite3_exec(getDb(), rqt_create.c_str(), 0, 0, &errorMsg);

    if (rc != SQLITE_OK)
        cerr << "Table could not be created : " << errorMsg << endl;

    sqlite3_close(getDb());
}

template <class T>
int BDD<T>::callback_function(void *inutil, int argc, char** argv, char** columns){
    cout << endl;
    for (int i=0; i<argc; i++){
        cout << columns[i] << " ->\t" << argv[i] << endl;
    }
    return 0;
}

template <class T>
void BDD<T>::display(){
    char* errorMsg = 0;
    int rc(0);

    rc = sqlite3_exec(getDb(), "SELECT * FROM " + getName(), callback_function, 0, &errorMsg);

    if (rc != SQLITE_OK)
        cerr << "Table could not be printed : " << errorMsg << endl;
}

template <class T>
void BDD<T>::add(string temp, string column){
    int rc(0);
    char* errorMsg = 0;
    stringstream ss;

    rc = sqlite3_open("BDD.db", &p_db);

    if (rc != SQLITE_OK)
        cerr << "BDD.db could not be opened : " << errorMsg << endl;

    ss << "INSERT INTO " << getName() << " (" << column << ") VALUES (" << temp << ")";

    rc = sqlite3_exec(getDb(), ss.str().c_str() , 0, 0, &errorMsg);

    if (rc != SQLITE_OK)
        cerr << "Could not insert into table : " << errorMsg << endl;

    sqlite3_close(getDb());

}

template<class T>
void BDD<T>::del(int id){
    char* errorMsg = 0;
    stringstream ss;
    int rc = 0;
    string rqt_create;

    rc = sqlite3_open("BDD.db", &p_db);

    if (rc != SQLITE_OK)
        cerr << "BDD.db could not be opened : " << errorMsg << endl;

    ss << "DELETE FROM " << getName() << " WHERE ROWID = " << id;

    rqt_create = ss.str();

    rc = sqlite3_exec(getDb(), rqt_create.c_str(), 0, 0, &errorMsg);

    if (rc != SQLITE_OK)
        cerr << "Could not delete from table : " << errorMsg << endl;

    sqlite3_close(getDb());
}

template <class T>
void BDD<T>::updateId(string col, int newId, int oldId){
    char* errorMsg = 0;
    stringstream ss;
    int rc = 0;
    string rqt_create;

    rc = sqlite3_open("BDD.db", &p_db);

    if (rc != SQLITE_OK)
        cerr << "BDD.db could not be opened : " << errorMsg << endl;

    ss << "UPDATE " << getName() << " SET " << col << " = " << newId << " WHERE " << col << " = " << oldId;

    rqt_create = ss.str();

    rc = sqlite3_exec(getDb(), rqt_create.c_str(), 0, 0, &errorMsg);

    if (rc != SQLITE_OK)
        cerr << "Could not update table : " << errorMsg << endl;

    sqlite3_close(getDb());
}

template <class T>
int BDD<T>::size() {
    //vector<string> col;
    stringstream ss;
    ss << "SELECT COUNT(ID) FROM " << getName() << ";";

    return sqlite3_exec(getDb(), ss.str().c_str(), 0, 0, 0);
}

template <class T>
vector<unique_ptr<T>> BDD<T>::getAll(vector<unique_ptr<Personne>>* clientsList,
                                     vector<unique_ptr<Personne>>* advisorsList,
                                     tagPersonne) {
    vector<unique_ptr<T>> res;
    sqlite3_stmt* stmt;
    stringstream ss;
    char* errorMsg = 0;
    int rc = 0;
    string rqt_getall;

    rc = sqlite3_open("BDD.db", &p_db);

    if (rc != SQLITE_OK)
        cerr << "BDD.db could not be opened : " << errorMsg << endl;

    ss << "SELECT * FROM " << getName();

    rqt_getall = ss.str();
    ss.str(std::string());

    if (sqlite3_prepare_v2(getDb(), rqt_getall.c_str(), -1, &stmt, nullptr))
        cerr << "SQL statement error" << endl;

    rc = sqlite3_step(stmt);

    while (rc == SQLITE_ROW)
    {
        if (getName() != "Account")
        {
            int id;
            string fname;
            string lname;
            string adress;

            id = sqlite3_column_int(stmt, 0);

            ss << sqlite3_column_text(stmt, 1);
            fname = ss.str();
            ss.str(std::string());

            ss << sqlite3_column_text(stmt, 2);
            lname = ss.str();
            ss.str(std::string());

            ss << sqlite3_column_text(stmt, 3);
            adress = ss.str();
            ss.str(std::string());

            if(getName() == "Client")
            {
                unique_ptr<T> personne1 = make_unique<Personne>(fname, lname, adress, id, 0);
                res.push_back(move(personne1));
            }
            else
            {
                unique_ptr<T> personne2 = make_unique<Personne>(fname, lname, adress, 0, id);
                res.push_back(move(personne2));
            }
        }

        rc = sqlite3_step(stmt);
    }

    sqlite3_reset(stmt);
    sqlite3_finalize(stmt);

    sqlite3_close(getDb());

    return res;
}

template <class T>
vector<unique_ptr<T>> BDD<T>::getAll(vector<unique_ptr<Personne>>* clientsList,
                                     vector<unique_ptr<Personne>>* advisorsList,
                                     tagCompte) {
    vector<unique_ptr<T>> res;
    sqlite3_stmt* stmt;
    stringstream ss;
    char* errorMsg = 0;
    int rc = 0;
    string rqt_getall;

    rc = sqlite3_open("BDD.db", &p_db);

    if (rc != SQLITE_OK)
        cerr << "BDD.db could not be opened : " << errorMsg << endl;

    ss << "SELECT * FROM " << getName();

    rqt_getall = ss.str();
    ss.str(std::string());

    if (sqlite3_prepare_v2(getDb(), rqt_getall.c_str(), -1, &stmt, nullptr))
        cerr << "SQL statement error" << endl;

    rc = sqlite3_step(stmt);

    while (rc == SQLITE_ROW)
    {
        if (getName() == "Account")
        {
            int id;
            string type;
            Personne* holder;
            Personne* advisor;
            float amount;
            float interest;
            int extId;

            id = sqlite3_column_int(stmt, 0);

            ss << sqlite3_column_text(stmt, 1);
            type = ss.str();
            ss.str(std::string());

            extId = sqlite3_column_int(stmt, 2) - 1;
            holder = clientsList->at(extId).get();

            extId = sqlite3_column_int(stmt, 3) - 1;
            advisor = advisorsList->at(extId).get();

            amount = sqlite3_column_int(stmt, 4);

            interest = sqlite3_column_int(stmt, 5);

            if (type == "Compte en Ligne")
            {
                unique_ptr<Compte> compte1 = make_unique<CompteEnLigne>(holder, advisor, amount, id);
                res.push_back(move(compte1));
            }
            else if (type == "Compte Epargne")
            {
                unique_ptr<Compte> compte2 = make_unique<CompteEpargne>(holder, advisor, amount, interest, id);
                res.push_back(move(compte2));
            }
            else if (type == "Compte Standard")
            {
                unique_ptr<Compte> compte3 = make_unique<CompteStandard>(holder, advisor, amount, id);
                res.push_back(move(compte3));
            }
        }

        rc = sqlite3_step(stmt);
    }

    sqlite3_reset(stmt);
    sqlite3_finalize(stmt);

    sqlite3_close(getDb());

    return res;
}

// Getters
template <class T>
string BDD<T>::getName(){ return this->p_name; }

template <class T>
sqlite3* BDD<T>::getDb() { return this->p_db; }

// Setters
template <class T>
void BDD<T>::setName(string name){ this->p_name = name; }

