#include <QCoreApplication>
#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    cout << "Hello World!" <<endl;

    return a.exec();
}
