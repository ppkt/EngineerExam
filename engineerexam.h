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

private slots:
    void on_nextQuestion_clicked();

    void on_prevQuestion_clicked();

private:
    int questionsAmount;
    Ui::EngineerExam *ui;
};

#endif // ENGINEEREXAM_H
