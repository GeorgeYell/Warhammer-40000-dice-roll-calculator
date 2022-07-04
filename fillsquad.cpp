#include "fillsquad.h"
#include "ui_fillsquad.h"


FillSquad::FillSquad(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FillSquad)
{
        ui->setupUi(this);
}

FillSquad::FillSquad(QWidget *parent, QVector <Squad> *vec_squads, QVector <Unit> *vec_unit) :
    QDialog(parent),
    ui(new Ui::FillSquad)
{
    ui->setupUi(this);   
    squads_vec = vec_squads;
    units_vec = vec_unit;
    change_b = false;
    for (int i = 0; i < units_vec->size(); i++)
    {
        ui->UnitComboBox->addItem((*vec_unit)[i].get_name_unit());
        ui->UnitComboBox_2->addItem((*vec_unit)[i].get_name_unit());
    }
}

FillSquad::FillSquad(QWidget *parent, Squad *squad, QVector<Squad> *vec_squads, QVector<Unit> *vec_unit) :
    QDialog(parent),
    ui(new Ui::FillSquad)
{
    ui->setupUi(this);
    squads_vec = vec_squads;
    units_vec = vec_unit;
    change_b = true;
    need_num = need_num_squad(squad->get_name());
    for (int i = 0; i < units_vec->size(); i++)
    {
        ui->UnitComboBox->addItem((*vec_unit)[i].get_name_unit());
        ui->UnitComboBox_2->addItem((*vec_unit)[i].get_name_unit());
    }

    ui->name_squad_edit->setText(squad->get_name());
    ui->spinBoxOne->setValue(squad->get_quant_ind_unit(0));
    ui->UnitComboBox->setCurrentText(squad->get_unit(0).get_name_unit());
    if (squad->get_size_vec_num_ind_unit() > 1)
    {
        int need_n = squad->get_num_ind_unit(1);
        ui->spinBoxTwo->setValue(squad->get_quant_ind_unit(1));
        ui->UnitComboBox_2->setCurrentText(squad->get_unit(need_n).get_name_unit());
    }


}

FillSquad::~FillSquad()
{
    delete ui;
}

int FillSquad::need_num_units(QString name)
{
    //Поиск совпадений имен из списка с вектором
    for(int i = 0; i < (*units_vec).size(); i++)
        if ((*units_vec).value(i).get_name_unit() == name)
            return i; // индекс нужного юнита
    return -1;
}

int FillSquad::need_num_squad(QString name)
{
    //Поиск совпадений имен из списка с вектором
    for(int i = 0; i < (*squads_vec).size(); i++)
        if ((*squads_vec)[i].get_name() == name)
            return i; // индекс нужного юнита
    return -1;
}

void FillSquad::on_cancelButton_clicked()
{
    this->close();
    emit firstWindow();
}

void FillSquad::on_acceptButton_clicked()
{
    bool err = false;
    QString err_msg = "";
    QString name_unit_one = ui->UnitComboBox->currentText();
    QString name_unit_two = ui->UnitComboBox_2->currentText();
    int n_unit_one = ui->spinBoxOne->value();
    int n_unit_two = ui->spinBoxTwo->value();

    QString name_squads = ui->name_squad_edit->toPlainText();
    if (name_squads == "")
    {
        err = true;
        err_msg = "Введите имя отряда!";
    }
    for (int i = 0; i < squads_vec->size(); i++)
    {
        if (name_squads == (*squads_vec)[i].get_name() && !change_b)
        {
            err = true;
            err_msg = "Отряд с таким именем уже существует!";
        }
    }


    if(!err)
    {
        Unit un_one = (*units_vec)[need_num_units(name_unit_one)];
        Unit un_two = (*units_vec)[need_num_units(name_unit_two)];
        Squad squad;

        squad.set_name(name_squads);
        for(int i = 0; i < n_unit_one; i++)
            squad.add_units(un_one);

        for(int i = 0; ui->spinBoxTwo->value() != 0 && i < n_unit_two; i++)
            squad.add_units(un_two);

        //Алгоритм наполнения вектора индексами уникальных юнитов и подсчёта их колличества
        for(int i = 0; i < squad.get_size_vec_units(); i++)
        {
            for(int j = 0; j < squad.get_size_vec_num_ind_unit(); j++)
            {

                if (squad.get_unit(i).get_name_unit() == squad.get_unit(squad.get_num_ind_unit(j)).get_name_unit())
                {
                   squad.change_vec_quant_ind_unit(j, 1);
                   break;
                }
                else if (j == squad.get_size_vec_num_ind_unit() - 1)
                {
                    squad.add_num_ind_unit(i);
                    squad.add_quant_ind_unit(1);
                    break;
                }
            }
        }

        if (!change_b)
        {
            (*squads_vec).push_back(squad);
        } else if (need_num > -1)
        {
            (*squads_vec)[need_num] = squad;
        }



        emit update_main(squads_vec, units_vec);
        this->close();
    }
    else
    {
        QMessageBox msg_err;
        msg_err.setText("Ошибка ввода!");
        msg_err.setInformativeText(err_msg);
        msg_err.setStandardButtons(QMessageBox::Ok);
        msg_err.setDefaultButton(QMessageBox::Ok);
        msg_err.setIcon(QMessageBox::Warning);
        msg_err.exec();
    }

}
