#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <algorithm>
#include <ctime>
#include "engineerexam.h"
#include "newgame.h"
#include "questionwidget.h"
#include "ui_engineerexam.h"

EngineerExam::EngineerExam(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EngineerExam) {
    ui->setupUi(this);

    this->addAction(ui->actionA);
    this->addAction(ui->actionB);
    this->addAction(ui->actionC);
    this->addAction(ui->actionNext);
    this->addAction(ui->actionPrev);
    this->addAction(ui->actionCheck);

    qsrand(time(NULL));
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

	    bool correct1 = answers.record(0).value("IsTrue").toBool();
	    bool correct2 = answers.record(1).value("IsTrue").toBool();
	    bool correct3 = answers.record(2).value("IsTrue").toBool();

	    if (correct1) {
		q.setCorrectAnswer(0);
	    } else if (correct2) {
		q.setCorrectAnswer(1);
	    } else if (correct3) {
		q.setCorrectAnswer(2);
	    }
	    q.setAnswers(qsl);
	    tmpList.append(q);
	}
    }
}

void EngineerExam::pickQuestions(int amount) {
    if (!questionsList.isEmpty()) {
        questionsList.clear();
    }
    std::random_shuffle(tmpList.begin(), tmpList.end());
    //Losujemy pytania
    int count = 0;
    while (count < amount) {
	if (tmpList.isEmpty()) {
	    return;
	}
        if (tmpList.size() < count) {
            return;
        }
        Question q = tmpList.at(count);
        questionsList.append(q);
        ++count;
    }
}

void EngineerExam::on_checkQuestions_clicked() {
    if (this->type == 1) {
        QuestionWidget *qw = static_cast<QuestionWidget*>(ui->stackedWidget->currentWidget());
        qw->isSelectedAnswerCorrect();
        return;
    }
    int correct = 0;
    for (int i = 0; i < ui->stackedWidget->count(); ++i) {
	QuestionWidget *qw = static_cast<QuestionWidget*>(ui->stackedWidget->widget(i));
	correct += qw->isSelectedAnswerCorrect();
    }
    double percent = (correct * 1.0) / (questionsList.size() * 1.0) * 100;


    qDebug() << correct;
    ui->timer->stop();

    if (type == 0) {
        QMessageBox::information(0, trUtf8("Wynik"),
                                 trUtf8("Odpowiedziałeś poprawnie na %1 z %2 pytań. Procentowo to %3. Otrzymujesz %4.")
                                 .arg(correct)
                                 .arg(questionsList.count())
                                 .arg(percent)
                                 .arg(grade(percent)));
    }

}

void EngineerExam::on_actionNowy_triggered() {
    if (filename.isEmpty()) {
        filename = QFileDialog::getOpenFileName(this,
                                                trUtf8("Otwórz bazę pytań"),
                                                QDir::currentPath(),
                                                trUtf8("Baza danych (*.sqlite)"));
        if (!filename.isEmpty()) {
            parseQuestions(filename);
        }
    }

    if (!filename.isEmpty()) {
        NewGame *ng = new NewGame;
        ng->show();
        connect(ng, SIGNAL(start(int,int)), this, SLOT(start(int,int)));
    }
}

void EngineerExam::start(int type, int amount) {
    this->type = type;
    if (type == 0) {
        ui->timer->start();
    }

    pickQuestions(amount);

    questionsAmount = questionsList.size();

    while (ui->stackedWidget->count() > 0) {
        QuestionWidget *qw = static_cast<QuestionWidget*>(ui->stackedWidget->widget(0));
        ui->stackedWidget->removeWidget(qw);
    }

    for (int i = 0; i < questionsAmount; ++i) {
        QuestionWidget *qw = new QuestionWidget();
        qw->setQuestion(i+1, questionsAmount, questionsList.at(i));
        ui->stackedWidget->addWidget(qw);
    }
    first_question();
}

void EngineerExam::first_question() {
    ui->stackedWidget->setCurrentIndex(0);
}

void EngineerExam::on_actionA_triggered() {
    QuestionWidget *qw = static_cast<QuestionWidget*>(ui->stackedWidget->currentWidget());
    if (qw == 0) {
        return;
    }
    qw->selectA();
}

void EngineerExam::on_actionB_triggered() {
    QuestionWidget *qw = static_cast<QuestionWidget*>(ui->stackedWidget->currentWidget());
    if (qw == 0) {
        return;
    }
    qw->selectB();
}

void EngineerExam::on_actionC_triggered() {
    QuestionWidget *qw = static_cast<QuestionWidget*>(ui->stackedWidget->currentWidget());
    if (qw == 0) {
        return;
    }
    qw->selectC();
}

void EngineerExam::on_actionNext_triggered() {
    ui->nextQuestion->click();
}

void EngineerExam::on_actionPrev_triggered() {
    ui->prevQuestion->click();
}

void EngineerExam::on_actionCheck_triggered() {
    ui->checkQuestions->click();
}

double EngineerExam::grade(double percent) {
    if (percent < 50) {
        return 2.0;
    } else if (percent <= 60) {
        return 3.0;
    } else if (percent <= 70) {
        return 3.5;
    } else if (percent <= 80) {
        return 4.0;
    } else if (percent <= 90) {
        return 4.5;
    } else {
        return 5.0;
    }
}
