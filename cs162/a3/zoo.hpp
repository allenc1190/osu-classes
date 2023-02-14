#ifndef zoo_hpp
#define zoo_hpp

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "animal.hpp"
#include "monkey.hpp"
#include "sea_otter.hpp"
#include "meerkat.hpp"

using namespace std;

class zoo{
    private:
    int bank;
    int monkey_amt, otter_amt, meerkat_amt;
    int monkey_total, otter_total, meerkat_total;
    animal *monkeys;
    animal *sea_otters;
    animal *meerkats;


    public:
    zoo();
    int ask_monkey_amt(int monkey_total);
    int ask_otter_amt(int otter_total);
    int ask_meerkat_amt(int meerkat_total);
    int buy_monkey(int old_monkey_amt, int monkey_total);
    int buy_sea_otter(int bank, int old_otter_amt, int otter_total);
    int buy_meerkat(int bank, int old_meerkat_amt, int meerkat_total);
    int buy_animals(int bank, int monkey_total, int otter_total, int meerkat_total, int &old_monkey_amt);
    int purchase_food(int bank, int monkey_amt, int otter_amt, int meerkat_amt);
    void add_monkey(int old_monkey_amt);
    void add_otter(int old_otter_amt);
    void add_meerkat(int old_meerkat_amt);
    int sick_animal(int bank, int &old_monkey_amt);
    int monkey_amt_ask(int bank);
    int otter_amt_ask();
    int meerkat_amt_ask();
    void delete_monkey(int monkey_sick, int monkey_amt);
    void delete_otter(int otter_sick, int otter_amt);
    void delete_meerkat(int meerkat_sick, int meerkat_amt);
    void give_birth(int &old_monkey_amt, int old_otter_amt, int old_meerkat_amt);
    void fill_monkey(animal m, int old_monkey_amt);
    void fill_otter(animal o, int old_otter_amt);
    void fill_meerkat(animal mk, int old_meerkat_kat);
    int revenue(int bank, int &monkey_total, int &otter_total, int &meerkat_total);
    void start_game();
    ~zoo();

    //void give_birth(int babies, int old_monkey_amt, int old_otter_amt, int old_meerkat_amt, int baby_chance);
};

#endif