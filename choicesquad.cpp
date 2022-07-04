#include "choicesquad.h"
#include "ui_choicesquad.h"
#include "editfile.h"
#include <QMessageBox>

ChoiceSquad::ChoiceSquad(QWidget *parent, QVector <Squad> *vec_squads, QVector <Unit> *vec_unit) :
    QWidget(parent),
    ui(new Ui::ChoiceSquad)
{
    ui->setupUi(this);

    squads_vec = vec_squads;
    units_vec = vec_unit;

    //Заполнение списков
    fill_lists();

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

ChoiceSquad::~ChoiceSquad()
{
    delete ui;
}

void ChoiceSquad::close_tabs()
{
    ui->tableUnit->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWeapon->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->add_unit_button->setEnabled(false);
    ui->cancel_button->setEnabled(false);
    ui->text_bar->setText("");
    fun = 0;
    ui->save_change_Button->setEnabled(true);
    ui->cancel_change_Button->setEnabled(true);
    ui->listUnits->setEnabled(true);
    ui->listSquads->setEnabled(true);
}

void ChoiceSquad::fill_lists ()
{
    //Заполнение списков
    ui->listSquads->clear();
    ui->listUnits->clear();

    for (int i = 0; i < (*squads_vec).size(); i++)
    {
        ui->listSquads->addItem((*squads_vec)[i].get_name());
    }
    for (int i = 0; i < (*units_vec).size(); i++)
    {
        ui->listUnits->addItem((*units_vec)[i].get_name_unit());
    }
}

void ChoiceSquad::on_Back_to_menu_button_clicked()
{
    if (ui->save_change_Button->isEnabled())
    {
        QMessageBox msg_err;
        msg_err.setText("Изменения не сохранены!");
        msg_err.setInformativeText("Сохранить изменения?");
        msg_err.setStandardButtons (QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        msg_err.setDefaultButton(QMessageBox::Yes);
        msg_err.setIcon(QMessageBox::Warning);
        int ret = msg_err.exec();

        switch (ret)
        {
          case QMessageBox::Yes:
            on_save_change_Button_clicked();
            this->close();
            emit firstWindow();
            break;

          case QMessageBox::No:
            on_cancel_change_Button_clicked();
            this->close();
            emit firstWindow();
            break;

          case QMessageBox::Cancel:
              break;

          default:
              break;
        }
    }
    else
    {
        this->close();
        emit firstWindow();
    }
}

void ChoiceSquad::on_listSquads_itemClicked(QListWidgetItem *item)
{
    item_squad = item;
    //Поиск совпадений имен из списка с вектором
    int need_num = need_num_squads(item);
    Squad *ptr_squad = new Squad ((*squads_vec).value(need_num));

    //Наполнение таблицы юнитов значениями выбранного отряда
    ui->tableUnit->clear();
    for (int i = 0; i < ptr_squad->get_size_vec_num_ind_unit();i++)
    {
        QTableWidgetItem *t_size = new QTableWidgetItem (QString("%1").arg(ptr_squad->get_quant_ind_unit(i)));
        ui->tableUnit->setItem(i, 0, t_size);

        QTableWidgetItem *t_name = new QTableWidgetItem (ptr_squad->get_unit(ptr_squad->get_num_ind_unit(i)).get_name_unit());
        ui->tableUnit->setItem(i, 1, t_name);

        QTableWidgetItem *t_D = new QTableWidgetItem (QString("%1").arg(ptr_squad->get_unit(ptr_squad->get_num_ind_unit( i)).get_D()));
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

int ChoiceSquad::need_num_units (QListWidgetItem *item)
{
    //Поиск совпадений имен из списка с вектором
    QString name = item->text();
    for(int i = 0; i < (*units_vec).size(); i++)
        if ((*units_vec).value(i).get_name_unit() == name)
            return i; // индекс нужного юнита
    return -1;
}

int ChoiceSquad::need_num_squads(QListWidgetItem *item)
{
    //Поиск совпадений имен из списка с вектором
    QString name = item->text();
    for(int i = 0; i < (*squads_vec).size(); i++)
        if ((*squads_vec).value(i).get_name() == name)
            return i; // индекс нужного отряда
    return -1;
}

void ChoiceSquad::update_window(QVector<Squad> *vec_squads, QVector<Unit> *vec_unit)
{
    squads_vec = vec_squads;
    units_vec = vec_unit;
    fill_lists();
    ui->save_change_Button->setEnabled(true);
    ui->cancel_change_Button->setEnabled(true);
    ui->add_unit_button->setEnabled(false);
    ui->cancel_button->setEnabled(false);
    ui->listSquads->repaint();
}

void ChoiceSquad::on_listUnits_itemClicked(QListWidgetItem *item)
{

    //Поиск совпадений имен из списка с вектором
    int need_num = need_num_units(item);
    if (need_num == -1)
        return void();
    Unit *ptr_unit = new Unit ((*units_vec).value(need_num));

    //Наполнение таблицы юнитов значениями выбранного юнита
    {
        ui->tableUnit->clear();
        int i = 0;
        QTableWidgetItem *t_size = new QTableWidgetItem ("#");
        ui->tableUnit->setItem(i, 0, t_size);

        QTableWidgetItem *t_name = new QTableWidgetItem (ptr_unit->get_name_unit());
        ui->tableUnit->setItem(i, 1, t_name);

        QTableWidgetItem *t_D = new QTableWidgetItem (QString("%1").arg(ptr_unit->get_D()));
        ui->tableUnit->setItem(i, 2, t_D);

        QTableWidgetItem *t_BB = new QTableWidgetItem (QString("%1").arg(ptr_unit->get_BB()));
        ui->tableUnit->setItem(i, 3, t_BB);

        QTableWidgetItem *t_NS = new QTableWidgetItem (QString("%1").arg(ptr_unit->get_NS()));
        ui->tableUnit->setItem(i, 4, t_NS);

        QTableWidgetItem *t_S = new QTableWidgetItem (QString("%1").arg(ptr_unit->get_SU()));
        ui->tableUnit->setItem(i, 5, t_S);

        QTableWidgetItem *t_St = new QTableWidgetItem (QString("%1").arg(ptr_unit->get_St()));
        ui->tableUnit->setItem(i, 6, t_St);

        QTableWidgetItem *t_R = new QTableWidgetItem (QString("%1").arg(ptr_unit->get_R()));
        ui->tableUnit->setItem(i, 7, t_R);

        QTableWidgetItem *t_A = new QTableWidgetItem (QString("%1").arg(ptr_unit->get_A()));
        ui->tableUnit->setItem(i, 8, t_A);

        QTableWidgetItem *t_Ld = new QTableWidgetItem (QString("%1").arg(ptr_unit->get_Ld()));
        ui->tableUnit->setItem(i, 9, t_Ld);

        QTableWidgetItem *t_Z = new QTableWidgetItem (QString("%1").arg(ptr_unit->get_Z()));
        ui->tableUnit->setItem(i, 10, t_Z);
    }

    //Наполнение вектора используемого юнитом оружием
    for(int i = 0; i < ptr_unit->get_size_vec_weapon(); i++)
    {
        vec_weapon.push_back(ptr_unit->get_weapon(i));
    }

    //Наполнение таблицы Оружия значениями выбранного юнита
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
    {
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
    }


    vec_weapon.clear();
    ui->tableUnit->repaint();
    ui->tableWeapon->repaint();
}

void ChoiceSquad::on_deleteSquadButton_clicked()
{
    //Поиск совпадений имен из списка с вектором
    int need_num = 0;
    if (ui->listSquads->selectedItems().size() != 0)
    {
        QString name = ui->listSquads->selectedItems()[0]->text();
        for(int i = 0; i < (*squads_vec).size(); i++)
        {
            if ((*squads_vec).value(i).get_name() == name)
            {
                need_num = i; // индекс нужного отряда
                break;
            }
        }

        //Удаление элементов из вектора и вджета списка
        squads_vec->erase(squads_vec->begin() + need_num);
        QString need_name = ui->listSquads->selectedItems()[0]->text();
        for (int i = 0; i < ui->listSquads->selectedItems().size(); i++)
        {
            if (need_name == ui->listSquads->item(i)->text())
            {
                need_num = i;
                break;
            }
        }
        ui->listSquads->takeItem(need_num);
        ui->tableUnit->clear();
        ui->tableWeapon->clear();
        ui->save_change_Button->setEnabled(true);
        ui->cancel_change_Button->setEnabled(true);
    }
}

void ChoiceSquad::on_deleteUnitButton_clicked()
{
    //Поиск совпадений имен из списка с вектором
    int need_num = 0;
    if (ui->listUnits->selectedItems().size() != 0)
    {
        need_num = need_num_units(ui->listUnits->currentItem());

        //Удаление элементов из вектора и вджета списка
        units_vec->erase(units_vec->begin() + need_num);
        QString need_name = ui->listUnits->selectedItems()[0]->text();
        for (int i = 0; i < ui->listUnits->selectedItems().size(); i++)
        {
            if (need_name == ui->listUnits->item(i)->text())
            {
                need_num = i;
                break;
            }
        }
        ui->listUnits->takeItem(need_num);
        ui->tableUnit->clear();
        ui->tableWeapon->clear();
        ui->save_change_Button->setEnabled(true);
        ui->cancel_change_Button->setEnabled(true);
    }
}

void ChoiceSquad::on_save_change_Button_clicked()
{
    EditFile e(*squads_vec, *units_vec);
    e.save_file();
    ui->save_change_Button->setEnabled(false);
    ui->cancel_change_Button->setEnabled(false);
}

void ChoiceSquad::on_newUnitButton_clicked()
{
    ui->text_bar->setText("<html><head/><body><p align=center>Введите данные юнита</p><p align=center>и его оружия в таблицы</p></body></html>");
    ui->tableUnit->clear();
    ui->tableWeapon->clear();
    ui->tableUnit->setEditTriggers(QAbstractItemView::AllEditTriggers);
    ui->tableWeapon->setEditTriggers(QAbstractItemView::AllEditTriggers);
    ui->listUnits->setEnabled(false);
    ui->listSquads->setEnabled(false);
    ui->add_unit_button->setEnabled(true);
    ui->cancel_button->setEnabled(true);
    QTableWidgetItem *t_size = new QTableWidgetItem ("#");
    ui->tableUnit->setItem(0, 0, t_size);
    fun = 1;
}

void ChoiceSquad::on_add_unit_button_clicked()
{
    //определение нужного элемента для изменения
    int need_num = 0;
    if (fun == 2)
        need_num = need_num_units(ui->listUnits->currentItem());

    bool err = false;
    QString err_msg = "";

    //проверки введенных значений юнита
     if (ui->tableUnit->item(0,1) == 0)
        err = true;
     for (int i = 0; i < ui->listUnits->count(); i++)
     {
         if (fun != 2 && ui->tableUnit->item(0,1)->text() == ui->listUnits->item(i)->text())
         {
            err = true;
            err_msg = "Юнит с таким именем уже существует!";
         }

     }
     for (int i = 2; !err && i < 11; i++)
    {
        if (ui->tableUnit->item(0,i)->text()[0] < "0" || ui->tableUnit->item(0,i)->text()[0] > "9")
        {
            err = true;
            err_msg = "В числовом поле юнита не число!";
        }

    }

    //проверки введенных значений оружия
    int n_weapon = 0;
    while (true)
    {
        if (ui->tableWeapon->item(n_weapon,0) == 0)
            break;
        else
            n_weapon += 1;
    }
    for (int i = 0; i < n_weapon; i++)
    {
        if (ui->tableWeapon->item(i,0) == 0 || ui->tableWeapon->item(i,2) == 0 || ui->tableWeapon->item(i,6) == 0)
        {
            err = true;
            err_msg = "Не заполнены текстовые поля оружия!";
        }


        for (int j = 1; !err && j < 6; j++)
        {
            if ((j != 4 && j != 2 && (ui->tableWeapon->item(i,j)->text()[0] < "0" || ui->tableWeapon->item(i,j)->text()[0] > "9")) ||
                    (j == 4 && ui->tableWeapon->item(i,j)->text()[0] != "-" && (ui->tableWeapon->item(i,j)->text()[0] < "0" || ui->tableWeapon->item(i,j)->text()[0] > "9")) )
            {
                err = true;
                err_msg = "В числовом поле оружия не число!";
            }
        }
    }

    //Создание объекта юнита
    if (!err)
    {
        QString name_unit = ui->tableUnit->item(0,1)->text();
        int D, BB, NS, SU, St, R, A, Ld, Z;

        D = ui->tableUnit->item(0,2)->text().toInt();
        BB = ui->tableUnit->item(0,3)->text().toInt();
        NS = ui->tableUnit->item(0,4)->text().toInt();
        SU = ui->tableUnit->item(0,5)->text().toInt();
        St = ui->tableUnit->item(0,6)->text().toInt();
        R = ui->tableUnit->item(0,7)->text().toInt();
        A = ui->tableUnit->item(0,8)->text().toInt();
        Ld = ui->tableUnit->item(0,9)->text().toInt();
        Z = ui->tableUnit->item(0,10)->text().toInt();
        Unit unit (name_unit, D, BB, NS, SU, St, R, A, Ld, Z);

        for (int i = 0; i < n_weapon; i++)
        {
            int Dist, SW, B, U;
            QString name_weapon, type, abilities;

            name_weapon = ui->tableWeapon->item(i,0)->text();
            type = ui->tableWeapon->item(i,2)->text();
            abilities = ui->tableWeapon->item(i,6)->text();
            Dist = ui->tableWeapon->item(i,1)->text().toInt();
            SW = ui->tableWeapon->item(i,3)->text().toInt();
            B = ui->tableWeapon->item(i,4)->text().toInt();
            U = ui->tableWeapon->item(i,5)->text().toInt();
            Weapon weap(name_weapon, Dist, type, SW, B, U, abilities);
            unit.add_weapon(weap);
        }

        //Изменение векторов в зависимости от выбранной функции
        if (fun == 1) // создать юнит
        {
            units_vec->push_back(unit);
            fill_lists();
            close_tabs();

        }
        else if (fun == 2) // изменить юнит
        {
            units_vec->takeAt(need_num);
            units_vec->push_back(unit);
            fill_lists();
            close_tabs();
        }
    }
    else // Вывод ошибки
    {
        QMessageBox msg_err;
        msg_err.setText("Ошибка заполнения, повторите ввод");
        msg_err.setInformativeText(err_msg);
        msg_err.setStandardButtons(QMessageBox::Ok);
        msg_err.setDefaultButton(QMessageBox::Ok);
        msg_err.setIcon(QMessageBox::Warning);
        msg_err.exec();
    }

}

void ChoiceSquad::on_cancel_change_Button_clicked()
{
    EditFile edit({},{});
    edit.read_file();
    *squads_vec = edit.get_vec_squads();
    *units_vec = edit.get_vec_units();
    fill_lists();
    ui->save_change_Button->setEnabled(false);
    ui->cancel_change_Button->setEnabled(false);
    ui->tableUnit->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWeapon->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void ChoiceSquad::on_changeUnitButton_clicked()
{
    ui->text_bar->setText("<html><head/><body><p align=center>Измените данные юнита</p><p align=center>и его оружия в таблице</p></body></html>");
    ui->tableUnit->setEditTriggers(QAbstractItemView::AllEditTriggers);
    ui->tableWeapon->setEditTriggers(QAbstractItemView::AllEditTriggers);
    ui->listUnits->setEnabled(false);
    ui->listSquads->setEnabled(false);
    ui->add_unit_button->setEnabled(true);
    ui->cancel_button->setEnabled(true);
    fun = 2;

}

void ChoiceSquad::on_cancel_button_clicked()
{
    ui->text_bar->setText("");
    ui->tableUnit->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWeapon->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listUnits->setEnabled(true);
    ui->listSquads->setEnabled(true);
    ui->add_unit_button->setEnabled(false);
    ui->cancel_button->setEnabled(false);
}

void ChoiceSquad::on_newSquadButton_clicked()
{
    ui_fill_squad = new FillSquad (this, squads_vec, units_vec);
    connect(ui_fill_squad, SIGNAL(update_main(QVector<Squad> *, QVector<Unit> *)),
            this, SLOT(update_window(QVector<Squad> *, QVector<Unit> *)));
    ui_fill_squad->show();
}

void ChoiceSquad::on_changeSquadButton_clicked()
{
    int need_num = need_num_squads(ui->listSquads->currentItem());
    Squad *ptr_sq = new Squad();
    *ptr_sq = (*squads_vec).at(need_num);

    ui_fill_squad = new FillSquad (this, ptr_sq , squads_vec, units_vec);
    connect(ui_fill_squad, SIGNAL(update_main(QVector<Squad> *, QVector<Unit> *)),
            this, SLOT(update_window(QVector<Squad> *, QVector<Unit> *)));
    ui_fill_squad->show();
}
