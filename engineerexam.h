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
    void on_nextQuestion_clicked();
    void on_prevQuestion_clicked();
    void on_checkQuestions_clicked();
    void on_actionNowy_triggered();
    void first_question();

private:
    QList<Question> questionsList;
    QList<Question> tmpList;
    unsigned questionsAmount;
    Ui::EngineerExam *ui;
};

#endif // ENGINEEREXAM_H
