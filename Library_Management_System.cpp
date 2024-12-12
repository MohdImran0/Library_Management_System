#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm> // Include this header for std::find

using namespace std;

// Class to represent a book in the library
class Book {
public:
    string title;
    string author;
    string ISBN;
    bool isAvailable;

    Book(string t, string a, string isbn) : title(t), author(a), ISBN(isbn), isAvailable(true) {}
};

// Class to represent a borrower
class Borrower {
public:
    string name;
    string id;
    vector<string> borrowedBooks;  // Store ISBNs of borrowed books

    Borrower(string borrowerName, string borrowerId) : name(borrowerName), id(borrowerId) {}
};

// Class to represent a transaction
class Transaction {
public:
    string bookISBN;
    string borrowerId;
    time_t checkoutDate;
    time_t returnDate;
    
    Transaction(string isbn, string id) {
        bookISBN = isbn;
        borrowerId = id;
        checkoutDate = time(0); // Current date and time
        returnDate = 0;  // Not returned yet
    }
    
    void returnBook() {
        returnDate = time(0);  // Return date is the current time
    }
    
    double calculateFine() {
        if (returnDate == 0) return 0.0;  // Not returned yet
        const double fineRatePerDay = 0.5;  // Fine rate per day
        double fine = 0.0;
        
        double daysOverdue = difftime(returnDate, checkoutDate) / (60 * 60 * 24);  // Convert seconds to days
        if (daysOverdue > 14) {  // 14 days borrow period
            fine = (daysOverdue - 14) * fineRatePerDay;
        }
        
        return fine;
    }
};

// Class to manage the library
class Library {
private:
    vector<Book> books;
    vector<Borrower> borrowers;
    vector<Transaction> transactions;

public:
    void addBook(string title, string author, string isbn) {
        books.push_back(Book(title, author, isbn));
    }

    void addBorrower(string name, string id) {
        borrowers.push_back(Borrower(name, id));
    }

    Book* findBookByISBN(string isbn) {
        for (auto &book : books) {
            if (book.ISBN == isbn) {
                return &book;
            }
        }
        return nullptr;  // Book not found
    }

    Borrower* findBorrowerById(string id) {
        for (auto &borrower : borrowers) {
            if (borrower.id == id) {
                return &borrower;
            }
        }
        return nullptr;  // Borrower not found
    }

    void checkoutBook(string isbn, string borrowerId) {
        Book* book = findBookByISBN(isbn);
        if (book && book->isAvailable) {
            Borrower* borrower = findBorrowerById(borrowerId);
            if (borrower) {
                book->isAvailable = false;
                borrower->borrowedBooks.push_back(isbn);
                transactions.push_back(Transaction(isbn, borrowerId));
                cout << "Book checked out successfully!" << endl;
            } else {
                cout << "Borrower not found!" << endl;
            }
        } else {
            cout << "Book is not available or doesn't exist." << endl;
        }
    }

    void returnBook(string isbn, string borrowerId) {
        Book* book = findBookByISBN(isbn);
        if (book && !book->isAvailable) {
            Borrower* borrower = findBorrowerById(borrowerId);
            if (borrower) {
                // Use std::find correctly to find the ISBN in the borrowedBooks vector
                auto it = find(borrower->borrowedBooks.begin(), borrower->borrowedBooks.end(), isbn);
                if (it != borrower->borrowedBooks.end()) {
                    borrower->borrowedBooks.erase(it);
                    book->isAvailable = true;
                    for (auto &transaction : transactions) {
                        if (transaction.bookISBN == isbn && transaction.borrowerId == borrowerId && transaction.returnDate == 0) {
                            transaction.returnBook();
                            double fine = transaction.calculateFine();
                            if (fine > 0) {
                                cout << "You have a fine of $" << fine << " for overdue days." << endl;
                            }
                            cout << "Book returned successfully!" << endl;
                            return;
                        }
                    }
                }
            } else {
                cout << "Borrower not found!" << endl;
            }
        } else {
            cout << "Book not found or not checked out!" << endl;
        }
    }

    void searchBook(string query) {
        bool found = false;
        for (auto &book : books) {
            if (book.title.find(query) != string::npos || book.author.find(query) != string::npos || book.ISBN.find(query) != string::npos) {
                cout << "Found book: " << book.title << " by " << book.author << ", ISBN: " << book.ISBN << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No books found matching the search criteria." << endl;
        }
    }
};

// Function to display menu
void displayMenu() {
    cout << "\nLibrary Management System" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Add Borrower" << endl;
    cout << "3. Checkout Book" << endl;
    cout << "4. Return Book" << endl;
    cout << "5. Search Book" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    Library library;

    // Sample Data (Optional)
    library.addBook("C++ Programming", "Bjarne Stroustrup", "978-0131103627");
    library.addBook("Data Structures", "Thomas Cormen", "978-0262033848");
    library.addBorrower("John Doe", "B123");
    library.addBorrower("Jane Smith", "B124");

    int choice;
    do {
        displayMenu();
        cin >> choice;
        cin.ignore();  // To clear the newline character after integer input

        switch (choice) {
        case 1: {
            string title, author, isbn;
            cout << "Enter book title: ";
            getline(cin, title);
            cout << "Enter book author: ";
            getline(cin, author);
            cout << "Enter ISBN: ";
            getline(cin, isbn);
            library.addBook(title, author, isbn);
            break;
        }
        case 2: {
            string name, id;
            cout << "Enter borrower name: ";
            getline(cin, name);
            cout << "Enter borrower ID: ";
            getline(cin, id);
            library.addBorrower(name, id);
            break;
        }
        case 3: {
            string isbn, borrowerId;
            cout << "Enter book ISBN: ";
            getline(cin, isbn);
            cout << "Enter borrower ID: ";
            getline(cin, borrowerId);
            library.checkoutBook(isbn, borrowerId);
            break;
        }
        case 4: {
            string isbn, borrowerId;
            cout << "Enter book ISBN: ";
            getline(cin, isbn);
            cout << "Enter borrower ID: ";
            getline(cin, borrowerId);
            library.returnBook(isbn, borrowerId);
            break;
        }
        case 5: {
            string query;
            cout << "Enter search query (title/author/ISBN): ";
            getline(cin, query);
            library.searchBook(query);
            break;
        }
        case 6:
            cout << "Exiting Library System. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice, please try again!" << endl;
        }
    } while (choice != 6);

    return 0;
}
