#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlTableModel>
#include "engineerexam.h"
#include "questionwidget.h"
#include "ui_engineerexam.h"

EngineerExam::EngineerExam(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EngineerExam) {
    ui->setupUi(this);

    qsrand(time(NULL));

    parseQuestions("/home/ppkt/Downloads/EngineerExamForm/questions.sqlite");
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
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(filename);
    if (!db.open()) {
	qCritical() << trUtf8("Nie można otworzyć bazy danych!");
    }

    QSqlTableModel question;
    question.setTable("Question");
    question.select();

    QSqlTableModel answers;
    answers.setTable("Answer");
    answers.select();

    QStringList qsl;

    int i = 0;
    while (question.canFetchMore()) {
	question.fetchMore();
	for (; i < question.rowCount(); ++i) {
	    qsl.clear();

	    quint32 id = question.record(i).value("Id").toUInt();
	    QString text = question.record(i).value("Text").toString();
	    Question q;
	    q.setId(id);
	    q.setQuestion(text);

	    answers.setFilter(QString("`id_Question` = %1").arg(id));
	    QString a1 = answers.record(0).value("Text").toString();
	    QString a2 = answers.record(1).value("Text").toString();
	    QString a3 = answers.record(2).value("Text").toString();
	    qsl << a1 << a2 << a3;
	    q.setCorrectAnswer(1);
	    q.setAnswers(qsl);
	    tmpList.append(q);
	}
    }
}

void EngineerExam::pickQuestions(unsigned amount) {
    if (!questionsList.isEmpty()) {
        questionsList.clear();
    }
    //Losujemy pytania
    unsigned count = 0;
    while (count < amount) {
	if (tmpList.isEmpty()) {
	    return;
	}
	int index = qrand() % tmpList.size();
        Question q = tmpList.at(index);
        if (!questionsList.contains(q)) {
            questionsList.append(q);
            ++count;
        }
    }
}

void EngineerExam::on_checkQuestions_clicked() {
    for (int i = 0; i < ui->stackedWidget->count(); ++i) {
	QuestionWidget *qw = static_cast<QuestionWidget*>(ui->stackedWidget->widget(i));
	qw->isSelectedAnswerCorrect();
    }
}

void EngineerExam::on_actionNowy_triggered() {
    pickQuestions(30);

    questionsAmount = questionsList.size();

    if (ui->stackedWidget->count() > 0) {
        for (int i = 0; i < ui->stackedWidget->count(); ++i) {
            QuestionWidget *qw = static_cast<QuestionWidget*>(ui->stackedWidget->widget(0));
            ui->stackedWidget->removeWidget(qw);
        }
    }

    for (unsigned i = 0; i < questionsAmount; ++i) {
        QuestionWidget *qw = new QuestionWidget();
        qw->setQuestion(i+1, questionsAmount, questionsList.at(i));
        ui->stackedWidget->addWidget(qw);
    }
    first_question();
}

void EngineerExam::first_question() {
    ui->stackedWidget->setCurrentIndex(0);
}
