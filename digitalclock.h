#ifndef DIGITALCLOCK_H
#define DIGITALCLOCK_H
#include <QTime>
#include <QLCDNumber>
#include <QPointer>

class DigitalClock : public QLCDNumber
{
    Q_OBJECT
public:
    explicit DigitalClock(QWidget *parent = 0);

signals:

public slots:
    void start();
    void stop();
    void showTime();

private:
    QPointer<QTimer> timer;
    QTime endTime;
};

#endif // DIGITALCLOCK_H
