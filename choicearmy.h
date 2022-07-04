#ifndef CHOICEARMY_H
#define CHOICEARMY_H

#include <QWidget>
#include <QListWidgetItem>
#include <QTableWidget>
#include <QList>
#include <QMainWindow>
#include "battle.h"
#include "choiceweapon.h"
#include "battlefield.h"

namespace Ui {
class ChoiceArmy;
}

class ChoiceArmy : public QWidget
{
    Q_OBJECT

public:
    explicit ChoiceArmy(QWidget *parent = nullptr, QVector <Squad> squads = {});
    ~ChoiceArmy();

    int need_num_units (QListWidgetItem *item);
    int need_num_squads (QListWidgetItem *item);
    void fill_tabs (QListWidgetItem *item);
    bool check_weapon(QListWidgetItem *item);
    Squad need_unit (QListWidgetItem *item);

signals:
    void firstWindow();  // Сигнал для первого окна на открытие

public slots:
    void add_squad_one (Squad *);
    void add_squad_two (Squad *);
    void update_window ();

private slots:
    void on_pushButton_clicked();
    void on_back_choice_clicked();
    void on_push_back_menu_clicked();
    void on_button_add_weapon_clicked();
    void on_ButtonGun_clicked();
    void on_listWidget_itemActivated(QListWidgetItem *item);
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void on_listWidget_clicked(const QModelIndex &index);
    void on_listWidget_itemPressed(QListWidgetItem *item);
    void on_tableUnit_itemChanged(QTableWidgetItem *item);

    void on_add_player_one_button_clicked();

    void on_add_player_one_button_2_clicked();

    void on_del_player_one_button_clicked();

    void on_add_player_two_button_clicked();

    void on_del_player_two_button_clicked();

    void on_PlayerOneList_itemClicked(QListWidgetItem *item);

    void on_PlayerTwoList_itemClicked(QListWidgetItem *item);

    void on_battle_button_clicked();

    void on_go_battle_button_clicked();

private:
    Ui::ChoiceArmy *ui;
    QVector <Squad> squads_vec;
    QVector <Weapon> vec_weapon;
    ChoiceWeapon *ui_choice_weapon;
    Battlefield *ui_battlefield;
    QVector <Squad> player_one_vec;
    QVector <Squad> player_two_vec;
};

#endif // CHOICEARMY_H
