#include "fight.h"

Fight::Fight()
{

}

Fight::Fight(QVector <Weapon> weapon_vec, QVector <Unit> vec_atack_unit, QVector <Unit> vec_defence_unit, Battle *bat)
{
    battle = bat;
    attack_weapon_vec = weapon_vec;
    attack_squad_vec = vec_atack_unit;
    defence_squad_vec = vec_defence_unit;
    if(bat->get_fase() == 0)
        close_combat = false;
    else if (bat->get_fase() == 1)
        close_combat = true;
}

Fight::Fight(QVector <Weapon> attack_weapon, QVector <Unit> vec_atack_unit,QVector <Weapon> defence_weapon, QVector <Unit> vec_defence_unit, Battle *bat)
{
    battle = bat;
    attack_weapon_vec = attack_weapon;
    defence_weapon_vec = defence_weapon;
    attack_squad_vec = vec_atack_unit;
    defence_squad_vec = vec_defence_unit;
    if(bat->get_fase() == 0)
        close_combat = false;
    else if (bat->get_fase() == 1)
        close_combat = true;
}

QVector<Weapon> Fight::get_vec_weapons()
{
    return attack_weapon_vec;
}

QVector<Weapon> Fight::get_vec_defence_weap()
{
    return defence_weapon_vec;
}

QVector<Unit> Fight::get_vec_attack_squad()
{
    return attack_squad_vec;
}

QVector<Unit> Fight::get_vec_defence_squad()
{
    return defence_squad_vec;
}

int Fight::roll()
{
    return Random::get(1,6);
}

bool Fight::check_hit(int NS, int value)
{
    if (value >= NS)
        return true;
    else
        return false;
}

bool Fight::check_injury(int S, int St, int value)
{
    if(S > St && S/St >= 2 && value >= 2)
        return true;
    else if (S > St && value >= 3)
        return true;
    else if (S == St && value >= 4)
        return true;
    else if (S < St && value >= 5)
        return true;
    else if (S < St && St/S >= 2 && value >= 6)
        return true;

    return false;
}

bool Fight::check_save(int Z, int value)
{
    if (Z >= value)
        return true;
    else
        return false;
}

Unit Fight::get_attack_unit(int i)
{
    return attack_squad_vec[i];
}

Unit Fight::get_defence_unit(int i)
{
    return defence_squad_vec[i];
}

bool Fight::get_fase()
{
    return close_combat;
}

bool Fight::take_damage(int n, int i)
{
    if (defence_squad_vec[i].get_R() - n > 0)
    {
        defence_squad_vec[i].set_R(defence_squad_vec[i].get_R() - 1);
        return true;
    }
    else
        return false;

}

bool Fight::death_unit ()
{
    if (defence_squad_vec.size() > 0)
    {
        defence_squad_vec.pop_front();
        return true;
    }
    else
        return false;

}

bool Fight::change_vectors(QVector<Weapon> attack_weapon_vec, QVector<Weapon> defence_weapon_vec, QVector<Unit> attack_squad_vec, QVector<Unit> defence_squad_vec)
{
    QVector <Weapon> temp_weap;
    QVector <Unit> temp_unit;
    temp_unit = attack_squad_vec;
    temp_weap = attack_weapon_vec;
    attack_squad_vec = defence_squad_vec;
    attack_weapon_vec = defence_weapon_vec;
    defence_squad_vec = temp_unit;
    defence_weapon_vec = temp_weap;
}

