#ifndef QUESTIONWIDGET_H
#define QUESTIONWIDGET_H

#include <QtGui/QWidget>
#include <QDataWidgetMapper>
#include <QPlainTextEdit>
#include <QRadioButton>
#include <QSqlTableModel>
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

    void setModel(QSqlTableModel* model);

public slots:
    void selectA();
    void selectB();
    void selectC();

private:
    quint16 correctAnswer;
    quint16 getSelectedAnswer();
    QPlainTextEdit* getSelectedWidget();
    QPlainTextEdit* getCorrectWidget();

    void setCorrectAnswer(quint16 correct) { this->correctAnswer = correct; }
    void setQuestionText(QString question);
    void setAnswers(QStringList answers);
    void setQuestionId(quint32 id) { this->questionId = id; }

    quint16 questionId;
    Ui::QuestionWidget *ui;
};

#endif // QUESTIONWIDGET_H
