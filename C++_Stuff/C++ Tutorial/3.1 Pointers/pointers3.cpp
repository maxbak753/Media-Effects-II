#include <iostream>
#include <cstdlib> // c standard library (C++ version)
#include <ctime> // to set random seed with current time

// [3 Functions that use pointers]

using namespace std;

void update_score(int *points, int pt);
void random_update(int *points);
void print_points_memory(int *points);

int main() {
    int decision;
    bool run = true;

    srand(time(0)); // use the current time as the seed (0 or NULL) <-- DO BEFORE THE LOOP!
    int r = rand() % 100 + 1;
    int *r_ptr = &r; 

    cout << "Initial Points = " << r << endl;

    while (run) {
        cout << "Choose Your Operation:\n[1] Update points (+1)\n[2] Random Update (+-?)\n[3] Print Memory Location\n[4] End\n" << endl;
        cin >> decision;

        if (decision == 1) {
            update_score(r_ptr, 1);
        } else if (decision == 2) {
            random_update(r_ptr);
        } else if (decision == 3) {
            print_points_memory(r_ptr);
        } else if (decision == 4) {
            run = false;
        } else {
            cout << "THAT'S NOT AN OPTION (1, 2, or 3)!!!" << endl;
        }

        cout << "Points = " << r << endl;
    }

}

void update_score(int *points, int pt) {
    *points += pt;
}

void random_update(int *points) {
    *points += (rand() - (RAND_MAX/2)) / 100;
}

void print_points_memory(int *points) {
    cout << points << endl;
}