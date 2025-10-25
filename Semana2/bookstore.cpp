#include "bookstore.h"
#include "book.h"

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <array>
#include <chrono>
#include <iomanip>
#include <sstream>

using std::sort;
using std::cout;
using std::endl;
using std::isdigit;
using std::vector;
using std::localtime;
using std::put_time;
using std::stringstream;

#define print cout <<
#define ln << endl

BookStore::BookStore() {}

string BookStore::arrayIsbnToString(const std::array<int, 13>& isbnArray) {
    stringstream tmp;
    for (int digit : isbnArray) {
        tmp << digit;
    }
    return tmp.str();
}

array<int, 13> BookStore::stringToIsbnArray(const string& input) {
    if (input.length() != 13) {
        throw std::invalid_argument("\n| ISBN must have 13 digits.");
    }

    array<int, 13> isbnArray{};
    for (int i = 0; i < 13; ++i) {
        if (!isdigit(input[i])) {
            throw std::invalid_argument("\n| ISBN should only have digits.");
        }
        isbnArray[i] = input[i] - '0';
    }
    return isbnArray;
}

void BookStore::insertBook(Book b){

    catalogue.push_back(b);

    sort(catalogue.begin(), catalogue.end());

    audit.push_front("\n| Book Added: " + b.title);
}

int BookStore::searchBookByTitle(string title){
    int low = 0;
    int high = catalogue.size() - 1;
    int result = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (catalogue[mid].title == title) {
            result = mid;
            break;
        } else if (catalogue[mid].title < title) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    if (result != -1) {
        audit.push_front("\n| Search by title: " + title + " - FOUND. [" + this->getCurrentTimestamp() + "]");
    } else {
        audit.push_front("\n| Search by title: " + title + " - NOT FOUND. [" + this->getCurrentTimestamp() + "]");
    }
    return result;
}

int BookStore::searchBookByISBN(string isbn){

    array<int, 13> targetIsbn;

    try {
        targetIsbn = stringToIsbnArray(isbn);
    } catch (const std::invalid_argument& e) {
        audit.push_front("\n| Search by ISBN: Invalid format! " + string(e.what()));
        return -1; // found this catch format at overflow, amazing way to check a format of this typo inge!
    }

    vector<int> sortedIndexs = sortIndexByIsbn(catalogue);

    int low = 0;
    int high = sortedIndexs.size() - 1;
    int resultIndexInCatalogue = -1;

    while (low <= high) {
        int mid_idx = low + (high - low) / 2;
        int realIndex = sortedIndexs[mid_idx];

        if (std::equal(catalogue[realIndex].isbn.begin(), catalogue[realIndex].isbn.end(), targetIsbn.begin())) {
            resultIndexInCatalogue = realIndex;
            break;
        } else if (catalogue[realIndex].isbn < targetIsbn) {
            low = mid_idx + 1;
        } else {
            high = mid_idx - 1;
        }
    }

    string timestamp = getCurrentTimestamp();
    if (resultIndexInCatalogue != -1) {
        audit.push_front("\n| Search by ISBN: " + isbn + " FOUND! " + timestamp);
    } else {
        audit.push_front("\n| Search by ISBN: " + isbn + " NOT FOUND! " + timestamp);
    }

    return resultIndexInCatalogue;
}

vector<int> BookStore::sortIndexByIsbn(const vector<Book>& books){

    vector<int> indexs(books.size());

    for (int i = 0; i < books.size(); ++i) {
        indexs[i] = (int)i;
    }

    sort(indexs.begin(), indexs.end(), [&books](int a, int b) {
        return books[a].isbn < books[b].isbn;
    });

    return indexs;
}

string BookStore::getCurrentTimestamp(){
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto local = localtime(&now);

    std::stringstream tmp;

    tmp << put_time(local, "%c");

    return tmp.str();
}

void BookStore::showAuditLog() const {
    cout << "\n === Audit Log ===" ln;
    if (audit.empty()) {
        cout << "\n| Log is empty!" ln;
    }
    for (const auto& logs : audit) {
        cout << logs ln;
    }
}

void BookStore::showCatalogue() const {
    cout << "\n === Book Catalogue ===\n" ln;
    if (catalogue.empty()) {
        cout << "\n| Catalogue is empty!" ln;
    }
    for (int i = 0; i < catalogue.size(); ++i) {
        cout << i << ". " << catalogue[i].title << " by " << catalogue[i].author << " (ISBN: ";
        for(int d : catalogue[i].isbn) cout << d;
        cout << ")" ln;
    }
}


