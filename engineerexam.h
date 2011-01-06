#ifndef ENGINEEREXAM_H
#define ENGINEEREXAM_H

#include <QtGui/QMainWindow>

namespace Ui {
    class EngineerExam;
}

class EngineerExam : public QMainWindow
{
    Q_OBJECT

public:
    explicit EngineerExam(QWidget *parent = 0);
    ~EngineerExam();

private:
    Ui::EngineerExam *ui;
};

#endif // ENGINEEREXAM_H
