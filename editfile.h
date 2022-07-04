#ifndef EDITFILE_H
#define EDITFILE_H
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "squad.h"


class EditFile
{

QVector <Squad> vec_squads;
QVector <Unit> vec_units;

public:
    EditFile();
    EditFile(QVector <Squad> squads ={}, QVector <Unit> units = {});

    void save_file();
    void read_file();

    QVector <Unit> get_vec_units();
    QVector <Squad> get_vec_squads();


};

#endif // EDITFILE_H
