#include "Tile.h"



// For aa sette Tilelabel i henhold til state
const std::map<Cell, std::string> cellToSymbol{{Cell::closed, ""},
									 			{Cell::open, ""},
									 	  		{Cell::flagged, "|>"}};

Tile::Tile(TDT4102::Point pos, int size) : 
	Button({pos.x, pos.y}, 1.5*size, size, "") {
		setButtonColor(TDT4102::Color::silver);
	}

void Tile::open()
{
	if (getState() == Cell::closed) {
		if (getMine()){
			set_label("X");
			set_label_color(TDT4102::Color::red);
		} else {
			setButtonColor(TDT4102::Color::white);
		}
		state = Cell::open;
	}
}

void Tile::flag()
{
	if (getState() == Cell::flagged){
		state = Cell::closed;
		set_label(cellToSymbol.find(state)->second);
	} else {
		state = Cell::flagged;
		set_label(cellToSymbol.find(state)->second);
		set_label_color(TDT4102::Color::black);
	}
}

bool Tile::getMine(){
	return isMine;
}

void Tile::setMine(){
	isMine = true;
}

void Tile::setAdjMine(int n){
	set_label_color(minesToColor.find(n)->second);
	set_label(std::to_string(n));
}

void Tile::showMines(std::string s, TDT4102::Color c){
	set_label_color(c);
	set_label(s);
}

void Tile::resetTile(){
	setButtonColor(TDT4102::Color::silver);
	isMine = false;
	state = Cell::closed;
	set_label("");
	set_label_color(TDT4102::Color::black);
}