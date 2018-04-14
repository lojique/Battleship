//<Battleship.cpp> -- Creates the game battleship
//CSIS 111-<002>
//<Problem 1 on page 615, received help from Dale Hall and his friend John>


//Include statements
#include <iostream>
#include <string>
#include <array>
#include <fstream>
#include "NegativeNumberException.h"

using namespace std;

//Global declarations: Constants and type definitions only -- no variables
const int ROWS = 25;
const int COLS = 25;

//Function prototypes
void Fire(int, int, int&);
void FleetSunk(int, int, bool&);
void validCoordinates(int, int);

//char board[COLS][ROWS];
array<array< char, COLS>, ROWS> board;



int main()
{
	//In cout statement below substitute your name and lab number
	cout << "Adam Kalu -- Lab 9" << endl << endl;

	//Variable declarations
	ifstream boardFile; //this is for the gameboard
	bool fleetSunk = false;
	int boatPieces = 0;
	int hitCount = 0;
	int x;
	int y;



	//Program logic
	boardFile.open("setup.txt"); //opens file containing board

	//Checks to see if the gameboard is in the file
	if (!boardFile){
		cout << "File opening error."
			<< "Program Terminated." << endl;
		//system("pause");
		return 1;
	}

	//inputs value from txtfile and puts it into the board
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			//takes information from setup.txt and puts it into the 25x25 array
			boardFile >> board[i][j];
			//if there is a # character found in the board, it will add them all up and assign them to the variable boatPieces
			if (board[i][j] == '#')
			{
				boatPieces++;
			}
		}
	}

	//for loop makes program run just once so once fleetsunk == true, program will terminate
	//1 has to be subtracted from x and y because initially (1,1) would really be (0,0)
	while (fleetSunk == false)
	{
		cout << "Enter an X and Y coordinate: ";
		while (fleetSunk == false && cin >> x >> y) {
			try {
				validCoordinates(x,y);
				
			}
			catch (const NegativeNumberException& negativeNumberException) {
				cout << "Exception occured: "
					<< negativeNumberException.what() << endl;
			}
			
			if (x > 0 && y > 0) {
				x = x - 1;
				y = y - 1;
				Fire(x, y, hitCount);
				FleetSunk(boatPieces, hitCount, fleetSunk);
			}
			if (fleetSunk == false) {
				cout << "Enter an X and Y coordinate: ";

			}

		}
		cout << endl;		

		//cout << "Enter an X coordinate: ";
		//cin >> x; //gets x coordinate from user
		//x = x - 1;
		//
	
		//cout << "Enter a Y coordinate: ";
		//cin >> y; //gets y coordinate from user
		//y = y - 1;
		
		//Both functions need to be put into for loop to
	
	}
	

	//Closing program statements
	boardFile.close();
	system("pause");
	return 0;
}

//Function definitions
//Function takes x and y coordinates to determine if a ship has been hit, 
void Fire(int x, int y, int& hitCount){
	

	//If the user's coordinates find a '~', console will print out "MISS"
	if (board[x][y] == '~' ){
		cout << "MISS!" << endl << endl;
	}

	//If the user's coordinate find a '#', console will print out "HIT"
	else if (board[x][y] == '#'){
		cout << "HIT!" << endl << endl;
		//Adds # to hit every time a user finds a #
		hitCount++;
		//changes # to H so user will know what coordinate has already been hit
		board[x][y] = 'H';
	}

	//if user's coordinate lands on 'H', console will tell user they've already made a hit
	else if (board[x][y] == 'H')
		cout << "HIT AGAIN" << endl << endl;


}

//Function determines whether or not all ships have been hit
void FleetSunk(int boatPieces, int hitCount, bool& fleetSunk){

	//if the number of boatpieces(#) are the same as the number of hits then all ships are destroyed and fleet is sunk
	if (boatPieces == hitCount){
		fleetSunk = true;
		cout << "The fleet was sunk!" << endl;

	}
}

void validCoordinates(int x, int y) {
	if (x < 0 || y < 0){
		throw NegativeNumberException{};
	}
}