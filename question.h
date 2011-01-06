#ifndef QUESTION_H
#define QUESTION_H
#include <QString>
#include <QStringList>

class Question
{
public:
    Question(quint32 id, QStringList lineFromFile);

    quint32 getId() const { return this->id; }
    quint16 getCorrectAnswer() const { return this->correctAnswer; }
    QString getQuestion() const { return this->question; }
    QStringList getAnswers() const { return this->answers; }

private:
    quint32 id;
    QString question;
    QStringList answers;
    quint16 correctAnswer;
};

#endif // QUESTION_H
