#include "squad.h"

Squad::Squad()
{
    vec_quantity_ind_unit = {0};
    vec_num_ind_unit = {0};
}

Squad::Squad(QString xname)
{
    name = xname;
    vec_quantity_ind_unit = {0};
    vec_num_ind_unit = {0};
}

void Squad::add_units(Unit unit)
{
    vec_units.push_back(unit);
}

void Squad::add_num_ind_unit(int n)
{
    vec_num_ind_unit.push_back(n);
}

void Squad::add_quant_ind_unit(int n)
{
    vec_quantity_ind_unit.push_back(n);
}

void Squad::change_unit(Unit u, int n)
{
    vec_units[n] = u;
}

void Squad::change_vec_quant_ind_unit(int n, int number)
{
    vec_quantity_ind_unit[n] += number;
}

void Squad::set_name(QString text)
{
    name = text;
}

bool Squad::del_unit(int n)
{
    if (n < vec_units.size())
    {
        vec_units.takeAt(n);
        return true;
    }
    else
    {
        return false;
    }

}

void Squad::insert_unit(int n, int i, Unit unit)
{
    vec_units.insert(this->get_num_ind_unit(n) + i, unit);
}

void Squad::clear_vecs_ind_un()
{
    vec_num_ind_unit.clear();
    vec_quantity_ind_unit.clear();
}

QString Squad::get_name() const {return name;}

Unit Squad::get_unit(int i)
{
    return vec_units[i];
}

QVector<Unit> Squad::get_vec_units()
{
    return vec_units;
}

QVector<int> Squad::get_vec_num_ind_units()
{
    return vec_num_ind_unit;
}

int Squad::get_size_vec_units()
{
    return vec_units.size();
}

int Squad::get_size_vec_num_ind_unit()
{
    return vec_num_ind_unit.size();
}

int Squad::get_num_ind_unit(int n)
{
    return vec_num_ind_unit.value(n);
}

int Squad::get_quant_ind_unit(int n)
{
    return vec_quantity_ind_unit.value(n);
}
