#ifndef CHOICESQUAD_H
#define CHOICESQUAD_H

#include <QWidget>
#include <QListWidgetItem>
#include <QTableWidget>
#include <QList>
#include <QMainWindow>
#include "squad.h"
#include "fillsquad.h"
#include <QStatusBar>


namespace Ui {
class ChoiceSquad;
}

class ChoiceSquad : public QWidget
{
    Q_OBJECT

public:
    ChoiceSquad(QWidget *parent = nullptr, QVector <Squad> *vec_squads = {}, QVector <Unit> *vec_unit = {});
    ~ChoiceSquad();

    void close_tabs();
    void fill_lists ();
    int need_num_units (QListWidgetItem *item);
    int need_num_squads (QListWidgetItem *item);


signals:
    void firstWindow();

public slots:
    void update_window (QVector <Squad> *, QVector <Unit> *);

private slots:

    void on_Back_to_menu_button_clicked();
    void on_listUnits_clicked(const QModelIndex &index);
    void on_listSquads_itemClicked(QListWidgetItem *item);
    void on_listUnits_itemClicked(QListWidgetItem *item);
    void on_deleteSquadButton_clicked();
    void on_deleteUnitButton_clicked();
    void on_save_change_Button_clicked();
    void on_newUnitButton_clicked();
    void on_add_unit_button_clicked();
    void on_cancel_change_Button_clicked();
    void on_changeUnitButton_clicked();
    void on_cancel_button_clicked();
    void on_newSquadButton_clicked();

    void on_changeSquadButton_clicked();

private:
    Ui::ChoiceSquad *ui;
    QVector <Squad> *squads_vec;
    QVector <Unit> *units_vec;
    QVector <Weapon> vec_weapon;
    QListWidgetItem *item_squad;
    FillSquad *ui_fill_squad;
    int fun = 0;
    bool change = false;
    friend class FillSquad;
};

#endif // CHOICESQUAD_H
