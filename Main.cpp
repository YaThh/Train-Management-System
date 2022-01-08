#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
using namespace std;

struct Time {
    string hour, minute, day, month, year;
};

struct Train {
    string tripID, trainID;
    string departure, destination;
    string passenger;
    Time departTime, arrivalTime, departDate, arrivalDate;
};

struct Node {
    Train info;
    Node *next;
};

Node *sp;
Node *sortHead_asc;

void init(Node *&peak);
void push(Train x, Node *&peak);
int pop(Train &x, Node *&peak);
void input_train_info(Train &train);
void input_train_info_from_file(Train &train, Node *&peak);
void clone_sort_list(Node *&head, Node *originalHead);
void sort_train_asc(Node *peak);
void sort_train_desc(Node *peak);
void traverse(Node *peak);
void update_list(Node *&peak);
int count_passenger(Node *peak);
void count_trainID(Node *&peak, Node *originalHead);
void delete_train(Node *&peak, string trainID);

int main()
{
    Train train;
    Node *sp;
    Node *sortHead_asc;
    bool check = false;
    int choose;
    do {
        system("cls");
        cout << "1. Add train\n"
            << "2. Add train from file\n"
            << "3. Remove train\n"
            << "4. Sort train descending\n"
            << "5. Count trainID\n"
            << "6. Quit\n"
            << "Choose: ";
        cin >> choose;
        switch (choose)
        {
            case 1:
            {
                if (!check)
                {
                    init(sp);
                    input_train_info(train);
                    push(train, sp);
                    check = true;
                }
                else
                {
                    input_train_info(train);
                    push(train, sp);
                }
                break;
            }
            case 2:
            {
                init(sp);
                update_list(sp);
                input_train_info_from_file(train, sp);
                break;
            }
            case 3:
            {
                if (pop(train, sp))
                    cout << "Trip ID: " << train.tripID << endl
                        << "Train ID: " << train.trainID << endl
                        << "Departure: " << train.departure << endl
                        << "Destination: " << train.destination << endl
                        << "Depart time: " << train.departTime.hour << ":" << train.departTime.minute << endl
                        << "Arrival Time: " << train.arrivalTime.hour << ":" << train.arrivalTime.minute << endl
                        << "Depart Date: " << train.departDate.day << "/" << train.departDate.month << "/" << train.departDate.year << endl
                        << "Arrival Date: " << train.arrivalDate.day << "/" << train.arrivalDate.month << "/" << train.arrivalDate.year << endl
                        << "The number of passengers: " << train.passenger;
                else
                    cout << "There is no train";
                break;
            }
            case 4:
            {
                init(sortHead_asc);
                clone_sort_list(sortHead_asc, sp);
                sort_train_desc(sortHead_asc);
                traverse(sortHead_asc);
                update_list(sortHead_asc);
                break;
            }
            case 5:
            {
                Node *count;
                init(count);
                count_trainID(count, sp);
                break;
            }
            default:
                cout << "You just quitted";
        }
        _getch();
    } while (choose >= 1 && choose <= 5);
    _getch();
    return 0;
}

void init(Node *&peak)
{
    peak = NULL;
}

void push(Train x, Node *&peak)
{
     Node *p;
     p = new Node;
     p->info = x;
     p->next = peak;
     peak = p;
}

int pop(Train &x, Node *&peak)
{
    if (peak != NULL)
    {
        Node *p = peak;
        x = p->info;
        peak = p->next;
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
    cout <<  "Input depart time(HH:MM): ";
    getline(cin, train.departTime.hour, ':');
    getline(cin, train.departTime.minute);
    cout << "Input arrival time(HH:MM): ";
    getline(cin, train.arrivalTime.hour, ':');
    getline(cin, train.arrivalTime.minute);
    cout << "Input depart date(dd/mm/yyyy): ";
    getline(cin, train.departDate.day, '/');
    getline(cin, train.departDate.month, '/');
    getline(cin, train.departDate.year);
    cout << "Input arrival date(dd/mm/yyyy): ";
    getline(cin, train.arrivalDate.day, '/');
    getline(cin, train.arrivalDate.month, '/');
    getline(cin, train.arrivalDate.year);
    cout << "Input the number of passengers: ";
    cin >> train.passenger;
}

void input_train_info_from_file(Train &train, Node *&peak)
{
    ifstream inTrain;
    inTrain.open("Train_List.txt");
    if (inTrain.is_open())
    {
        while (!inTrain.eof())
        {
            getline(inTrain, train.tripID, '#');
            getline(inTrain, train.trainID, '#');
            getline(inTrain, train.departure, '#');
            getline(inTrain, train.destination, '#');
            getline(inTrain, train.departTime.hour, ':');
            getline(inTrain, train.departTime.minute, '#');
            getline(inTrain, train.arrivalTime.hour, ':');
            getline(inTrain, train.arrivalTime.minute, '#');
            getline(inTrain, train.departDate.day, '/');
            getline(inTrain, train.departDate.month, '/');
            getline(inTrain, train.departDate.year, '#');
            getline(inTrain, train.arrivalDate.day, '/');
            getline(inTrain, train.arrivalDate.month, '/');
            getline(inTrain, train.arrivalDate.year, '#');
            getline(inTrain, train.passenger);
            push(train, peak);
        }
        cout << "Read file successfully";
        inTrain.close();
    }
    else
        cout << "Could not read the file";
}

void clone_sort_list(Node *&head, Node *originalHead)
{
    Node *sortList;
    Node *origin = originalHead;
    while (origin != NULL)
    {
        sortList = new Node;
        sortList->info = origin->info;
        sortList->next = head;
        head = sortList;
        origin = origin->next;
    }
}

void sort_train_asc(Node *peak)
{
    if (peak == NULL)
        return;
    else
    {
        Node *p, *q;
        p = peak;
        while (p != NULL)
        {
            q = p->next;
            while (q != NULL)
            {
                if (p->info.departDate.year == q->info.departDate.year && p->info.departDate.month == q->info.departDate.month)
                {
                    if (p->info.departDate.day > q->info.departDate.day)
                    {
                        Train temp = p->info;
                        p->info = q->info;
                        q->info = temp;
                    }
                    else if (p->info.departDate.day == q->info.departDate.day)
                    {
                        if (p->info.trainID > q->info.trainID)
                        {
                            Train temp = p->info;
                            p->info = q->info;
                            q->info = temp;
                        }
                    }
                    q = q->next;
                }
                else if (p->info.departDate.year == q->info.departDate.year && p->info.departDate.month != q->info.departDate.month)
                {
                    if (p->info.departDate.month > q->info.departDate.month)
                    {
                        Train temp = p->info;
                        p->info = q->info;
                        q->info = temp;
                    }
                    q = q->next;
                }
                else if (p->info.departDate.year != q->info.departDate.year)
                {
                    if (p->info.departDate.year > q->info.departDate.year)
                    {
                        Train temp = p->info;
                        p->info = q->info;
                        q->info = temp;
                    }
                    q = q->next; 
                }
            }
            p = p->next;
        }
    }
}

void sort_train_desc(Node *peak)
{
    if (peak == NULL)
        return;
    else
    {
        Node *p, *q;
        p = peak;
        while (p != NULL)
        {
            q = p->next;
            while (q != NULL)
            {
                if (p->info.departDate.year == q->info.departDate.year && p->info.departDate.month == q->info.departDate.month)
                {
                    if (p->info.departDate.day < q->info.departDate.day)
                    {
                        Train temp = p->info;
                        p->info = q->info;
                        q->info = temp;
                    }
                    else if (p->info.departDate.day == q->info.departDate.day)
                    {
                        if (p->info.trainID < q->info.trainID)
                        {
                            Train temp = p->info;
                            p->info = q->info;
                            q->info = temp;
                        }
                    }
                    q = q->next;
                }
                else if (p->info.departDate.year == q->info.departDate.year && p->info.departDate.month != q->info.departDate.month)
                {
                    if (p->info.departDate.month < q->info.departDate.month)
                    {
                        Train temp = p->info;
                        p->info = q->info;
                        q->info = temp;
                    }
                    q = q->next;
                }
                else if (p->info.departDate.year != q->info.departDate.year)
                {
                    if (p->info.departDate.year < q->info.departDate.year)
                    {
                        Train temp = p->info;
                        p->info = q->info;
                        q->info = temp;
                    }
                    q = q->next; 
                }
            }
            p = p->next;
        }
    }
}

void traverse(Node *peak)
{
    Node *p;
    p = peak;
    while (p != NULL)
    {
        cout << p->info.trainID << endl;
        cout << p->info.departDate.day << "/";
        cout << p->info.departDate.month << "/";
        cout << p->info.departDate.year << endl;
        p = p->next;
    }
}

void update_list(Node *&peak)
{
    if (peak == NULL)
        return;
    else
        while (peak != NULL)
        {
            Node *p = peak;
            peak = p->next;
            delete p;
        }
}

void count_trainID(Node *&peak, Node *originalHead)
{
    clone_sort_list(peak, originalHead);
    traverse(peak);
    Node *p = peak, *temp;
    while (p != NULL)
    {
        int count = 1;
        Node *q = p->next;
        while (q != NULL)
        {
            if (p->info.trainID== q->info.trainID)
                count++;
            q = q->next;
        }
        cout << p->info.trainID << ": " << count;
        cout << endl;
        temp = p;
        temp = temp->next;
        delete_train(p, p->info.trainID);
        p = temp;
    }
}

int count_passenger(Node *peak)
{
    int totalPassenger = 0;
    Node* p;
    p = peak;
    while (p != NULL) {
        if ((((stoi(p->info.departDate.day) >= 29) && (stoi(p->info.departDate.day) <= 31)) && (stoi(p->info.departDate.month) == 12) && (stoi(p->info.departDate.year) == 2020))
            || ((stoi(p->info.departDate.day) <= 3) && (stoi(p->info.departDate.month) == 1) && (stoi(p->info.departDate.year) == 2021)))
            totalPassenger += stoi(p->info.passenger);
        p = p->next;
    }
    return totalPassenger;
}

void delete_train(Node *&peak, string trainID)
{
    Node *p = peak, *q;
    while (p->next != NULL)
        p = p->next;
    do {
        q = peak;
        if (q != p)
        {
            while (q->next != p)
                q = q->next;
            if (p->info.trainID == trainID)
            {
                q->next = p->next;
                delete p;        
                Node *p = q;
            }
            else
                p = q;
        }
    } while (p != peak);
    if (p->info.trainID == trainID)
        delete p;
}