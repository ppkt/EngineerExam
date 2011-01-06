#ifndef QUESTIONWIDGET_H
#define QUESTIONWIDGET_H

#include <QtGui/QWidget>

namespace Ui {
    class QuestionWidget;
}

class QuestionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QuestionWidget(QWidget *parent = 0);
    ~QuestionWidget();

    void setQuestion(QString question);
    void setAnswers(QStringList answers);
    void setQuestionId(quint32 id) { this->questionId = id; }

    quint32 getQuestionId() const { return this->questionId; }
    quint16 getSelectedAnswer();
private:
    quint16 questionId;
    Ui::QuestionWidget *ui;
};

#endif // QUESTIONWIDGET_H
