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

void QuestionWidget::setQuestion(QString question) {
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

quint16 QuestionWidget::getSelectedAnswer() {
    if (ui->A->isChecked()) {
	return 0;
    } else if (ui->B->isChecked()) {
	return 1;
    } else {
	return 2;
    }
}
