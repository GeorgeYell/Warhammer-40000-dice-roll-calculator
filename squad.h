#ifndef SQUAD_H
#define SQUAD_H

#include "unit.h"


class Squad : public Unit
{
protected:
    QString name;
    QVector <Unit> vec_units;
    QVector <int> vec_num_ind_unit;
    QVector <int> vec_quantity_ind_unit;

public:

    Squad();
    Squad(QString xname);

    friend QDataStream& operator>>( QDataStream& d, Squad& u );

    void add_units(Unit unit);
    void add_num_ind_unit(int n);
    void add_quant_ind_unit(int n);
    void change_unit (Unit u, int n);
    void change_vec_quant_ind_unit(int n, int number);
    void set_name(QString text);
    bool del_unit (int n);
    void insert_unit(int n, int i, Unit unit);
    void clear_vecs_ind_un();


    QString get_name () const;
    Unit get_unit(int i);
    QVector <Unit> get_vec_units();
    QVector <int> get_vec_num_ind_units();
    int get_size_vec_units();
    int get_size_vec_num_ind_unit();
    int get_num_ind_unit(int n);
    int get_quant_ind_unit(int n);


};

#endif // SQUAD_H
