#ifndef ENGINEEREXAM_H
#define ENGINEEREXAM_H

#include <QtGui/QMainWindow>
#include "question.h"

namespace Ui {
    class EngineerExam;
}

class EngineerExam : public QMainWindow
{
    Q_OBJECT

public:
    explicit EngineerExam(QWidget *parent = 0);
    ~EngineerExam();
    void parseQuestions (QString filename);
    void pickQuestions(unsigned amount);

private slots:
    void on_actionCheck_triggered();
    void on_nextQuestion_clicked();
    void on_prevQuestion_clicked();
    void on_checkQuestions_clicked();
    void on_actionNowy_triggered();
    void first_question();
    void start(int type, int amount);
    void on_actionA_triggered();
    void on_actionB_triggered();
    void on_actionC_triggered();
    void on_actionNext_triggered();
    void on_actionPrev_triggered();

private:
    QList<Question> questionsList;
    QList<Question> tmpList;
    QString filename;
    double grade(double percent);
    unsigned questionsAmount;
    unsigned type;
    Ui::EngineerExam *ui;
};

#endif // ENGINEEREXAM_H
