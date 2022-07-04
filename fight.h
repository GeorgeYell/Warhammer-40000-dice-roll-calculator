#ifndef FIGHT_H
#define FIGHT_H

#include "squad.h"
#include "battle.h"
#include "random.h"

class Fight : public Squad
{
private:
    QVector <Weapon> attack_weapon_vec;
    QVector <Weapon> defence_weapon_vec;
    QVector <Unit> attack_squad_vec;
    QVector <Unit> defence_squad_vec;
    bool close_combat;
    Battle *battle;

public:
    Fight();
    Fight(QVector <Weapon> weapon_vec, QVector <Unit> vec_atack_unit, QVector <Unit> vec_defence_unit, Battle *bat);
    Fight(QVector <Weapon> attack_weapon_vec, QVector <Unit> vec_atack_unit,QVector <Weapon> defence_weapon_vec, QVector <Unit> vec_defence_unit, Battle *bat);

    QVector <Weapon> get_vec_weapons();
    QVector <Weapon> get_vec_defence_weap();
    QVector <Unit> get_vec_attack_squad();
    QVector <Unit> get_vec_defence_squad();
    int roll();
    bool check_hit(int NS, int value);
    bool check_injury(int S, int St, int value);
    bool check_save(int Z, int value);
    Unit get_attack_unit(int i);
    Unit get_defence_unit (int i);
    bool get_fase();
    bool take_damage(int n, int i);
    bool death_unit();
    bool change_vectors(QVector <Weapon> attack_weapon_vec, QVector <Weapon> defence_weapon_vec,
                        QVector <Unit> attack_squad_vec, QVector <Unit> defence_squad_vec);

};

#endif // FIGHT_H
