#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    int quantity;

    void inputData() {
        cout << "Enter Book ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Book Title: ";
        getline(cin, title);
        cout << "Enter Author Name: ";
        getline(cin, author);
        cout << "Enter Quantity: ";
        cin >> quantity;
    }

    void displayData() {
        cout << "ID: " << id << ", Title: " << title
             << ", Author: " << author << ", Quantity: " << quantity << endl;
    }
};

void addBook() {
    Book b;
    ofstream outFile("library.dat", ios::binary | ios::app);
    b.inputData();
    outFile.write(reinterpret_cast<char*>(&b), sizeof(b));
    outFile.close();
    cout << "Book added successfully.\n";
}

void displayBooks() {
    Book b;
    ifstream inFile("library.dat", ios::binary);
    cout << "\nList of Books:\n";
    while (inFile.read(reinterpret_cast<char*>(&b), sizeof(b))) {
        b.displayData();
    }
    inFile.close();
}

void searchBook(int id) {
    Book b;
    ifstream inFile("library.dat", ios::binary);
    bool found = false;
    while (inFile.read(reinterpret_cast<char*>(&b), sizeof(b))) {
        if (b.id == id) {
            cout << "\nBook Found:\n";
            b.displayData();
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Book with ID " << id << " not found.\n";
    }
    inFile.close();
}

void deleteBook(int id) {
    Book b;
    ifstream inFile("library.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);
    bool found = false;

    while (inFile.read(reinterpret_cast<char*>(&b), sizeof(b))) {
        if (b.id != id) {
            outFile.write(reinterpret_cast<char*>(&b), sizeof(b));
        } else {
            found = true;
        }
    }

    inFile.close();
    outFile.close();
    remove("library.dat");
    rename("temp.dat", "library.dat");

    if (found)
        cout << "Book deleted successfully.\n";
    else
        cout << "Book not found.\n";
}

void updateBook(int id) {
    Book b;
    fstream file("library.dat", ios::in | ios::out | ios::binary);
    bool found = false;

    while (file.read(reinterpret_cast<char*>(&b), sizeof(b))) {
        if (b.id == id) {
            cout << "Current Book Details:\n";
            b.displayData();
            cout << "Enter new details:\n";
            b.inputData();
            int pos = -1 * static_cast<int>(sizeof(b));
            file.seekp(pos, ios::cur);
            file.write(reinterpret_cast<char*>(&b), sizeof(b));
            cout << "Book updated successfully.\n";
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Book not found.\n";

    file.close();
}

int main() {
    int choice, id;

    do {
        cout << "\n----- Library Management System -----\n";
        cout << "1. Add Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Search Book by ID\n";
        cout << "4. Update Book\n";
        cout << "5. Delete Book\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addBook();
            break;
        case 2:
            displayBooks();
            break;
        case 3:
            cout << "Enter Book ID to search: ";
            cin >> id;
            searchBook(id);
            break;
        case 4:
            cout << "Enter Book ID to update: ";
            cin >> id;
            updateBook(id);
            break;
        case 5:
            cout << "Enter Book ID to delete: ";
            cin >> id;
            deleteBook(id);
            break;
        case 6:
            cout << "Exiting the program.\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}
