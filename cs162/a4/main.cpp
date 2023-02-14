/*******************************************************
** Program main.cpp
** Author: Allen Chan
** Date: 5/26/2019
** Description: game starts
** Input: user inputs
** Output: runs the game
********************************************************/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "room.hpp"

using namespace std;
void free_vec(int grid, vector<vector<Room*> > &room_vec);
void fill_bat(int grid, vector<vector<Room*> > &room_vec);
void fill_pit(int grid, vector<vector<Room*> > &room_vec);
void fill_gold(int grid, vector<vector<Room*> > &room_vec);
void fill_wumpus(int grid, vector<vector<Room*> > &room_vec);
void fill_player(int grid, vector<vector<Room*> > &room_vec, int &play_x, int &play_y);
void print_map(int grid, vector<vector<Room*> > &room_vec, int play_x, int play_y);
char action();
void map_set_up(int grid, vector<vector<Room*> > &room_vec, int &play_x, int &play_y);
void if_action(char move, vector<vector<Room*> > &room_vec, int &play_x, int &play_y, int grid, bool again);
void check_room(int grid, vector<vector<Room*> > &room_vec, int play_x, int play_y);
void move_up(int &play_x, int &play_y, vector<vector<Room*> > &room_vec, Event *temp);
void move_down(int grid, int &play_x, int &play_y, vector<vector<Room*> > &room_vec, Event *temp, bool again);
void move_right(int grid, int &play_x, int &play_y, vector<vector<Room*> > &room_vec, Event *temp);
void move_left(int &play_x, int &play_y, vector<vector<Room*> > &room_vec, Event *temp);
void check_up(int grid, vector<vector<Room*> > &room_vec, int play_x, int play_y);
void check_down(int grid, vector<vector<Room*> > &room_vec, int play_x, int play_y);
void check_left(int grid, vector<vector<Room*> > &room_vec, int play_x, int play_y);
void check_right(int grid, vector<vector<Room*> > &room_vec, int play_x, int play_y);
void if_shoot_arrow(int grid, int arrows, vector<vector<Room*> > &room_vec);
int shoot_arrow(int grid, int arrows, vector<vector<Room*> > &room_vec);

int main(int argc, char **argv){
    //Room r;
    //int count = 0, count2 = 0;
    bool again = true;
    /*Bats b;
    Pit p;
    Gold g;
    Wumpus w;*/
    //char m;
    Player player;
    //int arrows;
    char move;
    srand(time(NULL));
    int grid = argv[1][0] - 48;
    int play_x, play_y;

    if(argc >=2 && argc <= 3 && grid >= 4){
        vector<vector<Room*> > room_vec;
    
        map_set_up(grid, room_vec, play_x, play_y);

        while(again){
            //cout << room_vec[play_x][play_y-1]->get_event()->get_type() << endl;
            print_map(grid, room_vec, play_x, play_y);
            check_room(grid, room_vec, play_x, play_y);
            player.print_arrow();
            move = action();
            if_action(move, room_vec, play_x, play_y, grid, again);
            //cout << "test = " << room_vec[play_x][play_y]->get_event()->get_type() << endl;
            //cout << "test = " << room_vec[play_x+1][play_y]->get_event()->get_type() << endl;
            //cout << "move = " << move << endl;
            if(move == 'f'){
                //free_vec(grid, room_vec);
                again = false;
            }
        }
        
        //free_vec(grid, room_vec);

    }
    else{
        cout << "Enter a number greater than 4" << endl;
    }

    return 0;
}

/**************************************************
** Function: print_map
** Description: prints the map
** Parameters: int grid, vector<vector<Room*> > &room_vec, int play_x, int play_y
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
void print_map(int grid, vector<vector<Room*> > &room_vec, int play_x, int play_y){
//cout << "play x = " << play_x << "play y = " << play_y << endl;
            //cout << "test 3 = " << room_vec[play_x][play_y]->get_event()->get_type() << endl;


    for(int i = 0; i < grid; i++){
        for(int j = 0; j < grid; j++){
            cout << "+---+";
        }
        cout << endl;
        for(int j = 0; j < grid; j++){
            cout << "|   |";
        }
        cout << endl;

        for(int j = 0; j < grid; j++) {
            if(room_vec[i][j]->get_event()->get_type() == 'b') {
                cout << "| " << room_vec[i][j]->get_event()->get_type() << " |";
            }
            else if(room_vec[i][j]->get_event()->get_type() == 'p') {
                cout << "| " << room_vec[i][j]->get_event()->get_type() << " |";
            }
            else if(room_vec[i][j]->get_event()->get_type() == 'g') {
                cout << "| " << room_vec[i][j]->get_event()->get_type() << " |";
            }
            else if(room_vec[i][j]->get_event()->get_type() == 'w') {
                cout << "| " << room_vec[i][j]->get_event()->get_type() << " |";
            }
            else if(room_vec[i][j]->get_event()->get_type() == '*') {
                cout << "| " << room_vec[i][j]->get_event()->get_type() << " |";
            }
            else {
                cout << "|   |";
            }
            //cout << "| " << room_vec[i][j]->get_event()->get_type() << " |";
        }
        cout << endl;

        for(int j = 0; j < grid; j++){
            cout << "|   |";
        }
        cout << endl;

        for(int j = 0; j < grid; j++){
            cout << "+---+";
        }
        cout << endl;
        
    }
}

/**************************************************
** Function: free_vec
** Description: frees the vec
** Parameters: int grid, vector<vector<Room*> > &room_vec
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
void free_vec(int grid, vector<vector<Room*> > &room_vec){
    cout << "in free vec" << endl;
    for(int i = 0; i < grid; i++){
        for(int j = 0; j < grid; j++){
            delete room_vec[i][j];
        }
    }
}

/**************************************************
** Function: fill_bat
** Description: puts 2 bats in map
** Parameters: int grid, vector<vector<Room*> > &room_vec
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
void fill_bat(int grid, vector<vector<Room*> > &room_vec){
    int count = 0;
    //int num_b = 0;
    bool again = true;
    //while(num_b != 2) {
        while(count != 2){
            int x = (rand() % grid);
            int y = (rand() % grid);
            //cout << "bat x = "<< x << endl;
            //cout << "bat y = " << y << endl;
            if(room_vec[x][y]->get_event()->get_type() != 'w') {
              if(room_vec[x][y]->get_event()->get_type() != 'g') {
                  if(room_vec[x][y]->get_event()->get_type() != 'b') {
                    room_vec[x][y]->set_event('b');
                    count++; 
                  } 
                }
            }
        }
        /*while(again) {
            int num_ele = 0;
            for(int i = 0; i < grid; i++) {
                for(int j = 0; j < grid; j++) {
                    if(room_vec[i][j]->get_event()->get_type() == 'b') {
                        num_ele++;
                    }
                }
            }
            if(num_ele == 2) {
                again = false;
                num_b = 2;
                }
        }*/
        
//}

}

/**************************************************
** Function: fill_pit
** Description: fills the map with 2 pits
** Parameters: int grid, vector<vector<Room*> > &room_vec
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
void fill_pit(int grid, vector<vector<Room*> > &room_vec){
    int count = 0;
    //int num_p = 0;
    bool again = true;
    //while(num_p != 2) {
        while(count != 2){
            int x = (rand() % grid);
            int y = (rand() % grid);
            //cout << "pit x = "<< x << endl;
            //cout << "pit y = " << y << endl;
            if(room_vec[x][y]->get_event()->get_type() != 'w') {
              if(room_vec[x][y]->get_event()->get_type() != 'g') {
                  if(room_vec[x][y]->get_event()->get_type() != 'b') {
                      if(room_vec[x][y]->get_event()->get_type() != 'p') {
                        room_vec[x][y]->set_event('p');
                        count++; 
                      }
                  } 
                }
            }
        }
        /*while(again) {
            int num_ele = 0;
            for(int i = 0; i < grid; i++) {
                for(int j = 0; j < grid; j++) {
                    if(room_vec[i][j]->get_event()->get_type() == 'p') {
                        num_ele++;
                    }
                }
            }
            if(num_ele == 2) {
                again = false;
                num_p = 2;
                }
        }*/
//}

}


/**************************************************
** Function: fill_gold
** Description: fills map with 1 gold
** Parameters: int grid, vector<vector<Room*> > &room_vec
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
void fill_gold(int grid, vector<vector<Room*> > &room_vec){
    int count = 0;
    //int num_b = 0;
    bool again = true;
    //while(num_b != 2) {
        while(count != 1){
            int x = (rand() % grid);
            int y = (rand() % grid);
            //cout << "gold x = "<< x << endl;
            //cout << "gold y = " << y << endl;
            room_vec[x][y]->set_event('g');
            count++;
        }
   /*while(again) {
        int num_ele = 0;
        for(int i = 0; i < grid; i++) {
            for(int j = 0; j < grid; j++) {
                if(room_vec[i][j]->get_event()->get_type() == 'g') {
                    num_ele++;
                }
            }
        }
        if(num_ele == 1) {
            again = false;
            num_b = 2;
        }
    }*/
    //}
}

/**************************************************
** Function: fill_wumpus
** Description: fills map with 1 wumpus
** Parameters: int grid, vector<vector<Room*> > &room_vec
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
void fill_wumpus(int grid, vector<vector<Room*> > &room_vec){
    int count = 0;
    //int num_b = 0;
    bool again = true;
    //while(num_b != 2) {
        while(count != 1){
            int x = (rand() % grid);
            int y = (rand() % grid);
            //cout << "wumpus x = "<< x << endl;
            //cout << "wumpus y = " << y << endl;
              if(room_vec[x][y]->get_event()->get_type() != 'g') {
                room_vec[x][y]->set_event('w');
                count++;  
                }
        }
        /*while(again) {
            int num_ele = 0;
            for(int i = 0; i < grid; i++) {
                for(int j = 0; j < grid; j++) {
                    if(room_vec[i][j]->get_event()->get_type() == 'w') {
                        num_ele++;
                    }
                }
            }
            if(num_ele == 1) {
                again = false;
                num_b = 2;
                }
        }*/
        
//}
}

/**************************************************
** Function: fill_player
** Description: sets player location
** Parameters: int grid, vector<vector<Room*> > &room_vec
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
void fill_player(int grid, vector<vector<Room*> > &room_vec, int &play_x, int &play_y){
    int count = 0;
    //int num_b = 0;
    bool again = true;
    //while(num_b != 2) {
        while(count < 1){
            int start_x = (rand() % grid);
            int start_y = (rand() % grid);
            //cout << "player x = "<< start_x << endl;
            //cout << "player y = " << start_y << endl;
            if(room_vec[start_x][start_y]->get_event()->get_type() != 'w') {
              if(room_vec[start_x][start_y]->get_event()->get_type() != 'g') {
                  if(room_vec[start_x][start_y]->get_event()->get_type() != 'b') {
                      if(room_vec[start_x][start_y]->get_event()->get_type() != 'p') {
                        room_vec[start_x][start_y]->set_event('*');
                        play_x = start_x;
                        play_y = start_y;
                        count++;
                      }
                  }
                }
            }
        }
    /*while(again) {
        int num_ele = 0;
        for(int i = 0; i < grid; i++) {
            for(int j = 0; j < grid; j++) {
                if(room_vec[i][j]->get_event()->get_type() == '*') {
                    num_ele++;
                }
            }
        }
        if(num_ele == 1) {
            again = false;
            num_b = 2;
        }
    }     
    }*/
}

/**************************************************
** Function: action
** Description: ask user what to do
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returns move 
***************************************************/ 
char action(){
    char move;
    bool again = true;
    while(again){
        cout << "w. Up\ns. Down\nd. Right\na. Left\nf. Attack" << endl;
        cin >> move;
        if(move == 'w' || move == 'a' || move == 's' || move == 'd' || move == 'f'){
            break;
        }
    }
    return move;
}

/**************************************************
** Function: map_set_up
** Description: sets up the map
** Parameters: int grid, vector<vector<Room*> > &room_vec, int &play_x, int &play_y
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
void map_set_up(int grid, vector<vector<Room*> > &room_vec, int &play_x, int &play_y){
    for(int i = 0; i < grid; i++){
        vector<Room*> room_v;
        for(int j = 0; j < grid; j++){
            Room* r = new Room();
            room_v.push_back(r);
        }
        room_vec.push_back(room_v);
    }
    
    fill_gold(grid, room_vec);
    fill_wumpus(grid, room_vec);
    fill_bat(grid, room_vec);
    fill_pit(grid, room_vec);
    fill_player(grid, room_vec, play_x, play_y);
}

/**************************************************
** Function: if_action
** Description: moves player
** Parameters: int grid, vector<vector<Room*> > &room_vec, int &play_x, int &play_y
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
void if_action(char move, vector<vector<Room*> > &room_vec, int &play_x, int &play_y, int grid, bool again){
    Event *temp;
    if(move == 'w'){
        cout << "move up" << endl;
        move_up(play_x, play_y, room_vec, temp);
    }
    else if(move == 's'){
        cout << "move down" << endl;
        move_down(grid, play_x, play_y, room_vec, temp, again);
    }
    else if(move == 'd'){
        cout << "move right" << endl;
        move_right(grid, play_x, play_y, room_vec, temp);
    }
    else if(move == 'a'){
        cout << "move left" << endl;
        move_left(play_x, play_y, room_vec, temp);
    }
    else if(move == 'f'){
        cout << "attack" << endl;
    }
}

/**************************************************
** Function: check_room
** Description: checks event near player
** Parameters: int grid, vector<vector<Room*> > &room_vec, int play_x, int play_y
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
void check_room(int grid, vector<vector<Room*> > &room_vec, int play_x, int play_y){
    //check up
    if(play_x - 1 >= 0){
        check_up(grid, room_vec, play_x, play_y);
    }
    //check down
    if(play_x + 1 <= grid - 1){
        check_down(grid, room_vec, play_x, play_y);
    }
    //check left
    if(play_y - 1 >= 0){
        check_left(grid, room_vec, play_x, play_y);
    }
    //check right
    if(play_y + 1 <= grid - 1){
        check_right(grid, room_vec, play_x, play_y);
    }
}

/**************************************************
** Function: move_up
** Description: move up
** Parameters: int &play_x, int &play_y, vector<vector<Room*> > &room_vec, Event *tem
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
void move_up(int &play_x, int &play_y, vector<vector<Room*> > &room_vec, Event *temp){
    if(play_x == 0){
            cout << "can't move up" << endl;
        }
        else{
            temp = room_vec[play_x][play_y]->get_event();
            room_vec[play_x][play_y]->set_event(' ');
            //cout << "test2 = " <<  room_vec[play_x][play_y]->get_event()->get_type() << endl;
            play_x -= 1;
            room_vec[play_x][play_y]->set_player(temp);
            cout << room_vec[play_x][play_y]->get_event()->get_type() << endl;
            //room_vec[play_x+1][play_y]->set_event(' ');
            /*if(room_vec[play_x][play_y]->get_event()->get_type() == 'p'){
                again = false;
            }
            if(room_vec[play_x][play_y]->get_event()->get_type() == 'b'){
                fill_bat(grid, room_vec);
            }*/
        }
}

/**************************************************
** Function: move_down
** Description: move down
** Parameters: int &play_x, int &play_y, vector<vector<Room*> > &room_vec, Event *tem
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
void move_down(int grid, int &play_x, int &play_y, vector<vector<Room*> > &room_vec, Event *temp, bool again){
    if(play_x == grid - 1){
            cout << "can't move down" << endl;
        }
        else{
            temp = room_vec[play_x][play_y]->get_event();
            room_vec[play_x][play_y]->set_event(' ');
            play_x += 1;
            room_vec[play_x][play_y]->set_player(temp);
            /*if(room_vec[play_x][play_y]->get_event()->get_type() == 'p'){
                again = false;
            }
            if(room_vec[play_x][play_y]->get_event()->get_type() == 'b'){
                fill_bat(grid, room_vec);
            }*/
        }
}

/**************************************************
** Function: move right
** Description: move right
** Parameters: int &play_x, int &play_y, vector<vector<Room*> > &room_vec, Event *tem
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
void move_right(int grid, int &play_x, int &play_y, vector<vector<Room*> > &room_vec, Event *temp){
    if(play_y == grid - 1){
            cout << "can't move right" << endl;
        }
        else{
            temp = room_vec[play_x][play_y]->get_event();
            room_vec[play_x][play_y]->set_event(' ');
            play_y += 1;
            room_vec[play_x][play_y]->set_player(temp);
            /*if(room_vec[play_x][play_y]->get_event()->get_type() == 'p'){
                again = false;
            }
            if(room_vec[play_x][play_y]->get_event()->get_type() == 'b'){
                fill_bat(grid, room_vec);
            }*/
        }
}

/**************************************************
** Function: move_left
** Description: move left
** Parameters: int &play_x, int &play_y, vector<vector<Room*> > &room_vec, Event *tem
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
void move_left(int &play_x, int &play_y, vector<vector<Room*> > &room_vec, Event *temp){
    if(play_y == 0){
            cout << "can't move left" << endl;
        }
        else{
            temp = room_vec[play_x][play_y]->get_event();
            room_vec[play_x][play_y]->set_event(' ');
            play_y -= 1;
            room_vec[play_x][play_y]->set_player(temp);
            /*if(room_vec[play_x][play_y]->get_event()->get_type() == 'p'){
                again = false;
            }
            if(room_vec[play_x][play_y]->get_event()->get_type() == 'b'){
                fill_bat(grid, room_vec);
            }*/
        }
}

/**************************************************
** Function: check_up
** Description: check room above
** Parameters: int grid, vector<vector<Room*> > &room_vec, int play_x, int play_y
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
void check_up(int grid, vector<vector<Room*> > &room_vec, int play_x, int play_y){
    if(room_vec[play_x - 1][play_y]->get_event()->get_type() == 'b'){
        cout << room_vec[play_x - 1][play_y]->get_event()->get_message() << endl;
    }
    else if(room_vec[play_x - 1][play_y]->get_event()->get_type() == 'p'){
        cout << room_vec[play_x - 1][play_y]->get_event()->get_message() << endl;
    }
    else if(room_vec[play_x - 1][play_y]->get_event()->get_type() == 'g'){
        cout << room_vec[play_x - 1][play_y]->get_event()->get_message() << endl;
    }
    else if(room_vec[play_x - 1][play_y]->get_event()->get_type() == 'w'){
        cout << room_vec[play_x - 1][play_y]->get_event()->get_message() << endl;
    }
}

/**************************************************
** Function: check_down
** Description: check room below
** Parameters: int grid, vector<vector<Room*> > &room_vec, int play_x, int play_y
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
void check_down(int grid, vector<vector<Room*> > &room_vec, int play_x, int play_y){
    if(room_vec[play_x + 1][play_y]->get_event()->get_type() == 'b'){
        cout << room_vec[play_x + 1][play_y]->get_event()->get_message() << endl;
    }
    else if(room_vec[play_x + 1][play_y]->get_event()->get_type() == 'p'){
        cout << room_vec[play_x + 1][play_y]->get_event()->get_message() << endl;
    }
    else if(room_vec[play_x + 1][play_y]->get_event()->get_type() == 'g'){
        cout << room_vec[play_x + 1][play_y]->get_event()->get_message() << endl;
    }
    else if(room_vec[play_x + 1][play_y]->get_event()->get_type() == 'w'){
        cout << room_vec[play_x + 1][play_y]->get_event()->get_message() << endl;
    }
}

/**************************************************
** Function: check_left
** Description:  check room to left
** Parameters: int grid, vector<vector<Room*> > &room_vec, int play_x, int play_y
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
void check_left(int grid, vector<vector<Room*> > &room_vec, int play_x, int play_y){
    if(room_vec[play_x][play_y - 1]->get_event()->get_type() == 'b'){
        cout << room_vec[play_x][play_y - 1]->get_event()->get_message() << endl;
    }
    else if(room_vec[play_x][play_y - 1]->get_event()->get_type() == 'p'){
        cout << room_vec[play_x][play_y - 1]->get_event()->get_message() << endl;
    }
    else if(room_vec[play_x][play_y - 1]->get_event()->get_type() == 'g'){
        cout << room_vec[play_x][play_y - 1]->get_event()->get_message() << endl;
    }
    else if(room_vec[play_x][play_y - 1]->get_event()->get_type() == 'w'){
        cout << room_vec[play_x][play_y - 1]->get_event()->get_message() << endl;
    }
}

/**************************************************
** Function: check_right
** Description: check room to right
** Parameters: int grid, vector<vector<Room*> > &room_vec, int play_x, int play_y
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
void check_right(int grid, vector<vector<Room*> > &room_vec, int play_x, int play_y){
    if(room_vec[play_x][play_y + 1]->get_event()->get_type() == 'b'){
        cout << room_vec[play_x][play_y + 1]->get_event()->get_message() << endl;
    }
    else if(room_vec[play_x][play_y + 1]->get_event()->get_type() == 'p'){
        cout << room_vec[play_x][play_y + 1]->get_event()->get_message() << endl;
    }
    else if(room_vec[play_x][play_y + 1]->get_event()->get_type() == 'g'){
        cout << room_vec[play_x][play_y + 1]->get_event()->get_message() << endl;
    }
    else if(room_vec[play_x][play_y + 1]->get_event()->get_type() == 'w'){
        cout << room_vec[play_x][play_y + 1]->get_event()->get_message() << endl;
    }
}

/**************************************************
** Function: shoot_arrow
** Description: subtracts 1 arrow and chance of wumpus moving
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
int shoot_arrow(int grid, int arrows, vector<vector<Room*> > &room_vec){
    int chance = (rand() % 99) + 1;
    arrows -= 1;

    if(chance >= 1 && chance <= 75){
        fill_wumpus(grid, room_vec);
    }

    return arrows;
}