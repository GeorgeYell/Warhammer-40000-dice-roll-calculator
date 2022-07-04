#ifndef CHOICEWEAPON_H
#define CHOICEWEAPON_H

#include <QDialog>
#include <squad.h>
#include <QVector>

namespace Ui {
class ChoiceWeapon;
}

class ChoiceWeapon : public QDialog
{
    Q_OBJECT

public:
    explicit ChoiceWeapon(QWidget *parent = nullptr);
    ChoiceWeapon (QWidget *parent = nullptr, Squad *squad_need = nullptr, int n_units = 0, Squad *squad_full = nullptr);
    ~ChoiceWeapon();

    QVector <Weapon> need_weapons(Unit unit);
    void print_tabs();
    Unit unit_weapon(int n);

signals:
    void save(Squad *);

private slots:
    void on_cancelButton_clicked();

    void on_spinBoxOne_valueChanged(int arg1);

    void on_spinBoxTwo_valueChanged(int arg1);

    void on_spinBoxThree_valueChanged(int arg1);

    void on_spinBoxFour_valueChanged(int arg1);

    void on_acceptButton_clicked();



private:
    Ui::ChoiceWeapon *ui;
    QVector <int> count_weapon_units;
    QVector <Weapon> vec_weapon;
    Unit unit;
    Squad sqd;
    int n_units;
};

#endif // CHOICEWEAPON_H
