#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
int main()
{
	cout << "                    ---------------------------------" << endl;
	cout << "                    |           Nim Game            |" << endl;
	cout << "                    ---------------------------------" << endl;
	cout << "          NOTE: you win if you leave LAST MATCH STICK for your opponent!" << endl << endl;
	const int size = 100;
	char firstPlayer[size], secondPlayer[size], option;
	srand(time(0));
	do {
		cout << "Enter name for first Player: ";
		cin.getline(firstPlayer, size);
		cout << "Enter name for second player: ";
		cin.getline(secondPlayer, size);
		int turn;
		bool flag = rand() % 2;//randomly selecting one for toss
		if (flag)
			cout << firstPlayer;
		else
			cout << secondPlayer;
		cout << " please select head(H/h) or tail(T/t) for toss: ";
		cin >> option;
		while (option != 'h' && option != 'H' && option != 'T' && option != 't') {
			cout << "Wrong input entered! please enter again: ";
			cin >> option;
		}
		if (option >= 97 && option <= 122)
			option = option - 32;
		char result = rand() % 2 ? 'H' : 'T';
		cout << "Coin tosses for ";
		if (result == 'H')//checking toss results
			cout << "head" << endl;
		else
			cout << "tail" << endl;
		if (option == result)//selecting winner
		{
			if (flag)
				turn = 1;
			else
				turn = 0;
		}
		else {
			if (flag)
				turn = 0;
			else
				turn = 1;
		}
		if (turn)
			cout << firstPlayer;
		else
			cout << secondPlayer;
		cout << " won the toss!" << endl;
		int sticksRemain[4]{};
		for (int i = 3, h = 0; i >= 0; i--, h++) {//whole
			sticksRemain[h] = (h * 2) + 1;
			for (int j = 3, n = 0; j > 0; j--, n++) {//every match stick line
				for (int k = 0; k < i * (2 * (j + n)); k++) {//initial space for each line
					cout << " ";
				}
				for (int l = 0; l <= ((j + n) * 2) * (sticksRemain[h] - 1); l++) {//after initial space
					if (l % 6 == 0)
						cout << "|";
					else
						cout << " ";
				}
				cout << endl;
			}
			cout << endl;
		}
		int sum{}, line{}, sticks{};
		do {
			if (turn) {
				cout << firstPlayer;
				turn--;
			}
			else {
				cout << secondPlayer;
				turn++;
			}
			cout << " your turn" << endl;
			cout << "Please select row number(1,2,3,4): ";
			do {
				flag = false;
				cin >> line;
				if (line > 4 || line < 1) {
					cout << "Wrong row number entered! Please select again: ";
					flag = true;
				}
				else if (sticksRemain[line - 1] == 0) {
					cout << "No sticks in row! Please choose row with remaining sticks: ";
					flag = true;
				}
			} while (flag);

			do {
				flag = false;
				cout << "Enter number of sticks you want to remove availaible are (" << sticksRemain[line - 1] << "): ";
				do {
					flag = false;
					cin >> sticks;
					if (sticks > sticksRemain[line - 1] || sticks <= 0) {
						cout << "Wrong input! Please enter again availaible sticks are (" << sticksRemain[line - 1] << "): ";
						flag = true;
					}
				} while (flag);
				sticksRemain[line - 1] = sticksRemain[line - 1] - sticks;
				for (int i = 3, h = 0; i >= 0; i--, h++) {//whole
					for (int j = 3, n = 0; j > 0; j--, n++) {//every match stick line
						for (int k = 0; k < i * (2 * (j + n)); k++) {//initial space for each line
							cout << " ";
						}
						for (int l = 0; l <= ((j + n) * 2) * (sticksRemain[h] - 1); l++) {//after initial space
							if (l % 6 == 0)
								cout << "|";
							else
								cout << " ";
						}
						cout << endl;
					}
					cout << endl;
				}
				sum = 0;
				for (int i = 0; i < 4; i++) {
					sum = sum + sticksRemain[i];
				}
				if (sticksRemain[line - 1] > 0) {
					cout << "Do you want to remove more sticks from this row(Y/N): ";
					cin >> option;
					while (option != 'Y' && option != 'y' && option != 'n' && option != 'N') {
						cout << "Wrong input entered! Please enter again: ";
						cin >> option;
					}
					if (option == 'y' || option == 'Y')
						flag = true;
				}
			} while (flag);
		} while (sum >= 1);
		if (turn)
			cout << firstPlayer;
		else
			cout << secondPlayer;
		cout << " congradulation you won the game! ";
		cout << "Do you want to play again(Y/N): ";
		cin >> option;
		while (option != 'N' && option != 'n' && option != 'Y' && option != 'y') {
			cout << "Wrong input entered! please enter again: ";
			cin >> option;
		}
		cin.ignore();
	}while (option == 'y' || option == 'Y');
	cout << "Thanks for playing!";
}