#ifndef BATTLE_H
#define BATTLE_H

#include "squad.h"

class Battle;  // Battle - Singelton

class BattleDestroyer //Класс - деструктор
{
  private:
    Battle* p_instance; //указатель но объект Singelton
  public:
    ~BattleDestroyer();
    void initialize( Battle* p ); // Инициализация
};

class Battle : public Squad
{


private:
    static Battle* p_instance;
    static BattleDestroyer destroyer;

    QVector <Squad> command_one_vec;
    QVector <Squad> command_two_vec;
    int fase;
    int n_player;

protected:
    Battle() { }
    Battle( const Battle& );
    Battle& operator=( Battle& );
    ~Battle() { }
    friend class BattleDestroyer;

public:
    static Battle& getInstance(); // Метод для создания объекта
    void add_squad_vec_one(Squad sqd);
    void add_squad_vec_two(Squad sqd);
    void set_fase (int n);
    int get_fase();
    int get_size_vec_command_one();
    int get_size_vec_command_two();
    QVector <Squad> get_vec_com_one();
    QVector <Squad> get_vec_com_two();
    void set_n_player(int n);
    int get_n_player();
    void destroy_object();
    bool take_damage(int n, int i, Battle *battle);
    void death_unit(int need_num_sqd);
    void death_squad(int need_num_sqd);
    void reset_num_ind_unit(QVector <Squad> *vec_squads, int need_num);
    void set_R_first_unit(int value, int need_num_sqd);
};

#endif // BATTLE_H
