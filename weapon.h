#ifndef WEAPON_H
#define WEAPON_H
#include <QString>
#include <QVector>
#include <QDebug>
#include <QFile>
#include <QDataStream>
#include <QRect>


using namespace std;

class Weapon
{
private:
    QString name;
    int distance;
    QString type;
    QString abilities;

protected:
    int S;
    int B;
    int U;

public:
    Weapon();
    Weapon(QString name, int distance = 0, QString type = "-", int S = 0, int B = 0, int U = 0, QString abilities = "-");
    ~Weapon();


    friend QDataStream& operator>>( QDataStream& d, Weapon& u );

    Weapon save_file();

    void set_name (QString text);
    void set_distance(int number);
    void set_type(QString text);
    void set_abilities(QString text);
    void set_S(int n);
    void set_B(int n);
    void set_U(int n);

    QString get_name_weapon()const;
    int get_distance() const;
    QString get_type() const;
    int get_S()const;
    int get_B()const;
    int get_U()const;
    QString get_abilities()const;
};

#endif // WEAPON_H
