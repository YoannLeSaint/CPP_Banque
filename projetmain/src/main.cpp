#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <typeinfo>
#include <mutex>
#include <Personne.h>
#include <Operation.h>

#include "./include/Compte.h"
#include "./include/CompteEnLigne.h"
#include "./include/CompteEpargne.h"
#include "./include/CompteStandard.h"
#include "./include/BDD.h"

using namespace std;

//BDD
template<class T>
void addBDD(BDD<T> *tableName, string info, string columns){
    tableName->add(info, columns);
}

template<class T>
void suppBDD(BDD<T> *tableName, int id){
    tableName->del(id);
}


int displayVector(vector<unique_ptr<Personne>> *vect, string nameVect){
    int index = 0;

    if (vect->size() == 0){
        cout << "No " << nameVect << " data." << endl << endl;
    } else {
        for (long long unsigned int i = 0; i < vect->size(); i++){
            cout << "# " << i+1 << "\t" << vect->at(i).get()->toString() << endl;
        }
        cout << "> ";
        cin >> index;
    }
    return index - 1;
}

void displayAccount(vector<unique_ptr<Compte>> *acc){
    if (acc->size() == 0){
        cout << "No account." << endl << endl;
    } else {
        for (long long unsigned int i = 0; i < acc->size(); i++){
            cout << "+ " << i+1 << " " << acc->at(i).get()->toString() << endl;
        }
    }

    this_thread::sleep_for(5s);
}

void add(vector<unique_ptr<Personne>> *clientsList,
         vector<unique_ptr<Personne>> *advisorsList,
         vector<unique_ptr<Compte>>  *accountsList,
         BDD<Personne> *tableClients,
         BDD<Personne> *tableAdvisors,
         BDD<Compte> *tableAccounts,
         int* idClient,
         int* idAdvisor,
         int* idAccounts)
{
    char anwserADD;
    while (true){
        //loading();

        cout << "Which add do you want ?" << endl;
        cout <<  "\ta)Client\n\tb)Adviser\n\tc)Account\n\td)Back to main Menu" << endl;
        cout << "> ";
        cin >> anwserADD;
        switch (anwserADD){
        case 'a':
            {
            unique_ptr<Personne> pClient = make_unique<Personne>(*idClient, *idAdvisor);
            *idClient+=1;
            addBDD(tableClients, pClient->getValuesClient(), pClient->columns());
            clientsList->push_back(move(pClient));
            }
            break;
        case 'b':
            {
            unique_ptr<Personne> pAdviser = make_unique<Personne>(*idAdvisor, *idAdvisor);
            *idAdvisor+=1;
            addBDD(tableAdvisors, pAdviser->getValuesClient(), pAdviser->columns());
            advisorsList->push_back(move(pAdviser));
            }
            break;
        case 'c':
            int anwserCompte;
            while (true){
                int indexClient, indexAdvisor;
                float amount, interest;
                cout << "1) Inline account" << endl;
                cout << "2) Classic account" << endl;
                cout << "3) Saving account" << endl;
                cout << "4) Back to previous menu" << endl;
                cout << "> ";
                cin >> anwserCompte;

                switch (anwserCompte){
                    case 1:
                    {
                        // inline acount
                        cout << "Select your advisor" << endl;
                        indexAdvisor = displayVector(advisorsList, "advisor");
                        cout << "Select your client" << endl;
                        indexClient = displayVector(clientsList, "client");
                        if (indexAdvisor != -1 && indexAdvisor != -1)
                        {
                            cout << "Client amount : ";
                            cin >> amount;
                            cout << endl;
                            unique_ptr<Compte> inlineAcc = make_unique<CompteEnLigne>(clientsList->at(indexClient).get(), advisorsList->at(indexAdvisor).get(), amount, *idAccounts);
                            *idAccounts+=1;
                            addBDD(tableAccounts, inlineAcc->getValues(), inlineAcc->columns());
                            accountsList->push_back(move(inlineAcc));
                        }
                        return;
                    }
                    case 2:
                    {
                        // Classic account
                        cout << "Select your advisor" << endl;
                        indexAdvisor = displayVector(advisorsList, "advisor");
                        cout << "Select your client" << endl;
                        indexClient = displayVector(clientsList, "advisor");
                        if (indexAdvisor != -1 && indexAdvisor != -1)
                        {
                            cout << "Client amount : ";
                            cin >> amount;
                            cout << endl;
                            unique_ptr<Compte> standardAcc = make_unique<CompteStandard>(clientsList->at(indexClient).get(), advisorsList->at(indexAdvisor).get(), amount, *idAccounts);
                            *idAccounts+=1;
                            addBDD(tableAccounts, standardAcc->getValues(), standardAcc->columns());
                            accountsList->push_back(move(standardAcc));
                        }
                        return;
                    }
                    case 3:
                    {
                        // Saving account
                        cout << "Select your advisor" << endl;
                        indexAdvisor = displayVector(advisorsList, "advisor");
                        cout << "Select your client" << endl;
                        indexClient = displayVector(clientsList, "advisor");
                        if (indexAdvisor != -1 && indexAdvisor != -1)
                        {
                            cout << "Client amount : ";
                            cin >> amount;
                            cout << endl;
                            cout << "Interest : ";
                            cin >> interest;
                            cout << endl;
                            unique_ptr<Compte> savingAcc = make_unique<CompteEpargne>(clientsList->at(indexClient).get(), advisorsList->at(indexAdvisor).get(), amount, interest, *idAccounts);
                            *idAccounts+=1;
                            addBDD(tableAccounts, savingAcc->getValues(), savingAcc->columns());
                            accountsList->push_back(move(savingAcc));
                        }
                        return;
                    }
                    case 4:
                        return;
                    default:
                        cout << "Invalid account type, try again" << endl;
                        break;
                }
            }
            break;
        case 'd':
            return;
        default:
            cout << "Invalid command, try again" << endl;
            this_thread::sleep_for(3s);
            break;
        }
    }
}

void del(vector<unique_ptr<Personne>>* clientsList,
         vector<unique_ptr<Personne>>* advisorsList,
         vector<unique_ptr<Compte>>* accountsList,
         BDD<Personne> *tableClients,
         BDD<Personne> *tableAdvisors,
         BDD<Compte> *tableAccounts)
{
    char answerDel;
    int x(0);
    while(true){
        cout << "What do you want to delete ?" << endl;
        cout << "\ta)Client\n\tb)Advisor\n\tc)Account\n\td)Back to main menu" << endl;
        cout << "> ";
        cin >> answerDel;

        switch(answerDel){
            case 'a' :
                if (clientsList->size() == 0){
                    cout << "Empty clients list. Back to menu." << endl;
                    break;
                } else {
                    for (long unsigned int i = 0; i < clientsList->size(); i++)
                    {
                        cout << i << ") " << clientsList->at(i).get()->toString() << endl;
                    }
                    cout << "Please select the number of the client you want to delete : " << endl;
                    cout << "> ";
                    cin >> x;

                    for (long int i = accountsList->size() - 1; i >= 0; i--)
                    {
                        if (accountsList->at(i).get()->getHolder()->toString() == clientsList->at(x).get()->toString())
                        {
                            suppBDD(tableAccounts, accountsList->at(i)->getId());
                            accountsList->erase(accountsList->begin()+i);
                        }
                    }
                    suppBDD(tableClients, clientsList->at(x)->getIdClient());
                    clientsList->erase(clientsList->begin()+x);

                    return;
                }
            case 'b' :
                if (advisorsList->size() == 0){
                    cout << "Empty advisors list. Back to menu." << endl;
                    break;
                } else {
                    for (long unsigned int i = 0; i < advisorsList->size(); i++)
                    {
                        cout << i << ") " << advisorsList->at(i).get()->toString() << endl;
                    }

                    cout << "Please select the number of the advisor you want to delete : " << endl;
                    cout << "> ";
                    cin >> x;

                    for (long unsigned int i = 0; i < accountsList->size(); i++)
                    {
                        int adv = 0;
                        if (accountsList->at(i).get()->getAdvisor()->toString() == advisorsList->at(x).get()->toString()){
                            cout << "Please select a new advisor for the following account : " << endl;
                            cout << accountsList->at(i).get()->toString() << endl;

                            for (long unsigned int j = 0; j < advisorsList->size(); j++)
                            {
                                if (advisorsList->at(j).get()->toString() != advisorsList->at(x).get()->toString())
                                    cout << j << ") " << advisorsList->at(j).get()->toString();
                            }
                            cout << endl << "> ";
                            cin >> adv;
                            accountsList->at(i).get()->setAdvisor(advisorsList->at(adv).get());
                        }
                    }
                    suppBDD(tableAdvisors, advisorsList->at(x)->getIdAdvisor());
                    advisorsList->erase(advisorsList->begin()+x);
                    return;
                }
            case 'c' :
                if (accountsList->size() == 0){
                    cout << "Empty accounts list. Back to menu." << endl;
                    break;
                } else {
                    for (long unsigned int i = 0; i < accountsList->size(); i++)
                    {
                        cout << i << ") " << accountsList->at(i).get()->toString();
                    }
                    cout << "Please select the number of the account you want to delete : " << endl;
                    cout << "> ";
                    cin >> x;
                    suppBDD(tableAccounts, accountsList->at(x)->getId());
                    accountsList->erase(accountsList->begin()+x);
                    return;
                }
            case 'd' :
                cout << "Back to main menu." << endl;
                return;
            default :
                cout << "Invalid command, please try again.";
                this_thread::sleep_for(3s);
                break;
        }
    }
}

int choiceByHolder(vector<unique_ptr<Compte>>* accountsList,
                   vector<unique_ptr<Personne>>* clientsList)
{
    long long unsigned int personChoice = -1;
    long long unsigned int accountChoice = -1;

    while (personChoice < 0 || personChoice >= clientsList->size())
    {
        cout << "What is the name of the holder?" << endl;
        for (long unsigned int i = 0; i < clientsList->size(); i++)
        {
            cout << i << ") " << clientsList->at(i).get()->getFirstname() + " " + clientsList->at(i).get()->getLastname() << endl;
        }
        cout << "> ";
        cin >> personChoice;
    }

    while (accountChoice < 0 || accountChoice >= accountsList->size())
    {
        cout << "Accounts of the holder :" << endl;

        for (long unsigned int i = 0; i < accountsList->size(); i++)
        {
            if (accountsList->at(i).get()->getHolder()->getFirstname() == clientsList->at(personChoice).get()->getFirstname()
            && accountsList->at(i).get()->getHolder()->getLastname() == clientsList->at(personChoice).get()->getLastname())
            {
                cout << i << ") " << accountsList->at(i).get()->toString() << endl;
            }
        }
        cout << "> ";
        cin >> accountChoice;
    }

    return accountChoice;
}

int choiceByAdvisor(vector<unique_ptr<Compte>>* accountsList,
                    vector<unique_ptr<Personne>>* advisorsList)
{
    long long unsigned int personChoice = -1;
    long long unsigned int accountChoice = -1;

    while (personChoice < 0 || personChoice >= advisorsList->size())
    {
        cout << "What is the name of the advisor?" << endl;
        for (long unsigned int i = 0; i < advisorsList->size(); i++)
        {
            cout << i << ") " << advisorsList->at(i).get()->getFirstname() + " " + advisorsList->at(i).get()->getLastname() << endl;
        }
        cout << "> ";
        cin >> personChoice;
    }

    while (accountChoice < 0 || accountChoice >= accountsList->size())
    {
        cout << "Accounts managed by the advisor :" << endl;

        for (long unsigned int i = 0; i < accountsList->size(); i++)
        {
            if (accountsList->at(i).get()->getAdvisor()->getFirstname() == advisorsList->at(personChoice).get()->getFirstname()
            && accountsList->at(i).get()->getAdvisor()->getLastname() == advisorsList->at(personChoice).get()->getLastname())
            {
                cout << i << ") " << accountsList->at(i).get()->toString() << endl;
            }
        }
        cout << "> ";
        cin >> accountChoice;
    }

    return accountChoice;
}

void interaction(Compte* account, vector<thread>* threadsList)
{
    int userChoice = 0;
    float amount = 0.;
    vector<Operation*> listOpe;
    int opeChoice = 0;

    while(true)
    {
        cout << "What do you want to do with this account ?" << endl;
        cout << "0) Back to main menu." << endl;
        cout << "1) Deposit money." << endl;
        cout << "2) Withdraw money." << endl;
        cout << "3) Consult balance." << endl;
        cout << "4) Consult operations." << endl;
        cout << "5) Consult debits." << endl;
        cout << "6) Consult credits." << endl;
        cout << "7) Create a new recurrent operation." << endl;
        cout << "8) Disable a recurrent operation." << endl;
        cout << "9) Display list of recurrent operations." << endl;
        cout << "> ";
        cin >> userChoice;

        switch (userChoice)
        {
        case 0:
            return;

        case 1: // Deposit money
            cout << "How much do you want to deposit?" << endl;
            cout << "> ";
            cin >> amount;
            account->addMovement(amount);
            account->deposit(amount);
            break;

        case 2: // Withdraw money
            cout << "How much do you want to withdraw?" << endl;
            cout << "> ";
            cin >> amount;
            account->addMovement(amount*-1);
            account->withdraw(amount);
            break;

        case 3: // Consult balance
            cout << "You have " << account->ConsultBalance() << " euros on this account." << endl;
            this_thread::sleep_for(3s);
            break;

        case 4: // Consult operations
            listOpe = account->consultOperations();

            for (Operation* ope : listOpe)
            {
                cout << "\t* " << ope->toString() << endl;
            }
            this_thread::sleep_for(3s);
            break;

        case 5: // Consult debits
            listOpe = account->consultDebit();

            for (Operation* ope : listOpe)
            {
                cout << "\t* " << ope->toString() << endl;
            }
            this_thread::sleep_for(3s);
            break;

        case 6: // Consults credits
            listOpe = account->consultCredit();

            for (Operation* ope : listOpe)
            {
                cout << "\t* " << ope->toString() << endl;
            }
            this_thread::sleep_for(3s);
            break;

        case 7: // Create a new recurrent operation
        {
            account->addRecurrentOperation();

            thread execOpe = thread(&Compte::executeRecurrence, account, &account->getRecurrentOperations()->back());
            threadsList->push_back(move(execOpe));
            break;
        }

        case 8: // Disable a recurrent operation
            for (size_t i = 0; i < account->getRecurrentOperations()->size(); i++)
            {
                cout << i << ") " << account->getRecurrentOperations()->at(i).toString() << endl;
            }
            cout << "Choose the number of the operation you want to disable :" << endl;
            cout << "> ";
            cin >> opeChoice;

            account->getRecurrentOperations()->at(opeChoice).setActive(false);
            break;

        case 9: // Display list of recurrent operations
            for (size_t i = 0; i < account->getRecurrentOperations()->size(); i++)
            {
                cout << "\t* " << account->getRecurrentOperations()->at(i).toString() << endl;
            }
            break;

        default:
            cout << "Invalid command. Please try again." << endl;
            this_thread::sleep_for(3s);
            break;
        }
    }
}

void interact(vector<unique_ptr<Compte>>* accountsList,
              vector<unique_ptr<Personne>>* clientsList,
              vector<unique_ptr<Personne>>* advisorsList,
              vector<thread>* threadsList)
{
    int choice = 0;
    int accountNumber = 0;

    while (true)
    {
        cout << "How do you want to select the account to interact with?" << endl;
        cout << "0) None. I want to quit." << endl;
        cout << "1) By Holder." << endl;
        cout << "2) By Advisor." << endl;
        cout << "> ";
        cin >> choice;

        switch (choice)
        {
        case 0:
            return;

        case 1:
            accountNumber = choiceByHolder(accountsList, clientsList);
            interaction(accountsList->at(accountNumber).get(), threadsList);
            return;

        case 2:
            accountNumber = choiceByAdvisor(accountsList, advisorsList);
            interaction(accountsList->at(accountNumber).get(), threadsList);
            return;

        default:
            cout << "Not a valid option. Please try again." << endl;
            break;
        }
    }
}


void holdup(vector<unique_ptr<Compte>>* accountsList)
{
    int total = 0;
    for(long unsigned int i = 0; i < accountsList->size(); i++)
    {
        int stolen = rand() % (int)(accountsList->at(i).get()->ConsultBalance());
        total += stolen;
        accountsList->at(i).get()->withdraw(stolen);
    }

    cout << "Ho no! Robbers stole " << total << " euros in the bank! Call the police!" << endl;
    this_thread::sleep_for(3s);
}



void initBDD(vector<unique_ptr<Personne>>* clientsList, vector<unique_ptr<Personne>>* advisorsList,
               vector<unique_ptr<Compte>>* accountsList, BDD<Personne> *tableClients, BDD<Personne> *tableAdvisors, BDD<Compte> *tableAccounts,
               int *idClients, int *idAdvisors, int *idAccounts)
{
    // On ajoute à la BDD nos clients, conseillers, comptes
    addBDD(tableClients, clientsList->at(0)->getValuesClient(), clientsList->at(0)->columns());
    addBDD(tableClients, clientsList->at(1)->getValuesClient(), clientsList->at(1)->columns());
    addBDD(tableClients, clientsList->at(2)->getValuesClient(), clientsList->at(2)->columns());

    addBDD(tableAdvisors, advisorsList->at(0)->getValuesAdvisor(), advisorsList->at(0)->columns());
    addBDD(tableAdvisors, advisorsList->at(1)->getValuesAdvisor(), advisorsList->at(1)->columns());

    addBDD(tableAccounts, accountsList->at(0)->getValues(), accountsList->at(0)->columns());
    addBDD(tableAccounts, accountsList->at(1)->getValues(), accountsList->at(1)->columns());
    addBDD(tableAccounts, accountsList->at(2)->getValues(), accountsList->at(2)->columns());
    addBDD(tableAccounts, accountsList->at(3)->getValues(), accountsList->at(3)->columns());
    addBDD(tableAccounts, accountsList->at(4)->getValues(), accountsList->at(4)->columns());

}

int main() {
    srand(time(NULL));
    int idClients(1);
    int idAdvisors(1);
    int idAccounts(1);
    string rqt_create;


    // Création de la table des clients
    rqt_create = "CREATE TABLE IF NOT EXISTS Client ("  \
                 "ID          INTEGER  PRIMARY KEY,"    \
                 "FirstName   TEXT     NOT NULL,"       \
                 "LastName    TEXT     NOT NULL,"       \
                 "Address     TEXT     NOT NULL);";
    BDD<Personne> *tableClients = new BDD<Personne>("Client", rqt_create);

    // Création de la table des conseillers
    rqt_create = "CREATE TABLE IF NOT EXISTS Advisor (" \
                 "ID          INTEGER  PRIMARY KEY,"    \
                 "FirstName   TEXT     NOT NULL,"       \
                 "LastName    TEXT     NOT NULL,"       \
                 "Address     TEXT     NOT NULL);";
    BDD<Personne>* tableAdvisors = new BDD<Personne>("Advisor", rqt_create);

    // Création de la table des comptes
    rqt_create = "CREATE TABLE IF NOT EXISTS Account (" \
                 "ID          INTEGER  PRIMARY KEY,"    \
                 "Type        INTEGER  NOT NULL,"       \
                 "HolderId    INTEGER  NOT NULL,"       \
                 "AdvisorId   INTEGER  NOT NULL,"       \
                 "Balance     FLOAT    NOT NULL,"       \
                 "Interest    FLOAT);";
    BDD<Compte>* tableAccounts = new BDD<Compte>("Account", rqt_create);

    // Vecteurs clients, conseillers, comptes
    vector<unique_ptr<Personne>> clientsList;
    vector<unique_ptr<Personne>> advisorsList;
    vector<unique_ptr<Compte>> accountsList;
    vector<thread> threadsList;
    int answer(0);
    bool start = true;

    //Création de nos premiers clients
    unique_ptr<Personne> p1 = make_unique<Personne>("Jean", "Todt", "ici", idClients, 0);
    clientsList.push_back(move(p1));
    idClients+=1;
    unique_ptr<Personne> p2 = make_unique<Personne>("Jean", "Todd", "la bas", idClients, 0);
    clientsList.push_back(move(p2));
    idClients+=1;
    unique_ptr<Personne> p3 = make_unique<Personne>("Marc", "Todt", "chez lui", idClients, 0);
    clientsList.push_back(move(p3));
    idClients+=1;

    //Création de nos premiers conseillers
    unique_ptr<Personne> p4 = make_unique<Personne>("Yoann", "Le Saint", "Nantes DC", 0, idAdvisors);
    idAdvisors+=1;
    unique_ptr<Personne> p5 = make_unique<Personne>("Charlotte", "Todt", "NY", 0, idAdvisors);
    idAdvisors+=1;
    advisorsList.push_back(move(p4));
    advisorsList.push_back(move(p5));

    //Création de nos premiers comptes
    unique_ptr<Compte> account1 = make_unique<CompteEnLigne>(clientsList.at(0).get(), advisorsList.at(1).get(), 500.f, idAccounts);
    idAccounts+=1;
    unique_ptr<Compte> account2 = make_unique<CompteEpargne>(clientsList.at(0).get(), advisorsList.at(1).get(), 3450.f, 3, idAccounts);
    idAccounts+=1;
    unique_ptr<Compte> account3 = make_unique<CompteStandard>(clientsList.at(1).get(), advisorsList.at(0).get(), 500.f, idAccounts);
    idAccounts+=1;
    unique_ptr<Compte> account4 = make_unique<CompteStandard>(clientsList.at(2).get(), advisorsList.at(0).get(), 10.f, idAccounts);
    idAccounts+=1;
    unique_ptr<Compte> account5 = make_unique<CompteStandard>(clientsList.at(2).get(), advisorsList.at(0).get(), 10000.f, idAccounts);
    idAccounts+=1;

    accountsList.push_back(move(account1));
    accountsList.push_back(move(account2));
    accountsList.push_back(move(account3));
    accountsList.push_back(move(account4));
    accountsList.push_back(move(account5));

    //idAccounts = tableAccounts->lastId() + 1;
    //cout << idAccounts << endl;

    while(true) {

        if (start)
        {
            cout << "Welcome to bank simulator (free demo version)" << endl << endl;
            start = false;
        }

        cout << "What do you want to do?" << endl;
        cout << "0) Quit." << endl;
        cout << "1) Add." << endl;
        cout << "2) Delete." << endl;
        cout << "3) Interact with an account." << endl;
        cout << "4) Display all accounts." << endl;
        cout << "5) Suffer a holdup." << endl;
        cout << "> ";
        cin >> answer;

        switch (answer){
        case 0:
            // On passe l'attribut p_activeThread de RecurrentOperation à false pour stopper tous les threads
            for (size_t i = 0; i < accountsList.size(); i++)
            {
                if (accountsList[i]->getRecurrentOperations()->size() > 0)
                {
                    accountsList[i]->getRecurrentOperations()->at(0).setActiveThread(false);
                    break;
                }
            }

            // On s'assure que tous les threads sont terminés avant de quitter
            for (size_t i = 0; i < threadsList.size(); i++)
            {
                if (threadsList.at(i).joinable()){
                    threadsList.at(i).join();
                }
            }

            delete(tableClients);
            delete(tableAdvisors);
            delete(tableAccounts);
            cout << "Good bye!" << endl;
            return 0;
        case 1:
            add(&clientsList, &advisorsList, &accountsList, tableClients, tableAdvisors, tableAccounts, &idClients, &idAdvisors, &idAccounts);
            break;
        case 2:
            del(&clientsList, &advisorsList, &accountsList, tableClients, tableAdvisors, tableAccounts);
            break;
        case 3:
            interact(&accountsList, &clientsList, &advisorsList, &threadsList);
            break;
        case 4:
            displayAccount(&accountsList);
            break;
        case 5:
            holdup(&accountsList);
            break;
        case 6:
            initBDD(&clientsList, &advisorsList, &accountsList, tableClients, tableAdvisors, tableAccounts, &idClients, &idAdvisors, &idAccounts);
            break;
        default:
            cout << "Not a defined option. Please try again." << endl;
            break;
        }
    }

    return 0;
}
