#include "weapon.h"

Weapon::Weapon()
{

}

Weapon::Weapon(QString xname, int xdistance, QString xtype, int xS, int xB, int xU, QString xabilities)
{
    name = xname;
    distance = xdistance;
    type = xtype;
    S = xS;
    B = xB;
    U = xU;
    abilities = xabilities;
}

Weapon::~Weapon()
{

}




void Weapon::set_name(QString text) {name = text;}

void Weapon::set_distance(int number) {distance = number;}

void Weapon::set_type(QString text) {type = text;}

void Weapon::set_abilities(QString text) {abilities = text;}

void Weapon::set_S(int n) {S = n;}

void Weapon::set_B(int n) {B = n;}

void Weapon::set_U(int n) {U = n;}

QString Weapon::get_name_weapon() const{return name;}

int Weapon::get_distance() const{return distance;}

QString Weapon::get_type() const{return type;}

int Weapon::get_S() const{return S;}

int Weapon::get_B() const{return B;}

int Weapon::get_U() const{return U;}

QString Weapon::get_abilities() const{return abilities;}

/*
QDataStream& operator<<( QDataStream& d, const Weapon& u ) {
    d << u.get_name_weapon() << u.get_distance() << u.get_type() << u.get_S() << u.get_B() << u.get_U() << u.get_abilities();
    return d;
}

QDataStream& operator>>( QDataStream& d, Weapon& u ) {
    d >> u.name >> u.distance >> u.type >> u.S >> u.B >> u.U >> u.abilities;
    return d;
}

Weapon Weapon::save_file()
{
    QFile file("Weapon.bin");
    QDataStream stream( &file );
    Weapon bolt("Опустошающий болтовой пистолет", 18, "Пистолет 1", 4, -1, 1);
    file.open( QIODevice::WriteOnly );
    stream << bolt;
    file.close();

    file.open( QIODevice::ReadOnly );
    Weapon bolter;
    stream >> bolter;
    file.close();

    return bolter;
}
*/
