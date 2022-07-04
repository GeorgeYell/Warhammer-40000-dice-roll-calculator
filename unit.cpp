#include "unit.h"

Unit::Unit()
{
    name = "";
    D = 0;
    BB = 0;
    NS = 0;
    SU = 0;
    St = 0;
    R = 0;
    A = 0;
    Ld = 0;
    Z = 0;
    vec_weapons = {};
}

Unit::Unit(QString xname, int xD, int xBB, int xNS, int xSU, int xSt, int xR, int xA, int xLd, int xZ)
{
    name = xname;
    D = xD;
    BB = xBB;
    NS = xNS;
    SU = xSU;
    St = xSt;
    R = xR;
    A = xA;
    Ld = xLd;
    Z = xZ;
}


void Unit::add_weapon(Weapon weapon)
{
    vec_weapons.push_back(weapon);
}

int Unit::get_size_vec_weapon()
{
    return vec_weapons.size();
}

Weapon Unit::get_weapon(int n)
{
    return vec_weapons.value(n);
}

QString Unit::get_name_unit()const{return name;}

QVector <Weapon> Unit::get_vec_weapons()
{
    return vec_weapons;
}

int Unit::get_D() const{return D;}

int Unit::get_BB() const{return BB;}

int Unit::get_NS() const{return NS;}

int Unit::get_SU() const{return SU;}

int Unit::get_St() const{return St;}

int Unit::get_R() const{return R;}

int Unit::get_A() const{return A;}

int Unit::get_Ld() const{return Ld;}

int Unit::get_Z() const{return Z;}

void Unit::set_D(int n)
{
    D = n;
}

void Unit::set_BB(int n)
{
    BB = n;
}

void Unit::set_NS(int n)
{
    NS = n;
}

void Unit::set_SU(int n)
{
    SU = n;
}

void Unit::set_St(int n)
{
    St = n;
}

void Unit::set_R(int n)
{
    R = n;
}

void Unit::set_A(int n)
{
    A = n;
}

void Unit::set_Ld(int n)
{
    Ld = n;
}

void Unit::set_Z(int n)
{
    Z = n;
}

void Unit::clear_vec_weapon()
{
    vec_weapons.clear();
}

void Unit::del_weapon(int n)
{
    vec_weapons.remove(n);
}

void Unit::set_shelter(bool b)
{
    shelter = b;
}

bool Unit::get_shelter()
{
    return shelter;
}

bool Unit::take_damage(int n , Unit *un)
{
    if (R - n > 0)
    {
        un->set_R(un->get_R() - n);
        return true;
    }
    else
        return false;

}

