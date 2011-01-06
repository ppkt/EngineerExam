#include <QtGui/QApplication>
#include "engineerexam.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EngineerExam w;
    w.show();

    return a.exec();
}
