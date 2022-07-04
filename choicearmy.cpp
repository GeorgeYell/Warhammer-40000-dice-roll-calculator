#include "choicearmy.h"
#include "ui_choicearmy.h"


ChoiceArmy::ChoiceArmy(QWidget *parent, QVector <Squad> squads) :
    QWidget(parent),
    ui(new Ui::ChoiceArmy)
{
    ui->setupUi(this);
    squads_vec = squads;
    for (int i = 0; i < squads_vec.size(); i++)
    {
        ui->listWidget->addItem(squads_vec[i].get_name());
    }


    //Настройка отображения таблицы юнитов и оружия
    {
    ui->tableUnit->setColumnWidth(1, 424);
    ui->tableUnit->setColumnWidth(0, 45);
    for (int i = 2; i < 11; i++)
    {
        ui->tableUnit->setColumnWidth(i, 20);
    }
    ui->tableUnit->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableWeapon->setColumnWidth(0, 400);
    ui->tableWeapon->setColumnWidth(1, 45);
    ui->tableWeapon->setColumnWidth(2, 150);
    ui->tableWeapon->setColumnWidth(3, 20);
    ui->tableWeapon->setColumnWidth(4, 20);
    ui->tableWeapon->setColumnWidth(5, 20);
    ui->tableWeapon->setColumnWidth(6, 154);
    }

}
ChoiceArmy::~ChoiceArmy()
{
    delete ui;
}




int ChoiceArmy::need_num_squads(QListWidgetItem *item)
{
    //Поиск совпадений имен из списка с вектором
    QString name = item->text();
    for(int i = 0; i < squads_vec.size(); i++)
        if (squads_vec.value(i).get_name() == name)
            return i; // индекс нужного отряда
    return -1;
}

void ChoiceArmy::fill_tabs(QListWidgetItem *item)
{
    //Поиск совпадений имен из списка с вектором
    int need_num = need_num_squads(item);

    Squad *ptr_squad = new Squad (squads_vec.value(need_num));

    //Наполнение таблицы юнитов значениями выбранного отряда
    ui->tableUnit->clear();
    for (int i = 0; i < ptr_squad->get_size_vec_num_ind_unit();i++)
    {
        QTableWidgetItem *t_size = new QTableWidgetItem (QString("%1").arg(ptr_squad->get_quant_ind_unit(i)));
        ui->tableUnit->setItem(i, 0, t_size);

        QTableWidgetItem *t_name = new QTableWidgetItem (ptr_squad->get_unit(ptr_squad->get_num_ind_unit(i)).get_name_unit());
        ui->tableUnit->setItem(i, 1, t_name);

        QTableWidgetItem *t_D = new QTableWidgetItem (QString("%1").arg(ptr_squad->get_unit(ptr_squad->get_num_ind_unit(i)).get_D()));
        ui->tableUnit->setItem(i, 2, t_D);

        QTableWidgetItem *t_BB = new QTableWidgetItem (QString("%1").arg(ptr_squad->get_unit(ptr_squad->get_num_ind_unit(i)).get_BB()));
        ui->tableUnit->setItem(i, 3, t_BB);

        QTableWidgetItem *t_NS = new QTableWidgetItem (QString("%1").arg(ptr_squad->get_unit(ptr_squad->get_num_ind_unit(i)).get_NS()));
        ui->tableUnit->setItem(i, 4, t_NS);

        QTableWidgetItem *t_S = new QTableWidgetItem (QString("%1").arg(ptr_squad->get_unit(ptr_squad->get_num_ind_unit(i)).get_SU()));
        ui->tableUnit->setItem(i, 5, t_S);

        QTableWidgetItem *t_St = new QTableWidgetItem (QString("%1").arg(ptr_squad->get_unit(ptr_squad->get_num_ind_unit(i)).get_St()));
        ui->tableUnit->setItem(i, 6, t_St);

        QTableWidgetItem *t_R = new QTableWidgetItem (QString("%1").arg(ptr_squad->get_unit(ptr_squad->get_num_ind_unit(i)).get_R()));
        ui->tableUnit->setItem(i, 7, t_R);

        QTableWidgetItem *t_A = new QTableWidgetItem (QString("%1").arg(ptr_squad->get_unit(ptr_squad->get_num_ind_unit(i)).get_A()));
        ui->tableUnit->setItem(i, 8, t_A);

        QTableWidgetItem *t_Ld = new QTableWidgetItem (QString("%1").arg(ptr_squad->get_unit(ptr_squad->get_num_ind_unit(i)).get_Ld()));
        ui->tableUnit->setItem(i, 9, t_Ld);

        QTableWidgetItem *t_Z = new QTableWidgetItem (QString("%1").arg(ptr_squad->get_unit(ptr_squad->get_num_ind_unit(i)).get_Z()));
        ui->tableUnit->setItem(i, 10, t_Z);
    }

    //Наполнение вектора используемого отрядом оружием
    for (int i = 0; i < ptr_squad->get_size_vec_units(); i++)
    {
        for(int j = 0; j < ptr_squad->get_unit(i).get_size_vec_weapon(); j++)
        {
            if(i == 0 && j == 0)
            {
                vec_weapon.push_back(ptr_squad->get_unit(i).get_weapon(j));
            }
            for (int l = 0; l < vec_weapon.size(); l++)
            {
                if (ptr_squad->get_unit(i).get_weapon(j).get_name_weapon() == vec_weapon[l].get_name_weapon() ||
                      (l > 0 && ptr_squad->get_unit(i).get_weapon(j).get_name_weapon() == vec_weapon[l-1].get_name_weapon())   )
                {
                    break;
                }
                else if (l == vec_weapon.size() - 1)
                {
                    vec_weapon.push_back(ptr_squad->get_unit(i).get_weapon(j));
                }
            }
        }
    }

    //Наполнение таблицы Оружия значениями выбранного отряда
    if (vec_weapon.size() > 4)
        ui->tableWeapon->setRowCount(vec_weapon.size());
    else
        ui->tableWeapon->setRowCount(4);
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
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 11; j++)
        {
            if (j != 1 && ui->tableUnit->item(i,j) != 0)
                ui->tableUnit->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 7; j++)
        {
            if (j != 0 && ui->tableWeapon->item(i,j) != 0)
                ui->tableWeapon->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }

    vec_weapon.clear();
    ui->tableUnit->repaint();
    ui->tableWeapon->repaint();
}

void ChoiceArmy::on_push_back_menu_clicked()
{
    this->close();
    emit firstWindow();
}

void ChoiceArmy::on_listWidget_itemClicked(QListWidgetItem *item)
{
    fill_tabs(item);
}

bool ChoiceArmy::check_weapon (QListWidgetItem *item)
{
    int need_num = need_num_squads(item);
    QVector <Unit> units = squads_vec[need_num].get_vec_units();

    for (int i = 0; i < units.size(); i++)
    {
        QVector <Weapon> weapons = units[i].get_vec_weapons();
        for (int j = 0; weapons.size() > 1 && j < weapons.size();j++)
        {
            if (j < weapons.size() - 1 && weapons[j].get_type() == weapons[j + 1].get_type())
            {
                return false;
            }
            else if (j == weapons.size() - 1 && weapons[j].get_type() == weapons[0].get_type())
            {
                 return false;
            }
        }
    }
    return true;
}

Squad ChoiceArmy::need_unit (QListWidgetItem *item)
{
    int need_num = need_num_squads(item);
    QVector <Unit> units = squads_vec[need_num].get_vec_units();
    Squad need_units_skuad;

    for (int i = 0; i < units.size(); i++)
    {
        QVector <Weapon> weapons = units[i].get_vec_weapons();
        for (int j = 0; weapons.size() > 1 && j < weapons.size();j++)
        {
            if (j < weapons.size() - 1 && weapons[j].get_type() == weapons[j + 1].get_type())
            {
                need_units_skuad.add_units(units[i]);
                break;
            }
            else if (j == weapons.size() - 1 && weapons[j].get_type() == weapons[0].get_type())
            {
                 need_units_skuad.add_units(units[i]);
                 break;
            }
        }
    }
    return need_units_skuad;
}

void ChoiceArmy::add_squad_one (Squad *squad)
{
    player_one_vec.push_back(*squad);
    ui->PlayerOneList->addItem(ui->listWidget->currentItem()->text());
}

void ChoiceArmy::add_squad_two (Squad *squad)
{
    player_two_vec.push_back(*squad);
    ui->PlayerTwoList->addItem(ui->listWidget->currentItem()->text());
}

void ChoiceArmy::on_add_player_one_button_clicked()
{
    Squad sqd_need_un;
    Squad squad_full;
    Squad *sqd_ptr_need_un = new Squad();
    Squad *squad_full_ptr = new Squad();
    squad_full = squads_vec[need_num_squads(ui->listWidget->currentItem())];

    if (check_weapon(ui->listWidget->currentItem()))
    {
        ui->PlayerOneList->addItem(ui->listWidget->currentItem()->text());
        player_one_vec.push_back(squad_full);
    }
    else
    {
        sqd_need_un = need_unit(ui->listWidget->currentItem());
        *sqd_ptr_need_un = sqd_need_un;
        *squad_full_ptr = squad_full;
        ui_choice_weapon = new ChoiceWeapon (this, sqd_ptr_need_un, sqd_need_un.get_size_vec_units(),squad_full_ptr);
        connect(ui_choice_weapon, SIGNAL(save(Squad *)), this, SLOT(add_squad_one (Squad *)));
        ui_choice_weapon->show();
    }
}

void ChoiceArmy::on_add_player_two_button_clicked()
{
    Squad sqd_need_un;
    Squad squad_full;
    Squad *sqd_ptr_need_un = new Squad();
    Squad *squad_full_ptr = new Squad();
    squad_full = squads_vec[need_num_squads(ui->listWidget->currentItem())];

    if (check_weapon(ui->listWidget->currentItem()))
    {
        ui->PlayerTwoList->addItem(ui->listWidget->currentItem()->text());
        player_two_vec.push_back(squad_full);
    }
    else
    {
        sqd_need_un = need_unit(ui->listWidget->currentItem());
        *sqd_ptr_need_un = sqd_need_un;
        *squad_full_ptr = squad_full;
        ui_choice_weapon = new ChoiceWeapon (this, sqd_ptr_need_un, sqd_need_un.get_size_vec_units(),squad_full_ptr);
        connect(ui_choice_weapon, SIGNAL(save(Squad *)),this, SLOT(add_squad_two (Squad *)));
        ui_choice_weapon->show();
    }
}

void ChoiceArmy::on_del_player_one_button_clicked()
{
    ui->PlayerOneList->takeItem(ui->PlayerOneList->currentRow());
}

void ChoiceArmy::on_del_player_two_button_clicked()
{
    ui->PlayerTwoList->takeItem(ui->PlayerOneList->currentRow());
}

void ChoiceArmy::on_PlayerOneList_itemClicked(QListWidgetItem *item)
{
    fill_tabs(item);
}

void ChoiceArmy::on_PlayerTwoList_itemClicked(QListWidgetItem *item)
{
    fill_tabs(item);
}

void ChoiceArmy::on_battle_button_clicked()
{

}

void ChoiceArmy::on_go_battle_button_clicked()
{
    Battle &battle = Battle::getInstance();
    battle.set_fase(0);
    for (int i = 0; i < player_one_vec.size(); i++)
    {
        battle.add_squad_vec_one(player_one_vec[i]);
    }
    for (int i = 0; i < player_two_vec.size(); i++)
    {
        battle.add_squad_vec_two(player_two_vec[i]);
    }
    ui_battlefield = new Battlefield (nullptr, &battle);
    connect(ui_battlefield, &Battlefield::firstWindow, this, &ChoiceArmy::show);
    ui_battlefield->show();
    this->close();
}
