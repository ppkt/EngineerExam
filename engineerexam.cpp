#include "engineerexam.h"
#include "ui_engineerexam.h"

EngineerExam::EngineerExam(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EngineerExam)
{
    ui->setupUi(this);
}

EngineerExam::~EngineerExam()
{
    delete ui;
}
