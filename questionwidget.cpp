#include <QDebug>
#include "questionwidget.h"
#include "ui_questionwidget.h"

QuestionWidget::QuestionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuestionWidget) {
    ui->setupUi(this);
}

QuestionWidget::~QuestionWidget() {
    delete ui;
}

void QuestionWidget::setQuestion(int index, int max, Question q) {
    setQuestionId(q.getId());
    setAnswers(q.getAnswers());
    setQuestionText(trUtf8("Pytanie nr %1 z %2.\n%3")
		    .arg(index)
		    .arg(max)
		    .arg(q.getQuestion()));
    setCorrectAnswer(q.getCorrectAnswer());
}

void QuestionWidget::setQuestionText(QString question) {
    ui->text->setPlainText(question);
}

void QuestionWidget::setAnswers(QStringList answers) {
    if (answers.size() != 3) {
	qCritical() << trUtf8("Niepełna lista odpowiedzi!");
	return;
    }
    ui->ALabel->setPlainText(answers.at(0));
    ui->BLabel->setPlainText(answers.at(1));
    ui->CLabel->setPlainText(answers.at(2));
}

bool QuestionWidget::isSelectedAnswerCorrect() {

    ui->A->setDisabled(true);
    ui->B->setDisabled(true);
    ui->C->setDisabled(true);

    quint16 selected = getSelectedAnswer();
    if (selected == correctAnswer) {
	QPlainTextEdit* selected = getSelectedWidget();
	if (selected) {
            selected->setStyleSheet("QPlainTextEdit { border:  2px solid grey; border-radius: 10px; padding: 0 8px; background: green; }");
	}
	qDebug() << "OK";
	return true;
    } else {
	QPlainTextEdit* selected = getSelectedWidget();
        if (selected) {
            selected->setStyleSheet("QPlainTextEdit { border:  2px solid grey; border-radius: 10px; padding: 0 8px; background: red; }");
	}
        QPlainTextEdit* correct = getCorrectWidget();
        correct->setStyleSheet("QPlainTextEdit { border:  2px solid grey; border-radius: 10px; padding: 0 8px; background: green; }");
	qDebug() << "Nieok";
	return false;
    }
}

quint16 QuestionWidget::getSelectedAnswer() {
    if (ui->A->isChecked()) {
        return 0;
    } else if (ui->B->isChecked()) {
        return 1;
    } else if (ui->C->isChecked()){
        return 2;
    } else {
	return 999;
    }
}

QPlainTextEdit* QuestionWidget::getSelectedWidget() {
    if (ui->A->isChecked()) {
	return ui->ALabel;
    } else if (ui->B->isChecked()) {
	return ui->BLabel;
    } else if (ui->C->isChecked()){
	return ui->CLabel;
    } else {
	return 0;
    }
}

QPlainTextEdit* QuestionWidget::getCorrectWidget() {
    if (correctAnswer == 0) {
	return ui->ALabel;
    } else if (correctAnswer == 1) {
	return ui->BLabel;
    } else if (correctAnswer == 2) {
	return ui->CLabel;
    }
    return 0;
}
