#ifndef FASEMORAL_H
#define FASEMORAL_H

#include <QDialog>
#include <battle.h>

namespace Ui {
class FaseMoral;
}

class FaseMoral : public QDialog
{
    Q_OBJECT

public:
    explicit FaseMoral(QWidget *parent = nullptr);
    FaseMoral(QWidget *parent = nullptr, Battle *bat = nullptr);
    ~FaseMoral();

private slots:
    void on_ok_button_clicked();

private:
    Ui::FaseMoral *ui;
    Battle *battle;
};

#endif // FASEMORAL_H
