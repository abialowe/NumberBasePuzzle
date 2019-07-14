// INCLUDE NEEDED LIBRARIES
#include <iostream>		// for IO
#include <iomanip>		// for stream-based IO formatting
using namespace std;

#include <conio.h>		// for _getch()
#include <Windows.h>	// for API-based "console" manipulation

#include <stdlib.h>		// for rand() and srand()
#include <time.h>		// for time()

// DEFINES (GREEK SYMBOLIC REPRESENTATIONS)
#define CH_ALPHA			224		// α -> Z
#define CH_OMEGA			234		// Ω -> I
#define CH_MU				230		// µ -> II
#define CH_SIGMA			228		// Σ -> III
#define CH_PI				227		// π -> IV
#define CH_EPSILON			238		// ε -> V

#define B_BLACK_F_WHITE		15		// COLOR CODES!
#define B_BLACK_F_RED		12		// ""
#define B_BLACK_F_BLUE		3		// ""
#define B_BLACK_F_GREEN		10		// ""
#define B_BLACK_F_PURPLE	13		// ""
#define B_BLACK_F_AQUA		11		// ""
#define B_BLACK_F_YELLOW	14		// ""

#define MAX_DIGITS			10		// NO TOGGLE
#define LOGICAL_BASE		6		// THE LOGICAL NUMERIC BASE

// STRUCTURES
struct B6Integer {
	int digits[MAX_DIGITS];
};

// FUNCTION PROTOTYPES
bool printSymbol(int symbolCode);
void backToBlack();
void InitializeB6Integer(B6Integer&);
void printB6IntegerNoMask(B6Integer);
void printB6IntegerYesMask(B6Integer);
B6Integer AddB6Integers(B6Integer, B6Integer);
void loadRandomB6(B6Integer&, int);

// CORE LOGIC
void main() {
	// SETUP
	// seed RNG
	srand((unsigned int)time(NULL));
	
	// establish a baseline color aesthetic
	backToBlack();

	// initialize it
	B6Integer add1;
	B6Integer add2;
	B6Integer result;
	InitializeB6Integer(add1);
	InitializeB6Integer(add2);
	InitializeB6Integer(result);

	for (;;) {
		// load test case and operate
		int firstDigitGroup = rand() % 5 + 3;
		loadRandomB6(add1, firstDigitGroup);
		loadRandomB6(add2, firstDigitGroup - rand() % 3);
		result = AddB6Integers(add1, add2);

		// show some addition
		cout << setw(8) << "";
		printB6IntegerYesMask(add1); cout << endl;

		cout << setw(8) << "#";
		printB6IntegerYesMask(add2); cout << endl;

		cout << setfill('-') << setw(36) << "" << setfill(' ') << endl;

		cout << setw(8) << "";
		printB6IntegerYesMask(result); cout << endl;

		cout << endl << endl;
		cout << "PRESS ANY KEY TO GENERATE ANOTHER ONE!" << endl;
		_getch();
		cout << endl << endl;
	}
}

// FUNCTION DEFINITIONS
bool printSymbol(int symbolCode) {
	// get the console window's handle
	HANDLE currentConsole;
	currentConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (symbolCode == CH_ALPHA || symbolCode == CH_OMEGA ||
		symbolCode == CH_MU || symbolCode == CH_SIGMA ||
		symbolCode == CH_PI || symbolCode == CH_EPSILON) {

		// shift color
		switch (symbolCode) {
		case CH_ALPHA:
			SetConsoleTextAttribute(currentConsole, B_BLACK_F_RED);
			break;
		case CH_OMEGA:
			SetConsoleTextAttribute(currentConsole, B_BLACK_F_BLUE);
			break;
		case CH_MU:
			SetConsoleTextAttribute(currentConsole, B_BLACK_F_GREEN);
			break;
		case CH_SIGMA:
			SetConsoleTextAttribute(currentConsole, B_BLACK_F_PURPLE);
			break;
		case CH_PI:
			SetConsoleTextAttribute(currentConsole, B_BLACK_F_AQUA);
			break;
		case CH_EPSILON:
			SetConsoleTextAttribute(currentConsole, B_BLACK_F_YELLOW);
			break;
		}
		
		// echo the symbol
		cout << (char)symbolCode;

		// shift color back
		backToBlack();

		return true;
	}
	else {
		return false;
	}
}

void backToBlack() {
	// get the current window's handle
	HANDLE currentConsole;
	currentConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// shift to black
	SetConsoleTextAttribute(currentConsole, B_BLACK_F_WHITE);

}

void InitializeB6Integer(B6Integer& initializeMe) {
	for (int i = 0; i < MAX_DIGITS; i++) {
		initializeMe.digits[i] = 0;
	}
}

void printB6IntegerNoMask(B6Integer showMe) {
	cout << left;
	for (int i = 0; i < MAX_DIGITS; i++) {
		cout << setw(3) << showMe.digits[i];
	}

}

void printB6IntegerYesMask(B6Integer showMe) {
	cout << left;
	for (int i = 0; i < MAX_DIGITS; i++) {
		cout << setw(3);
		switch (showMe.digits[i]) {
		case 0:
			printSymbol(CH_ALPHA);
			break;
		case 1:
			printSymbol(CH_OMEGA);
			break;
		case 2:
			printSymbol(CH_MU);
			break;
		case 3:
			printSymbol(CH_SIGMA);
			break;
		case 4:
			printSymbol(CH_PI);
			break;
		case 5:
			printSymbol(CH_EPSILON);
			break;
		}
	}
}

B6Integer AddB6Integers(B6Integer ad1, B6Integer ad2) {
	B6Integer result;				// tabulate the result in here
	InitializeB6Integer(result);	// remove memory garbage
	int carryCharge = 0;			// holds the carry charge as we add

	for (int i = MAX_DIGITS - 1; i >= 0; i--) {
		int chargeCount = ad1.digits[i] + ad2.digits[i] + carryCharge;
		carryCharge = 0;			// reset the carry charge... it has just been exhausted

		if (chargeCount < LOGICAL_BASE) {
			result.digits[i] = chargeCount;
		}
		else {
			while (chargeCount >= LOGICAL_BASE) {
				chargeCount -= LOGICAL_BASE;
				carryCharge += 1;
			}
			result.digits[i] = chargeCount;
		}
	}

	return result;
}

void loadRandomB6(B6Integer& loadMe, int thisManyFigures) {
	for (int i = 0; i < thisManyFigures; i++) {
		loadMe.digits[MAX_DIGITS - 1 - i] = rand() % LOGICAL_BASE;
	}
}