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
void fill_blanks(int grid, vector<vector<Room*> > &room_vec);
void fill_player(int grid, vector<vector<Room*> > &room_vec);

void print_map(int grid, vector<vector<Room*> > room_vec){

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
        //if value != " "
        if(room_vec[i][j]->get_event().get_type() == 'b') {
            cout << "| " << room_vec[i][j]->get_event().get_type() << " |";
        }
        else if(room_vec[i][j]->get_event().get_type() == 'p') {
            cout << "| " << room_vec[i][j]->get_event().get_type() << " |";
        }
        else if(room_vec[i][j]->get_event().get_type() == 'g') {
            cout << "| " << room_vec[i][j]->get_event().get_type() << " |";
        }
        else if(room_vec[i][j]->get_event().get_type() == 'w') {
            cout << "| " << room_vec[i][j]->get_event().get_type() << " |";
        }
        else if(room_vec[i][j]->get_event().get_type() == '*') {
            cout << "| " << room_vec[i][j]->get_event().get_type() << " |";
        }
        else {
            cout << "|   |";
        }
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

int main(int argc, char **argv){
    //Room r;
    //int count = 0, count2 = 0;
    bool again = true;
    /*Bats b;
    Pit p;
    Gold g;
    Wumpus w;*/
    char m;
    srand(time(NULL));
    int grid = argv[1][0] - 48;

    if(argc == 2 && grid >= 4){
        cout << "Game starts" << endl;
        vector<vector<Room*> > room_vec;

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
    fill_player(grid, room_vec);

    print_map(grid, room_vec);
    free_vec(grid, room_vec);
    }
    else{
        cout << "Enter a number greater than 4" << endl;
    }

    return 0;
}

void free_vec(int grid, vector<vector<Room*> > &room_vec){
    for(int i = 0; i < grid; i++){
        for(int j = 0; j < grid; j++){
            delete room_vec[i][j];
        }
    }
}

void fill_bat(int grid, vector<vector<Room*> > &room_vec){
    int count = 0;
    int num_b = 0;
    bool again = true;
    while(num_b != 2) {
        while(count != 2){
            int x = (rand() % grid);
            int y = (rand() % grid);
            cout << "bat x = "<< x << endl;
            cout << "bat y = " << y << endl;
            if(room_vec[x][y]->get_event().get_type() != 'w') {
              if(room_vec[x][y]->get_event().get_type() != 'g') {
                  if(room_vec[x][y]->get_event().get_type() != 'b') {
                    room_vec[x][y]->set_event('b');
                    count++; 
                  } 
                }
            }
        }
        while(again) {
            int num_ele = 0;
            for(int i = 0; i < grid; i++) {
                for(int j = 0; j < grid; j++) {
                    if(room_vec[i][j]->get_event().get_type() == 'b') {
                        num_ele++;
                    }
                }
            }
            if(num_ele == 2) {
                again = false;
                num_b = 2;
                }
        }
        
}

}

void fill_pit(int grid, vector<vector<Room*> > &room_vec){
    int count = 0;
    int num_b = 0;
    bool again = true;
    while(num_b != 2) {
        while(count != 2){
            int x = (rand() % grid);
            int y = (rand() % grid);
            cout << "pit x = "<< x << endl;
            cout << "pit y = " << y << endl;
            if(room_vec[x][y]->get_event().get_type() != 'w') {
              if(room_vec[x][y]->get_event().get_type() != 'g') {
                  if(room_vec[x][y]->get_event().get_type() != 'b') {
                      if(room_vec[x][y]->get_event().get_type() != 'p') {
                        room_vec[x][y]->set_event('p');
                        count++; 
                      }
                  } 
                }
            }
        }
        while(again) {
            int num_ele = 0;
            for(int i = 0; i < grid; i++) {
                for(int j = 0; j < grid; j++) {
                    if(room_vec[i][j]->get_event().get_type() == 'p') {
                        num_ele++;
                    }
                }
            }
            if(num_ele == 2) {
                again = false;
                num_b = 2;
                }
        }
        
}

}


void fill_gold(int grid, vector<vector<Room*> > &room_vec){
    int count = 0;
    int num_b = 0;
    bool again = true;
    while(num_b != 2) {
        while(count != 1){
            int x = (rand() % grid);
            int y = (rand() % grid);
            cout << "gold x = "<< x << endl;
            cout << "gold y = " << y << endl;
            room_vec[x][y]->set_event('g');
            count++;
        }
    while(again) {
        int num_ele = 0;
        for(int i = 0; i < grid; i++) {
            for(int j = 0; j < grid; j++) {
                if(room_vec[i][j]->get_event().get_type() == 'g') {
                    num_ele++;
                }
            }
        }
        if(num_ele == 1) {
            again = false;
            num_b = 2;
        }
    }     
    }
}

void fill_wumpus(int grid, vector<vector<Room*> > &room_vec){
    int count = 0;
    int num_b = 0;
    bool again = true;
    while(num_b != 2) {
        while(count != 1){
            int x = (rand() % grid);
            int y = (rand() % grid);
            cout << "wumpus x = "<< x << endl;
            cout << "wumpus y = " << y << endl;
              if(room_vec[x][y]->get_event().get_type() != 'g') {
                room_vec[x][y]->set_event('w');
                count++;  
                }
        }
        while(again) {
            int num_ele = 0;
            for(int i = 0; i < grid; i++) {
                for(int j = 0; j < grid; j++) {
                    if(room_vec[i][j]->get_event().get_type() == 'w') {
                        num_ele++;
                    }
                }
            }
            if(num_ele == 1) {
                again = false;
                num_b = 2;
                }
        }
        
}
}

void fill_player(int grid, vector<vector<Room*> > &room_vec){
    int count = 0;
    int num_b = 0;
    bool again = true;
    while(num_b != 2) {
        while(count < 1){
            int x = (rand() % grid);
            int y = (rand() % grid);
            cout << "player x = "<< x << endl;
            cout << "player y = " << y << endl;
            if(room_vec[x][y]->get_event().get_type() != 'w') {
              if(room_vec[x][y]->get_event().get_type() != 'g') {
                  if(room_vec[x][y]->get_event().get_type() != 'b') {
                      if(room_vec[x][y]->get_event().get_type() != 'p') {
                        room_vec[x][y]->set_event('*');
                        count++;
                      }
                  }
                }
            }
        }
    while(again) {
        int num_ele = 0;
        for(int i = 0; i < grid; i++) {
            for(int j = 0; j < grid; j++) {
                if(room_vec[i][j]->get_event().get_type() == '*') {
                    num_ele++;
                }
            }
        }
        if(num_ele == 1) {
            again = false;
            num_b = 2;
        }
    }     
    }
}