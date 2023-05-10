#ifdef _WIN32
#include "./include/BDD.h"
#endif

template <class T>
BDD<T>::BDD(string name, string rqt_create, vector<string> column) {
    this->setName(name);
    this->setColumn(column);
    char* errorMsg = 0;
    int rc = 0;

    rc = sqlite3_open("BDD.db", &p_db);

    if (rc != SQLITE_OK)
        cerr << "BDD.db could not be opened : " << errorMsg << endl;
    else
        cout << "BDD.db opened." << endl;

    // arg1 = database
    // arg2 = requête à exécuter
    // arg3 = Fonction à appeler après l'exécution (0 pour pas d'appel)
    // arg4 = premier argument de la fonction, doit être à 0
    // arg5 = Variable qui stocke le message d'erreur (en cas d'erreur)
    rc = sqlite3_exec(getDb(), rqt_create.c_str(), 0, 0, &errorMsg);

    if (rc != SQLITE_OK)
        cerr << "Table could not be created : " << errorMsg << endl;
    else
        cout << name << " created." << endl;

    sqlite3_close(getDb());
    cout << "BDD.db closed." << endl;

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
void BDD<T>::add(T *temp){
    int rc(0);
    char* errorMsg = 0;
    stringstream ss;
    string s = "";
    vector<string> colomn = getColumns();

    for (int i = 1; i < colomn.size(); i++)
    {
        s += colomn[i-1] + ", ";
    }
    s += colomn[colomn.size()-1];

    ss << "INSERT INTO " << getName() << " (" << s << ") VALUES (" << temp << ")";

    cout << "---------" << typeid(T).name() << endl;

    rc = sqlite3_exec(getDb(), ss.str().c_str() , 0, 0, &errorMsg);

    if (rc != SQLITE_OK)
        cerr << "Could not insert into table : " << errorMsg << endl;
    else
        cout << "Insertion into " << getName() << " done." << endl;

}


template <class T>
int BDD<T>::size() {
    vector<string> col;
    stringstream ss;
    ss << "SELECT COUNT(ID) FROM " << getName() << ";";

    return sqlite3_exec(getDb(), ss.str().c_str(), 0, 0, 0);
    //return col;
}

template <class T>
T BDD<T>::operator[](int i) {
    int rc(0);
    char* errorMsg = 0;
    T res;
    string rqt;
    sqlite3_stmt* stmt;

    // Ouverture de la base de données
    rc = sqlite3_open("BDD.db", &getDb());
    if (rc != SQLITE_OK)
        cerr << "BDD.db could not be opened (operator) : " << errorMsg << endl;
    else
        cout << "BDD.db opened." << endl;

    // On récupère la ligne où l'ID est celui passé en argument
    rqt = "SELECT * FROM ? WHERE ID = ?;";

    // On prépare la requete
    if (sqlite3_prepare_v2(getDb(), rqt.c_str(), -1, &stmt, nullptr))
    {
        cout << "Error SQL statement." << endl;
    }

    // On bind le nom de la table et l'ID
    sqlite3_bind_text(stmt, 1, getName().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, i);

    rc = sqlite3_step(stmt);

    // On traite la ligne
    while (rc == SQLITE_ROW) {
        // sqlite3_column_int(stmt, 0)
        // sqlite3_column_text(stmt, 2)
        if (typeid(res).name() == "Personne"){
            return Personne(sqlite3_column_text(stmt, 1), sqlite3_column_text(stmt, 2), sqlite3_column_text(stmt, 3));
        }
        else if (typeid(res).name() == "Operation"){
            return Operation(sqlite3_column_text(stmt, 2), sqlite3_column_text(stmt, 3), (float)sqlite3_column_double(stmt, 4));
        }
        else // C'est un compte
        {
            switch (sqlite3_column_int(stmt, 1)){
            case 0: // En Ligne
                return CompteEnLigne(sqlite3_column_text(stmt, 2), sqlite3_column_text(stmt, 3), (float)sqlite3_column_double(stmt, 4));
            case 1: // Epargne
                return CompteEpargne(sqlite3_column_text(stmt, 2), sqlite3_column_text(stmt, 3), (float)sqlite3_column_double(stmt, 4), (float)sqlite3_column_double(stmt, 5));
            case 2: // Standard
                return CompteStandard(sqlite3_column_text(stmt, 2), sqlite3_column_text(stmt, 3), (float)sqlite3_column_double(stmt, 4));
            }
        }
    }

    // On finalise le statement
    sqlite3_reset(stmt);
    sqlite3_finalize(stmt);

    // Fermeture de la base de données
    sqlite3_close(getDb());

    return res;
}



// Getters
template <class T>
string BDD<T>::getName(){ return this->p_name; }

template <class T>
vector<string> BDD<T>::getColumns() { return this->p_column; }

template <class T>
sqlite3* BDD<T>::getDb() { return this->p_db; }


// Setters
template <class T>
void BDD<T>::setName(string name){ this->p_name = name; }

template <class T>
void BDD<T>::setColumn(vector<string> column){ this->p_column = column; }
