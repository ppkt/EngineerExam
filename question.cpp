#include <algorithm>
#include "question.h"
Question::Question(quint32 id, QStringList lineFromFile) {
    setId(id);
    setQuestion(lineFromFile.takeFirst());
    setCorrectAnswer(lineFromFile.takeFirst().toUInt()-1);
    setAnswers(lineFromFile);
}

void Question::setAnswers(QStringList answers) {
    QString correctAnswerText = answers.at(correctAnswer);

    std::random_shuffle(answers.begin(), answers.end());

    this->answers = answers;
    this->correctAnswer = answers.indexOf(correctAnswerText);
}

bool Question::operator ==(const Question &second) const {
    if (second.getId() == this->getId()) {
        return true;
    } else if (second.getQuestion() == this->getQuestion()) {
        return true;
    } else {
        return false;
    }
}
