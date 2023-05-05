#include "./include/RecurrentOperation.h"


RecurrentOperation::RecurrentOperation(string date, string name, float sum,
                                       chrono::seconds recurrence, bool active)
{
    this->setDate(date);
    this->setName(name);
    this->setSum(sum);
    this->p_recurrence = recurrence;
    this->p_active = active;
    this->p_count = 0;
    this->p_activeThread = true;
}

RecurrentOperation::RecurrentOperation(){
    string name;
    float sum;
    stringstream d;
    time_t now = time(0);
    int frequency = 1;

    d << localtime(&now)->tm_mday << "/" << localtime(&now)->tm_mon+1 << "/" << localtime(&now)->tm_year+1900;
    d << " " << localtime(&now)->tm_hour << ":" << localtime(&now)->tm_min << ":" << localtime(&now)->tm_sec;

    cout << "Enter your operation's name:" << endl;
    cout << "> ";
    cin >> name;

    cout << "Enter the operation's amount (EUR):" << endl;
    cout << "> ";
    cin >> sum;

    cout << "Choose the operation's frequency (seconds):" << endl;
    cout << "> ";
    cin >> frequency;

    *this = RecurrentOperation(d.str(), name, sum, (chrono::seconds) frequency, true);
}

string RecurrentOperation::toString(){
    stringstream ss;
    stringstream act;

    if (getActive() == false){
        act << "INACTIVE";
    } else {
        act << "ACTIVE -- frequency : " << getRecurrence().count() << " seconds";
    }

    ss << getName() << " (" << getDate() << ") : ";

    if (getSum() > 0){
        ss << "+";
    }

    ss << getSum() << "EUR | " << act.str() << endl;
    ss << "this operation has been executed " << getCount() << " times." << endl;

    return ss.str();
}

void RecurrentOperation::incrCount() {
    this->p_count++;
}

// Getters
chrono::seconds RecurrentOperation::getRecurrence(){ return this->p_recurrence; }
bool RecurrentOperation::getActive(){ return this->p_active; }
int RecurrentOperation::getCount(){ return this->p_count; }
bool RecurrentOperation::getActiveThread(){ return this->p_activeThread; }

// Setters
void RecurrentOperation::setReccurence(chrono::seconds recurrence){
    this-> p_recurrence = recurrence;
}

void RecurrentOperation::setActive(bool active){
    this-> p_active = active;
}

void RecurrentOperation::setCount(int count){
    this->p_count = count;
}

void RecurrentOperation::setActiveThread(bool active){
    this->p_activeThread = active;
}
