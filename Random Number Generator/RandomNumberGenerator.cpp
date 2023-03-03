#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <math.h>
#include <chrono>
using namespace std;

static bool wantNumber = true;
static char more = ' ';
static int digits = 1;

void setDigits() {
	while (true) {
		cout << "How many digits should the code have? (maximum 5): ";
		cin >> digits;
		cin.ignore(LLONG_MAX, '\n');
		if (cin.fail()) {
			cerr << "Please only use numbers." << endl;
			cin.clear();
			cin.ignore(LLONG_MAX, '\n');
		}
		else if (digits <= 0) {
			cout << "The number must be at least 1." << endl;
			cin.clear();
			cin.ignore();
		}
		else if (digits > 5) {
			cout << "The number was too big. It will be set to 5." << endl;
			digits = 5;
			break;
		}
		else if (digits >= 1 && digits <= 5) {
			break;
		}
	}
}

void askForRepeat() {
	while (true) {
		cout << "Do you want to generate another code? y/n/(r)eset: ";
		cin >> setw(1) >> more;
		cin.ignore(LLONG_MAX, '\n');
		if (more == 'y' || more == 'Y') {
			break;
		}
		else if (more == 'n' || more == 'N') {
			wantNumber = false;
			break;
		}
		else if (more == 'r' || more == 'R') {
			setDigits();
			break;
		}
		else {
			cout << "Invalid input." << endl;
		}
	}
}

int main() {
	int number = 0;
	int seedLifeTime = 0;
	long seed;
	setDigits();
	while (wantNumber) {
		if (!seedLifeTime) {
			seed = (chrono::high_resolution_clock::now().time_since_epoch().count() / 100);
			if (seed < 0) {
				seed *= -1;
			}
			seedLifeTime = 5;
			srand(seed);
		}
		number = rand() % (int)pow(10, digits);
		cout << setfill('0') << setw(digits) << number << endl;
		seedLifeTime--;
		askForRepeat();
	}
	cout << endl << "Close program with Return..." << endl;
	cin.ignore();
	return 1;
}