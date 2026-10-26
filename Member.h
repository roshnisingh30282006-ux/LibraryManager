#pragma once
#include <string>
#include <vector>

class Member {
private:
    int id;
    std::string name;
    std::vector<int> borrowedBookIds;

public:
    Member(int memberId = 0, const std::string& memberName = "");
    int getId() const;
    std::string getName() const;
    const std::vector<int>& getBorrowedBookIds() const;
    bool hasBorrowed(int bookId) const;
    void borrowBook(int bookId);
    bool returnBook(int bookId);
    std::string toFileLine() const;
};
