#ifndef QUESTION_H
#define QUESTION_H
#include <QString>
#include <QStringList>

class Question
{
public:
    Question() {}
    Question(quint32 id, QStringList lineFromFile);

    quint32 getId() const { return this->id; }
    quint16 getCorrectAnswer() const { return this->correctAnswer; }
    QString getQuestion() const { return this->question; }
    QStringList getAnswers() const { return this->answers; }

    void setId(quint32 id) { this->id = id; }
    void setQuestion(QString question) { this->question = question; }
    void setAnswers(QStringList answers);
    void setCorrectAnswer(quint16 correct) { this->correctAnswer = correct; }

    bool operator==(const Question& second) const;
private:
    quint32 id;
    QString question;
    QStringList answers;
    quint16 correctAnswer;
};

#endif // QUESTION_H
