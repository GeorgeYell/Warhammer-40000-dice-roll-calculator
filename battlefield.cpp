#include "battlefield.h"
#include "ui_battlefield.h"

Battlefield::Battlefield(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Battlefield)
{
    ui->setupUi(this);
}

Battlefield::Battlefield(QWidget *parent, Battle *bat) :
    QWidget(parent),
    ui(new Ui::Battlefield)
{
     ui->setupUi(this);


     //Настройка отображения таблицы юнитов и оружия
     {
     ui->tableUnit->setColumnWidth(0, 499);

     for (int i = 1; i < 10; i++)
     {
         ui->tableUnit->setColumnWidth(i, 20);
     }
     ui->tableUnit->setEditTriggers(QAbstractItemView::NoEditTriggers);
     ui->tableWeapon->setEditTriggers(QAbstractItemView::NoEditTriggers);
     ui->tableWeapon->setColumnWidth(0, 380);
     ui->tableWeapon->setColumnWidth(1, 45);
     ui->tableWeapon->setColumnWidth(2, 150);
     ui->tableWeapon->setColumnWidth(3, 20);
     ui->tableWeapon->setColumnWidth(4, 20);
     ui->tableWeapon->setColumnWidth(5, 20);
     ui->tableWeapon->setColumnWidth(6, 104);
     }
     battle = bat;
     battle->set_n_player(1);
     battle->set_fase(0);


    //Заполнение  списков
     for (int i = 0; i < battle->get_size_vec_command_one(); i++)
     {
         ui->PlayerOneList->addItem(battle->get_vec_com_one()[i].get_name());
     }
     for (int i = 0; i < battle->get_size_vec_command_two(); i++)
     {
         ui->PlayerTwoList->addItem(battle->get_vec_com_two()[i].get_name());
     }

     ui->PlayerOneList->setCurrentRow(0);
     ui->PlayerTwoList->setCurrentRow(0);
     reset_labels();
     fill_unit_table(bat->get_vec_com_two(), ui->PlayerTwoList->currentItem());
     fill_weapon_table(bat->get_vec_com_one(), ui->PlayerOneList->currentItem());


}

Battlefield::~Battlefield()
{
    delete ui;
}

int Battlefield::need_num_squads(QVector <Squad> squads_vec, QListWidgetItem *item)
{
    //Поиск совпадений имен из списка с вектором
    QString name = item->text();
    for(int i = 0; i < squads_vec.size(); i++)
        if (squads_vec.value(i).get_name() == name)
            return i; // индекс нужного отряда
    return -1;
}

bool Battlefield::check_vec_weapon(QVector <Weapon> vec_weapon, Weapon weapon)
{
    for (int i = 0; i < vec_weapon.size(); i++)
    {
        if (vec_weapon[i].get_name_weapon() == weapon.get_name_weapon())
        {
            return true;
        }
    }
    return false;
}

void Battlefield::reset_labels()
{
    ui->num_player_label->setText("<html><head/><body><p align=center><span style= font-size:10pt;>Ход игрока №" +
                                  QString::number(battle->get_n_player()) +"</span></p></body></html>");
    if (battle->get_fase() == 0)
    {
        ui->fase_label->setText("<html><head/><body><p align=center><span style= font-size:10pt;>Фаза</span></p><p align=center><span style=font-size:10pt;>СТРЕЛЬБЫ</span></p></body></html>");
    }
    else
    {
        ui->fase_label->setText("<html><head/><body><p align=center><span style= font-size:10pt;>Фаза</span></p><p align=center><span style=font-size:10pt;>СРАЖЕНИЯ</span></p></body></html>");
    }
    if (battle->get_n_player() == 1)
    {
        ui->_atack_label->setText(ui->PlayerOneList->currentItem()->text());
        ui->name_defence_label->setText(ui->PlayerTwoList->currentItem()->text());
    }
    else
    {
        ui->_atack_label->setText(ui->PlayerTwoList->currentItem()->text());
        ui->name_defence_label->setText(ui->PlayerOneList->currentItem()->text());
    }

}

bool Battlefield::check_type_speed(int n)
{
    for (int j = 0; j < 10; j++)
    {
        QString str = "Скорострельное";
        if (ui->tableWeapon->item(n, 2)->text()[j] != str[j])
        {
            return false;
        }
    }
    return true;
}

QVector<Weapon> Battlefield::fill_vec_weapons(QVector <Unit> *units, Squad sqd)
{
    QVector <Weapon> weapons = {};
    int one, two, three, four, one_un, two_un;
    one = ui->spinBoxOne->value();
    two = ui->spinBoxTwo->value();
    three = ui->spinBoxThree->value();
    four = ui->spinBoxFour->value();
    one_un = ui->spinBoxUnitOne->value();
    two_un = ui->spinBoxUnitTwo->value();

    int sum;
    if (count_fill == 0)
        sum = one + two + three + four;
    else
        sum = one_un + two_un;

    int num = 0;
    int need_num = need_num_squads(battle->get_vec_com_one(), ui->PlayerOneList->currentItem());
    for (int i = 0; i < sum; i++)
    {
        bool speed = false;
        Weapon weapon;
        if (i == one)
            num++;
        else if (i == one + two)
            num++;
        else if (i == one + two + three)
            num++;

        if (i < one && ui->speed_checkBox->isChecked())
            speed = true;
        else if (i >= one && i < one + two && ui->speed_checkBox_2->isChecked())
            speed = true;
        else if (i >= one + two && i < one + two + three && ui->speed_checkBox_3->isChecked())
            speed = true;
        else if (i >= one + two  + three && i < one + two + three + four && ui->speed_checkBox_4->isChecked())
            speed = true;

        weapon.set_name(ui->tableWeapon->item(num, 0)->text());
        weapon.set_distance(ui->tableWeapon->item(num, 1)->text().toInt());
        weapon.set_type(ui->tableWeapon->item(num, 2)->text());
        weapon.set_S(ui->tableWeapon->item(num, 3)->text().toInt());
        weapon.set_B(ui->tableWeapon->item(num, 4)->text().toInt());
        weapon.set_U(ui->tableWeapon->item(num, 5)->text().toInt());
        weapon.set_abilities(ui->tableWeapon->item(num, 6)->text());

        int n_shot = 0;
        QString type = weapon.get_type();
        if (type != "Ближнее" && type != "ближнее")
        {
            n_shot = type[type.size() - 1].unicode() - 48;
        } else if (type == "Ближнее" || type == "ближнее")
        {
            n_shot = sqd.get_unit(i).get_A();
        }

        if (speed)
            n_shot *= 2;

        for (int j = 0; j < n_shot; j++)
        {
            weapons.push_back(weapon);
            units->push_back(sqd.get_unit(i));
        }
    }
    return weapons;
}

QVector<Unit> Battlefield::fill_vec_units()
{
    QVector <Unit> vec_units = {};
    int one, two;
    one = ui->spinBoxUnitOne->value();
    two = ui->spinBoxUnitTwo->value();
    int sum = one + two;

    int num = 0;
    for (int i = 0; i < sum; i++)
    {
        bool shelter = false;
        Unit unit;
        if (i == one)
            num++;

        if (i < one && ui->cover_checkBox->isTristate() == true)
            shelter = true;
        else if (i < one + two && ui->cover_checkBox_2->isTristate() == true)
            shelter = true;

        unit.set_name(ui->tableUnit->item(num, 0)->text());
        unit.set_D(ui->tableUnit->item(num, 1)->text().toInt());
        unit.set_BB(ui->tableUnit->item(num, 2)->text().toInt());
        unit.set_NS(ui->tableUnit->item(num, 3)->text().toInt());
        unit.set_SU(ui->tableUnit->item(num, 4)->text().toInt());
        unit.set_St(ui->tableUnit->item(num, 5)->text().toInt());
        unit.set_R(ui->tableUnit->item(num, 6)->text().toInt());
        unit.set_A(ui->tableUnit->item(num, 7)->text().toInt());
        unit.set_Ld(ui->tableUnit->item(num, 8)->text().toInt());
        if (shelter)
            unit.set_Z(ui->tableUnit->item(num, 9)->text().toInt() - 1);
        else
            unit.set_Z(ui->tableUnit->item(num, 9)->text().toInt());

        vec_units.push_back(unit);
    }
    return vec_units;
}

void Battlefield::update_window()
{
    /*
    int need_num = 0;
    QVector <Squad> *sqd_ptr = new QVector <Squad>();
    if (battle->get_n_player() == 1)
    {
        need_num = need_num_squads(battle->get_vec_com_two(), ui->PlayerTwoList->currentItem());
        *sqd_ptr = battle->get_vec_com_two();
        battle->reset_num_ind_unit(sqd_ptr, need_num);
    }
    else
    {
        need_num = need_num_squads(battle->get_vec_com_one(), ui->PlayerOneList->currentItem());
        *sqd_ptr = battle->get_vec_com_one();
        battle->reset_num_ind_unit(sqd_ptr, need_num);
    }*/

    if (battle->get_n_player() == 1)
    {
        fill_unit_table(battle->get_vec_com_two(), ui->PlayerTwoList->currentItem());
        fill_weapon_table(battle->get_vec_com_one(), ui->PlayerOneList->currentItem());
    }
    else
    {
        fill_unit_table(battle->get_vec_com_one(), ui->PlayerOneList->currentItem());
        fill_weapon_table(battle->get_vec_com_two(), ui->PlayerTwoList->currentItem());
    }


}

void Battlefield::fill_unit_table (QVector <Squad> squads_vec, QListWidgetItem *item)
{
    int need_num = need_num_squads(squads_vec, item);
    reset_spins_unit();
    Squad *ptr_squad = new Squad (squads_vec.value(need_num));

    //Наполнение таблицы юнитов значениями выбранного отряда
    ui->tableUnit->clear();
    for (int i = 0; i < ptr_squad->get_size_vec_num_ind_unit();i++)
    {
        set_spins_unit(ptr_squad, i);

        QTableWidgetItem *t_name = new QTableWidgetItem (ptr_squad->get_unit(ptr_squad->get_num_ind_unit(i)).get_name_unit());
        ui->tableUnit->setItem(i, 0, t_name);

        QTableWidgetItem *t_D = new QTableWidgetItem (QString("%1").arg(ptr_squad->get_unit(ptr_squad->get_num_ind_unit(i)).get_D()));
        ui->tableUnit->setItem(i, 1, t_D);

        QTableWidgetItem *t_BB = new QTableWidgetItem (QString("%1").arg(ptr_squad->get_unit(ptr_squad->get_num_ind_unit(i)).get_BB()));
        ui->tableUnit->setItem(i, 2, t_BB);

        QTableWidgetItem *t_NS = new QTableWidgetItem (QString("%1").arg(ptr_squad->get_unit(ptr_squad->get_num_ind_unit(i)).get_NS()));
        ui->tableUnit->setItem(i, 3, t_NS);

        QTableWidgetItem *t_S = new QTableWidgetItem (QString("%1").arg(ptr_squad->get_unit(ptr_squad->get_num_ind_unit(i)).get_SU()));
        ui->tableUnit->setItem(i, 4, t_S);

        QTableWidgetItem *t_St = new QTableWidgetItem (QString("%1").arg(ptr_squad->get_unit(ptr_squad->get_num_ind_unit(i)).get_St()));
        ui->tableUnit->setItem(i, 5, t_St);

        QTableWidgetItem *t_R = new QTableWidgetItem (QString("%1").arg(ptr_squad->get_unit(ptr_squad->get_num_ind_unit(i)).get_R()));
        ui->tableUnit->setItem(i, 6, t_R);

        QTableWidgetItem *t_A = new QTableWidgetItem (QString("%1").arg(ptr_squad->get_unit(ptr_squad->get_num_ind_unit(i)).get_A()));
        ui->tableUnit->setItem(i, 7, t_A);

        QTableWidgetItem *t_Ld = new QTableWidgetItem (QString("%1").arg(ptr_squad->get_unit(ptr_squad->get_num_ind_unit(i)).get_Ld()));
        ui->tableUnit->setItem(i, 8, t_Ld);

        QTableWidgetItem *t_Z = new QTableWidgetItem (QString("%1").arg(ptr_squad->get_unit(ptr_squad->get_num_ind_unit(i)).get_Z()));
        ui->tableUnit->setItem(i, 9, t_Z);
    }
    //Установить значения ячеек по центру (только для заполненных)
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 10; j++)
        {
            if (j != 0 && ui->tableUnit->item(i,j) != 0)
                ui->tableUnit->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }

}

void Battlefield::fill_weapon_table(QVector <Squad> squads_vec, QListWidgetItem *item)
{
    int need_num = need_num_squads(squads_vec, item);
    reset_spins_weapon();
    Squad *ptr_squad = new Squad (squads_vec.value(need_num));
    QVector <int> qual_weapons;
    QVector <Weapon> vec_weapon = {};
    QVector <int> qual_ind_weapons = {0, 0, 0, 0};

    ui->tableWeapon->clear();
    //Наполнение вектора используемого отрядом оружием
    for (int i = 0; i < ptr_squad->get_size_vec_units(); i++)
    {
        QVector <Weapon> weapons_unit = ptr_squad->get_unit(i).get_vec_weapons();
        for(int j = 0; j < ptr_squad->get_unit(i).get_size_vec_weapon(); j++)
        {
            //Условие выбора в зависимости от фазы
            if (battle->get_fase() == 0) // фаза стрельбы
            {
                if (weapons_unit[j].get_type() != "Ближнее" && !check_vec_weapon(vec_weapon, weapons_unit[j]))
                {
                    vec_weapon.push_back(weapons_unit[j]);
                }
            } else
            {
                if (weapons_unit[j].get_type() == "Ближнее" && !check_vec_weapon(vec_weapon, weapons_unit[j]))
                {
                    vec_weapon.push_back(weapons_unit[j]);
                }
            }
        }
    }

    //Подсчёт кол-ва оружия
    for (int i = 0; i < ptr_squad->get_size_vec_units(); i++)
    {
        for (int j = 0; j < vec_weapon.size(); j++)
        {
            if (check_vec_weapon(ptr_squad->get_unit(i).get_vec_weapons(), vec_weapon[j]))
            {
                qual_ind_weapons[j] += 1;
            }
        }
    }

    //Отображение в таблицу оружия
    for(int i = 0; i < vec_weapon.size(); i++)
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

        set_spins_weapon(qual_ind_weapons, i);
    }

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 7; j++)
        {
            if (j != 0 && ui->tableWeapon->item(i,j) != 0)
                ui->tableWeapon->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }
}

void Battlefield::set_spins_unit(Squad *ptr_squad, int i)
{
    if (i == 0)
    {
        ui->spinBoxUnitOne->setMaximum(ptr_squad->get_quant_ind_unit(i));
        ui->spinBoxUnitOne->setEnabled(true);
        ui->spinBoxUnitOne->setValue(ptr_squad->get_quant_ind_unit(i));
        ui->cover_checkBox_2->setEnabled(false);
    }else if (i == 1)
    {
        ui->spinBoxUnitTwo->setMaximum(ptr_squad->get_quant_ind_unit(i));
        ui->spinBoxUnitTwo->setEnabled(true);
        ui->spinBoxUnitTwo->setValue(ptr_squad->get_quant_ind_unit(i));
        ui->cover_checkBox_2->setEnabled(true);
    }
}

void Battlefield::set_spins_weapon(QVector <int> quant, int i)
{

    if (i == 0)
    {
        ui->spinBoxOne->setMaximum(quant[i]);
        ui->spinBoxOne->setEnabled(true);
        ui->spinBoxOne->setValue(quant[i]);
        if (check_type_speed(0))
            ui->speed_checkBox->setEnabled(true);

    }else if (i == 1)
    {
        ui->spinBoxTwo->setMaximum(quant[i]);
        ui->spinBoxTwo->setEnabled(true);
        ui->spinBoxTwo->setValue(quant[i]);
        if (check_type_speed(1))
            ui->speed_checkBox_2->setEnabled(true);
    }else if (i == 2)
    {
        ui->spinBoxThree->setMaximum(quant[i]);
        ui->spinBoxThree->setEnabled(true);
        ui->spinBoxThree->setValue(quant[i]);
        if (check_type_speed(2))
            ui->speed_checkBox_3->setEnabled(true);
    }else if (i == 3)
    {
        ui->spinBoxFour->setMaximum(quant[i]);
        ui->spinBoxFour->setEnabled(true);
        ui->spinBoxFour->setValue(quant[i]);
        if (check_type_speed(3))
            ui->speed_checkBox_4->setEnabled(true);
    }
}

void Battlefield::reset_spins_weapon()
{
    ui->spinBoxOne->setValue(0);
    ui->spinBoxOne->setMaximum(0);
    ui->spinBoxOne->setEnabled(false);
    ui->spinBoxTwo->setValue(0);
    ui->spinBoxTwo->setMaximum(0);
    ui->spinBoxTwo->setEnabled(false);
    ui->spinBoxThree->setValue(0);
    ui->spinBoxThree->setMaximum(0);
    ui->spinBoxThree->setEnabled(false);
    ui->spinBoxFour->setValue(0);
    ui->spinBoxFour->setMaximum(0);
    ui->spinBoxFour->setEnabled(false);

    ui->speed_checkBox->setTristate(false);
    ui->speed_checkBox_2->setTristate(false);
    ui->speed_checkBox_3->setTristate(false);
    ui->speed_checkBox_4->setTristate(false);
    ui->speed_checkBox->setEnabled(false);
    ui->speed_checkBox_2->setEnabled(false);
    ui->speed_checkBox_3->setEnabled(false);
    ui->speed_checkBox_4->setEnabled(false);
}

void Battlefield::reset_spins_unit()
{

    ui->spinBoxUnitTwo->setValue(0);
    ui->spinBoxUnitTwo->setMaximum(0);
    ui->spinBoxUnitTwo->setEnabled(false);
    ui->spinBoxUnitOne->setValue(0);
    ui->spinBoxUnitOne->setMaximum(0);
    ui->spinBoxUnitOne->setEnabled(false);

    ui->cover_checkBox->setTristate(false);
    ui->cover_checkBox_2->setTristate(false);
    ui->cover_checkBox_2->setEnabled(false);

}

void Battlefield::on_PlayerOneList_itemClicked(QListWidgetItem *item)
{

    if (battle->get_n_player() == 1)
    {
        reset_spins_weapon();
        fill_weapon_table(battle->get_vec_com_one(), item);
        ui->_atack_label->setText("<html><head/><body><p align=center><span style= font-size:11pt;>" + item->text() + "</span></p></body></html>");
    }else
    {
        reset_spins_unit();
        fill_unit_table(battle->get_vec_com_one(), item);
        ui->name_defence_label->setText("<html><head/><body><p align=center><span style= font-size:11pt;>" + item->text() + "</span></p></body></html>");
    }
}

void Battlefield::on_PlayerTwoList_itemClicked(QListWidgetItem *item)
{

    if (battle->get_n_player() == 1)
    {
        reset_spins_unit();
        fill_unit_table(battle->get_vec_com_two(), item);
        ui->name_defence_label->setText("<html><head/><body><p align=center><span style= font-size:11pt;>" + item->text() + "</span></p></body></html>");
    }else
    {
        reset_spins_weapon();
        fill_weapon_table(battle->get_vec_com_two(), item);
        ui->_atack_label->setText("<html><head/><body><p align=center><span style= font-size:11pt;>" + item->text() + "</span></p></body></html>");
    }
}

void Battlefield::on_back_button_clicked()
{
    QMessageBox msg_err;
    msg_err.setText("Вы уверены что хотите выйти?");
    msg_err.setInformativeText("Игра не будет сохранена!");
    msg_err.setStandardButtons (QMessageBox::Yes | QMessageBox::No);
    msg_err.setDefaultButton(QMessageBox::No);
    msg_err.setIcon(QMessageBox::Warning);
    int ret = msg_err.exec();

    switch (ret)
    {
      case QMessageBox::Yes:
        this->close();
        battle->destroy_object();
        emit firstWindow();
        break;

      case QMessageBox::No:
        break;

      default:
          break;
    }
}

void Battlefield::on_fase_button_clicked()
{
    if (battle->get_fase() == 0)
    {
        battle->set_fase(1);
        reset_labels();
        update_window();
    }

    else if (battle->get_fase() == 1 && battle->get_n_player() == 1)
    {
        battle->set_fase(0);
        battle->set_n_player(2);
        reset_labels();
        update_window();
    }
    else
    {
        battle->set_fase(0);
        battle->set_n_player(1);
        reset_labels();
        update_window();
    }


}

void Battlefield::on_attack_button_clicked()
{
    QString err_msg = "";
    bool err = false;
    if (ui->tableWeapon->item(0,0) == 0)
    {
        err = true;
        err_msg = "Не выбран атакующий отряд";
    } else if (ui->tableUnit->item(0,0) == 0)
    {
        err = true;
        err_msg = "Не выбран обороняемый отряд";
    }

    QVector <Unit> attack_units_vec = {};
    QVector <Unit> defence_units_vec = fill_vec_units();
    QVector <Weapon> weapons = {};
    QVector <Weapon> defence_weapon = {};
    int need_num = 0;
    count_fill = 0;
    if (battle->get_fase() == 0)
    {
        if (battle->get_n_player() == 1)
        {
            weapons = fill_vec_weapons(&attack_units_vec,
                                        battle->get_vec_com_one()[need_num_squads(battle->get_vec_com_one(),
                                                                                    ui->PlayerOneList->currentItem())]);
            need_num = need_num_squads(battle->get_vec_com_one(), ui->PlayerOneList->currentItem());
        } else if (battle->get_n_player() == 2)
        {
            weapons = fill_vec_weapons(&attack_units_vec,
                                        battle->get_vec_com_two()[need_num_squads(battle->get_vec_com_two(),
                                                                                    ui->PlayerTwoList->currentItem())]);
            need_num = need_num_squads(battle->get_vec_com_two(), ui->PlayerTwoList->currentItem());
        }


        Fight fight(weapons, attack_units_vec, defence_units_vec, battle);
        ui_attack_result = new AttackResult (nullptr, &fight, battle, need_num);
        connect (ui_attack_result, SIGNAL(set_battlefield()), this, SLOT(update_window()));
        ui_attack_result->show();
    }
    else if (battle->get_fase() == 1)
    {
        if (battle->get_n_player() == 1)
        {
            weapons = fill_vec_weapons(&attack_units_vec,
                                        battle->get_vec_com_one()[need_num_squads(battle->get_vec_com_one(),
                                                                                    ui->PlayerOneList->currentItem())]);
            count_fill = 1;
            defence_weapon = fill_vec_weapons(&defence_units_vec,
                                        battle->get_vec_com_two()[need_num_squads(battle->get_vec_com_two(),
                                                                                    ui->PlayerTwoList->currentItem())]);
            need_num = need_num_squads(battle->get_vec_com_one(), ui->PlayerOneList->currentItem());
        } else if (battle->get_n_player() == 2)
        {
            weapons = fill_vec_weapons(&attack_units_vec,
                                        battle->get_vec_com_two()[need_num_squads(battle->get_vec_com_two(),
                                                                                   ui->PlayerTwoList->currentItem())]);
            defence_weapon = fill_vec_weapons(&defence_units_vec,
                                        battle->get_vec_com_one()[need_num_squads(battle->get_vec_com_one(),
                                                                                    ui->PlayerOneList->currentItem())]);
            need_num = need_num_squads(battle->get_vec_com_two(), ui->PlayerTwoList->currentItem());
        }
        Fight fight(weapons, attack_units_vec, defence_weapon, defence_units_vec, battle);
        ui_attack_result = new AttackResult (nullptr, &fight, battle, need_num);
        connect (ui_attack_result, SIGNAL(set_battlefield()), this, SLOT(update_window()));
        ui_attack_result->show();
    }

}
