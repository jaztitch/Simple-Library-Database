#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <algorithm>

using namespace std;

struct Book {int id;string title;string author;string year;string genre;string isbn;string shelf;};

vector<Book> books;
int nextId = 1;
const string DATABASE_FILE = "bookLibrary.txt";

void saveDatabase() {
    ofstream file(DATABASE_FILE);

    for (const auto& b : books) {
        file << b.id << "|"
             << b.title << "|"
             << b.author << "|"
             << b.year << "|"
             << b.genre << "\n";}
			 }

void loadDatabase() {
    ifstream file(DATABASE_FILE);
    if (!file) return;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        Book b;
        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);
        size_t p4 = line.find('|', p3 + 1);
        if (p1 == string::npos || p2 == string::npos || p3 == string::npos || p4 == string::npos)continue;
        try {b.id = stoi(line.substr(0, p1));} catch (...) {continue;}

        b.title = line.substr(p1 + 1, p2 - p1 - 1);
        b.author = line.substr(p2 + 1, p3 - p2 - 1);
        b.year = line.substr(p3 + 1, p4 - p3 - 1);
        b.genre = line.substr(p4 + 1);
        books.push_back(b);

        if (b.id >= nextId)nextId = b.id + 1;}
}

void addBook() {
    Book b;
    b.id = nextId++;
    cout << "\nEnter title: ";
    getline(cin, b.title);
    cout << "Enter author: ";
    getline(cin, b.author);
    cout << "Enter year: ";
    getline(cin, b.year);
    cout << "Enter Genre: ";
    getline(cin, b.genre);
    books.push_back(b);
    saveDatabase();
    cout << "\nBook added with ID: " << b.id << "\n";
}

void searchBook() {
    string query;
    cout << "\nSearch Title, Author or Genre: ";
    getline(cin, query);
    bool found = false;

    for (const auto& b : books) {
        if (b.title.find(query) != string::npos ||
            b.author.find(query) != string::npos ||
            b.genre.find(query) != string::npos) {

            cout << "\nID: " << b.id << "\n";
            cout << "Title: " << b.title << "\n";
            cout << "Author: " << b.author << "\n";
            cout << "Year: " << b.year << "\n";
            cout << "Genre: " << b.genre << "\n";
            found = true;}
    }

    if (!found)
        cout << "No matches found.\n";
}

void editBook() {
    int id;
    cout << "\nEnter ID to edit: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (auto& b : books) {
        if (b.id == id) {
            string input;

            cout << "New Title (leave blank to keep): ";
            getline(cin, input);
            if (!input.empty()) b.title = input;
            cout << "New Author (leave blank to keep): ";
            getline(cin, input);
            if (!input.empty()) b.author = input;
            cout << "New Print Year (leave blank to keep): ";
            getline(cin, input);
            if (!input.empty()) b.year = input;
            saveDatabase();
            cout << "Book updated.\n";
            return;
        }
    }

    cout << "Book not found.\n";}

void deleteBook() {
    int id;
    cout << "\nEnter ID to delete: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (size_t i = 0; i < books.size(); i++) {
        if (books[i].id == id) {
            books.erase(books.begin() + i);
            saveDatabase();
            cout << "Book deleted.\n";
            return;}
    }

    cout << "Book not found.\n";
}

void sortByTitle() {
    sort(books.begin(), books.end(),
        [](const Book& a, const Book& b) {return a.title < b.title;});
    cout << "Sorted by Title.\n";}
void sortByAuthor() {
    sort(books.begin(), books.end(),
        [](const Book& a, const Book& b) {return a.author < b.author;});
    cout << "Sorted by Author.\n";}
void sortByYear() {
    sort(books.begin(), books.end(),
        [](const Book& a, const Book& b) {return a.year < b.year;});
    cout << "Sorted by Print Year.\n";}
void sortByGenre() {
    sort(books.begin(), books.end(),
        [](const Book& a, const Book& b) {return a.genre < b.genre;});
    cout << "Sorted by Genre.\n";}

void viewBooks() {
    if (books.empty()) {cout << "\nNo books found.\n";return;}
    int st;

    cout << "\n===== Library =====\n\n";    
    cout << "How would you prefer your books sorted?\n";
    cout << "1. Sort by Title.\n2. Sort by Author.\n3. Sort by Print Year.\n4. Sort by Genre.\n";
    cin >> st;
    
    switch (st){
		case 1:sortByTitle();break;
    	case 2:sortByAuthor();break;
    	case 3:sortByYear();break;
    	case 4:sortByGenre();break;}

    for (const auto& b : books) {
        cout << "\n\nID: " << b.id << "\n";
        cout << "Title: " << b.title << "\n";
        cout << "Author: " << b.author << "\n";
        cout << "Year: " << b.year << "\n";
        cout << "Genre: " << b.genre << "\n";
        cout << "----------------------\n";}
}

void menu() {
    cout << "\n===========================\n";
    cout << "   Library System\n";
    cout << "===========================\n";
    cout << "Total Books: " << books.size() << "\n\n";
    cout << "1. Add Book\n";
    cout << "2. View Books\n";
    cout << "3. Search Books\n";
    cout << "4. Edit Book\n";
    cout << "5. Delete Book\n";
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
            case 1: addBook(); break;
            case 2: viewBooks(); break;
            case 3: searchBook(); break;
            case 4: editBook(); break;
            case 5: deleteBook(); break;
            case 6:saveDatabase();cout << "Goodbye.\n";return 0;
            default:cout << "Invalid option.\n";}
    }
}