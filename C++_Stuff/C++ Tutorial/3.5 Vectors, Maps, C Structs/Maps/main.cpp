#include <iostream>
#include <map>

using namespace std;

int main() {
    // Map where key & value are both strings
    map<string, string> address_book;
    // Create key-value pair
    address_book["Maxwell"] = "19 Falkland St, Brighton MA 02135";
    // print value for key
    cout << address_book["Maxwell"] << endl;
    // Insert new pair (another way better for pointers!)
    address_book.insert(pair<string, string> ("Pericles", "9 Allan Drive, Maynard MA 01754"));
    cout << address_book["Pericles"] << endl;

    // ------------------------------------
    cout << "---{FOR-EACH LOOP}---" << endl;
    // enhanced for loop AKA for-each loop
    // for (data : collection)
    // auto = automatically chooses type for data (prevents errors if you don't know what will come out of a collection)
    for (auto const &pair : address_book) {
        cout << pair.first << endl;  // key
        cout << pair.second << endl; // value
    }

    return 0;
}