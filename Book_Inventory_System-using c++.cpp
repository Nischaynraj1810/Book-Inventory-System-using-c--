#include <iostream>
#include <string>
using namespace std;

class Book {
private:
    string title;
    string author;
    int id;
    int quantity;
public:
    Book(string title, string author, int id, int quantity) {
        this->title = title;
        this->author = author;
        this->id = id;
        this->quantity = quantity;
    }

    string getTitle() { return title; }
    string getAuthor() { return author; }
    int getId() { return id; }
    int getQuantity() { return quantity; }
    void setQuantity(int quantity) { this->quantity = quantity; }
};

class BookShop {
private:
    Book** books;  
    int size;
public:
    BookShop(int size) {
        this->size = size;
        books = new Book*[size];
        for (int i = 0; i < size; i++) {
            books[i] = nullptr;
        }
    }

    void addBook(string title, string author, int id, int quantity) {
        for (int i = 0; i < size; i++) {
            if (books[i] != nullptr && books[i]->getId() == id) {
                books[i]->setQuantity(books[i]->getQuantity() + quantity);
                cout << "Book quantity updated successfully!" << endl;
                return;
            }
        }
        for (int i = 0; i < size; i++) {
            if (books[i] == nullptr) {
                books[i] = new Book(title, author, id, quantity);  
                cout << "Book added successfully!" << endl;
                return;
            }
        }
        cout << "No space available to add new book!" << endl;
    }

    void removeBook(int id) {
        for (int i = 0; i < size; i++) {
            if (books[i] != nullptr && books[i]->getId() == id) {
                delete books[i];  
                books[i] = nullptr;
                cout << "Book removed successfully!" << endl;
                return;
            }
        }
        cout << "Book not found!" << endl;
    }

    void purchaseBook(int id) {
        for (int i = 0; i < size; i++) {
            if (books[i] != nullptr && books[i]->getId() == id) {
                int quantityAvailable = books[i]->getQuantity();
                if (quantityAvailable > 0) {
                    int quantityToPurchase;
                    cout << "Enter the number of copies to purchase: ";
                    cin >> quantityToPurchase;

                    if (quantityToPurchase <= quantityAvailable) {
                        books[i]->setQuantity(quantityAvailable - quantityToPurchase);
                        cout << "Book(s) purchased successfully!" << endl;
                    } else {
                        cout << "Only " << quantityAvailable << " copies are available." << endl;
                    }
                } else {
                    cout << "Book is out of stock!" << endl;
                }
                return;
            }
        }
        cout << "Book not found!" << endl;
    }

    void searchBook(int id) {
        for (int i = 0; i < size; i++) {
            if (books[i] != nullptr && books[i]->getId() == id) {
                cout << "Book Title: " << books[i]->getTitle() << endl;
                cout << "Book Author: " << books[i]->getAuthor() << endl;
                cout << "Book Quantity: " << books[i]->getQuantity() << endl;
                return;
            }
        }
        cout << "Book not found!" << endl;
    }

    void displayBooks() {
        for (int i = 0; i < size; i++) {
            if (books[i] != nullptr) {
                cout << "Book Title: " << books[i]->getTitle() << endl;
                cout << "Book Author: " << books[i]->getAuthor() << endl;
                cout << "Book ID: " << books[i]->getId() << endl;
                cout << "Book Quantity: " << books[i]->getQuantity() << endl;
                cout << endl;
            }
        }
    }

    ~BookShop() {
        for (int i = 0; i < size; i++) {
            if (books[i] != nullptr) {
                delete books[i];  
            }
        }
        delete[] books;  
    }
};

int main() {
    BookShop bookShop(10);

    while (true) {
        cout << "Book Shop Inventory System" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Remove Book" << endl;
        cout << "3. Purchase Book" << endl;
        cout << "4. Search Book" << endl;
        cout << "5. Display Books" << endl;
        cout << "6. Exit" << endl;

        int choice;
        cout << "\n Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string title, author;
                int id, quantity;
                cout << "Enter book title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter book author: ";
                getline(cin, author);
                cout << "Enter book ID: ";
                cin >> id;
                cout << "Enter book quantity: ";
                cin >> quantity;
                bookShop.addBook(title, author, id, quantity);
                break;
            }
            case 2: {
                int id;
                cout << "Enter book ID to remove: ";
                cin >> id;
                bookShop.removeBook(id);
                break;
            }
            case 3: {
                int id;
                cout << "Enter book ID to purchase: ";
                cin >> id;
                bookShop.purchaseBook(id);
                break;
            }
            case 4: {
                int id;
                cout << "Enter book ID to search: ";
                cin >> id;
                bookShop.searchBook(id);
                break;
            }
            case 5: {
                bookShop.displayBooks();
                break;
            }
            case 6: {
                return 0;
            }
            default: {
                cout << "Invalid choice. Please choose a valid option." << endl;
                break;
            }
        }
    }
    return 0;
}
