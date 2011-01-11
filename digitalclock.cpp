#include <QDebug>
#include <QTimer>
#include "digitalclock.h"

DigitalClock::DigitalClock(QWidget *parent) :
    QLCDNumber(parent) {
    setSegmentStyle(Filled);
}

void DigitalClock::start() {
    stop();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start(1000);

    endTime = QTime::currentTime().addSecs(5400);
    showTime();
}

void DigitalClock::stop() {
    if (timer) {
        delete timer;
    }
}

void DigitalClock::showTime() {
    QTime time = QTime::currentTime();

    int seconds = time.secsTo(endTime);
    QTime disp = QTime().addSecs(seconds);
//    disp.addSecs(seconds);

    QString text = disp.toString("hh:mm:ss");
//    qDebug() << disp;
//    if ((disp.second() % 2) == 0)
//	text[2] = ' ';
    display(text);
    update();
}
