#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <windows.h>
#include <string>
using namespace std;
const int MAX_ROWS = 10;
const int MAX_COLS = 10;

const int REDPEN = 4;
const int GREENPEN = 2;
const int BLUE = 153;
const int RED = 204;
const int GREEN = 119;
const int WHITEPEN = 7;
const int YELLOWPEN = 14;
#define toDigit(c) (c-'0')

void drawGrid(char ships[MAX_ROWS][MAX_COLS]);
void revealShips(char ships[MAX_ROWS][MAX_COLS], char guesses[MAX_ROWS][MAX_COLS]);
void initGrid(char ships[MAX_ROWS][MAX_COLS]);
void enterShips(char ships[MAX_ROWS][MAX_COLS]);
void setColor(int  colorDesired);
bool validateCoordinates(char orientation, char row, char column, char ships[MAX_ROWS][MAX_COLS], int shipSize);
void playGame(char ships[MAX_ROWS][MAX_COLS], char guesses[MAX_ROWS][MAX_COLS]);
bool isEndOfGame(int numberOfGuesses, char ships[MAX_ROWS][MAX_COLS]);
void updateGuesses(char guesses[MAX_ROWS][MAX_COLS]);
void generateShips(char ships[MAX_ROWS][MAX_COLS]); 
bool validateRandomCoordinates(char orientation, int int_row, int int_column, char ships[MAX_ROWS][MAX_COLS], int shipSize);

int main()
{
	srand(time(0));
	char ships[MAX_ROWS][MAX_COLS];
	char guesses[MAX_ROWS][MAX_COLS];
	bool play_game = true;
	char play_again;
	int player_count;
 

	while (play_game == true) {
		system("cls");
		for (int i = 0; i < MAX_ROWS; i++)
			for (int j = 0; j < MAX_COLS; j++) {
				ships[i][j] = ' ';
				guesses[i][j] = ' ';
			}

		initGrid(ships);
		setColor(WHITEPEN);
		cout << "Welcome to Battleship! " << endl; 
		cout << "" << endl;
		cout << "Would you like to play 1 player or 2 player ? Enter 1 or 2 : ";
		cin >> player_count;

		if (player_count == 1)
			generateShips(ships);
		else
			enterShips(ships);
		setColor(WHITEPEN);
		cout << "Ships are all set. Game will begin on <Enter>." << endl;
		system("pause");
		system("cls");
		playGame(ships, guesses);

		bool ship_not_found = true;
		for (int i = 0; i < MAX_ROWS; i++) {
			for (int j = 0; j < MAX_COLS; j++) {
				if (ships[i][j] == 'x')
					ship_not_found = false;
			}
		}

		if (ship_not_found == true) {
			setColor(WHITEPEN);
			cout << "You have won the game!" << endl;
			cout << "Would you like to play again? Enter Y for yes or N for no : ";
		}
		else {
			revealShips(ships, guesses);
			cout << "You have lost the game!" << endl;
			cout << "Would you like to play again? Enter Y for yes or N for no : ";
		}

		cin >> play_again;
		if (tolower(play_again) == 'y')
			play_game = true;
		else
			play_game = false;
	}
	return 0;
}

void initGrid(char ships[MAX_ROWS][MAX_COLS]) {
	for (int i = 0; i < MAX_ROWS; i++) {
		if (i == 0) {
			cout << "  0 1 2 3 4 5 6 7 8 9" << endl;
		}
		else {
			cout << endl;
		}
		for (int j = 0; j < MAX_COLS; j++) {
			if (j == 0) {
				setColor(WHITEPEN);
				cout << i << " ";
			}
			setColor(BLUE);
			cout << ships[i][j] << " ";
		}
	}

	cout << endl;
	cout << endl;
}

void generateShips(char ships[MAX_ROWS][MAX_COLS])
{
	int row, column, ship_size, orientation_number;
	char orientation;
	ship_size = 6;
	bool isValid = false;

	for (int i = 1; i < ship_size; i++) {
		while (!isValid) {
		row = rand() % (9 + 1);
		column = rand() % (9 + 1);
		orientation_number = rand() % 2;
		if (orientation_number == 0)
			orientation = 'h';
		else
			orientation = 'v';
		
			isValid = validateRandomCoordinates(orientation, row, column, ships, i);
		}

		//drawGrid(ships);
		isValid = false;
	}
}

void enterShips(char ships[MAX_ROWS][MAX_COLS])
{
	char ship1[256], ship2[256], ship3[256], ship4[256], ship5[256];
	bool isValid = false;
	setColor(WHITEPEN);
	cout << "**************************************************" << endl;
	cout << "* You will enter 5 ships [size 1-5],             *" << endl;
	cout << "* For each ship enter H=horizontal, V=vertical   *" << endl;
	cout << "* followed by row, column coordinates            *" << endl;
	cout << "* Example: H 0 0                                 *" << endl;
	cout << "**************************************************" << endl;
	cout << "Begin Entering Ships!" << endl;
	cin.ignore();

	while (!isValid) { // SHIP 1
		setColor(WHITEPEN);
		cout << "Ship #1 [1]: ";
		cin.getline(ship1, 256);
		if (!(tolower(ship1[0]) == 'h' || tolower(ship1[0]) == 'v' ||
			  tolower(ship1[0]) == 'x' || tolower(ship1[0]) == 'y')) {
			isValid = false;
			cout << "Error: enter H or V" << endl;
		}
		else {
			isValid = validateCoordinates(ship1[0], ship1[2], ship1[4], ships, 1);
			if (isValid == false) {
				cout << "Error: invalid row, col grid coordinate!" << endl;
			}
		}
	}

	drawGrid(ships);
	isValid = false;

	while (!isValid) { // SHIP 2
		setColor(WHITEPEN);
		cout << "Ship #2 [2]: ";
		cin.getline(ship2, 256);
		if (!(tolower(ship2[0]) == 'h' || tolower(ship2[0]) == 'v' ||
			tolower(ship2[0]) == 'x' || tolower(ship2[0]) == 'y')) {
			isValid = false;
			cout << "Error: enter H or V" << endl;
		}
		else {
			isValid = validateCoordinates(ship2[0], ship2[2], ship2[4], ships, 2);
			if (isValid == false) {
				cout << "Error: invalid row, col grid coordinate!" << endl;
			}
		}
	}

	drawGrid(ships);
	isValid = false;

	while (!isValid) { // SHIP 3
		setColor(WHITEPEN);
		cout << "Ship #3 [3]: ";
		cin.getline(ship3, 256);
		if (!(tolower(ship3[0]) == 'h' || tolower(ship3[0]) == 'v' ||
			tolower(ship3[0]) == 'x' || tolower(ship3[0]) == 'y')) {
			isValid = false;
			cout << "Error: enter H or V" << endl;
		}
		else {
			isValid = validateCoordinates(ship3[0], ship3[2], ship3[4], ships, 3);
			if (isValid == false) {
				cout << "Error: invalid row, col grid coordinate!" << endl;
			}
		}
	}

	drawGrid(ships);
	isValid = false;

	while (!isValid) { // SHIP 4
		setColor(WHITEPEN);
		cout << "Ship #4 [4]: ";
		cin.getline(ship4, 256);
		if (!(tolower(ship4[0]) == 'h' || tolower(ship4[0]) == 'v' ||
			tolower(ship4[0]) == 'x' || tolower(ship4[0]) == 'y')) {
			isValid = false;
			cout << "Error: enter H or V" << endl;
		}
		else {
			isValid = validateCoordinates(ship4[0], ship4[2], ship4[4], ships, 4);
			if (isValid == false) {
				cout << "Error: invalid row, col grid coordinate!" << endl;
			}
		}
	}

	drawGrid(ships);
	isValid = false;

	while (!isValid) { // SHIP 5
		setColor(WHITEPEN);
		cout << "Ship #5 [5]: ";
		cin.getline(ship5, 256);
		if (!(tolower(ship5[0]) == 'h' || tolower(ship5[0]) == 'v' ||
			tolower(ship5[0]) == 'x' || tolower(ship5[0]) == 'y')) {
			isValid = false;
			cout << "Error: enter H or V" << endl;
		}
		else {
			isValid = validateCoordinates(ship5[0], ship5[2], ship5[4], ships, 5);
			if (isValid == false) {
				cout << "Error: invalid row, col grid coordinate!" << endl;
			}
		}
	}

	drawGrid(ships);
	isValid = false;
}

void drawGrid(char ships[MAX_ROWS][MAX_COLS])
{
	for (int i = 0; i < MAX_ROWS; i++) {
		if (i == 0) {
			setColor(WHITEPEN);
			cout << "  0 1 2 3 4 5 6 7 8 9" << endl;
		}
		else {
			cout << endl;
		}
		for (int j = 0; j < MAX_COLS; j++) {
			if (j == 0) {
				setColor(WHITEPEN);
				cout << i << " ";
			}
			if (ships[i][j] == 'x') {
				setColor(YELLOWPEN);
				cout << ships[i][j] << ships[i][j];
			}
			else {
				setColor(BLUE);
				cout << ships[i][j] << ships[i][j];
			}
		}
	}

	cout << endl;
	cout << endl;
}

void revealShips(char ships[MAX_ROWS][MAX_COLS], char guesses[MAX_ROWS][MAX_COLS])
{
	for (int i = 0; i < MAX_ROWS; i++) {
		if (i == 0) {
			setColor(WHITEPEN);
			cout << "  0 1 2 3 4 5 6 7 8 9" << endl;
		}
		else {
			setColor(WHITEPEN);
			cout << endl;
		}
		for (int j = 0; j < MAX_COLS; j++) {
			if (j == 0) {
				setColor(WHITEPEN);
				cout << i << " ";
			}
			if (guesses[i][j] == 'H') {
				setColor(RED);
				cout << "  ";
			}
			else if (guesses[i][j] == '*') {
				setColor(GREEN);
				cout << "  ";
			}
			else if (ships[i][j] == 'x') {
				setColor(YELLOWPEN);
				cout << "xx";
			}
			else {
				setColor(BLUE);
				cout << "  ";
			}
		}
	}

	setColor(WHITEPEN);
	cout << endl;
	cout << endl;
}

void setColor(int colorDesired) {
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, colorDesired);
}

bool validateRandomCoordinates(char orientation, int int_row, int int_column, char ships[MAX_ROWS][MAX_COLS], int shipSize)
{
	if (int_row > 9 || int_column > 9)
		return false;

	for (int i = 0; i < shipSize; i++) { // check
		if (orientation == 'h' || orientation == 'x') {
			if (ships[int_row][int_column + i] == 'x' || (int_column + i) > 9 ||
				ships[int_row + 1][int_column + i] == 'x' || ships[int_row - 1][int_column + i] == 'x' ||
				ships[int_row][(int_column + i) + 1] == 'x' || ships[int_row][(int_column + i) - 1] == 'x') {
				return false;
			}
		}

		if (orientation == 'v' || orientation == 'y') {
			if (ships[int_row + i][int_column] == 'x' || (int_row + i) > 9 ||
				ships[int_row + i][int_column + 1] == 'x' || ships[int_row + i][int_column - 1] == 'x' ||
				ships[(int_row + i) + 1][int_column] == 'x' || ships[(int_row + i) - 1][int_column] == 'x') {
				return false;
			}
		}
	}

	for (int i = 0; i < shipSize; i++) { // add
		if (orientation == 'h' || orientation == 'x') {
			if (ships[int_row][int_column + i] != 'x') {
				ships[int_row][int_column + i] = 'x';
			}
			else {
				return false;
			}
		}

		if (orientation == 'v' || orientation == 'y') {
			if (ships[int_row + i][int_column] != 'x') {
				ships[int_row + i][int_column] = 'x';
			}
			else {
				return false;
			}
		}
	}

	return true;
}

bool validateCoordinates(char orientation, char row, char column, char ships[MAX_ROWS][MAX_COLS], int shipSize)
{
	int int_row, int_column;
	int_row = toDigit(row);
	int_column = toDigit(column);

	if (int_row > 9 || int_column > 9)
		return false;

	for (int i = 0; i < shipSize; i++) { // check
		if (orientation == 'h' || orientation == 'x') {
			if (ships[int_row][int_column + i]       == 'x' || (int_column + i) > 9 ||
				ships[int_row + 1][int_column + i]   == 'x' || ships[int_row - 1][int_column + i] == 'x' ||
				ships[int_row][(int_column + i) + 1] == 'x' || ships[int_row][(int_column + i) - 1] == 'x') {
				return false;
			}
		}

		if (orientation == 'v' || orientation == 'y') {
			if (ships[int_row + i][int_column]       == 'x' || (int_row + i) > 9 ||
				ships[int_row + i][int_column + 1]   == 'x' || ships[int_row + i][int_column - 1] == 'x' ||
				ships[(int_row + i) + 1][int_column] == 'x' || ships[(int_row + i) - 1][int_column] == 'x') {
				return false;
			}
		}
	}

	for (int i = 0; i < shipSize; i++) { //add
		if (orientation == 'h' || orientation == 'x') {
			if (ships[int_row][int_column + i] != 'x') {
				ships[int_row][int_column + i] = 'x';
			}
			else {
				return false;
			}
		}

		if (orientation == 'v' || orientation == 'y') {
			if (ships[int_row + i][int_column] != 'x') {
				ships[int_row + i][int_column] = 'x';
			}
			else {
				return false;
			}
		}
	}

	return true;
}

void playGame(char ships[MAX_ROWS][MAX_COLS], char guesses[MAX_ROWS][MAX_COLS])
{
	char coordinate[256];
	int int_row, int_column;

	int numberOfGuesses = 50;
	cin.ignore();
	while (!isEndOfGame(numberOfGuesses, ships)) {
		setColor(WHITEPEN);
		cout << "Enter guess: ";
		cin.getline(coordinate, 256);
		int_row = toDigit(coordinate[0]);
		int_column = toDigit(coordinate[2]);
		if (ships[int_row][int_column] == 'x') {
			guesses[int_row][int_column] = 'H';
			ships[int_row][int_column] = 'H';
		}
		else {
			guesses[int_row][int_column] = '*';
		}

		updateGuesses(guesses);
		numberOfGuesses--;
		setColor(WHITEPEN);
		cout << "You have " << numberOfGuesses << " guesses left." << endl;
	}
}

bool isEndOfGame(int numberOfGuesses, char ships[MAX_ROWS][MAX_COLS])
{
	bool ship_not_found = true;
	for (int i = 0; i < MAX_ROWS; i++) {
		for (int j = 0; j < MAX_COLS; j++) {
			if (ships[i][j] == 'x')
				ship_not_found = false;
		}
	}

	if (ship_not_found == true)
		return true;

	if (numberOfGuesses == 0)
		return true;
	else
		return false;
}

void updateGuesses(char guesses[MAX_ROWS][MAX_COLS])
{
	for (int i = 0; i < MAX_ROWS; i++) {
		if (i == 0) {
			setColor(WHITEPEN);
			cout << "  0 1 2 3 4 5 6 7 8 9" << endl;
		}
		else {
			setColor(WHITEPEN);
			cout << endl;
		}
		for (int j = 0; j < MAX_COLS; j++) {
			if (j == 0) {
				setColor(WHITEPEN);
				cout << i << " ";
			}
			if (guesses[i][j] == 'H') {
				setColor(RED);
				cout << "  ";
			}
			else if (guesses[i][j] == '*') {
				setColor(GREEN);
				cout << "  ";
			}
			else {
				setColor(BLUE);
				cout << "  ";
			}
		}
	}

	setColor(WHITEPEN);
	cout << endl;
	cout << endl;
}
