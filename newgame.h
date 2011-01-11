#ifndef NEWGAME_H
#define NEWGAME_H

#include <QWidget>

namespace Ui {
    class NewGame;
}

class NewGame : public QWidget
{
    Q_OBJECT

public:
    explicit NewGame(QWidget *parent = 0);
    ~NewGame();

signals:
    void start(int, int);

private slots:
    void on_btnStart_clicked();

private:
    Ui::NewGame *ui;
};

#endif // NEWGAME_H
