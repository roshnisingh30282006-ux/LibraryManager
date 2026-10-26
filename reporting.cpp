
#include "reporting.h"

void displayLibraryReport(
    const std::vector<Book>& books,
    const std::vector<Member>& members,
    const std::vector<Loan>& loans
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

    std::cout << "\n===== LIBRARY REPORT =====\n";
    std::cout << "Total books: " << books.size() << '\n';
    std::cout << "Available books: " << availableBooks << '\n';
    std::cout << "Issued books: " << issuedBooks << '\n';
    std::cout << "Registered members: " << members.size() << '\n';
    std::cout << "Active loan records: " << loans.size() << '\n';
    std::cout << "==========================\n";
}
