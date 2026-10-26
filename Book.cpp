#include "Book.h"
#include <sstream>

Book::Book(int bookId, const std::string& bookTitle,
           const std::string& bookAuthor, bool isAvailable)
    : id(bookId), title(bookTitle), author(bookAuthor), available(isAvailable) {}

int Book::getId() const { return id; }
std::string Book::getTitle() const { return title; }
std::string Book::getAuthor() const { return author; }
bool Book::isAvailable() const { return available; }
void Book::setAvailable(bool value) { available = value; }

std::string Book::toFileLine() const {
    std::ostringstream out;
    out << id << '|' << title << '|' << author << '|' << (available ? 1 : 0);
    return out.str();
}
