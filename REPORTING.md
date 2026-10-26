
#include <iostream>
#include <vector>
#include <string>
#include "Book.h"
#include "Member.h"
#include "Loan.h"

using namespace std;

// Display library statistics using the current records.
void displayLibraryReport(
    const vector<Book>& books,
    const vector<Member>& members,
    const vector<Loan>& loans
) {
    int availableBooks = 0;
    int issuedBooks = 0;

    for (const Book& book : books) {
        if (book.isAvailable()) {
            availableBooks++;
        } else {
            issuedBooks++;
        }
    }

    cout << "\n===== LIBRARY REPORT =====\n";
    cout << "Total books: " << books.size() << '\n';
    cout << "Available books: " << availableBooks << '\n';
    cout << "Issued books: " << issuedBooks << '\n';
    cout << "Registered members: " << members.size() << '\n';
    cout << "Active loan records: " << loans.size() << '\n';
    cout << "==========================\n";
}
