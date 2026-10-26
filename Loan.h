#pragma once
#include <string>

class Loan {
private:
    int bookId;
    int memberId;
    std::string issueDate;

public:
    Loan(int book = 0, int member = 0, const std::string& date = "");
    int getBookId() const;
    int getMemberId() const;
    std::string getIssueDate() const;
    std::string toFileLine() const;
};
