#include "newgame.h"
#include "ui_newgame.h"

NewGame::NewGame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewGame)
{
    ui->setupUi(this);
}

NewGame::~NewGame()
{
    delete ui;
}

void NewGame::on_btnStart_clicked()
{
    int type = -1;
    if (ui->radioExam->isChecked()) {
        type = 0;
    } else if (ui->radioLearn->isChecked()) {
        type = 1;
    }
    emit start(type, ui->questionsAmount->value());
    this->close();
}
