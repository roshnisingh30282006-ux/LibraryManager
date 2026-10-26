#include "Member.h"
#include <algorithm>
#include <sstream>

Member::Member(int memberId, const std::string& memberName)
    : id(memberId), name(memberName) {}

int Member::getId() const { return id; }
std::string Member::getName() const { return name; }
const std::vector<int>& Member::getBorrowedBookIds() const { return borrowedBookIds; }

bool Member::hasBorrowed(int bookId) const {
    return std::find(borrowedBookIds.begin(), borrowedBookIds.end(), bookId) != borrowedBookIds.end();
}

void Member::borrowBook(int bookId) {
    if (!hasBorrowed(bookId)) borrowedBookIds.push_back(bookId);
}

bool Member::returnBook(int bookId) {
    auto it = std::find(borrowedBookIds.begin(), borrowedBookIds.end(), bookId);
    if (it == borrowedBookIds.end()) return false;
    borrowedBookIds.erase(it);
    return true;
}

std::string Member::toFileLine() const {
    std::ostringstream out;
    out << id << '|' << name << '|';
    for (std::size_t i = 0; i < borrowedBookIds.size(); ++i) {
        if (i) out << ',';
        out << borrowedBookIds[i];
    }
    return out.str();
}
