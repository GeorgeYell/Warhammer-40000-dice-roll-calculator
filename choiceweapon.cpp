#include "choiceweapon.h"
#include "ui_choiceweapon.h"
#include <QMessageBox>

ChoiceWeapon::ChoiceWeapon(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChoiceWeapon)
{

}

ChoiceWeapon::ChoiceWeapon(QWidget *parent, Squad *squad_need, int n_unit, Squad *squad_full ) :
    QDialog(parent),
    ui(new Ui::ChoiceWeapon)
{
    ui->setupUi(this);
    n_units = n_unit;
    ui->tableWeapon->setColumnWidth(0, 370);
    ui->tableWeapon->setColumnWidth(1, 45);
    ui->tableWeapon->setColumnWidth(2, 150);
    ui->tableWeapon->setColumnWidth(3, 20);
    ui->tableWeapon->setColumnWidth(4, 20);
    ui->tableWeapon->setColumnWidth(5, 20);
    ui->tableWeapon->setColumnWidth(6, 144);
    ui->spinBoxOne->setMaximum(n_units);
    ui->spinBoxTwo->setMaximum(n_units);
    ui->spinBoxThree->setMaximum(n_units);
    ui->spinBoxFour->setMaximum(n_units);
    ui->tableWeapon->setEditTriggers(QAbstractItemView::NoEditTriggers);
    sqd = *squad_full;
    unit = squad_need->get_unit(0);
    ui->name_squad_label->setText("<html><head/><body><p align=center><span style= font-size:11pt;>" +
                                  unit.get_name_unit() + "</span></p></body></html>");

    vec_weapon = need_weapons(unit);

    if (vec_weapon.size() < 3)
    {
        ui->spinBoxFour->setEnabled(false);
        ui->spinBoxThree->setEnabled(false);
    } else if (vec_weapon.size() < 4)
    {
         ui->spinBoxFour->setEnabled(false);
    }

    print_tabs();
}

ChoiceWeapon::~ChoiceWeapon()
{
    delete ui;
}

void ChoiceWeapon::on_cancelButton_clicked()
{
    this->close();
}

QVector <Weapon> ChoiceWeapon::need_weapons(Unit unit)
{
    QVector <Weapon> weapons = unit.get_vec_weapons();
    QVector <Weapon> need_weapon ={};
    for (int j = 0; weapons.size() > 1 && j < weapons.size();j++)
    {
        if (j < weapons.size() - 1 && weapons[j].get_type() == weapons[j + 1].get_type())
        {
            need_weapon.push_back(weapons[j]);
        }
        else if (j == weapons.size() - 1 && weapons[j].get_type() == weapons[0].get_type())
        {
             need_weapon.push_back(weapons[j]);
        }
    }
    return need_weapon;
}

void ChoiceWeapon::print_tabs()
{
    //Наполнение таблицы Оружия значениями выбранного отряда
    ui->tableWeapon->clear();
    for (int i = 0; i < vec_weapon.size(); i++)
    {
        QTableWidgetItem *t_name = new QTableWidgetItem (vec_weapon[i].get_name_weapon());
        ui->tableWeapon->setItem(i, 0, t_name);

        QTableWidgetItem *t_dist = new QTableWidgetItem (QString("%1").arg(vec_weapon[i].get_distance()));
        ui->tableWeapon->setItem(i, 1, t_dist);

        QTableWidgetItem *t_type = new QTableWidgetItem (vec_weapon[i].get_type());
        ui->tableWeapon->setItem(i, 2, t_type);

        QTableWidgetItem *t_S = new QTableWidgetItem (QString("%1").arg(vec_weapon[i].get_S()));
        ui->tableWeapon->setItem(i, 3, t_S);

        QTableWidgetItem *t_B = new QTableWidgetItem (QString("%1").arg(vec_weapon[i].get_B()));
        ui->tableWeapon->setItem(i, 4, t_B);

        QTableWidgetItem *t_U = new QTableWidgetItem (QString("%1").arg(vec_weapon[i].get_U()));
        ui->tableWeapon->setItem(i, 5, t_U);

        QTableWidgetItem *t_abil = new QTableWidgetItem (vec_weapon[i].get_abilities());
        ui->tableWeapon->setItem(i, 6, t_abil);

    }

    //Установить значения ячеек по центру (только для заполненных)
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 7; j++)
        {
            if (j != 0 && ui->tableWeapon->item(i,j) != 0)
                ui->tableWeapon->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }
}

void ChoiceWeapon::on_spinBoxOne_valueChanged(int arg1)
{
    ui->spinBoxTwo->setMaximum(n_units - arg1);
    ui->spinBoxThree->setMaximum(n_units - arg1);
    ui->spinBoxFour->setMaximum(n_units - arg1);
}

void ChoiceWeapon::on_spinBoxTwo_valueChanged(int arg1)
{
    ui->spinBoxOne->setMaximum(n_units - arg1);
    ui->spinBoxThree->setMaximum(n_units - arg1);
    ui->spinBoxFour->setMaximum(n_units - arg1);
}

void ChoiceWeapon::on_spinBoxThree_valueChanged(int arg1)
{
    ui->spinBoxTwo->setMaximum(n_units - arg1);
    ui->spinBoxOne->setMaximum(n_units - arg1);
    ui->spinBoxFour->setMaximum(n_units - arg1);
}

void ChoiceWeapon::on_spinBoxFour_valueChanged(int arg1)
{
    ui->spinBoxTwo->setMaximum(n_units - arg1);
    ui->spinBoxThree->setMaximum(n_units - arg1);
    ui->spinBoxOne->setMaximum(n_units - arg1);
}

Unit ChoiceWeapon::unit_weapon(int n)
{
    Unit un = unit;
    QVector <Weapon> weapon_del;

    //Наполнение вектора оружия для удаления
    for (int j = 0; j < vec_weapon.size(); j++)
    {
        if (j != n)
        {
            weapon_del.push_back(vec_weapon[j]);
        }
    }

    //Удаление ненужного оружия у юнита
    for (int j = 0; j < weapon_del.size(); j++)
    {
        for (int l = 0; l < unit.get_size_vec_weapon(); l++)
        {          
            if (weapon_del[j].get_name_weapon() == unit.get_vec_weapons()[l].get_name_weapon())
            {
                un.del_weapon(l);
            }
        }
    }
    return un;
}

void ChoiceWeapon::on_acceptButton_clicked()
{
    bool err = false;
    QString err_msg = "";
    int one, two, three, four;
    one = ui->spinBoxOne->value();
    two = ui->spinBoxTwo->value();
    three = ui->spinBoxThree->value();
    four = ui->spinBoxFour->value();

    if ((one + two + three + four) != n_units)
    {
        err = true;
        err_msg = "Вы выбрали оружие не для всех юнитов!";
    }

    if (!err)
    {
        //Удаление всех юнитов со спорным оружием
        int count_del = 0;
        int num_del = 0;
        for (int i = 0; i < sqd.get_vec_units().size(); i++)
        {
            Unit un = unit;
            if (sqd.get_unit(i).get_name_unit() == un.get_name_unit())
            {
                sqd.del_unit(i);
                i -= 1;
                count_del += 1;
            }
        }

        for (int i = 0; i < sqd.get_size_vec_num_ind_unit(); i++)
        {
            if (count_del == sqd.get_num_ind_unit(i))
                num_del = i;
        }

        //Добавление юнитов в отряд с нужным оружием
        for (int i = 0; i < n_units; i++)
        {
            if (i < one)
            {
                sqd.insert_unit(sqd.get_num_ind_unit(num_del), i, unit_weapon(0));
            } else if (i < one + two)
            {
               sqd.insert_unit(sqd.get_num_ind_unit(num_del), i, unit_weapon(1));
            }else if (i < one + two + three)
            {
                sqd.insert_unit(sqd.get_num_ind_unit(num_del), i, unit_weapon(2));
            }else if (i < one + two + three + four)
            {
                sqd.insert_unit(sqd.get_num_ind_unit(num_del), i, unit_weapon(3));
            }
        }
        Squad *sqd_ptr = new Squad ();
        *sqd_ptr = sqd;

        emit save(sqd_ptr);
        this->close();
    }
    else
    {
        QMessageBox msg_err;
        msg_err.setText("Ошибка ввода!");
        msg_err.setInformativeText(err_msg);
        msg_err.setStandardButtons(QMessageBox::Ok);
        msg_err.setDefaultButton(QMessageBox::Ok);
        msg_err.setIcon(QMessageBox::Warning);
        msg_err.exec();
    }



}


