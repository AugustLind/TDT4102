#include "MinesweeperWindow.h"
#include <iostream>
#include <random>

MinesweeperWindow::MinesweeperWindow(int x, int y, int width, int height, int mines, const string &title) : 
	// Initialiser medlemsvariabler, bruker konstruktoren til AnimationWindow-klassen
	AnimationWindow{x, y, width * cellSize, (height + 3) * cellSize, title},
	width{width}, height{height}, mines{mines}, gameOverText{{100, 300}, 150, 50, ""}, 
	numberMines{{10, 300}, 75, 50, std::to_string(minesLeft)}, QuitBtn{{10,400},75,50,"Quit"},
	RestartBtn{{100,400},90,50,"Restart"}
{

	// Legg til alle tiles i vinduet
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			tiles.emplace_back(new Tile{ Point{j * cellSize, i * cellSize}, cellSize});
			tiles.back()->setCallback(std::bind(&MinesweeperWindow::cb_click, this));
			auto temp = tiles.back().get();
			add(*temp); 
		}
	}
	// Legg til miner paa tilfeldige posisjoner
	int placedMines{0};
	while (placedMines != mines){
		random_device rd;
		default_random_engine generator(rd());
		uniform_int_distribution<int> distribution(0, width * height - 1);
		int n = distribution(generator);

		if (tiles[n]->getMine() == false){
			tiles[n]->setMine();
			placedMines += 1;
		}
	}

	add(numberMines);

	add(gameOverText);

	add(QuitBtn);
	add(RestartBtn);
	QuitBtn.setCallback(std::bind(&MinesweeperWindow::cb_quit, this));
	RestartBtn.setCallback(std::bind(&MinesweeperWindow::cb_restart, this));

	QuitBtn.setVisible(false);
	RestartBtn.setVisible(false);
	gameOverText.setVisible(false);

}

vector<Point> MinesweeperWindow::adjacentPoints(Point xy) const {
	vector<Point> points;
	for (int di = -1; di <= 1; ++di) {
		for (int dj = -1; dj <= 1; ++dj) {
			if (di == 0 && dj == 0) {
				continue;
			}

			Point neighbour{ xy.x + di * cellSize,xy.y + dj * cellSize };
			if (inRange(neighbour)) {
				points.push_back(neighbour);
			}
		}
	}
	return points;
}

void MinesweeperWindow::openTile(Point xy) {
	shared_ptr<Tile>& tileOpen = at(xy);
	if (tileOpen->getState() == Cell::closed){
		tileOpen->open();
		if (tileOpen->getMine() == false){
			openedTiles += 1;
			vector<Point> neighbourPoints = adjacentPoints(xy);
			int value = countMines(neighbourPoints);
			if (value != 0){
				tileOpen->setAdjMine(value);
			} else {
				for (const Point& xyNei : neighbourPoints){
					openTile(xyNei);
				}
			}
		} else{
			gameOverText.setText("You have lost");
			gameOver = true;
			QuitBtn.setVisible(true);
			RestartBtn.setVisible(true);
			gameOverText.setVisible(true);
			for (const auto& tilePtr : tiles) {
				if (tilePtr->getMine()){
					tilePtr->showMines("X", Color::red);
				}
			}
		}
	}
	if ((openedTiles == height*width - mines)){
		gameOverText.setText("You have won");
		gameOver = true;
		QuitBtn.setVisible(true);
		RestartBtn.setVisible(true);
		gameOverText.setVisible(true);
		for (const auto& tilePtr : tiles) {
				if (tilePtr->getMine()){
					tilePtr->showMines("|>", Color::green);
				}
			}	
	}
}

void MinesweeperWindow::flagTile(Point xy) {
	shared_ptr<Tile>& tileFlagged = at(xy);
	if (tileFlagged->getState() != Cell::open){
		if (tileFlagged->getState() == Cell::flagged){
			flaggedMines -= 1;
		} else {
			flaggedMines += 1;
		}
		tileFlagged->flag();
		minesLeft = mines - flaggedMines;
		numberMines.setText(std::to_string(minesLeft));
	}
}

//Kaller openTile ved venstreklikk og flagTile ved hoyreklikk
void MinesweeperWindow::cb_click() {
	if (!gameOver){
	Point xy{this->get_mouse_coordinates()};

	if (!inRange(xy)) {
		return;
	}
	if (this->is_left_mouse_button_down()) {
		openTile(xy);
	}
	else if(this->is_right_mouse_button_down()){
		flagTile(xy);
	}
	}
}

int MinesweeperWindow::countMines(vector<Point> coords) const{
	int count{0};

	for (const Point& xy : coords){
		const shared_ptr<Tile>& tileCheck = at(xy);
		if (tileCheck->getMine()){
			count += 1;
		}
	} 
	return count;
}

void MinesweeperWindow::cb_quit(){
	close();
}

void MinesweeperWindow::cb_restart(){
    gameOver = false;
    openedTiles = 0;
    flaggedMines = 0;
    minesLeft = mines;

	QuitBtn.setVisible(false);
	RestartBtn.setVisible(false);
	gameOverText.setVisible(false);

	for (auto tile : tiles){
		tile->resetTile();
	}

	int placedMines{0};
	while (placedMines != mines){
		random_device rd;
		default_random_engine generator(rd());
		uniform_int_distribution<int> distribution(0, width * height - 1);
		int n = distribution(generator);

		if (tiles[n]->getMine() == false){
			tiles[n]->setMine();
			placedMines += 1;
		}
	}
	numberMines.setText(std::to_string(minesLeft));

}