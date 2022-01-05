#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

struct Train {
    string tripID, trainID;
    string departure, destination;
    int passenger;
    int departTime, arrivalTime, departDate, arrivalDate;
};

struct Node {
    Train info;
    Node *next;
};

Node *sp;

void init();
void push(Train x);
int pop(Train &x);
void input_train_info(Train &train);

int main()
{
    int choose;
    do {
        system("cls");
        cout << "1. Input Train Information\n"
            << "2. literally XIAO that fucking train\n"
            << "3. Quit\n"
            << "Choose: ";
        cin >> choose;
        switch (choose)
        {
            case 1:
            {
                Train x;
                input_train_info(x);
                push(x);
                break;
            }
            case 2:
            {
                Train x;
                if (pop(x))
                    cout << "Trip ID: " << x.tripID << endl
                        << "Train ID: " << x.trainID << endl
                        << "Departure: " << x.departure << endl
                        << "Destination: " << x.destination << endl
                        << "Depart time: " << x.departTime << endl
                        << "Arrival Time: " << x.arrivalTime << endl
                        << "Depart Date: " << x.departDate << endl
                        << "Arrival Date: " << x.arrivalDate << endl
                        << "The number of passengers: " << x.passenger;
                else
                    cout << "There's no train";
                break;
            }
            default:
                cout << "You just quitted, what a LOSER";
        }
        _getch();
    } while (choose >= 1 && choose <= 2);
    _getch();
    return 0;
}

void init()
{
    sp = NULL;
}

void push(Train x)
{
     Node *p;
     p = new Node;
     p->info = x;
     p->next = sp;
     sp = p;
}

int pop(Train &x)
{
    if (sp != NULL)
    {
        Node *p = sp;
        x = p->info;
        sp = p->next;
        delete p;
        return 1;
    }
    return 0;
}

void input_train_info(Train &train)
{
    cout << "Input trip ID: ";
    cin >> train.tripID;
    cout << "Input train ID: ";
    cin >> train.trainID;
    cout << "Input departure: ";
    cin.ignore();
    getline(cin, train.departure); 
    cout << "Input destination: ";
    getline(cin, train.destination);
    cout <<  "Input depart time: ";
    cin >> train.departTime;
    cout << "Input arrival time: ";
    cin >> train.arrivalTime;
    cout << "Input depart date: ";
    cin >> train.departDate;
    cout << "Input arrival date: ";
    cin >> train.arrivalDate;
    cout << "Input the number of passengers: ";
    cin >> train.passenger;
}