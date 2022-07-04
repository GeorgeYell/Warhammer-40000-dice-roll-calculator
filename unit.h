#ifndef UNIT_H
#define UNIT_H

#include "weapon.h"

class Unit : public Weapon
{
protected:
    QString name;
    int D;
    int BB;
    int NS;
    int SU;
    int St;
    int R;
    int A;
    int Ld;
    int Z;
    QVector <Weapon> vec_weapons;
    bool shelter;

public:
    Unit();
    Unit(QString xname, int xD = 0, int xBB = 0, int xNS = 0, int xSU = 0, int xSt = 0, int xR = 0,
         int xA = 0, int xLd = 0, int xZ = 0);

    friend QDataStream& operator>>( QDataStream& d, Unit& u );

    void add_weapon( Weapon weapon);

    int get_size_vec_weapon();
    Weapon get_weapon (int n);

    QString get_name_unit() const;
    QVector <Weapon> get_vec_weapons();
    int get_D()const;
    int get_BB()const;
    int get_NS()const;
    int get_SU()const;
    int get_St()const;
    int get_R()const;
    int get_A()const;
    int get_Ld()const;
    int get_Z()const;

    void set_D(int n);
    void set_BB(int n);
    void set_NS(int n);
    void set_SU(int n);
    void set_St(int n);
    void set_R(int n);
    void set_A(int n);
    void set_Ld(int n);
    void set_Z(int n);

    void clear_vec_weapon();
    void del_weapon(int n);
    void set_shelter(bool b);
    bool get_shelter();
    bool take_damage(int n, Unit *un);

};

#endif // UNIT_H
