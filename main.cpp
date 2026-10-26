#include "Book.h"
#include "Member.h"
#include "Loan.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

class LibraryManager {
private:
    std::vector<Book> books;
    std::vector<Member> members;
    std::vector<Loan> loans;
    const std::string booksFile = "books.txt";
    const std::string membersFile = "members.txt";
    const std::string loansFile = "loans.txt";

    static std::string trim(const std::string& value) {
        const auto first = value.find_first_not_of(" \t\r\n");
        if (first == std::string::npos) return "";
        const auto last = value.find_last_not_of(" \t\r\n");
        return value.substr(first, last - first + 1);
    }

    static bool parseInt(const std::string& text, int& value) {
        std::istringstream in(trim(text));
        char extra;
        if (!(in >> value) || (in >> extra)) return false;
        return true;
    }

    static int readInt(const std::string& prompt) {
        while (true) {
            std::cout << prompt;
            std::string line;
            if (!std::getline(std::cin, line)) {
                std::cout << "\nInput ended. Exiting safely.\n";
                std::exit(0);
            }
            int value;
            if (parseInt(line, value)) return value;
            std::cout << "Invalid input. Please enter a whole number.\n";
        }
    }

    static std::string readRequiredText(const std::string& prompt) {
        while (true) {
            std::cout << prompt;
            std::string value;
            if (!std::getline(std::cin, value)) {
                std::cout << "\nInput ended. Exiting safely.\n";
                std::exit(0);
            }
            value = trim(value);
            if (value.empty() || value.find('|') != std::string::npos) {
                std::cout << "Input cannot be empty or contain '|'. Try again.\n";
            } else {
                return value;
            }
        }
    }

    Book* findBook(int id) {
        for (auto& book : books) if (book.getId() == id) return &book;
        return nullptr;
    }

    Member* findMember(int id) {
        for (auto& member : members) if (member.getId() == id) return &member;
        return nullptr;
    }

    void loadData() {
        std::ifstream bf(booksFile);
        std::string line;
        while (std::getline(bf, line)) {
            std::istringstream in(line);
            std::string idText, title, author, availableText;
            if (std::getline(in, idText, '|') && std::getline(in, title, '|') &&
                std::getline(in, author, '|') && std::getline(in, availableText)) {
                int id, available;
                if (parseInt(idText, id) && parseInt(availableText, available) && id > 0)
                    books.emplace_back(id, title, author, available == 1);
            }
        }

        std::ifstream mf(membersFile);
        while (std::getline(mf, line)) {
            std::istringstream in(line);
            std::string idText, name, ids;
            if (std::getline(in, idText, '|') && std::getline(in, name, '|') &&
                std::getline(in, ids)) {
                int id;
                if (!parseInt(idText, id) || id <= 0) continue;
                Member member(id, name);
                std::istringstream idStream(ids);
                std::string part;
                while (std::getline(idStream, part, ',')) {
                    int bookId;
                    if (parseInt(part, bookId) && bookId > 0) member.borrowBook(bookId);
                }
                members.push_back(member);
            }
        }

        std::ifstream lf(loansFile);
        while (std::getline(lf, line)) {
            std::istringstream in(line);
            std::string bookText, memberText, date;
            if (std::getline(in, bookText, '|') && std::getline(in, memberText, '|') &&
                std::getline(in, date)) {
                int bookId, memberId;
                if (parseInt(bookText, bookId) && parseInt(memberText, memberId))
                    loans.emplace_back(bookId, memberId, date);
            }
        }
    }

    void saveData() const {
        std::ofstream bf(booksFile);
        for (const auto& book : books) bf << book.toFileLine() << '\n';
        std::ofstream mf(membersFile);
        for (const auto& member : members) mf << member.toFileLine() << '\n';
        std::ofstream lf(loansFile);
        for (const auto& loan : loans) lf << loan.toFileLine() << '\n';
        if (!bf || !mf || !lf) std::cout << "Warning: one or more data files could not be saved.\n";
    }

    void addBook() {
        int id = readInt("Book ID (positive number): ");
        if (id <= 0 || findBook(id)) {
            std::cout << "Book ID must be positive and unique.\n";
            return;
        }
        std::string title = readRequiredText("Title: ");
        std::string author = readRequiredText("Author: ");
        books.emplace_back(id, title, author, true);
        saveData();
        std::cout << "Book added successfully.\n";
    }

    void addMember() {
        int id = readInt("Member ID (positive number): ");
        if (id <= 0 || findMember(id)) {
            std::cout << "Member ID must be positive and unique.\n";
            return;
        }
        std::string name = readRequiredText("Member name: ");
        members.emplace_back(id, name);
        saveData();
        std::cout << "Member added successfully.\n";
    }

    void listBooks() const {
        if (books.empty()) {
            std::cout << "No books found. Add a book first.\n";
            return;
        }
        std::cout << "\n--- Books ---\n";
        for (const auto& b : books) {
            std::cout << "ID: " << b.getId() << " | " << b.getTitle()
                      << " | Author: " << b.getAuthor()
                      << " | " << (b.isAvailable() ? "Available" : "Issued") << '\n';
        }
    }

    void listMembers() const {
        if (members.empty()) {
            std::cout << "No members found. Add a member first.\n";
            return;
        }
        std::cout << "\n--- Members ---\n";
        for (const auto& m : members) {
            std::cout << "ID: " << m.getId() << " | " << m.getName()
                      << " | Borrowed books: " << m.getBorrowedBookIds().size() << '\n';
        }
    }

    void searchBook() const {
        std::string query = readRequiredText("Enter book title or ID: ");
        int id;
        if (parseInt(query, id)) {
            for (const auto& b : books) if (b.getId() == id) {
                std::cout << b.getTitle() << " by " << b.getAuthor() << " — "
                          << (b.isAvailable() ? "Available" : "Issued") << '\n';
                return;
            }
        } else {
            std::string lowered = query;
            std::transform(lowered.begin(), lowered.end(), lowered.begin(),
                           [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
            for (const auto& b : books) {
                std::string title = b.getTitle();
                std::transform(title.begin(), title.end(), title.begin(),
                               [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
                if (title.find(lowered) != std::string::npos) {
                    std::cout << "ID: " << b.getId() << " | " << b.getTitle()
                              << " | " << b.getAuthor() << " | "
                              << (b.isAvailable() ? "Available" : "Issued") << '\n';
                    return;
                }
            }
        }
        std::cout << "Book not found.\n";
    }

    void issueBook() {
        int bookId = readInt("Book ID to issue: ");
        int memberId = readInt("Member ID: ");
        Book* book = findBook(bookId);
        Member* member = findMember(memberId);
        if (!book) { std::cout << "Book not found.\n"; return; }
        if (!member) { std::cout << "Member not found.\n"; return; }
        if (!book->isAvailable()) { std::cout << "That book is already issued.\n"; return; }
        book->setAvailable(false);
        member->borrowBook(bookId);
        std::string date = readRequiredText("Issue date (YYYY-MM-DD): ");
        loans.emplace_back(bookId, memberId, date);
        saveData();
        std::cout << "Book issued successfully.\n";
    }

    void returnBook() {
        int bookId = readInt("Book ID to return: ");
        int memberId = readInt("Member ID: ");
        Book* book = findBook(bookId);
        Member* member = findMember(memberId);
        if (!book) { std::cout << "Book not found.\n"; return; }
        if (!member) { std::cout << "Member not found.\n"; return; }
        if (book->isAvailable() || !member->returnBook(bookId)) {
            std::cout << "This member does not have that issued book.\n";
            return;
        }
        book->setAvailable(true);
        loans.erase(std::remove_if(loans.begin(), loans.end(), [=](const Loan& loan) {
            return loan.getBookId() == bookId && loan.getMemberId() == memberId;
        }), loans.end());
        saveData();
        std::cout << "Book returned successfully.\n";
    }

public:
    LibraryManager() { loadData(); }

    void run() {
        while (true) {
            std::cout << "\n====== LIBRARY MANAGER ======\n"
                      << "1. Add book\n2. Add member\n3. List books\n4. List members\n"
                      << "5. Search book\n6. Issue book\n7. Return book\n0. Save and exit\n";
            int choice = readInt("Choose an option: ");
            switch (choice) {
                case 1: addBook(); break;
                case 2: addMember(); break;
                case 3: listBooks(); break;
                case 4: listMembers(); break;
                case 5: searchBook(); break;
                case 6: issueBook(); break;
                case 7: returnBook(); break;
                case 0: saveData(); std::cout << "Data saved. Goodbye!\n"; return;
                default: std::cout << "Invalid menu choice. Choose 0-7.\n";
            }
        }
    }
};

int main() {
    LibraryManager app;
    app.run();
    return 0;
}
