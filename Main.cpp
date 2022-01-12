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
    int trips;
};

struct Node {
    Train info;
    Node *next;
};


void init(Node *&peak);
void push(Train x, Node *&peak);
int pop(Train &x, Node *&peak);
void input_train_info(Train &train);
void input_train_info_from_file(Train &train, Node *&peak);
void clone_list(Node *&head, Node *originalHead);
void sort_train_asc(Node *peak);
void sort_train_desc(Node *peak);
void traverse(Node *peak);
int count_passenger(Node *peak);
void count_trip(Node *peak, Node *originalHead, Node *&archive);
void sort_list(Node* peak);
void find_trip_max(Node *peak, Node *originalHead, Node *&archive);
void delete_first(Node *&peak);
void delete_list(Node *&peak);
int search_list(Node *peak, string trainID);

int main()
{
    Train train;
    Node *sp;
    Node *sortHead_asc, *sortHead_desc;
    bool check = false, sortIn = false;
    int choose;
    do {
        system("cls");
        cout << "1. Add train\n"
            << "2. Add train from file\n"
            << "3. Remove train\n"
            << "4. Sort train ascending\n"
            << "5. Sort train after adding a new train\n"
            << "6. Count trip\n"
            << "7. Find trip max\n"
            << "8. Count the number of passengers in Tet holiday\n"
            << "8. Quit\n"
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
                delete_list(sp);
                input_train_info_from_file(train, sp);
                check = true;
                break;
            }
            case 3:
            {
                if (check)
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
                }
                else
                    cout << "No data";
                break;
            }
            case 4:
            {
                if (check)
                {
                    init(sortHead_asc);
                    clone_list(sortHead_asc, sp);
                    sort_train_asc(sortHead_asc);
                    traverse(sortHead_asc);
                    sortIn = true;
                }
                else
                    cout << "No data";
                break;
            }
            case 5:
            {   if (check)
                {
                    if (sortIn)
                    {
                        input_train_info(train);
                        push(train, sortHead_asc);
                        sort_train_asc(sortHead_asc);
                        traverse(sortHead_asc);
                    }
                    else
                        cout << "You must choose the option 4 first";
                } 
                else
                    cout << "No data";
                break;
            }
            case 6:
            {
                if (check)
                {
                    Node *countTrip;
                    Node *archive;
                    init(countTrip);
                    init(archive);
                    count_trip(countTrip, sp, archive);
                    while (archive != NULL)
                    {
                        cout << archive->info.trainID << ": " << archive->info.trips << endl;
                        archive = archive->next;
                    }
                }
                else
                    cout << "No data";
                break;
            }
            case 7:
            {
                if (check)
                {
                    Node *tripMax;
                    Node *archive;
                    init(tripMax);
                    init(archive);
                    find_trip_max(tripMax, sp, archive);
                }
                else
                    cout << "No data";
                break;
            }
            case 8:
            {
                if (check)
                    cout << "The number of passengers used train in Tet holiday: "
                        << count_passenger(sp) << endl;
                else
                    cout << "No data";
                break;
            }
            default:
                cout << "You just quitted";
        }
        _getch();
    } while (choose >= 1 && choose <= 8);
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

void clone_list(Node *&head, Node *originalHead)
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

void count_trip(Node *peak, Node *originalHead, Node *&archive)
{
    clone_list(peak, originalHead);
    sort_list(peak);
    Node *p = peak;
    Node *q = p->next;
    while (p != NULL)
    {
        int count = 1;
        while (q->info.trainID == p->info.trainID)
        {
            if (q->next != NULL)
            {
                count++;
                q = q->next;
            }
            else
                break;
        } 
        p->info.trips = count;
        if (count != 1)
        {
            push(p->info, archive);
            while (p != q)
                p = p->next;
            if (q->next != NULL)
                q = p->next;
        }
        else
        {
            push(p->info, archive);
            p = p->next;
            if (q->next != NULL)
                q = p->next;
        }
    }
}

void sort_list(Node* peak)
{
    Node *p = peak;
    while (p != NULL)
    {
        Node *q = p->next;
        while (q != NULL)
        {
            if (p->info.trainID > q->info.trainID)
            {
                Train temp;
                temp = p->info;
                p->info = q->info;
                q->info = temp;
            }
            q = q->next;
        }
        p = p->next;
    }
}

void find_trip_max(Node *peak, Node *originalHead, Node *&archive)
{
    count_trip(peak, originalHead, archive);
    Node *maxList = NULL;
    Node *p = archive;
    Node *q;
    int max = p->info.trips;
    while (p != NULL)
    {
        q = p->next;
        while (q != NULL)
        {
            if (q->info.trips > max)
            {
                max = q->info.trips;
                delete_list(maxList);
                push(q->info, maxList);
            }
            else if (q->info.trips == max && !search_list(maxList, q->info.trainID))
                push(q->info, maxList);
            q = q->next;
        }    
        p = p->next;
    }
    cout << "Train with the most trips: " << endl;
    while (maxList != NULL)
    {
        cout << maxList->info.trainID << ": " << maxList->info.trips << endl;
        maxList = maxList->next;
    }
}

void delete_first(Node *&peak)
{
    Node *p = peak;
    if (peak == NULL)
        return;
    peak = peak->next;
    delete p;
}

void delete_list(Node *&peak)
{
    while (peak != NULL)
        delete_first(peak);
}

int search_list(Node *peak, string trainID)
{
    Node *p = peak;
    while (p != NULL)
    {
        if (p->info.trainID == trainID)
            return 1;
        p = p->next;
    }
    return 0;
}