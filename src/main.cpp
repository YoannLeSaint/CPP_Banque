#include <iostream>
#include <string>
#include <vector>

#include "./include/Compte.h"
#include "./include/CompteEnLigne.h"
#include "./include/CompteEpargne.h"
#include "./include/CompteStandard.h"
#include "./include/Operation.h"
#include "./include/Personne.h"

using namespace std;

int main(){
    vector<Personne> clientsList;
    vector<Personne> AdvisorsList;
    vector<Compte> accountsList;
    Personne* chose = new Personne();

    CompteStandard* truc = new CompteStandard(chose, chose, 1000.0);

    cout << "Hello World!" << endl;

    delete truc;
    return 0;
}