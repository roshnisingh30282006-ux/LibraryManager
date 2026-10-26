#pragma once
#include <string>

class Book {
private:
    int id;
    std::string title;
    std::string author;
    bool available;

public:
    Book(int bookId = 0, const std::string& bookTitle = "",
         const std::string& bookAuthor = "", bool isAvailable = true);

    int getId() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    bool isAvailable() const;
    void setAvailable(bool value);
    std::string toFileLine() const;
};
