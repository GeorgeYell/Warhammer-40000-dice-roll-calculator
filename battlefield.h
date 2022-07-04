#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include <QWidget>
#include <QListWidgetItem>
#include <QTableWidget>
#include <QMessageBox>
#include <battle.h>
#include "fasemoral.h"
#include "attackresult.h"
#include "fight.h"

namespace Ui {
class Battlefield;
}

class Battlefield : public QWidget
{
    Q_OBJECT

public:
    explicit Battlefield(QWidget *parent = nullptr);
    Battlefield(QWidget *parent = nullptr, Battle *bat = nullptr);
    ~Battlefield();

    void fill_weapon_table(QVector <Squad> squads_vec, QListWidgetItem *item);
    int need_num_squads(QVector <Squad> squads_vec, QListWidgetItem *item);
    void fill_unit_table (QVector <Squad> squads_vec, QListWidgetItem *item);
    void set_spins_unit(Squad *ptr_squad, int i);
    void set_spins_weapon(QVector <int> quant, int i);
    void reset_spins_unit();
    void reset_spins_weapon();
    bool check_vec_weapon(QVector <Weapon> vec_weapon, Weapon weapon);
    void reset_labels();
    bool check_type_speed(int n);
    QVector <Weapon> fill_vec_weapons(QVector <Unit> *units, Squad sqd);
    QVector <Unit> fill_vec_units();

signals:
    void firstWindow();

public slots:
    void update_window();

private slots:
    void on_PlayerOneList_itemClicked(QListWidgetItem *item);
    void on_PlayerTwoList_itemClicked(QListWidgetItem *item);
    void on_back_button_clicked();
    void on_fase_button_clicked();
    void on_attack_button_clicked();


private:
    Ui::Battlefield *ui;
    Battle *battle;
    FaseMoral *ui_fase_moral;
    AttackResult *ui_attack_result;
    int count_fill;
};

#endif // BATTLEFIELD_H
