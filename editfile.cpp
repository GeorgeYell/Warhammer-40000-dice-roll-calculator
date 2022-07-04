#include "editfile.h"
#include <fstream>
#include <iostream>
#include <sstream>

EditFile::EditFile()
{
    vec_squads = {};
    vec_units = {};
}

EditFile::EditFile(QVector <Squad> squads, QVector <Unit> units)
{
    for (int i = 0; i < squads.size(); i++)
    {
        vec_squads.push_back(squads[i]);
    }
    for (int i = 0; i < units.size(); i++)
    {
        vec_units.push_back(units[i]);
    }
}



QDataStream& operator<<( QDataStream& d, const Weapon& u ) {
    d << u.get_name_weapon() << u.get_distance() << u.get_type() << u.get_S() << u.get_B() << u.get_U() << u.get_abilities();
    return d;
}

QDataStream& operator>>( QDataStream& d, Weapon& u ) {
    d >> u.name >> u.distance >> u.type >> u.S >> u.B >> u.U >> u.abilities;
    return d;
}

QDataStream& operator<<( QDataStream& d, const Unit& u ) {
    d << u.get_name_unit() << u.get_D() << u.get_BB() << u.get_NS() << u.get_SU() << u.get_St() << u.get_R() << u.get_A()<< u.get_Ld()<< u.get_Z();
    return d;
}

QDataStream& operator>>( QDataStream& d, Unit& u ) {
    d >> u.name >> u.D >> u.BB >> u.NS >> u.SU >> u.St >> u.R >> u.A >> u.Ld >> u.Z;
    return d;
}

QDataStream& operator<<( QDataStream& d, const Squad& u ) {
    d << u.get_name();
    return d;
}

QDataStream& operator>>( QDataStream& d, Squad& u ) {
    d >> u.name;
    return d;
}

void EditFile::save_file()
{
    QFile main_file("Save_file.bin"); //
    QFile size_vecs ("size_vec.bin");

    QDataStream stream( &main_file );
    QDataStream stream_size( &size_vecs );

    int size_unit = 0;
    int size_weapon = 0;
    int size_squad = 0;
    size_unit = vec_units.size();
    size_squad = vec_squads.size();

    size_vecs.open(QIODevice::WriteOnly);
    main_file.open(QIODevice::WriteOnly);


    //Запись вектора юнитов в файл и запись размеров векторов в файл size
    stream_size << size_unit;
    for (int i = 0; i < vec_units.size(); i++)
    {
        Unit temp_unit = vec_units[i];
        size_weapon = temp_unit.get_vec_weapons().size();

        stream_size << size_weapon;
        stream << temp_unit;

        for (int j = 0; j < temp_unit.get_vec_weapons().size(); j++)
        {
            Weapon weap = temp_unit.get_weapon(j);
            stream << weap;
        }
    }

    //Запись вектора отрядов в файл и запись размеров векторов в файл size
    stream_size << size_squad;
    for (int l = 0; l < size_squad; l++)
    {
        Squad temp_squad = vec_squads[l];
        size_unit = temp_squad.get_vec_units().size();

        stream_size << size_unit;
        stream << temp_squad;

        for (int i = 0; i < temp_squad.get_vec_units().size(); i++)
        {
            Unit temp_unit = temp_squad.get_vec_units()[i];
            size_weapon = temp_squad.get_unit(i).get_vec_weapons().size();

            stream_size << size_weapon;
            stream << temp_unit;

            for (int j = 0; j < temp_unit.get_vec_weapons().size(); j++)
            {
                Weapon weap = temp_unit.get_weapon(j);
                stream << weap;
            }
        }
    }

    main_file.close();
    size_vecs.close();
}

void EditFile::read_file()
{
    QFile main_file("Save_file.bin");
    QFile size_vecs_units ("size_vec.bin");

    QDataStream stream( &main_file );
    QDataStream stream_size( &size_vecs_units );

    int size_unit = 0;
    int size_weapon = 0;
    int size_squad = 0;

    size_vecs_units.open(QIODevice::ReadOnly);
    main_file.open(QIODevice::ReadOnly);

    //Чтение вектора юнитов из файла
    stream_size >> size_unit;
    for (int i = 0; i < size_unit; i++)
    {
        Unit tmp_unit;

        stream_size >> size_weapon;
        stream >> tmp_unit;

        vec_units.push_back(tmp_unit);
        for (int j = 0; j < size_weapon; j++)
        {
            Weapon weap;
            stream >> weap;
            vec_units[i].add_weapon(weap);
        }
    }

    //Чтение вектора отрядов из файла
    stream_size >> size_squad;
    for (int l = 0; l < size_squad; l++)
    {
        Squad temp_squad;
        stream_size >> size_unit;
        stream >> temp_squad;
        vec_squads.push_back(temp_squad);

        for (int i = 0; i < size_unit; i++)
        {
            stream_size >> size_weapon;
            Unit tmp_unit;
            stream >> tmp_unit;
            vec_squads[l].add_units(tmp_unit);
            for (int j = 0; j < size_weapon; j++)
            {
                Weapon weap;
                stream >> weap;
                tmp_unit.add_weapon(weap);
            }
            vec_squads[l].change_unit(tmp_unit, i);
        }

        //Алгоритм наполнения вектора индексами уникальных юнитов и подсчёта их колличества
        for(int i = 0; i < vec_squads[l].get_size_vec_units(); i++)
        {
            for(int j = 0; j < vec_squads[l].get_size_vec_num_ind_unit(); j++)
            {

                if (vec_squads[l].get_unit(i).get_name_unit() == vec_squads[l].get_unit(vec_squads[l].get_num_ind_unit(j)).get_name_unit())
                {
                   vec_squads[l].change_vec_quant_ind_unit(j, 1);
                   break;
                }
                else if (j == vec_squads[l].get_size_vec_num_ind_unit() - 1)
                {
                    vec_squads[l].add_num_ind_unit(i);
                    vec_squads[l].add_quant_ind_unit(1);
                    break;
                }
            }
        }
    }


    main_file.close();
    size_vecs_units.close();
}

QVector<Unit> EditFile::get_vec_units()
{
    return vec_units;
}

QVector<Squad> EditFile::get_vec_squads()
{
    return vec_squads;
}
