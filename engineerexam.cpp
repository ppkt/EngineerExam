#include "engineerexam.h"
#include "questionwidget.h"
#include "ui_engineerexam.h"

EngineerExam::EngineerExam(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EngineerExam) {
    ui->setupUi(this);

    questionsAmount = 30;

    for (int i = 0; i < questionsAmount; ++i) {
	QuestionWidget *qw = new QuestionWidget();
	qw->setQuestion(trUtf8("Pytanie nr: %1").arg(i));
	qw->setQuestionId(i);

	QStringList list;
	list.append(trUtf8("Odpowiedź A do pytania %1").arg(i));
	list.append(trUtf8("Odpowiedź B do pytania %1").arg(i));
	list.append(trUtf8("Odpowiedź C do pytania %1").arg(i));

	qw->setAnswers(list);

	ui->stackedWidget->addWidget(qw);
    }
}

EngineerExam::~EngineerExam() {
    delete ui;
}

void EngineerExam::on_nextQuestion_clicked() {
    int currentIndex = ui->stackedWidget->currentIndex();
    int nextIndex;
    if ((currentIndex + 1) < questionsAmount) {
	nextIndex = currentIndex + 1;
    } else {
	nextIndex = 0;
    }
    ui->stackedWidget->setCurrentIndex(nextIndex);
}

void EngineerExam::on_prevQuestion_clicked() {
    int currentIndex = ui->stackedWidget->currentIndex();
    int nextIndex;
    if ((currentIndex - 1) >= 0) {
	nextIndex = currentIndex - 1;
    } else {
	nextIndex = questionsAmount - 1;
    }
    ui->stackedWidget->setCurrentIndex(nextIndex);
}
