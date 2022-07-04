#include "battle.h"

Battle * Battle::p_instance = 0;
BattleDestroyer Battle::destroyer;

BattleDestroyer::~BattleDestroyer()
{
    delete p_instance;
}

void BattleDestroyer::initialize( Battle* p )
{
    p_instance = p;
}

Battle& Battle::getInstance()
{
    if(!p_instance)
    {
        p_instance = new Battle();
        destroyer.initialize(p_instance);
    }
    return *p_instance;
}

void Battle::add_squad_vec_one(Squad sqd)
{
    command_one_vec.push_back(sqd);
}

void Battle::add_squad_vec_two(Squad sqd)
{
    command_two_vec.push_back(sqd);
}

void Battle::set_fase(int n)
{
    fase = n;
}

int Battle::get_fase()
{
    return fase;
}

int Battle::get_size_vec_command_one()
{
    return command_one_vec.size();
}

int Battle::get_size_vec_command_two()
{
    return command_two_vec.size();
}

QVector<Squad> Battle::get_vec_com_one()
{
    return command_one_vec;
}

QVector<Squad> Battle::get_vec_com_two()
{
    return command_two_vec;
}

void Battle::set_n_player(int n)
{
    n_player = n;
}

int Battle::get_n_player()
{
    return n_player;
}

void Battle::destroy_object()
{
    command_one_vec.clear();
    command_two_vec.clear();
    fase = 0;
    n_player = 1;
}

bool Battle::take_damage(int n, int need_num_sqd, Battle *battle)
{

    if (n_player != 1)
    {
        if (battle->get_vec_com_one()[need_num_sqd].get_unit(0).get_R() - n > 0)
        {
            battle->set_R_first_unit(battle->get_vec_com_one()[need_num_sqd].get_unit(0).get_R() - n, need_num_sqd);
            return true;
        }
        else
        {
            battle->death_unit(need_num_sqd);
            return false;
        }

    } else
    {
        if (battle->get_vec_com_two()[need_num_sqd].get_vec_units()[0].get_R() - n > 0)
        {
            battle->set_R_first_unit((battle->get_vec_com_two()[need_num_sqd].get_vec_units()[0].get_R() - n), need_num_sqd);
            return true;
        }
        else
        {
            battle->death_unit(need_num_sqd);
            return false;
        }
    }


}

void Battle::death_unit(int need_num_sqd)
{
    if (n_player == 1)
    {
        if (command_two_vec[need_num_sqd].get_size_vec_units() > 0)
            command_two_vec[need_num_sqd].get_vec_units().pop_front();
        else
            death_squad(need_num_sqd);
    }
    else
    {
        if (command_one_vec[need_num_sqd].get_size_vec_units() > 0)
            command_one_vec[need_num_sqd].get_vec_units().pop_front();
        else
            death_squad(need_num_sqd);
    }
}

void Battle::death_squad(int need_num_sqd)
{
    if (n_player == 1)
    {
        command_two_vec.remove(need_num_sqd);
    }
    else
    {
        command_one_vec.remove(need_num_sqd);
    }
}

void Battle::reset_num_ind_unit(QVector <Squad> *vec_squads, int need_num)
{
    int l = need_num;

    (*vec_squads)[l].clear_vecs_ind_un();

    //Алгоритм наполнения вектора индексами уникальных юнитов и подсчёта их колличества
    for(int i = 0; i < (*vec_squads)[l].get_size_vec_units(); i++)
    {
        for(int j = 0; j < (*vec_squads)[l].get_size_vec_num_ind_unit(); j++)
        {

            if ((*vec_squads)[l].get_unit(i).get_name_unit() == (*vec_squads)[l].get_unit((*vec_squads)[l].get_num_ind_unit(j)).get_name_unit())
            {
               (*vec_squads)[l].change_vec_quant_ind_unit(j, 1);
               break;
            }
            else if (j == (*vec_squads)[l].get_size_vec_num_ind_unit() - 1)
            {
                (*vec_squads)[l].add_num_ind_unit(i);
                (*vec_squads)[l].add_quant_ind_unit(1);
                break;
            }
        }
    }
}

void Battle::set_R_first_unit(int value, int need_num_sqd)
{
    command_one_vec[need_num_sqd].get_unit(0).set_R(value);
}
