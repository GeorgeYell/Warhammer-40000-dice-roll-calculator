#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "choicearmy.h"
#include "choicesquad.h"
#include "squad.h"
#include "editfile.h"
QT_BEGIN_NAMESPACE

namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void check_weapon(Weapon bolter);

private slots:

    void on_Battle_Button_clicked();

    void on_Choice_Squad_Button_clicked();

    void on_pushButton_clicked();

    void on_exit_button_clicked();

private:
    Ui::MainWindow *ui;
    ChoiceArmy *ui_choice_army;
    ChoiceSquad *ui_choice_squad;

protected:
    QVector <Squad> squads_vec;
    QVector <Unit> unit_vec;


};
#endif // MAINWINDOW_H
