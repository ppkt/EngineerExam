#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include "engineerexam.h"
#include "questionwidget.h"
#include "ui_engineerexam.h"

EngineerExam::EngineerExam(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EngineerExam) {
    ui->setupUi(this);

    questionsAmount = 30;

    parseQuestions("questions.txt");
    parseQuestions("questions.txt");

    pickQuestions(30);

    questionsAmount = questionsList.size();

    for (unsigned i = 0; i < questionsAmount; ++i) {
	QuestionWidget *qw = new QuestionWidget();
	qw->setQuestion(i+1, questionsAmount, questionsList.at(i));
	ui->stackedWidget->addWidget(qw);
    }

}

EngineerExam::~EngineerExam() {
    delete ui;
}

void EngineerExam::on_nextQuestion_clicked() {
    unsigned currentIndex = ui->stackedWidget->currentIndex();
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

void EngineerExam::parseQuestions(QString filename) {
    QFile questions(filename);

    QFileInfo info(questions);

    if (!info.isFile()) {
	qCritical() << trUtf8("Plik %1 jest niepoprawny").arg(filename);
	return;
    } else if (!info.isReadable()) {
	qCritical() << trUtf8("Plik %1 nie nadaje się do odczytu").arg(filename);
	return;
    } else if (!questions.open(QFile::Text | QFile::ReadOnly)) {
	qCritical() << trUtf8("Nie można otworzyć pliku %1 !").arg(filename);
	return;
    }

    QTextStream ts(&questions);
    quint32 id = 0;
    while (!ts.atEnd()) {
	QString line = ts.readLine();
	QStringList bum = line.split("|", QString::KeepEmptyParts);

	/**
	  * Uwaga - konstruktor klasy "Question" miesza odpowiedzi!
	  */
	Question q(++id, bum);
	tmpList.append(q);
    }
}

void EngineerExam::pickQuestions(unsigned amount) {
    //Losujemy pytania
    unsigned count = 0;
    qsrand(time(NULL));
    while (count < amount) {
	if (tmpList.isEmpty()) {
	    return;
	}
	int index = qrand() % tmpList.size();
	Question q = tmpList.takeAt(index);
	questionsList.append(q);
	++count;
    }
    tmpList.clear();
}

void EngineerExam::on_checkQuestions_clicked() {
    for (int i = 0; i < ui->stackedWidget->count(); ++i) {
	QuestionWidget *qw = static_cast<QuestionWidget*>(ui->stackedWidget->widget(i));
	qw->isSelectedAnswerCorrect();
    }
}
