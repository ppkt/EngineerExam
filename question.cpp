#include <algorithm>
#include "question.h"
Question::Question(quint32 id, QStringList lineFromFile) {
    this->id = id;
    this->question = lineFromFile.takeFirst();
    this->correctAnswer = lineFromFile.takeFirst().toUInt()-1;

    QString correctAnswerText = lineFromFile.at(correctAnswer);

    std::random_shuffle(lineFromFile.begin(), lineFromFile.end());

    this->answers = lineFromFile;
    this->correctAnswer = lineFromFile.indexOf(correctAnswerText);
}
