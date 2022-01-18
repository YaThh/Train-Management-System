#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include "Console.h"
using namespace std;

struct Time {
    string hour, minute, day, month, year;
};

struct Train {
    string tripID, trainID;
    string departure, destination;
    string passenger;
    Time departTime, arrivalTime, departDate, arrivalDate;
    int trips, date;
};

struct Node {
    Train info;
    Node *next;
};

int x = 40, y = 13;
string title[9] =
        {
            " _             _                                                     ",
            "| |           (_)                                                    ",
            "| |_ _ __ __ _ _ _ __    _ __ ___   __ _ _ __   __ _  __ _  ___ _ __ ",
            "| __| '__/ _` | | '_ \\  | '_ ` _ \\ / _` | '_ \\ / _` |/ _` |/ _ \\ '__|",
            "| |_| | | (_| | | | | | | | | | | | (_| | | | | (_| | (_| |  __/ |   ",
            " \\__|_|  \\__,_|_|_| |_| |_| |_| |_|\\__,_|_| |_|\\__,_|\\__, |\\___|_|   ",
            "                                                      __/ |          ",
            "                                                      |___/           ",
        };

void init(Node *&peak);
void push(Train x, Node *&peak);
int pop(Train &x, Node *&peak);
void input_train_info(Train &train);
void input_train_info_from_file(Train &train, Node *&peak);
void clone_list(Node *&peak, Node *originalPeak);
void sort_train_asc(Node *peak);
void sort_train_desc(Node *peak);
void traverse_list(Node *peak);
int count_passenger(Node *peak);
void count_trip(Node *peak, Node *originalPeak, Node *&archive);
void sort_list(Node* peak);
void find_trip_max(Node *peak, Node *originalPeak, Node *&archive);
void delete_first(Node *&peak);
void delete_list(Node *&peak);
int search_list(Node *peak, string trainID);
void count_time(Node *peak);
void output(Node *peak);
int convert_to_min(Node *p, int min, int hour, int d, int m, int yDepart, int yArrive);
int find_time_max(Node* peak);
int transform_to_min(int min);
int transform_to_hour(int min);
bool check_input_date(int day, int month, int year);
bool check_input_time(int hour, int min);
void count_date(Node* peak, Node* originalPeak, Node*& archive);
void menu(int &check);
void clear_menu();
void draw_title(string title[]);
void menu_sort(int &check);

int main()
{
    ShowCur(false);
    Train train;
    Node *sp = NULL;
    Node *sortHead_asc, *sortHead_desc;
    bool check = false, checkSortAsc = false, checkSortDesc = false;
    int in = 0, sortIn = 0;
    do {
        Menu:
        system("cls");
        menu(in); 
        switch (in)
        {
            case 1:
                clear_menu();
                if(!check)
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
                in = 0;
                break;
            case 2:
                clear_menu();
                init(sp);
                delete_list(sp);
                input_train_info_from_file(train, sp);
                check = true;
                in = 0;
                break;
            case 3:
                clear_menu();
                if (check)
                {
                    if (pop(train, sp))
                    {
                        gotoXY(x, y++);
                        cout << "Trip ID: " << train.tripID << endl;
                        gotoXY(x, y++);
                        cout << "Train ID: " << train.trainID << endl;
                        gotoXY(x, y++);
                        cout << "Departure: " << train.departure << endl;
                        gotoXY(x,y++);
                        cout << "Destination: " << train.destination << endl;
                        gotoXY(x, y++);
                        cout << "Depart time: " << train.departTime.hour << ":" << train.departTime.minute << endl;
                        gotoXY(x, y++);
                        cout << "Arrival Time: " << train.arrivalTime.hour << ":" << train.arrivalTime.minute << endl;
                        gotoXY(x, y++);
                        cout << "Depart Date: " << train.departDate.day << "/" << train.departDate.month << "/" << train.departDate.year << endl;
                        gotoXY(x, y++);
                        cout << "Arrival Date: " << train.arrivalDate.day << "/" << train.arrivalDate.month << "/" << train.arrivalDate.year << endl;
                        gotoXY(x, y++);
                        cout << "The number of passengers: " << train.passenger;
                    }
                    else
                    {
                        gotoXY(x, y++);
                        cout << "There is no train";
                    }
                }
                else
                {
                    gotoXY(x, y++);
                    cout << "No data";
                }
                in = 0;
                break;
            case 4:
                clear_menu();
                if (check)
                {
                    do {
                        system("cls");
                        menu_sort(sortIn);
                        switch (sortIn)
                        {
                            case 1:
                                init(sortHead_asc);
                                clone_list(sortHead_asc, sp);
                                sort_train_asc(sortHead_asc);
                                traverse_list(sortHead_asc);
                                sortIn = 0;
                                checkSortAsc = true;
                                checkSortDesc = false;
                                break;
                            case 2:
                                init(sortHead_desc);
                                clone_list(sortHead_desc, sp);
                                sort_train_desc(sortHead_desc);
                                traverse_list(sortHead_desc);
                                checkSortDesc = true;
                                checkSortAsc = false;
                                sortIn = 0;
                                break;
                            default:
                                sortIn = 0;
                                in = 0;
                                goto Menu;
                        }
                        _getch();
                    } while (sortIn != 3);
                }
                else
                {
                    gotoXY(x, y++);
                    cout << "No data";
                    sortIn = 0;
                    in = 0;
                }
                break;
            case 5:
                clear_menu();
                if (check)
                {
                    if (checkSortAsc)
                    {
                        input_train_info(train);
                        push(train, sortHead_asc);
                        sort_train_asc(sortHead_asc);
                        traverse_list(sortHead_asc);
                    }
                    else if (checkSortDesc)
                    {
                        input_train_info(train);
                        push(train, sortHead_desc);
                        sort_train_desc(sortHead_desc);
                        traverse_list(sortHead_desc);
                    } 
                    else
                    {
                        gotoXY(x, y++);
                        cout << "You must choose the option 4 first";
                    }
                }
                else
                {
                    gotoXY(x, y++);
                    cout << "No data";
                }
                in = 0;
                break;
            case 6:
                clear_menu();
                if (check)
                {
                    Node* countTrip;
                    Node* archive;
                    init(countTrip);
                    init(archive);
                    count_trip(countTrip, sp, archive);
                    while (archive != NULL)
                    {
                        gotoXY(x, y++);
                        cout << archive->info.trainID << ": " << archive->info.trips;
                        archive = archive->next;
                    }
                }
                else
                {
                    gotoXY(x, y++);
                    cout << "No data";
                }
                in = 0;
                break;  
            case 7:
                clear_menu();
                if (check)
                {
                    Node* tripMax;
                    Node* archive;
                    init(tripMax);
                    init(archive);
                    find_trip_max(tripMax, sp, archive);
                }
                else
                {
                    gotoXY(x, y++);
                    cout << "No data";
                }
                in = 0;
                break;
            case 8:
                clear_menu();
                if (check)
                {
                    gotoXY(x, y++);
                    cout << "The number of passengers used train in New Year: " << count_passenger(sp);
                }
                else
                {
                    gotoXY(x, y++);
                    cout << "No data";
                }
                in = 0;
                break;
            case 9:
                clear_menu();
                if (check)
                    count_time(sp);
                else
                {
                    gotoXY(x, y++);
                    cout << "No data";
                }
                in = 0;
                break;
            case 10:
                clear_menu();
                if (check)
                {
                    Node* countDate;
                    Node* archive;
                    init(countDate);
                    init(archive);
                    count_date(countDate, sp, archive);
                while (archive != NULL)
                {
                    gotoXY(x, y++);
                    cout << archive->info.departDate.day << "/" << archive->info.departDate.month << "/" << archive->info.departDate.year << ": " << archive->info.date << endl;
                    archive = archive->next;
                }
                }
                else
                {
                    gotoXY(x, y++);
                    cout << "No data";
                }
                in = 0;
                break;
            default:
                clear_menu();
                gotoXY(x, y++);
                SetColor(7);
                cout << "You just quitted";
        }
        _getch();
    } while (in != 11);
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
    gotoXY(x, y++);
    cout << "Input trip ID: ";
    cin >> train.tripID;
    gotoXY(x, y++);
    cout << "Input train ID: ";
    cin >> train.trainID;
    gotoXY(x, y++);
    cout << "Input departure: ";
    cin.ignore();
    getline(cin, train.departure); 
    gotoXY(x, y++);
    cout << "Input destination: ";
    getline(cin, train.destination);
    do {
        gotoXY(x, y++);
        cout <<  "Input depart time(HH:MM): ";
        getline(cin, train.departTime.hour, ':');
        getline(cin, train.departTime.minute);
        if (!check_input_time(stoi(train.departTime.hour), stoi(train.departTime.minute)))
        {
            gotoXY(x, y++);
            cout << "Invalid\n";
        }
    } while (!check_input_time(stoi(train.departTime.hour), stoi(train.departTime.minute)));
    do {
        gotoXY(x, y++);
        cout << "Input arrival time(HH:MM): ";
        getline(cin, train.arrivalTime.hour, ':');
        getline(cin, train.arrivalTime.minute);
        if (!check_input_time(stoi(train.arrivalTime.hour), stoi(train.arrivalTime.minute)))
        {
            gotoXY(x, y++);
            cout << "Invalid\n";
        }
    } while (!check_input_time(stoi(train.departTime.hour), stoi(train.arrivalTime.minute)));
    do {
        gotoXY(x, y++);
        cout << "Input depart date(dd/mm/yyyy): ";
        getline(cin, train.departDate.day, '/');
        getline(cin, train.departDate.month, '/');
        getline(cin, train.departDate.year);        
        if (!check_input_date(stoi(train.departDate.day), stoi(train.departDate.month), stoi(train.departDate.year)))
        {
            gotoXY(x, y++);
            cout << "Invalid input\n";
        }
    } while (!check_input_date(stoi(train.departDate.day), stoi(train.departDate.month), stoi(train.departDate.year)));
    do {
        gotoXY(x, y++);
        cout << "Input arrival date(dd/mm/yyyy): ";
        getline(cin, train.arrivalDate.day, '/');
        getline(cin, train.arrivalDate.month, '/');
        getline(cin, train.arrivalDate.year);
        if (!check_input_date(stoi(train.arrivalDate.day), stoi(train.arrivalDate.month), stoi(train.arrivalDate.year)))
        {
            gotoXY(x, y++);
            cout << "Invalid input\n";
        }
    } while(!check_input_date(stoi(train.arrivalDate.day), stoi(train.arrivalDate.month), stoi(train.arrivalDate.year)));
    do {
        gotoXY(x, y++);
        cout << "Input the number of passengers: ";
        cin >> train.passenger;
        if (stoi(train.passenger) < 0)
        {
            gotoXY(x, y++);
            cout << "Invalid input";
        }
    } while (stoi(train.passenger) < 0);
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
        gotoXY(x, y++);
        cout << "Read file successfully";
        inTrain.close();
    }
    else
        cout << "Could not read the file";
}

void clone_list(Node *&peak, Node *originalPeak)
{
    Node *sortList;
    Node *origin = originalPeak;
    while (origin != NULL)
    {
        sortList = new Node;
        sortList->info = origin->info;
        sortList->next = peak;
        peak = sortList;
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

void traverse_list(Node *peak)
{
    Node *p;
    p = peak;
    while (p != NULL)
    {
        gotoXY(x, y++);
        cout << p->info.trainID << ": "
            << p->info.departDate.day << "/"
            << p->info.departDate.month << "/"
            << p->info.departDate.year << " - "
            << p->info.arrivalDate.day << "/"
            << p->info.arrivalDate.month << "/"
            << p->info.arrivalDate.year;
        p = p->next;
    }
    x = 40; y = 13;
}

void output(Node *peak)
{
    Node *p;
    p = peak;
    gotoXY(x, y++);
    cout << p->info.trainID << ": "
        << p->info.departDate.day << "/"
        << p->info.departDate.month << "/"
        << p->info.departDate.year << " - "
        << p->info.arrivalDate.day << "/"
        << p->info.arrivalDate.month << "/"
        << p->info.arrivalDate.year;
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

void count_trip(Node *peak, Node *originalPeak, Node *&archive)
{
    int count;
    if (originalPeak == NULL)
        return;
    clone_list(peak, originalPeak);
    if (peak->next == NULL)
    {
        peak->info.trips = 1;
        push(peak->info, archive);
        return;
    }
    sort_list(peak);
    Node *p = peak;
    Node *q = p->next;
    while (p->next != NULL)
    {
        count = 1;
        while (q->info.trainID == p->info.trainID)
        {
            if (q->next != NULL)
            {
                count++;
                q = q->next;
            }
            else
            {
                count++;
                break;
            }
        } 
        p->info.trips = count;
        push(p->info, archive);
        if (count != 1)
        {
            while (p != q)
                p = p->next;
            if (q->next != NULL)
                q = q->next;
        }
        else
        {
            p = p->next;
            if (q->next != NULL)
                q = q->next;
        }
    }
    if (p->next == NULL && !search_list(archive, p->info.trainID))
    {
        p->info.trips = 1;
        push(p->info, archive);
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

void find_trip_max(Node *peak, Node *originalPeak, Node *&archive)
{
    count_trip(peak, originalPeak, archive);
    Node *maxList = NULL;
    Node *p = archive;
    Node *q;
    int max = p->info.trips;
    push(p->info, maxList);
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
    gotoXY(x, y++);
    cout << "Train with the most trips: " << endl;
    while (maxList != NULL)
    {
        gotoXY(x, y++);
        cout << maxList->info.trainID << ": " << maxList->info.trips;
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

void count_time(Node* peak)
{
    Node* p;
    int max;
    p = peak;
    max = find_time_max(p);
    while (p != NULL) {
        int minA, minB;
        minA = convert_to_min(p, stoi(p->info.departTime.minute), stoi(p->info.departTime.hour),
        stoi(p->info.departDate.day), stoi(p->info.departDate.month), stoi(p->info.departDate.year), stoi(p->info.arrivalDate.year));

        minB = convert_to_min(p, stoi(p->info.arrivalTime.minute), stoi(p->info.arrivalTime.hour),
        stoi(p->info.arrivalDate.day), stoi(p->info.arrivalDate.month), stoi(p->info.arrivalDate.year), stoi(p->info.departDate.year));

        int totalM;
        totalM = minB - minA;
        if (max == totalM)
        {
            output(p);
            cout << " Total time: " << transform_to_hour(totalM) << " hour " << transform_to_min(totalM) << " minute\n";
        }
        p = p->next;
    }
}

int find_time_max(Node* peak)
{
    int MAX = 0;
    Node* p;
    p = peak;
    int minA, minB;
    while (p != NULL) {

        minA = convert_to_min(p, stoi(p->info.departTime.minute), stoi(p->info.departTime.hour),
        stoi(p->info.departDate.day), stoi(p->info.departDate.month), stoi(p->info.departDate.year), stoi(p->info.arrivalDate.year));

        minB = convert_to_min(p, stoi(p->info.arrivalTime.minute), stoi(p->info.arrivalTime.hour),
        stoi(p->info.arrivalDate.day), stoi(p->info.arrivalDate.month), stoi(p->info.arrivalDate.year), stoi(p->info.departDate.year));

        int totalM;
        totalM = minB - minA;
        if (MAX < totalM) {
            MAX = totalM;
        }
        p = p->next;
    }
    return MAX;
}

int convert_to_min(Node *p, int min, int hour, int d, int m, int yDepart, int yArrive)
{
    int minute, hConvert, dConvert, dom = 0, mConvert, yConvert;
    hConvert = hour * 60;
    dConvert = d * 60 * 24;
    for (int i = 1; i < m; i++) {
        if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12)
            dom += 31;
        else if (i == 4 || i == 6 || i == 9 || i == 11)
            dom += 30;
        else if (i == 2 && ((yDepart % 400 == 0) && (yDepart % 4 == 0 && yDepart % 100 != 0)))
            dom += 29;
        else
            dom += 28;
    }
    mConvert = dom * 60 * 24;
    if (yDepart == yArrive)
        yConvert = 0;
    else if ((yDepart % 400 == 0) && (yDepart % 4 == 0 && yDepart % 100 != 0))
        yConvert = (yDepart - 2000) * 366 * 60 * 24;
    else
        yConvert = (yDepart - 2000) * 365 * 60 * 24;
    minute = min + hConvert + dConvert + mConvert + yConvert;
    return minute;
}

int transform_to_min(int min)
{
    return min % 60;
}

int transform_to_hour(int min)
{
    return min / 60;
}

bool check_input_date(int day, int month, int year)
{
    int dom;
    if (month > 12 || month < 1 || year < 0)
        return false;
    switch(month)
    {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            dom = 31;
            break;
        case 4: case 6: case 9: case 11:
            dom = 30;
            break;
        case 2:
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
                dom = 29;
            else
                dom = 28;
    }
    if (day < 1 || day > dom)
        return false;
    return true;
}

bool check_input_time(int hour, int min)
{
    if (hour < 0 || hour > 23 || min < 0 || hour > 59)
        return false;
    return true;
}

void count_date(Node* peak, Node* originalPeak, Node*& archive)
{
    clone_list(peak, originalPeak);
    sort_train_desc(peak);
    Node* p = peak;
    Node* q = p->next;
    while (p != NULL)
    {
        int count = 1;
        while ((p->info.departDate.day == q->info.departDate.day)
            && (p->info.departDate.month == q->info.departDate.month)
            && (p->info.departDate.year == q->info.departDate.year))
        {
            if (q->next != NULL)
            {
                count++;
                q = q->next;
            }
            else
                break;
        }
        p->info.date = count;
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

void menu(int &check)
{
    int set[] = {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7};
    char key;
    int pos = 1;
    while (check == 0)
    {
        
        draw_title(title);
        gotoXY(2, 27);
        SetColor(7);
        cout << "Note: use arrow keys to move,";
        gotoXY(2, 28);
        cout << "press ENTER to choose";
        gotoXY(40, 13);
        SetColor(set[0]);
        cout << "1. Add train";
        gotoXY(40, 14);
        SetColor(set[1]);
        cout << "2. Add train from file";
        gotoXY(40, 15);
        SetColor(set[2]);
        cout << "3. Remove train";
        gotoXY(40, 16);
        SetColor(set[3]);
        cout << "4. Sort train's date";
        gotoXY(40, 17);
        SetColor(set[4]);
        cout << "5. Sort train after adding a new train";
        gotoXY(40, 18);
        SetColor(set[5]);
        cout << "6. Count trip";
        gotoXY(40, 19);
        SetColor(set[6]);
        cout << "7. Find trains with the most trips";
        gotoXY(40, 20);
        SetColor(set[7]);
        cout << "8. Count the number of passengers in New Year";
        gotoXY(40, 21);
        SetColor(set[8]);
        cout << "9. Find the most runtime train";
        gotoXY(40, 22);
        SetColor(set[9]);
        cout << "10. Find the most trips in days";
        gotoXY(40, 23);
        SetColor(set[10]);
        cout << "11. Quit";
        if (_kbhit())
        {
            key = _getch();
            if (key == -32)
            {
                key = _getch();
                if (key == 80 && (pos >= 1 && pos < 11))
                    pos++;
                else if (key == 72 && (pos <= 11 && pos > 1))
                    pos--;
            }
            else if (key == 13)
            {
                switch (pos)
                {
                    case 1: check = 1; break;
                    case 2: check = 2; break;
                    case 3: check = 3; break;
                    case 4: check = 4; break;
                    case 5: check = 5; break;
                    case 6: check = 6; break;
                    case 7: check = 7; break;
                    case 8: check = 8; break;
                    case 9: check = 9; break;
                    case 10: check = 10; break;
                    case 11: check = 11; break;
                }
            }
        }
        for (int i = 0; i < 11; i++)
            set[i] = 7;
        for (int i = 1; i <= 11; i++)
            if (pos == i)
                set[pos - 1] = 12;
    }
}

void draw_title(string title[])
{
    int x1 = 28, y1 = 1;
    for (int i = 0; i < 9; i++)
    {
        gotoXY(x1, y1);
        SetColor(3);
        cout << title[i];
        y1++;
    }
}

void clear_menu()
{
    int x1 = 40, y1 = 13;
    string space[12] = 
    {
        "                                              ",
        "                                              ",
        "                                              ",
        "                                              ",
        "                                              ",
        "                                              ",
        "                                              ",
        "                                              ",
        "                                              ",
        "                                              ",
        "                                              ",
    };
    for (int i = 0; i < 11; i++)
    {
        gotoXY(x1, y1);
        cout << space[i];
        y1++;
    }
    x = 40; y = 13;
}

void menu_sort(int &check)
{
    int set[] = {7, 7, 7};
    char key;
    int pos = 1;
    while (check == 0)
    {
        draw_title(title);
        gotoXY(40, 13);
        SetColor(set[0]);
        cout << "Sort train's date ascending";
        gotoXY(40, 14);
        SetColor(set[1]);
        cout << "Sort train's date descending";
        gotoXY(40, 15);
        SetColor(set[2]);
        cout << "Go back to main menu";
        if (_kbhit())
        {
            key = _getch();
            if (key == -32)
            {
                key = _getch();
                if (key == 80 && (pos >= 1 && pos < 3))
                    pos++;
                else if (key == 72 && (pos > 1 && pos <=3))
                    pos--;
            }
            else if (key == 13)
            {
                switch (pos)
                {
                    case 1: check = 1; break; 
                    case 2: check = 2; break;
                    case 3: check = 3; break;
                }
            }
        }
        for (int i = 0; i < 3; i++)
            set[i] = 7;
        for (int i = 1; i <= 3; i++)
            if (pos == i)
                set[pos - 1] = 12;
    }
}