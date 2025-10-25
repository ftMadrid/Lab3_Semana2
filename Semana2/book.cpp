#include "book.h"
#include <iostream>
#include <string>

using std::string;
using std::array;

Book::Book(string title, string author, array<int, 13> isbn) {
    this->title = title;
    this->author = author;
    this->isbn = isbn;
}

bool Book::operator<(const Book& other) const {

    if(title != other.title){
        return title < other.title;
    }
    if(author != other.author){
        return author < other.author;
    }

    return isbn < other.isbn;
}
