#include <QCoreApplication>
#include <iostream>

#include "bookstore.h"
#include "book.h"
#include <string>
#include <array>
#include <stdexcept>
#include <limits>
#include <numeric>

using std::cout;
using std::endl;
using std::cin;
using std::array;
using std::string;
using std::getline;

#define print cout <<
#define ln << endl
#define set cin >>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    BookStore store;
    int option = 0;

    string title, author, isbnString;

    do{

        print "\n === BOOK STORE === \n" ln;
        print "1. Insert Book" ln;
        print "2. Search by title" ln;
        print "3. Search by ISBN" ln;
        print "4. Show Catalogue" ln;
        print "5. Show the Audit Log" ln;
        print "6. Exit\n" ln;

        print "| Choose an option: ";
        set option;

        switch(option){
        case 1: {

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            print "\n === INSERT BOOK === \n" ln;
            print "| Set the title: ";
            getline(cin, title);
            print "\n| Set the author: ";
            getline(cin, author);
            print "\n| Set the ISBN code (13 digits): ";
            getline(cin, isbnString);

            try {
                array<int, 13> isbn = store.stringToIsbnArray(isbnString);
                store.insertBook(Book(title, author, isbn));
                print "\n| The book " << title << " has been inserted!" ln;
            } catch (const std::invalid_argument& e) {
                print e.what() ln;
            }

            break;
        }
        case 2: {
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            print "\n === SEARCH BY TITLE === \n" ln;
            print "| Enter title to search: ";
            getline(cin, title);

            int index_title = store.searchBookByTitle(title);
            if (index_title != -1) {
                print "\n| Book FOUND at [" << index_title << "]: " << store.catalogue[index_title].title << " by " << store.catalogue[index_title].author ln;
            } else {
                print "\n| Book NOT FOUND: " << title ln;
            }
            break;
        }
        case 3: {
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            print "\n === SEARCH BY ISBN === \n" ln;
            print "\n| Enter 13-digit ISBN: ";
            getline(cin, isbnString);

            int index_isbn = store.searchBookByISBN(isbnString);
            if (index_isbn != -1) {
                print "\n| Book FOUND at [" << index_isbn << "]: " << store.catalogue[index_isbn].title << " by " << store.catalogue[index_isbn].author ln;
            } else {
                print "\n| ISBN NOT FOUND or Invalid Format: " << isbnString ln;
            }
            break;
        }
        case 4:
            store.showCatalogue();
            break;
        case 5:
            store.showAuditLog();
            break;
        case 6:
            print "\n| Have a great day!" ln;
            break;
        default:
            print "\n| This option doesnt exists!" ln;
            break;
        }

    }while(option != 6);

    return a.exec();
}
