#include<iostream>
#include<limits.h>
#include<cstdlib>
#include<ctime>
using namespace std;

int evaluate(int sticksRemain[4]) {
    int sum = 0;
    for (int i = 0; i < 4; i++) {
        sum ^= sticksRemain[i];
    }
    return sum;
}

int minimax(int sticksRemain[4], int depth, bool isMax) {
    int score = evaluate(sticksRemain);

    if (score == 0) {
        return 0; // Game ends in a draw
    }

    if (depth == 0) {
        return score; // Return the evaluation score
    }

    if (isMax) {
        int best = INT_MIN;

        for (int i = 0; i < 4; i++) {
            if (sticksRemain[i] > 0) {
                int original = sticksRemain[i];
                sticksRemain[i] = 0;

                best = max(best, minimax(sticksRemain, depth - 1, !isMax));

                sticksRemain[i] = original;
            }
        }

        return best;
    } else {
        int best = INT_MAX;

        for (int i = 0; i < 4; i++) {
            if (sticksRemain[i] > 0) {
                int original = sticksRemain[i];
                sticksRemain[i] = 0;

                best = min(best, minimax(sticksRemain, depth - 1, !isMax));

                sticksRemain[i] = original;
            }
        }

        return best;
    }
}

int findBestMove(int sticksRemain[4]) {
    int bestVal = INT_MIN;
    int bestMove = -1;

    for (int i = 0; i < 4; i++) {
        if (sticksRemain[i] > 0) {
            int original = sticksRemain[i];
            sticksRemain[i] = 0;

            int moveVal = minimax(sticksRemain, 3, false);

            sticksRemain[i] = original;

            if (moveVal > bestVal) {
                bestMove = i + 1; // Convert to 1-based index
                bestVal = moveVal;
            }
        }
    }

    return bestMove;
}

int main() {
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
        // cout << "Enter name for second player: ";
        // cin.getline(secondPlayer, size);

        int sticksRemain[4]{ 1, 3, 5, 7 }; // Initial sticks in each row
        int sum{}, line{}, sticks{};
        int turn;

        bool flag = rand() % 2; // randomly selecting one for toss
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
        if (result == 'H')
            cout << "head" << endl;
        else
            cout << "tail" << endl;

        if (option == result) {
            if (flag)
                turn = 1;
            else
                turn = 0;
        } else {
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

        do {
            if (turn) {
                cout << firstPlayer;
                turn--;
            } else {
                cout << secondPlayer;
                turn++;
            }

            cout << " your turn" << endl;

            if (turn == 0) { // Human player's turn
                cout << "Please select row number(1,2,3,4): ";
                cin >> line;
                while (line < 1 || line > 4 || sticksRemain[line - 1] == 0) {
                    cout << "Invalid input! Please choose a valid row: ";
                    cin >> line;
                }

                cout << "Enter number of sticks you want to remove available are (" << sticksRemain[line - 1] << "): ";
                cin >> sticks;
                while (sticks <= 0 || sticks > sticksRemain[line - 1]) {
                    cout << "Invalid input! Please enter a valid number of sticks: ";
                    cin >> sticks;
                }

            } else { // AI player's turn
                cout << "AI is thinking..." << endl;
                int bestMove = findBestMove(sticksRemain);
                line = bestMove;
                sticks = sticksRemain[bestMove - 1];

                cout << "AI chose to remove " << sticks << " sticks from row " << line << endl;
            }

            sticksRemain[line - 1] -= sticks;

            // Display the updated game state
            for (int i = 3, h = 0; i >= 0; i--, h++) {
                for (int j = 3, n = 0; j > 0; j--, n++) {
                    for (int k = 0; k < i * (2 * (j + n)); k++) {
                        cout << " ";
                    }
                    for (int l = 0; l <= ((j + n) * 2) * (sticksRemain[h] - 1); l++) {
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
                sum += sticksRemain[i];
            }

        } while (sum >= 1);

        if (turn)
            cout << firstPlayer;
        else
            cout << secondPlayer;

        cout << " congratulations you won the game! ";

        cout << "Do you want to play again(Y/N): ";
        cin >> option;

        while (option != 'N' && option != 'n' && option != 'Y' && option != 'y') {
            cout << "Wrong input entered! please enter again: ";
            cin >> option;
        }

        cin.ignore();
    } while (option == 'y' || option == 'Y');

    cout << "Thanks for playing!";
    return 0;
}
