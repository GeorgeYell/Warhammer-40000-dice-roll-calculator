#ifndef ATTACKRESULT_H
#define ATTACKRESULT_H

#include <QDialog>
#include <QTableWidget>
#include "fight.h"


namespace Ui {
class AttackResult;
}

class AttackResult : public QDialog
{
    Q_OBJECT

public:
    explicit AttackResult(QWidget *parent = nullptr);
    AttackResult(QWidget *parent = nullptr, Fight *fight_obj = nullptr, Battle *bat = nullptr, int need_num_sqd = 0);
    ~AttackResult();

    void set_paint(bool hit, int i, int cow);
    void distance_attack();
    void close_attack();

signals:
    void set_battlefield();

private slots:
    void on_ok_button_clicked();

private:
    Ui::AttackResult *ui;
    Fight *fight;
    Battle *battle;
    int need_num_sqd;
};

#endif // ATTACKRESULT_H
