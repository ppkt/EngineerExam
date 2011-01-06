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
    ui->question->setText(question);
}

void QuestionWidget::setAnswers(QStringList answers) {
    if (answers.size() != 3) {
	qCritical() << trUtf8("Niepełna lista odpowiedzi!");
	return;
    }
    ui->A->setText(answers.at(0));
    ui->B->setText(answers.at(1));
    ui->C->setText(answers.at(2));
}

bool QuestionWidget::isSelectedAnswerCorrect() {
    QFont ok;
    ok.setPointSize(18);
    ok.setUnderline(true);

    QFont fail;
    fail.setPointSize(18);
    fail.setStrikeOut(true);

    quint16 selected = getSelectedAnswer();
    if (selected == correctAnswer) {
	QRadioButton* selected = getSelectedWidget();
	if (selected) {
	    selected->setFont(ok);
	}
	qDebug() << "OK";
	return true;
    } else {
	QRadioButton* selected = getSelectedWidget();
	if (selected) {
	    selected->setFont(fail);
	}
	QRadioButton* correct = getCorrectWidget();
	correct->setFont(ok);
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

QRadioButton* QuestionWidget::getSelectedWidget() {
    if (ui->A->isChecked()) {
	return ui->A;
    } else if (ui->B->isChecked()) {
	return ui->B;
    } else if (ui->C->isChecked()){
	return ui->C;
    } else {
	return 0;
    }
}

QRadioButton* QuestionWidget::getCorrectWidget() {
    if (correctAnswer == 0) {
	return ui->A;
    } else if (correctAnswer == 1) {
	return ui->B;
    } else if (correctAnswer == 2) {
	return ui->C;
    }
}
