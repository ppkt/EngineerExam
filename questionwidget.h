#ifndef QUESTIONWIDGET_H
#define QUESTIONWIDGET_H

#include <QtGui/QWidget>
#include <QRadioButton>
#include "question.h"

namespace Ui {
    class QuestionWidget;
}

class QuestionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QuestionWidget(QWidget *parent = 0);
    ~QuestionWidget();

    void setQuestion(int index, int max, Question q);
    quint32 getQuestionId() const { return this->questionId; }
    bool isSelectedAnswerCorrect();
private:
    quint16 correctAnswer;
    quint16 getSelectedAnswer();
    QRadioButton* getSelectedWidget();
    QRadioButton* getCorrectWidget();

    void setCorrectAnswer(quint16 correct) { this->correctAnswer = correct; }
    void setQuestionText(QString question);
    void setAnswers(QStringList answers);
    void setQuestionId(quint32 id) { this->questionId = id; }

    quint16 questionId;
    Ui::QuestionWidget *ui;
};

#endif // QUESTIONWIDGET_H
