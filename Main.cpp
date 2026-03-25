#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>

using namespace std;

struct Book {
    string title;
    string author;
    string year;
    string genre;
};

vector<Book> books;
const string DATABASE_FILE = "library.txt";

/* void saveDatabase() {
    ofstream file(DATABASE_FILE);

    for (const auto& b : books) {
        file << b.title << endl;
        file << b.author << endl;
        file << b.year << endl;
        file << b.genre << endl;
        file << "----" << endl;
    }

    file.close();
} */

void saveDatabase() {
    ofstream file("library.txt");

    for (const auto& b : books) {
        file << b.title << "|" 
             << b.author << "|" 
             << b.year << "\n";
    }

    file.close();
}

/* void loadDatabase() {
    ifstream file(DATABASE_FILE);

    if (!file)
        return;

    Book b;
    string separator;

    while (getline(file, b.title)) {
        getline(file, b.author);
        getline(file, b.year);
        getline(file, b.genre);
        getline(file, separator);
        books.push_back(b);
    }

    file.close();
} */

void loadDatabase() {
    ifstream file("library.txt");

    if (!file)
        return;

    string line;

    while (getline(file, line)) {
        Book b;
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);

        if (pos1 == string::npos || pos2 == string::npos)
            continue; // skip bad lines

        b.title = line.substr(0, pos1);
        b.author = line.substr(pos1 + 1, pos2 - pos1 - 1);
        b.year = line.substr(pos2 + 1);

        books.push_back(b);
    }

    file.close();
}

void addBook() {
    Book b;

    cout << "\nEnter Book Title: ";
    getline(cin, b.title);

    cout << "Enter Author: ";
    getline(cin, b.author);

    cout << "Enter year of Printing: ";
    getline(cin, b.year);
    
    cout << "Enter Book Genre: ";
    getline(cin, b.genre);

    books.push_back(b);
    saveDatabase();

    cout << "\nBook added successfully.\n";
}

void viewBooks() {
    if (books.empty()) {
        cout << "\nNo books in library.\n";
        return;
    }

    cout << "\nLibrary Books:\n";
    cout << "------------------------\n";

    for (size_t i = 0; i < books.size(); i++) {
        cout << "Book #" << i + 1 << endl;
        cout << "Title: " << books[i].title << endl;
        cout << "Author: " << books[i].author << endl;
        cout << "Year: " << books[i].year << endl;
        cout << "Genre: " << books[i].genre << endl;
        cout << "------------------------\n";
    }
}

void searchBook() {
    string query;
    cout << "\nEnter title, author or genre to search: ";
    getline(cin, query);

    bool found = false;

    for (const auto& b : books) {
        if (b.title.find(query) != string::npos ||
            b.author.find(query) != string::npos ||
            b.genre.find(query) != string::npos) {

            cout << "\nMatch Found:\n";
            cout << "Title: " << b.title << endl;
            cout << "Author: " << b.author << endl;
            cout << "Year: " << b.year << endl;
            found = true;
        }
    }

    if (!found)
        cout << "\nNo matching books found.\n";
}

void deleteBook() {
    viewBooks();

    if (books.empty())
        return;

    int choice;
    cout << "\nEnter book number to delete: ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (choice < 1 || choice > books.size()) {
        cout << "Invalid selection.\n";
        return;
    }

    books.erase(books.begin() + (choice - 1));
    saveDatabase();

    cout << "Book deleted.\n";
}

void menu() {
    cout << "\n===== Library System =====\n";
    cout << "You have " << books.size() << " books recorded. \n";
    cout << "For better legibility, your database file is named " << DATABASE_FILE << ".\n\n";
    
    cout << "1. Add Book\n";
    cout << "2. View Books\n";
    cout << "3. Search Books\n";
    cout << "4. Delete Book\n";
    cout << "5. Save Database\n";
    cout << "6. Exit\n";
    cout << "Select option: ";
}

int main() {
    loadDatabase();

    int choice;

    while (true) {
        menu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                viewBooks();
                break;
            case 3:
                searchBook();
                break;
            case 4:
                deleteBook();
                break;
            case 5:
                saveDatabase();
                cout << "Database saved.\n";
                break;
            case 6:
                saveDatabase();
                cout << "Goodbye.\n";
                return 0;
            default:
                cout << "Invalid option.\n";
        }
    }
}
