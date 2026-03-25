#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <algorithm>

using namespace std;

struct Album {int id;string title;string artist;string year;string genre;string medium;};

vector<Album> albums;
int nextId = 1;
const string DATABASE_FILE = "musicLibrary.txt";

void saveDatabase() {
    ofstream file(DATABASE_FILE);

    for (const auto& b : albums) {
        file << b.id << "|"
             << b.title << "|"
             << b.artist << "|"
             << b.year << "|"
             << b.genre << "|"
			 << b.medium << "\n";}
			 }

void loadDatabase() {
    ifstream file(DATABASE_FILE);
    if (!file) return;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        Album b;
        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);
        size_t p4 = line.find('|', p3 + 1);
        size_t p5 = line.find('|', p4 + 1);
        if (p1 == string::npos || p2 == string::npos || p3 == string::npos || p4 == string::npos)continue;
        try {b.id = stoi(line.substr(0, p1));} catch (...) {continue;}

        b.title = line.substr(p1 + 1, p2 - p1 - 1);
        b.artist = line.substr(p2 + 1, p3 - p2 - 1);
        b.year = line.substr(p3 + 1, p4 - p3 - 1);
        b.genre = line.substr(p4 + 1, p5 - p4 - 1);
        b.genre = line.substr(p5+1);
        albums.push_back(b);

        if (b.id >= nextId)nextId = b.id + 1;}
}

void addAlbum() {
    Album b;
    b.id = nextId++;
    cout << "\nEnter title: ";
    getline(cin, b.title);
    cout << "Enter artist: ";
    getline(cin, b.artist);
    cout << "Enter year: ";
    getline(cin, b.year);
    cout << "Enter Genre: ";
    getline(cin, b.genre);
    cout << "Enter Medium: ";
    getline(cin,b.medium);
    albums.push_back(b);

    saveDatabase();
    cout << "\nAlbum added with ID: " << b.id << "\n";
}

void searchAlbum() {
    string query;
    cout << "\nSearch Title, Artist or Genre: ";
    getline(cin, query);
    bool found = false;

    for (const auto& b : albums) {
        if (b.title.find(query) != string::npos ||
            b.artist.find(query) != string::npos ||
            b.genre.find(query) != string::npos) {

            cout << "\nID: " << b.id << "\n";
            cout << "Title: " << b.title << "\n";
            cout << "Artist: " << b.artist << "\n";
            cout << "Year: " << b.year << "\n";
            cout << "Genre: " << b.genre << "\n";
            cout << "Medium: " << b.medium << "\n";
            found = true;}
    }

    if (!found)
        cout << "No matches found.\n";
}

void editAlbum() {
    int id;
    cout << "\nEnter ID to edit: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (auto& b : albums) {
        if (b.id == id) {
            string input;

            cout << "New Title (leave blank to keep): ";
            getline(cin, input);
            if (!input.empty()) b.title = input;
            cout << "New Artist (leave blank to keep): ";
            getline(cin, input);
            if (!input.empty()) b.artist = input;
            cout << "New Print Year (leave blank to keep): ";
            getline(cin, input);
            if (!input.empty()) b.year = input;
            saveDatabase();
            cout << "Album updated.\n";
            return;
        }
    }

    cout << "Album not found.\n";}

void deleteAlbum() {
    int id;
    cout << "\nEnter ID to delete: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (size_t i = 0; i < albums.size(); i++) {
        if (albums[i].id == id) {
            albums.erase(albums.begin() + i);
            saveDatabase();
            cout << "Album deleted.\n";
            return;}
    }

    cout << "Album not found.\n";
}

void sortByTitle() {
    sort(albums.begin(), albums.end(),
        [](const Album& a, const Album& b) {return a.title < b.title;});
    cout << "Sorted by Title.\n";}
void sortByArtist() {
    sort(albums.begin(), albums.end(),
        [](const Album& a, const Album& b) {return a.artist < b.artist;});
    cout << "Sorted by Artist.\n";}
void sortByYear() {
    sort(albums.begin(), albums.end(),
        [](const Album& a, const Album& b) {return a.year < b.year;});
    cout << "Sorted by Print Year.\n";}
void sortByGenre() {
    sort(albums.begin(), albums.end(),
        [](const Album& a, const Album& b) {return a.genre < b.genre;});
    cout << "Sorted by Genre.\n";}

void viewAlbums() {
    if (albums.empty()) {cout << "\nNo albums found.\n";return;}
    int st;

    cout << "\n===== Library =====\n\n";    
    cout << "How would you prefer your albums sorted?\n";
    cout << "1. Sort by Title.\n2. Sort by Artist.\n3. Sort by Print Year.\n4. Sort by Genre.\n";
    cin >> st;
    
    switch (st){
		case 1:sortByTitle();break;
    	case 2:sortByArtist();break;
    	case 3:sortByYear();break;
    	case 4:sortByGenre();break;}

    for (const auto& b : albums) {
        cout << "\n\nID: " << b.id << "\n";
        cout << "Title: " << b.title << "\n";
        cout << "Artist: " << b.artist << "\n";
        cout << "Year: " << b.year << "\n";
        cout << "Genre: " << b.genre << "\n";
        cout << "Medium: " << b.medium << "\n";
        cout << "----------------------\n";}
}

void menu() {
    cout << "\n===========================\n";
    cout << "   Library System\n";
    cout << "===========================\n";
    cout << "Total Albums: " << albums.size() << "\n\n";
    cout << "1. Add Album\n";
    cout << "2. View Albums\n";
    cout << "3. Search Albums\n";
    cout << "4. Edit Album\n";
    cout << "5. Delete Album\n";
    cout << "6. Exit\n";
    cout << "Select option: ";}

// ================= MAIN =================
int main() {
    loadDatabase();
    int choice;

    while (true) {
        menu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: addAlbum(); break;
            case 2: viewAlbums(); break;
            case 3: searchAlbum(); break;
            case 4: editAlbum(); break;
            case 5: deleteAlbum(); break;
            case 6:saveDatabase();cout << "Goodbye.\n";return 0;
            default:cout << "Invalid option.\n";}
    }
}