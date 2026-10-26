
#pragma once

#include <iostream>
#include <vector>
#include "Book.h"
#include "Member.h"
#include "Loan.h"

void displayLibraryReport(
    const std::vector<Book>& books,
    const std::vector<Member>& members,
    const std::vector<Loan>& loans
);
