#include "Loan.h"
#include <sstream>

Loan::Loan(int book, int member, const std::string& date)
    : bookId(book), memberId(member), issueDate(date) {}

int Loan::getBookId() const { return bookId; }
int Loan::getMemberId() const { return memberId; }
std::string Loan::getIssueDate() const { return issueDate; }

std::string Loan::toFileLine() const {
    std::ostringstream out;
    out << bookId << '|' << memberId << '|' << issueDate;
    return out.str();
}
