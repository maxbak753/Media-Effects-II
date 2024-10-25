#include <iostream>
#include <fstream> // File Stream Library

using namespace std;

void simple_write();
void simple_read();
void simple_append();
void simple_readAll();

// fstream functions
string get_filename();
bool open_file(fstream& file, string filename);
void write_text(fstream& file);
void read_text(fstream& file);

void file_handler(); // does all handling for fstream

int main() {
    bool run = 1; // run until "-1. Exit" is chosen
    while(run) {
        int response = 0;
        cout << "Please choose your file operations!" << endl;
        cout << "1. Write to file" << endl;
        cout << "2. Read to file" << endl;
        cout << "3. Append to file" << endl;
        cout << "4. Read All from file" << endl;
        cout << "5. Use fstream" << endl;
        cout << "-1. Exit" << endl;
        cin >> response;
        cout << "You chose:" << response << endl;

        switch(response) { // Switch-Case Statement
            case 1:
                simple_write();
                break; // must end each case with a break
            case 2:
                simple_read();
                break;
            case 3:
                simple_append();
                break;
            case 4:
                simple_readAll();
                break;
            case 5:
                file_handler();
                break;
            case -1:
                run = 0;
                cout << "Goodbye!" << endl;
                break;
            default: // if none trigger then default does
                cout << "You must not have entered in something correct" << endl;
                break;
        }

    }

    return 0;
}

void simple_write() {
    // Create file object from output file stream class
    ofstream file;
    // Open the file (creates it if nonexistent)
    file.open("myText.txt");
    // check if it actually opened
    if (file.is_open()) {
        // Write to the file (will overwrite EVERYTHING in the previous file!)
        file << "Line 1 of writing" << endl; //must put endl or \n for newline
        file << "Line 2 of writing\n";
        file << "Line 3 of writing" << endl;
    } else {
        cout << "The file didn't open" << endl;
    }
    // Close the file
    file.close();
}

void simple_read() {
    // Create file object from input file stream class
    ifstream file;
    // open file
    file.open("myText.txt");
    string extracted = "";
    string extracted2 = "";
    string extracted3 = "";
    // make sure file is open
    if (file.is_open()) {
        // read and store in variable
        // reads until a space or newline (whichever comes 1st)
        file >> extracted;
        file >> extracted2;
        file >> extracted3;
    } else {
        cout << "The file must not have opened" << endl;
    }
    // close file
    file.close();
    // print extracted text
    cout << "I read this from the file: " << extracted << endl;
    cout << "I read this from the file: " << extracted2 << endl;
    cout << "I read this from the file: " << extracted3 << endl;
}

void simple_append() {
    // Create file object from output file stream class
    ofstream file;
    // Open the file (creates it if nonexistent)
    file.open("myText.txt", ios::app); // use input/output stream append mode
    // check if it actually opened
    if (file.is_open()) {
        // Append the file
        file << "Appending to the end!" << endl;
    } else {
        cout << "The file didn't open" << endl;
    }
    // Close the file
    file.close();
}

void simple_readAll() {
    ifstream file;
    file.open("myText.txt");

    string temp = "";
    string store = "";

    if (file.is_open()) {
        while(getline(file, temp)) {
            store += temp;
            store += "\n";
        }
    } else {
        cout << "This file didn't open" << endl;
    }

    file.close();
    cout << "Reading All from File...\n" << store << endl;
}

// ------------------------------
// FSTREAM FUNCTIONS

void file_handler() {
    fstream file; // must create variable here so it is in the scope of other files via reference (&)
    string filename = get_filename();
    if (open_file(file, filename)) {
        write_text(file);
        read_text(file);
    } else {
        cout << "The file never opened" << endl;
    }
    file.close(); // close file
}

string get_filename() {
    cout << "Enter a file name you want to work with: " <<endl;
    string filename = "";
    cin >> filename;
    return filename;
}

bool open_file(fstream& file, string filename) {
    // open file (will only create a new file if using just output mode, but fstream uses both input & output modes, so it cannot create a new file)
    file.open(filename.c_str()); // c_str() turns C++ string into C string
    // return whether or not the file opoened correctly
    if (file.is_open()) {
        return true;
    } else {
        return false;
    }
}

// the file must be open to use this function!
void write_text(fstream& file) {
    file << "This is me writing to an fstream file" << endl;
}

void read_text(fstream& file) {
    string store = "";
    file >> store; // reads from the line you stopped writing from (line 2 in this case)

    cout << "I read this from an fstream file: ";
    cout << store << endl;
}