Its provides a basic framework for managing a library system, including:


Book Management        : Adding, searching, and checking the availability of books.

Borrower Management    : Adding and managing borrower information.

Transaction Management : Checking out and returning books, calculating fines for overdue returns.


Key Features


Book Management                :     addBook(title, author, isbn): Adds a new book to the library.

Borrower Management            :     addBorrower(name, id): Adds a new borrower to the library.

Transaction Management         :     checkoutBook(isbn, borrowerId): Checks out a book to a borrower.

returnBook(isbn, borrowerId)   :     Returns a book and calculates any fines.

Book Search: searchBook(query) :     Searches for books by title, author, or ISBN.

