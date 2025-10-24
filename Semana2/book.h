#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>

using std::string;
using std::array;

class Book
{
public:

    string title;
    string author;
    array<int, 13> isbn();

    Book();
    Book(string title, string author, array<int, 13> isbn);

    bool operator<(const Book& other) const;
};

#endif // BOOK_H
