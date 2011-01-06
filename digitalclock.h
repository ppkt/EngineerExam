#ifndef DIGITALCLOCK_H
#define DIGITALCLOCK_H
#include <QTime>
#include <QLCDNumber>

class DigitalClock : public QLCDNumber
{
    Q_OBJECT
public:
    explicit DigitalClock(QWidget *parent = 0);

signals:

public slots:
    void start();
    void showTime();

private:
    QTime endTime;
};

#endif // DIGITALCLOCK_H
