#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <algorithm>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);

void sort_goats(list<Goat> &trip); //1
void reverse_trip(list<Goat> &trip);
void remove_duplicates(list<Goat> &trip);
void count_by_color(list<Goat> trip);
void find_oldest_goat(list<Goat> trip);
void find_goats_older_than(list<Goat> trip);
void move_first_to_back(list<Goat> &trip);
void clear_trip(list<Goat> &trip); //8

int main_menu();

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 12) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:    
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            case 4:
                cout << "Sorting goats by name.\n";
                sort_goats(trip);
                display_trip(trip);
                break;
            case 5:  
                cout << "Reversing trip.\n";
                reverse_trip(trip);
                display_trip(trip);
                break;
            case 6:
                cout << "Removing duplicate goats.\n";
                remove_duplicates(trip);
                display_trip(trip);
                break;
            case 7:
                cout << "Counting goats by color.\n";
                count_by_color(trip);
                break;
            case 8:
                cout << "Finding oldest goat.\n";
                find_oldest_goat(trip);
                break;
            case 9:
                cout << "Finding goats older than an age.\n";
                find_goats_older_than(trip);
                break;
            case 10:
                cout << "Moving first goat to back.\n";
                move_first_to_back(trip);
                display_trip(trip);
                break;
            case 11:
                cout << "Clearing all goats.\n";
                clear_trip(trip);
                break;
                
            
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }
    

    return 0;
}

int main_menu() {
    int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add goat\n";
    cout << "[2] Delete goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Sort goats by name\n";
    cout << "[5] Reverse trip\n";
    cout << "[6] Remove dupl icate goats\n";
    cout << "[7] Count goat by color\n";
    cout << "[8] Find oldest goat\n";
    cout << "[9] Find goats older than an age\n" ;
    cout << "[10] Move first goat to back\n" ;
    cout << "[11] Clear all goats\n";
    cout << "[12] Quit\n";
    cout << "Choice -->";

    return choice;
}
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}

// Milestone 1
void sort_goats(list<Goat> &trip) {
    cout << "SORT GOATS BY NAME\n";
    trip.sort();
    cout << "Trip sorted by name.\n";
}

// Milestone 2
void reverse_trip(list<Goat> &trip) {
    cout << "REVERSE TRIP\n";
    trip.reverse();
    cout << "Trip reversed.\n";
}

// Milestone 3
void remove_duplicates(list<Goat> &trip) {
    cout << "REMOVE DUPLICATE GOATS\n";
    trip.sort();
    trip.unique();
    cout << "Duplicate goats removed.\n";
}


// Milestone 4
void count_by_color(list<Goat> trip) {
    cout << "COUNT GOATS BY COLOR\n";
    string color;
    cout << "Enter color --> ";
    cin >> color;

    int count = count_if(trip.begin(), trip.end(),
        [color](Goat g) {
            return g.get_color() == color;
        });

    cout << "Number of goats with color " << color << ": " << count << endl;
}

// Milestone 5
void find_oldest_goat(list<Goat> trip) {
    cout << "FIND OLDEST GOAT\n";

    if (trip.empty()) {
        cout << "No goats in the trip.\n";
        return;
    }

    auto it = max_element(trip.begin(), trip.end(),
        [](Goat a, Goat b) {
            return a.get_age() < b.get_age();
        });

}


// Milestone 6
void find_goats_older_than(list<Goat> trip) {
    cout << "FIND GOATS OLDER THAN AN AGE\n";
    int age;
    cout << "Enter age --> ";
    cin >> age;

    bool found = false;
    for (auto gt : trip) {
        if (gt.get_age() > age) {
            cout << gt.get_name()
                 << " (" << gt.get_age()
                 << ", " << gt.get_color() << ")\n";
            found = true;
        }
    }

    if (!found) {
        cout << "No goats found older than " << age << ".\n";
    }
}
