/*
 * MinimaxPlayer.cpp
 *
 *  Created on: Apr 17, 2015
 *      Author: wong
 */
#include <iostream>
#include <assert.h>
#include "MinimaxPlayer.h"

using std::vector;
using namespace std;

MinimaxPlayer::MinimaxPlayer(char symb) :
		Player(symb) {

}

MinimaxPlayer::~MinimaxPlayer() {

}

int MinimaxPlayer::utility(OthelloBoard b){
	int val = b.count_score(b.get_p1_symbol()) - b.count_score(b.get_p2_symbol());
	
	return val;
}

vector<MinimaxPlayer::Node> MinimaxPlayer::successor(char symbol, OthelloBoard b){
	//valid moves
	vector<MinimaxPlayer::Node> valid;

	int row = 0;
	int col = 0;

	//loop each column
	for(col = 0; col < b.get_num_cols(); col++){
		//loop each row
		for(row = 0; row < b.get_num_rows(); row++){
			//check if board has empty cells and the move is valid
			if(b.is_cell_empty(col, row) && b.is_legal_move(col, row, symbol)){
				//temp board to hold
				OthelloBoard temp = b;

				//play move into the temp
				temp.play_move(col, row, symbol);
				Node join = {col, row, temp};
				
				//put in back
				valid.push_back(move(join));
			}
		}
	}
	
	return valid;
}

int MinimaxPlayer::minVal(OthelloBoard b){
	//successor node
	vector<Node> suc;

	//check if game is over
	if(!b.has_legal_moves_remaining(b.get_p2_symbol()) && !b.has_legal_moves_remaining(b.get_p1_symbol())){
		return utility(b);
	}

	int minimum = 1000;
	int succSize = suc.size();
	char symbol = b.get_p2_symbol();
	suc = successor(symbol, b);

	for(int i = 0; i < succSize; i++){
		minimum = min(minimum, maxVal(suc[i].b));
	}

	return minimum;
}

int MinimaxPlayer::maxVal(OthelloBoard b){
	//successor node
	vector<Node> suc;

	//check if game is over
	if(!b.has_legal_moves_remaining(b.get_p2_symbol()) && !b.has_legal_moves_remaining(b.get_p1_symbol())){
		return utility(b);
	}

	int maximum = -1000;
	int succSize = suc.size();
	char symbol = b.get_p1_symbol();
	suc = successor(symbol, b);

	for(int i = 0; i < succSize; i++){
		maximum = max(maximum, minVal(suc[i].b));
	}

	return maximum;
}

void MinimaxPlayer::get_move(OthelloBoard* b, int& col, int& row) {

	int i;
	int minBest = 1000;
	int maxBest = -1000;

	//successor node
	vector<Node> suc = successor(get_symbol(), *b);
	Node newBoard = {-1, -1, *b};

	for(i = 0; i < suc.size(); i++){
		int max = maxVal(suc[i].b);

		if(max < minBest){
			minBest = max;
			newBoard = suc[i];
		}
	}

	col = newBoard.col;
	row = newBoard.row;
}

MinimaxPlayer* MinimaxPlayer::clone() {
	MinimaxPlayer* result = new MinimaxPlayer(symbol);
	return result;
}
