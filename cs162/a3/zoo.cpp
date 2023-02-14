#include <iostream>
#include <cstdlib>
#include <ctime>
#include "zoo.hpp"

using namespace std;

/**************************************************
** Function: zoo
** Description: constructor
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
zoo::zoo(){
    bank = 100000;
    monkey_amt = 0;
    otter_amt = 0;
    meerkat_amt = 0;
    monkeys = new animal [monkey_amt];
    sea_otters = new animal [otter_amt];
    meerkats = new animal [meerkat_amt];
}

/**************************************************
** Function: monkey_amt_ask
** Description: ask for how many monkey's to buy
** Parameters: bank
** Pre-Conditions: none
** Post-Conditions: amount of monkeys to buy
***************************************************/ 
int zoo::monkey_amt_ask(int bank){
    int monkey_total;
    bool again = true;

    while(again){
        cout << "How many monkeys do you want to buy for $15,000 each? (0-2): ";
        cin >> monkey_total;

        if(monkey_total ==0 || monkey_total == 1 || monkey_total == 2){
            break;
        }
        else{
            again = true;
        }
    }

    return monkey_total;
}


/**************************************************
** Function: ask_monkey_amt
** Description: gets the amount of monkeys before the user buys more
** Parameters: monkey_total
** Pre-Conditions: none
** Post-Conditions: returns amount of monkeys before buying more
***************************************************/ 
int zoo::ask_monkey_amt(int monkey_total){
    bool again = true;
    int old_monkey_amt;
    
    while(again){
        //cout << "You have $" << bank << " in your bank" << endl;
        //cout << "How many monkeys do you want to buy for $15,000 each? (0-2): ";
        //cin >> monkey_total;

        if(monkey_total >= 0 && monkey_total <= 2){
            old_monkey_amt = monkey_amt;
            monkey_amt = monkey_amt + monkey_total;
            //cout << "You now have $" << bank << endl;
            break;
        }
        else if(monkey_total < 0 || monkey_total > 2){
            //cout << "Enter a number between 0-2" << endl;
            again = true;
        }
    }

    return old_monkey_amt;
}

/**************************************************
** Function: buy_monkey
** Description: subtracts money from bank and creates a monkey array
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: creates monkey array
***************************************************/ 
int zoo::buy_monkey(int old_monkey_amt, int monkey_total){
    int monkey_cost;
    bool again = true;
    
    monkey_cost = monkey_total * 15000;

    if(bank > 0 && monkey_amt > 0 && monkey_amt <= 2){
        if(monkey_total == 1 || monkey_total == 2){
            bank -= monkey_cost;
            cout << "You now have $" << bank << endl;
            for(int i =0; i < monkey_total; i++){
            fill_monkey(monkey(2), old_monkey_amt);
            }
        }
    }
    else if(monkey_amt < 0 || monkey_amt > 2){
        //cout << "Enter a number between 0-2" << endl;
        again = true;
    }
    else if(bank < 0){
        cout << "You do not have enough money." << endl;
        again = true;
    }

    return bank;
}

/**************************************************
** Function: otter_amt_ask
** Description: ask for how many sea otters to buy
** Parameters:
** Pre-Conditions: none
** Post-Conditions: amount of sea otters to buy
***************************************************/ 
int zoo::otter_amt_ask(){
    int otter_total;
    bool again = true;

    while(again){
        //cout << "You have $" << bank << " in your bank" << endl;
        cout << "How many sea otters do you want to buy for $5,000 each? (0-2): ";
        cin >> otter_total;

        if(otter_total ==0 || otter_total == 1 || otter_total == 2){
                break;
            }
        else{
            again = true;
        }
    }

    return otter_total;
}


/**************************************************
** Function: ask_otter_amt
** Description: gets the amount of sea otters before the user buys more
** Parameters: otter_total
** Pre-Conditions: none
** Post-Conditions: returns amount of sea otters before buying more
***************************************************/ 
int zoo::ask_otter_amt(int otter_total){
    bool again = true;
    int old_otter_amt;
    
    while(again){
        //cout << "You have $" << bank << " in your bank" << endl;
        //cout << "How many otters do you want to buy for $5,000 each? (0-2): ";
        //cin >> otter_total;

        if(otter_total >= 0 && otter_total <= 2){
            if(otter_total != 0) {
            old_otter_amt = otter_amt;
            otter_amt = otter_amt + otter_total;
            //cout << "You now have $" << bank << endl;
            break;
            }
            else{
                break;
            }
        }
        else if(otter_total < 0 || otter_total > 2){
            //cout << "Enter a number between 0-2" << endl;
            again = true;
        }
    }

    return old_otter_amt;
}

/**************************************************
** Function: buy_sea_otter
** Description: subtracts money from bank and creates a sea otter array
** Parameters: bank, old_otter_amt, otter_total
** Pre-Conditions: none
** Post-Conditions: creates sea otter array
***************************************************/ 
int zoo::buy_sea_otter(int bank, int old_otter_amt, int otter_total){
    int otter_cost;
    bool again = true;

    otter_cost = otter_total * 5000;

    if(bank > 0 && otter_amt > 0 && otter_amt <= 2){
        if(otter_total == 1 || otter_total == 2){
            bank -= otter_cost;
            cout << "You now have $" << bank << endl;
            for(int i = 0; i < otter_total; i++){
            fill_otter(sea_otter(), old_otter_amt);
            }
        }
    }
    else if(otter_amt < 0 || otter_amt > 2){
        //cout << "Enter a number between 0-2" << endl;
        again = true;
    }
    else if(bank < 0){
        cout << "You do not have enough money." << endl;
        again = true;
    }

    return bank;
}

/**************************************************
** Function: meerkat_amt_ask
** Description: ask for how many meerkatss to buy
** Parameters: 
** Pre-Conditions: none
** Post-Conditions: amount of meerkats to buy
***************************************************/ 
int zoo::meerkat_amt_ask(){
    int meerkat_total;
    bool again = true;

    while(again){
        //cout << "You have $" << bank << " in your bank" << endl;
        cout << "How many meerkats do you want to buy for $500 each? (0-2): ";
        cin >> meerkat_total;

        if(meerkat_total ==0 || meerkat_total == 1 || meerkat_total == 2){
                break;
        }
        else{
            again = true;
        }
    }

    return meerkat_total;
}

/**************************************************
** Function: ask_monkey_amt
** Description: gets the amount of monkeys before the user buys more
** Parameters: monkey_total
** Pre-Conditions: none
** Post-Conditions: returns amount of monkeys before buying more
***************************************************/ 
int zoo::ask_meerkat_amt(int meerkat_total){
    bool again = true;
    int old_meerkat_amt;
    
    while(again){
        //cout << "You have $" << bank << " in your bank" << endl;
        //cout << "How many meerkats do you want to buy for $500 each? (0-2): ";
        //cin >> meerkat_total;

        if(meerkat_total >= 0 && meerkat_total <= 2){
            old_meerkat_amt = meerkat_amt;
            meerkat_amt = meerkat_amt + meerkat_total;
            //cout << "You now have $" << bank << endl;
            break;
        }
        else if(meerkat_total < 0 || meerkat_total > 2){
            //cout << "Enter a number between 0-2" << endl;
            again = true;
        }
    }

    return old_meerkat_amt;
}

/**************************************************
** Function: buy_monkey
** Description: subtracts money from bank and creates a monkey array
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: creates monkey array
***************************************************/ 
int zoo::buy_meerkat(int bank, int old_meerkat_amt, int meerkat_total){
    int meerkat_cost;
    bool again = true;
    
    meerkat_cost = meerkat_total * 500;

    if(bank > 0 && meerkat_amt > 0 && meerkat_amt <= 2){
        if(meerkat_total == 1 || meerkat_total == 2){
            bank -= meerkat_cost;
            cout << "You now have $" << bank << endl;
            for(int i = 0; i < meerkat_total; i++){
            fill_meerkat(meerkat(), old_meerkat_amt);
            }
        }
    }
    else if(meerkat_amt < 0 || meerkat_amt > 2){
        //cout << "Enter a number between 0-2" << endl;
        again = true;
    }
    else if(bank < 0){
        cout << "You do not have enough money." << endl;
        again = true;
    }

    return bank;
}

/**************************************************
** Function: buy_animals
** Description: asks to buy and subtracts money for all animals
** Parameters: bank, monkey_total, otter_total, meerkat_total, &old_monkey_amt
** Pre-Conditions: none
** Post-Conditions: returns bank
***************************************************/ 
int zoo::buy_animals(int bank, int monkey_total, int otter_total, int meerkat_total, int &old_monkey_amt){
    monkey_total = monkey_amt_ask(bank);
    old_monkey_amt = ask_monkey_amt(monkey_total);
    bank = buy_monkey(old_monkey_amt, monkey_total);
    otter_total = otter_amt_ask();
    int old_otter_amt = ask_otter_amt(otter_total);
    bank = buy_sea_otter(bank, old_otter_amt, otter_total);
    meerkat_total = meerkat_amt_ask();
    int old_meerkat_amt = ask_meerkat_amt(meerkat_total);
    bank = buy_meerkat(bank, old_meerkat_amt, meerkat_total);

    return bank;
}

/**************************************************
** Function: purchase_food
** Description: calculates food costs and subtract from bank
** Parameters: bank, monkey_amt, otter_amt, meerkat_amt
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
int zoo::purchase_food(int bank, int monkey_amt, int otter_amt, int meerkat_amt){
    float food_cost;
    srand(time(NULL));
    float percent = (rand() %(125-75+1)+75);
    percent = percent * .01;

    //if(monkey_amt == 1 || monkey_amt == 2){
    food_cost = 40 * percent * 4 * monkey_amt;
    cout << endl;
    cout << "Your animals are hungry" << endl;
    cout << "You have bought food for monkeys for $" << food_cost << endl;
    bank -= food_cost;
    cout << "You have $" << bank << endl; 
    cout << endl;
    //}

    //if(otter_amt == 1 || otter_amt == 2){
    food_cost = 40 * percent * 2 * otter_amt;
    cout << "You have bought food for sea otters for $" << food_cost << endl;
    bank -= food_cost;
    cout << "You have $" << bank << endl; 
    cout << endl;
    //}

    //if(meerkat_amt == 1 || meerkat_amt == 2){
    food_cost = 40 * percent * meerkat_amt;
    cout << "You have bought food for meerkats for $" << food_cost << endl;
    bank -= food_cost;
    cout << "You have $" << bank << endl; 
    cout << endl;
    //}
}

/**************************************************
** Function: add_monkey
** Description: resize the array when user buys more
** Parameters: old_monkey_amt
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
void zoo::add_monkey(int old_monkey_amt){
    animal *temp = new monkey[old_monkey_amt];
    for(int i = 0; i < old_monkey_amt; i++){
        temp[i] = monkeys[i];
    }

    delete[] monkeys;
    monkeys = new monkey[monkey_amt];

    for(int i = 0; i < old_monkey_amt; i++){
        monkeys[i] = temp[i];
    }
    delete[] temp;
}

/**************************************************
** Function: add_otter
** Description: resize the array when user buys more
** Parameters: old_otter_amt
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/
void zoo::add_otter(int old_otter_amt){
    animal *temp = new sea_otter[old_otter_amt];
    for(int i = 0; i < old_otter_amt; i++){
        temp[i] = sea_otters[i];
    }
    delete[] sea_otters;
    
    sea_otters = new sea_otter[otter_amt];

    for(int i = 0; i < old_otter_amt; i++){
        sea_otters[i] = temp[i];
    }
    delete[] temp;
}

/**************************************************
** Function: add_meerkat
** Description: resize the array when user buys more
** Parameters: old_meerkat_amt
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/
void zoo::add_meerkat(int old_meerkat_amt){
    animal *temp = new meerkat[old_meerkat_amt];
    for(int i = 0; i < old_meerkat_amt; i++){
        temp[i] = meerkats[i];
    }
    delete[] meerkats;
    
    meerkats = new meerkat[meerkat_amt];

    for(int i = 0; i < old_meerkat_amt; i++){
        meerkats[i] = temp[i];
    }
    delete[] temp;
}

/**************************************************
** Function: sick_animal
** Description: random animal gets sick
** Parameters: old_monkey_amt, bank
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/
int zoo::sick_animal(int bank, int &old_monkey_amt){
    srand(time(NULL));
    //int chance = (rand() % 4 + 1);
    int monkey_sick = (rand() % monkey_amt);
    int otter_sick = (rand() % otter_amt);
    int meerkat_sick = (rand() % meerkat_amt);
    int chance = 2;
    int pay;

    if(chance == 1){
        cout << "No animals got sick" << endl;
    }

    else if(chance == 2){   
        cout << "Pay $7500 to cure monkey or let it die.\n1. Pay $7,500\n2. Let it die" << endl;
        cin >> pay;

        if(pay == 1){
            
            bank -= 7500;
            cout << "You now have $" << bank << endl;
            return bank;
        }
        else{
            cout << "monkey died" << endl;
            delete_monkey(monkey_sick, monkey_amt);
        }

    }
    else if(chance == 3){
        cout << "Pay $2,500 to cure monkey or let it die.\n1. Pay $2,500\n2. Let it die" << endl;
        cin >> pay;

        if(pay == 1){
            bank -= 2500;
            cout << "You now have $" << bank << endl;
            return bank;
        }
        else{
            cout << "Sea otter died" << endl;
            delete_otter(otter_sick, otter_amt);
        }
    }
    else if(chance == 4){
        cout << "Pay $250 to cure meerkat or let it die.\n1. Pay $250\n2. Let it die" << endl;
        cin >> pay;

        if(pay == 1){
            bank -= 250;
            cout << "You now have $" << bank << endl;
            return bank;
        }
        else {
            cout << "meerkat died" << endl;
            delete_meerkat(meerkat_sick, meerkat_amt);
        }
    }
    return bank;
}

/**************************************************
** Function: delete_monkey
** Description: resize the array when animals die
** Parameters: monkey_sick, monkey_amt
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/
void zoo::delete_monkey(int monkey_sick, int monkey_amt){
    animal *temp = new monkey[monkey_amt -1];
    int j = 0;
    for(int i = 0; i < monkey_amt; i++){
        if(i != monkey_sick){
            temp[j] = monkeys[i];
        }
        else{
            j++;
        }
    }

    delete[] monkeys;
    monkeys = new monkey[monkey_amt - 1];
    for(int i = 0; i < monkey_amt; i++){
        monkeys[i] = temp[i];
    }
    delete[] temp;
}

/**************************************************
** Function: delete_otter
** Description: resize the array when animals die
** Parameters: otter_sick, otter_amt
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/
void zoo::delete_otter(int otter_sick, int otter_amt){
    animal *temp = new sea_otter[otter_amt -1];
    int j = 0;
    for(int i = 0; i < otter_amt; i++){
        if(i != otter_sick){
            temp[j] = sea_otters[i];
        }
        else{
            j++;
        }
    }

    delete[] sea_otters;
    sea_otters = new sea_otter[monkey_amt - 1];
    for(int i = 0; i < otter_amt; i++){
        sea_otters[i] = temp[i];
    }
    delete[] temp;
}

/**************************************************
** Function: delete_meerkat
** Description: resize the array when animals die
** Parameters: moeerkat_sick, meerkat_amt
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/
void zoo::delete_meerkat(int meerkat_sick, int meerkat_amt){
    animal *temp = new meerkat[meerkat_amt -1];
    int j = 0;
    for(int i = 0; i < meerkat_amt; i++){
        if(i != meerkat_sick){
            temp[j] = meerkats[i];
        }
        else{
            j++;
        }
    }

    delete[] meerkats;
    meerkats = new meerkat[meerkat_amt - 1];
    for(int i = 0; i < meerkat_amt; i++){
        meerkats[i] = temp[i];
    }
    delete[] temp;
}

/**************************************************
** Function: give_birth
** Description: chance of animal giving birth
** Parameters: old_monkey_amt, old_otter_amt, old_meerkat_amt
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/
void zoo::give_birth(int &old_monkey_amt, int old_otter_amt, int old_meerkat_amt) {
    srand(time(NULL));
    int baby_chance = (rand() %(3)+1);
    //int baby_chance = 3;
    if(baby_chance == 1){
        cout << "Baby monkey born" << endl;
        fill_monkey(monkey(0), old_monkey_amt);
    }
    else if(baby_chance == 2){
        cout << "Baby sea otter born" << endl;
        fill_otter(sea_otter(0), old_otter_amt);
    }
    else if(baby_chance == 3){
        cout << "Baby meerkat born" << endl;
        fill_meerkat(meerkat(0), old_meerkat_amt);
    }
}

/**************************************************
** Function: fill_monkey
** Description: fills the array with m for the amount of monkeys in array
** Parameters: animal m, old_monkey_amt
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/
void zoo::fill_monkey(animal m, int old_monkey_amt){
    add_monkey(old_monkey_amt);
    monkeys[monkey_amt - 1] = m;
}

/**************************************************
** Function: fill_otter
** Description: fills the array with o for the amount of sea_otterss in array
** Parameters: animal o, old_otter_amt
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/
void zoo::fill_otter(animal o, int old_otter_amt){
    add_otter(old_otter_amt);
    sea_otters[otter_amt - 1] = o;
}

/**************************************************
** Function: fill_mmeerkat
** Description: fills the array with mk for the amount of meerkats in array
** Parameters: animal mk, old_meerkat_amt
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/
void zoo::fill_meerkat(animal mk, int old_meerkat_amt){
    add_meerkat(old_meerkat_amt);
    meerkats[meerkat_amt - 1] = mk;
}

/**************************************************
** Function: revenue
** Description: calculates teh revenue that each animal generates per week
** Parameters: bank, monkey_total, otter_total, meerkat_total
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/
int zoo::revenue(int bank, int &monkey_total, int &otter_total, int &meerkat_total){
    srand(time(NULL));
    int monkey_boom = (rand() % (700-300+1)+300);
    int boom = (rand() % 10) + 1;
    int otter_revenue;

    if(boom <= 2){
        cout << "Boom event" << endl;
        cout << "Moneky revenue = " << monkey_amt * monkey_boom << endl;
        cout << "Sea otter revenue = " << otter_amt * 250 << endl;
        cout << "Meerkat revenue = " << meerkat_amt * 25 << endl;

        bank += (monkey_amt * monkey_boom) + (otter_amt * 250) + (meerkat_amt * 25);

        cout << "Bank = " << bank << endl;

    }
    else{
        cout << "Revenue" << endl;
        cout << "Moneky revenue = " << monkey_amt * 0.05 * 15000 << endl;
        cout << "Sea otter revenue = " << otter_amt * 250 << endl;
        cout << "Meerkat revenue = " << meerkat_amt * 25 << endl;

        bank += (monkey_amt * 0.05 * 15000);
        bank += (otter_amt * 250);
        bank += (meerkat_amt * 25);

        cout << "Bank = " << bank << endl;
    }

    return bank;

}

/**************************************************
** Function: start_game
** Description: starts the game
** Parameters: None
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/
void zoo::start_game(){
    int week = 0;
    bool again = true;
    int old_monkey_amt = 0, old_otter_amt = 0, old_meerkat_amt = 0;
    int cont;

    while(again){
        if(bank >= 0){
        week++;
        cout << "week " << week << endl;
        bank = buy_animals(bank, monkey_total, otter_total, meerkat_total, old_monkey_amt);
        purchase_food(bank, monkey_amt, otter_amt, meerkat_amt);
        bank = sick_animal(bank, old_monkey_amt);
        give_birth(old_monkey_amt, old_otter_amt, old_meerkat_amt);
        bank = revenue(bank, monkey_total, otter_total, meerkat_total);

        cout << "Do you want to keep going?\n1. Yes\n2. No" << endl;
        cin >> cont;
            if(cont == 2){
                break;
            }

        for(int i = 0; i < monkey_amt; i++){
            monkeys[i].inc_age();
            sea_otters[i].inc_age();
            meerkats[i].inc_age();
        }

        }
        else{
            again = false;
        }
    }
}

/**************************************************
** Function: ~zoo
** Description: destructor
** Parameters: None
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/
zoo::~zoo(){
    delete[] monkeys;
    delete[] sea_otters;
    delete[] meerkats;
}