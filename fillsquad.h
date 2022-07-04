#ifndef FILLSQUAD_H
#define FILLSQUAD_H

#include <QDialog>
#include <QMessageBox>
#include <squad.h>

namespace Ui {
class FillSquad;
}

class FillSquad : public QDialog
{
    Q_OBJECT

public:
    explicit FillSquad(QWidget *parent = nullptr);
    FillSquad(QWidget *parent = nullptr, QVector <Squad> *vec_squads = {}, QVector <Unit> *vec_unit = {});
    FillSquad(QWidget *parent = nullptr, Squad *squad = nullptr, QVector <Squad> *vec_squads = {}, QVector <Unit> *vec_unit = {});
    ~FillSquad();

    int need_num_units (QString name);
    int need_num_squad (QString name);


signals:
    void firstWindow();
    void update_main(QVector<Squad> *, QVector<Unit> *);

private slots:
    void on_cancelButton_clicked();

    void on_acceptButton_clicked();

private:
    Ui::FillSquad *ui;
    QVector <Squad> *squads_vec;
    QVector <Unit> *units_vec;
    bool change_b;
    int need_num;
};

#endif // FILLSQUAD_H
