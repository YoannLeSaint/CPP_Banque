#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <typeinfo>

#include "./include/Compte.h"
#include "./include/CompteEnLigne.h"
#include "./include/CompteEpargne.h"
#include "./include/CompteStandard.h"
#include "./include/Operation.h"
#include "./include/Personne.h"

using namespace std;


int displayVector(vector<Personne> *vect, string nameVect){
    int index = 0;
    cout << nameVect << endl;
    if (vect->size() == 0){
        cout << "No " << nameVect << " data." << endl << endl;
    } else {
        for (int i = 0; i < vect->size(); i++){
            cout << "+ " << i+1 << "\t" << vect->at(i).toString() << endl;
        }
        cout << "> ";
        cin >> index;
    }
    return index - 1;
}


void add(vector<Personne> *clientsList,
         vector<Personne> *advisorsList,
         vector<Compte>   *accountsList)
{
    char anwserADD;
    while (true){
        cout << "Which add do you want ?" << endl;
        cout <<  "\ta)Client\n\tb)Adviser\n\tc)Account\n\td)Back to main Menu" << endl;
        cin >> anwserADD;
        switch (anwserADD){
        case 'a':
            {
            Personne *pClient = new Personne();
            clientsList->push_back(*pClient);
            return;
            }
        case 'b':
            {
            Personne* pAdviser = new Personne();
            advisorsList->push_back(*pAdviser);
            return;
            }
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
                        indexClient = displayVector(clientsList, "advisor");
                        if (indexAdvisor != -1 && indexAdvisor != -1)
                        {
                            cout << "Client amount :";
                            cin >> amount;
                            cout << endl;
                            CompteEnLigne *inlineAcc = new CompteEnLigne(&clientsList->at(indexClient), &advisorsList->at(indexAdvisor), amount);
                            accountsList->push_back(*inlineAcc);
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
                            cout << "Client amount :";
                            cin >> amount;
                            cout << endl;
                            CompteStandard *standardAcc = new CompteStandard(&clientsList->at(indexClient), &advisorsList->at(indexAdvisor), amount);
                            accountsList->push_back(*standardAcc);
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
                            cout << "Client amount :";
                            cin >> amount;
                            cout << endl;
                            cout << "Interest :";
                            cin >> interest;
                            cout << endl;
                            CompteEpargne *savingAcc = new CompteEpargne(&clientsList->at(indexClient), &advisorsList->at(indexAdvisor), amount, interest);
                            accountsList->push_back(*savingAcc);
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
            break;
        }
    }
}

string printPersonne(Personne list){
    return list.toString();
}

string printCompte(Compte list){
    stringstream ss;
	ss << list.getHolder().toString() << " (" << typeid(list).name() << ") - " << list.ConsultBalance() << "EUR" << endl;
	return ss.str();
}

void del(vector<Personne>* clientsList, vector<Personne>* advisorsList, vector<Compte>* accountsList){
    char answerDel;
    int x(0);
    while(true){
        cout << "What do you want to delete ?" << endl;
        cout << "\ta)Client\n\tb)Adviser\n\tc)Account\n\td)Back to main menu" << endl;
        cout << ">";
        cin >> answerDel;

        switch(answerDel){
            case 'a' :
                if (clientsList->size() == 0){
                    cout << "Empty clients list. Back to menu." << endl;
                    break;
                } else {
                    for (long unsigned int i = 0; i < clientsList->size(); i++)
                    {
                        cout << i << ") " << printPersonne(clientsList->at(i));
                    }
                    cout << "Please select the number of the client you want to delete : " << endl;
                    cout << ">";
                    cin >> x;
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
                        cout << i << ") " << printPersonne(advisorsList->at(i));
                    }
                    cout << "Please select the number of the advisor you want to delete : " << endl;
                    cout << ">";
                    cin >> x;
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
                        cout << i << ") " << printCompte(accountsList->at(i));
                    }
                    cout << "Please select the number of the account you want to delete : " << endl;
                    cout << ">";
                    cin >> x;
                    accountsList->erase(accountsList->begin()+x);
                    return;
                }
            case 'd' :
                cout << "Back to main menu." << endl;
                return;
            default :
                cout << "Invalid command, please try again.";
                break;
        }
    }
}

int choiceByHolder(vector<Compte>* accountsList, vector<Personne>* clientsList)
{
    int personChoice = -1;
    int accountChoice = -1;

    while (personChoice < 0 || personChoice >= clientsList->size())
    {
        cout << "What is the name of the holder?" << endl;
        for (long unsigned int i = 0; i < clientsList->size(); i++)
        {
            cout << i << ") " << clientsList->at(i).getFirstname() + " " + clientsList->at(i).getLastname() << endl;
        }
        cin >> personChoice;
    }

    while (accountChoice < 0 || accountChoice >= accountsList->size())
    {
        cout << "Accounts of the holder :" << endl;

        for (long unsigned int i = 0; i < accountsList->size(); i++)
        {
            if (accountsList->at(i).getHolder().getFirstname() == clientsList->at(personChoice).getFirstname()
            && accountsList->at(i).getHolder().getLastname() == clientsList->at(personChoice).getLastname())
            {
                cout << i << ") " << typeid(accountsList->at(i)).name() << " : " << accountsList->at(i).ConsultBalance() << endl;
            }
        }
        cin >> accountChoice;
    }

    return accountChoice;
}

int choiceByAdvisor(vector<Compte>* accountsList, vector<Personne>* advisorsList)
{
    int personChoice = -1;
    int accountChoice = -1;

    while (personChoice < 0 || personChoice >= advisorsList->size())
    {
        cout << "What is the name of the holder?" << endl;
        for (long unsigned int i = 0; i < advisorsList->size(); i++)
        {
            cout << i << ") " << advisorsList->at(i).getFirstname() + " " + advisorsList->at(i).getLastname() << endl;
        }
        cin >> personChoice;
    }

    while (accountChoice < 0 || accountChoice >= accountsList->size())
    {
        cout << "Accounts of the holder :" << endl;

        for (long unsigned int i = 0; i < accountsList->size(); i++)
        {
            if (accountsList->at(i).getAdvisor().getFirstname() == advisorsList->at(personChoice).getFirstname()
            && accountsList->at(i).getAdvisor().getLastname() == advisorsList->at(personChoice).getLastname())
            {
                cout << i << ") " << typeid(accountsList->at(i)).name() << " : " << accountsList->at(i).ConsultBalance();
            }
        }
        cin >> accountChoice;
    }

    return accountChoice;
}

void interaction(Compte& account)
{
    int userChoice = 0;
    float amount = 0.;
    vector<Operation> listOpe;

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
            account.deposit(amount);
            break;

        case 2: // Withdraw money
            cout << "How much do you want to withdraw?" << endl;
            cout << "> ";
            cin >> amount;
            account.withdraw(amount);
            break;

        case 3: // Consult balance
            cout << "You have " << account.ConsultBalance() << " euros on this account." << endl;
            break;

        case 4: // Consult operations
            listOpe = account.consultOperations();

            for (Operation ope : listOpe)
            {
                cout << "* " << ope.toString() << endl;
            }
            break;

        case 5: // Consult debits
            listOpe = account.consultDebit();

            for (Operation ope : listOpe)
            {
                cout << "* " << ope.toString() << endl;
            }
            break;

        case 6: // Consults credits
            listOpe = account.consultCredit();

            for (Operation ope : listOpe)
            {
                cout << "* " << ope.toString() << endl;
            }
            break;

        default:
            cout << "Invalid command. Please try again." << endl;
            break;
        }
    }
}

void interact(vector<Compte>* accountsList, vector<Personne>* clientsList, vector<Personne>* advisorsList) {
    int choice = 0;
    int accountNumber = 0;

    while (true)
    {
        cout << "How do you want to select the account to interact with?" << endl;
        cout << "0) None. I want to quit." << endl;
        cout << "1) By Holder." << endl;
        cout << "2) By Advisor." << endl;
        cout << ">";
        cin >> choice;

        switch (choice)
        {
        case 0:
            return;

        case 1:
            accountNumber = choiceByHolder(accountsList, clientsList);
            interaction(accountsList->at(accountNumber));
            return;

        case 2:
            accountNumber = choiceByAdvisor(accountsList, advisorsList);
            interaction(accountsList->at(accountNumber));
            return;

        default:
            cout << "Not a valid option. Please try again." << endl;
            break;
        }
    }
}

int main() {

    // Vecteurs clients, conseillers, comptes
    vector<Personne> clientsList;
    vector<Personne> advisorsList;
    vector<Compte> accountsList;
    int answer(0);

    while(true) {
        cout << "What do you want to do?" << endl;
        cout << "0) Quit." << endl;
        cout << "1) Add." << endl;
        cout << "2) Delete." << endl;
        cout << "3) Interact with an account." << endl;
        cout << "> ";
        cin >> answer;

        switch (answer){
        case 0:
            cout << "Good bye!" << endl;
            return 0;
        case 1:
            add(&clientsList, &advisorsList, &accountsList);
            break;
        case 2:
            del(&clientsList, &advisorsList, &accountsList);
            break;
        case 3:
            interact(&accountsList, &clientsList, &advisorsList);
            break;
        default:
            cout << "Not a defined option. Please try again." << endl;
            break;
        }
    }

    return 0;
}