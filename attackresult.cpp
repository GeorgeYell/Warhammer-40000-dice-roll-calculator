#include "attackresult.h"
#include "ui_attackresult.h"

AttackResult::AttackResult(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AttackResult)
{

}

AttackResult::AttackResult(QWidget *parent, Fight *fight_obj, Battle *bat, int need_num) :
    QDialog(parent),
    ui(new Ui::AttackResult)
{   
    ui->setupUi(this);
    ui->tableResult->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableResult->setColumnWidth(0, 304);

    for (int i = 1; i < 5; i++)
        ui->tableResult->setColumnWidth(i, 70);

    fight = fight_obj;
    battle = bat;
    need_num_sqd = need_num;

    if (fight->get_fase()) // фаза ближнего боя
    {
        close_attack();
    } else // фаза дальнего боя
    {
        distance_attack();
    }



}

AttackResult::~AttackResult()
{
    delete ui;
}

void AttackResult::set_paint(bool hit, int i, int cow)
{
    if (hit)
        ui->tableResult->item(i, cow)->setBackground(Qt::green);
    else
        ui->tableResult->item(i, cow)->setBackground(Qt::red);
}

void AttackResult::distance_attack()
{
    int row = fight->get_vec_weapons().size();
    ui->tableResult->setRowCount(row);
    int count_damage = 0;
    int count_death = 0;
    for (int i = 0;fight->get_vec_defence_squad().size() > 0 && i < row; i++)
    {
        int roll = 0;
        bool hit_flag = false;
        bool damage = false;

        QTableWidgetItem *t_name = new QTableWidgetItem (fight->get_vec_weapons()[i].get_name_weapon());
        ui->tableResult->setItem(i, 0, t_name);

        //проверка на попадание
        roll = fight->roll();
        hit_flag = fight->check_hit(fight->get_attack_unit(i).get_NS(), roll);
        QTableWidgetItem *t_hit = new QTableWidgetItem (QString("%1").arg(roll));
        ui->tableResult->setItem(i, 1, t_hit);
        set_paint(hit_flag, i, 1);

        //Если попадание было, то проверка на ранение
        if (hit_flag)
        {
            roll = fight->roll();
            hit_flag = fight->check_injury(fight->get_vec_weapons()[i].get_S(),
                                           fight->get_defence_unit(0).get_St(), roll);
            QTableWidgetItem *t_injury = new QTableWidgetItem (QString("%1").arg(roll));
            ui->tableResult->setItem(i, 2, t_injury);
            set_paint(hit_flag, i, 2);
        }
        else
        {
            QTableWidgetItem *t_miss = new QTableWidgetItem ("");
            ui->tableResult->setItem(i, 2, t_miss);
            ui->tableResult->item(i, 2)->setBackground(Qt::gray);
        }

        //Если ранение было, то спас-бросок
        if(hit_flag)
        {
            roll = fight->roll();
            hit_flag = fight->check_save(fight->get_defence_unit(0).get_Z(), roll);
            QTableWidgetItem *t_save = new QTableWidgetItem (QString("%1").arg(roll));
            ui->tableResult->setItem(i, 3, t_save);
            set_paint(hit_flag, i, 3);
            if(hit_flag)
                damage = true;
        }
        else
        {
            QTableWidgetItem *t_miss = new QTableWidgetItem ("");
            ui->tableResult->setItem(i, 3, t_miss);
            ui->tableResult->item(i, 3)->setBackground(Qt::gray);
        }

        //Отображение и нанесение урона
        if (damage)
        {
            QTableWidgetItem *t_damage = new QTableWidgetItem (QString("%1").arg(fight->get_vec_weapons()[i].get_U()));
            ui->tableResult->setItem(i, 4, t_damage);
            ui->tableResult->item(i, 4)->font().setBold(true);
            ui->tableResult->item(i, 4)->setBackground(Qt::yellow);
            count_damage += fight->get_vec_weapons()[i].get_U();

            //Уменьшение здоровья и удаление усли Р == 0
            Unit *un_ptr = new Unit ();
            *un_ptr = fight->get_defence_unit(0);

            bool isDamage = fight->take_damage(fight->get_vec_weapons()[i].get_U(), need_num_sqd);
            if (!isDamage)
            {
                fight->death_unit();
                count_death++;
            }
        }
        else
        {
            QTableWidgetItem *t_miss = new QTableWidgetItem ("");
            ui->tableResult->setItem(i, 4, t_miss);
            ui->tableResult->item(i, 4)->setBackground(Qt::gray);
        }

        for (int j = 0; j < 5; j++)
        {
            if (j != 0 && ui->tableResult->item(i,j) != 0)
                ui->tableResult->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }
    }

    ui->damage_label->setText(QString("%1").arg(count_damage));
    ui->death_label->setText(QString("%1").arg(count_death));

}

void AttackResult::close_attack()
{

    int row;
    if (battle->get_n_player() == 1)
    {
        row = fight->get_vec_weapons().size();
    }else
    {
        row = fight->get_vec_defence_weap().size();
    }
    ui->tableResult->setRowCount(row);
    int count_damage = 0;
    int count_death = 0;
    for (int i = 0;fight->get_vec_defence_squad().size() > 0 && i < row; i++)
    {
        int roll = 0;
        bool hit_flag = false;
        bool damage = false;

        QTableWidgetItem *t_name = new QTableWidgetItem (fight->get_vec_weapons()[i].get_name_weapon());
        ui->tableResult->setItem(i, 0, t_name);

        //проверка на попадание
        roll = fight->roll();
        hit_flag = fight->check_hit(fight->get_attack_unit(i).get_BB(), roll);
        QTableWidgetItem *t_hit = new QTableWidgetItem (QString("%1").arg(roll));
        ui->tableResult->setItem(i, 1, t_hit);
        set_paint(hit_flag, i, 1);

        //Если попадание было, то проверка на ранение
        if (hit_flag)
        {
            roll = fight->roll();
            hit_flag = fight->check_injury(fight->get_vec_weapons()[i].get_S() + fight->get_attack_unit(i).get_SU(),
                                           fight->get_defence_unit(0).get_St(), roll);
            QTableWidgetItem *t_injury = new QTableWidgetItem (QString("%1").arg(roll));
            ui->tableResult->setItem(i, 2, t_injury);
            set_paint(hit_flag, i, 2);
        }
        else
        {
            QTableWidgetItem *t_miss = new QTableWidgetItem ("");
            ui->tableResult->setItem(i, 2, t_miss);
            ui->tableResult->item(i, 2)->setBackground(Qt::gray);
        }

        //Если ранение было, то спас-бросок
        if(hit_flag)
        {
            roll = fight->roll();
            hit_flag = fight->check_save(fight->get_defence_unit(0).get_Z(), roll);
            QTableWidgetItem *t_save = new QTableWidgetItem (QString("%1").arg(roll));
            ui->tableResult->setItem(i, 3, t_save);
            set_paint(hit_flag, i, 3);
            if(hit_flag)
                damage = true;
        }
        else
        {
            QTableWidgetItem *t_miss = new QTableWidgetItem ("");
            ui->tableResult->setItem(i, 3, t_miss);
            ui->tableResult->item(i, 3)->setBackground(Qt::gray);
        }

        //Отображение и нанесение урона
        if (damage)
        {
            QTableWidgetItem *t_damage = new QTableWidgetItem (QString("%1").arg(fight->get_vec_weapons()[i].get_U()));
            ui->tableResult->setItem(i, 4, t_damage);
            ui->tableResult->item(i, 4)->font().setBold(true);
            ui->tableResult->item(i, 4)->setBackground(Qt::yellow);
            count_damage += fight->get_vec_weapons()[i].get_U();

            //Уменьшение здоровья и удаление усли Р == 0
            Unit *un_ptr = new Unit ();
            *un_ptr = fight->get_defence_unit(0);

            bool isDamage = fight->take_damage(fight->get_vec_weapons()[i].get_U(), need_num_sqd);
            if (!isDamage)
            {
                fight->death_unit();
                count_death++;
            }
        }
        else
        {
            QTableWidgetItem *t_miss = new QTableWidgetItem ("");
            ui->tableResult->setItem(i, 4, t_miss);
            ui->tableResult->item(i, 4)->setBackground(Qt::gray);
        }

        for (int j = 0; j < 5; j++)
        {
            if (j != 0 && ui->tableResult->item(i,j) != 0)
                ui->tableResult->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }
    }

    ui->damage_label->setText(QString("%1").arg(count_damage));
    ui->death_label->setText(QString("%1").arg(count_death));
}

void AttackResult::on_ok_button_clicked()
{

    if(battle->get_fase() == 0)
        emit set_battlefield();
    else if (battle->get_fase() == 1)
    {
        emit set_battlefield(); /*
        (*fight).change_vectors((*fight).get_vec_weapons(), (*fight).get_vec_defence_weap(),
                                (*fight).get_vec_attack_squad(), (*fight).get_vec_defence_squad());
        ui->label->setText("Ответный удар");
        ui->tableResult->clear();
        close_attack();
        */

    }

    this->close();
}
