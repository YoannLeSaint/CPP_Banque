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

    if (rc != SQLITE_OK) cerr << "Table could not be printed : " << errorMsg << endl;
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
int BDD<T>::size() {
    vector<string> col;
    stringstream ss;
    ss << "SELECT COUNT(ID) FROM " << getName() << ";";

    return sqlite3_exec(getDb(), ss.str().c_str(), 0, 0, 0);
}

template <class T>
int BDD<T>::lastId() {
    vector<string> col;
    stringstream ss;
    ss << "SELECT ID FROM " << getName() << "ORDER BY ID DESC LIMIT 1;";

    return sqlite3_exec(getDb(), ss.str().c_str(), 0, 0, 0);
}

// Getters
template <class T>
string BDD<T>::getName(){ return this->p_name; }

template <class T>
sqlite3* BDD<T>::getDb() { return this->p_db; }


// Setters
template <class T>
void BDD<T>::setName(string name){ this->p_name = name; }

