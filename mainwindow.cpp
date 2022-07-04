#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "weapon.h"
#include "unit.h"
#include "squad.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    EditFile e({},{});
    e.read_file();
    unit_vec = e.get_vec_units();
    squads_vec = e.get_vec_squads();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::check_weapon(Weapon bolter)
{

}

void MainWindow::on_Battle_Button_clicked()
{
    ui_choice_army = new ChoiceArmy(nullptr, squads_vec);
    connect(ui_choice_army, &ChoiceArmy::firstWindow, this, &MainWindow::show);
    this->close();
    ui_choice_army->show();
}

void MainWindow::on_Choice_Squad_Button_clicked()
{
    ui_choice_squad = new ChoiceSquad(nullptr, &squads_vec, &unit_vec);
    connect(ui_choice_squad, &ChoiceSquad::firstWindow, this, &MainWindow::show);
    this->close();
    ui_choice_squad->show();
}

void MainWindow::on_exit_button_clicked()
{
    this->close();
}
