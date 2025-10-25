#ifndef BOOKSTORE_H
#define BOOKSTORE_H

#include "book.h"

#include <vector>
#include <list>
#include <string>
#include <array>

using std::vector;
using std::list;
using std::string;
using std::array;

class BookStore
{
public:

    vector<Book> catalogue;
    list<string> audit;

    BookStore();
    string arrayIsbnToString(const std::array<int, 13>& isbnArray);
    void insertBook(Book b);
    int searchBookByTitle(string title);
    int searchBookByISBN(string isbn);
    vector<int> sortIndexByIsbn(const vector<Book>&);
    array<int, 13> stringToIsbnArray(const string& input);
    string getCurrentTimestamp();
    void showAuditLog() const;
    void showCatalogue() const;
};

#endif // BOOKSTORE_H
