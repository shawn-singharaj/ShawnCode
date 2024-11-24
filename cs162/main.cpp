/*
 * Author: Shawn Singharaj
 * Program description: Simulates a basketball shooting game reminiscent of the NBA 3-point contest. Two or more players
 * will take turns inputting their money ball rack of choice and shooting ability to get the results of each rack and
 * scores compared to declare a winner.
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// function declarations
void moneyInd(int *m, int *l, int *h);
void genArray(int arr[], int *s, int *m);

// sets the low and high range of the array indexes for money ball rack based on user input
void moneyInd(int *m, int *l, int *h){
	switch(*m){ // using the moneyRack var from main
		case 1: // if user inputs rack 1, then the index positions are 0 to 4
			*l = 0;
			*h = 4;
			break;
		case 2: 
			*l = 5;
			*h = 9;
			break;
		case 3: 
			*l = 11; // because of starry ball, the index range is pushed by 1
			*h = 15;
			break;
		case 4: 
			*l = 17; // now pushed by 2 compared to originally
			*h = 21;
			break;
		default: // user input = 5
			*l = 22;
			*h = 27;
			break;
	}
}
// generates the array and assigns value based on random int 0-99
void genArray(int arr[], int *s, int *m, int *sc){
	int low, high; // index ranges from moneyInd()
	moneyInd(m, &low, &high); // call function for index range
	*sc = 0;
	for(int i = 0; i < 27; i++){
		int randNum = rand() % 100; // 0-99
		if(randNum <= *s) // if the random int is less than shooting ability, shot is made
		{
			if(i == 10 || i == 16) // if starry ball
			{
				arr[i] = 3;
			}
			else if((i == 4 || i == 9 || i == 15 || i == 21 || i == 26) || ((i >= low) && (i <= high))) // if money ball or moneyball rack
			{
				arr[i] = 2;
			}
			else // if regular ball
			{
				arr[i] = 1;
			}
		}
		else // if miss
		{
			arr[i] = 0;
		}
		*sc += arr[i]; // score is the total value of array
	}
}

int main() {
	srand(time(nullptr)); 
	int shooting_results[27]; // main array
	char playAgain = 'y';
	
	do{ // loop until player chooses not to play again
		int playerNum, moneyRack, shootingAbility, score, rackScore, hiScore, winner; // declare int vars
		int player = 1; // first player starts
		do{ // ask user for how many players
			cout << "How many players will be playing? ";
			cin >>  playerNum;

			if(playerNum < 2) // input cannot be less than 2
			{
				cout << "\nInvalid input, must be more than 1: ";
			}
		}while(playerNum < 2);
		
		for(int i = 0; i < playerNum; i++) // loop for however many players there are
		{
			cout << "\nPlayer " << player << ":"; 
			do{ // ask user for which money ball rack
			cout << "\n Where do you want your money ball rack? (1-5): "; 
			cin >> moneyRack;
			if(moneyRack < 1 || moneyRack > 5) // must be between 1-5
			{
				cout << "Invalid input, try again.";
			}
			}while(moneyRack < 1 || moneyRack > 5);
			
			do{ // ask user for shooting ability
				cout << "\n What is your shooting ability? (1-99): ";
				cin >> shootingAbility;
				if(shootingAbility < 1 || shootingAbility > 99) // must be between 1-99
				{
					cout << "Invalid input, try again.";
				}
			}while(shootingAbility < 1 || shootingAbility > 99);
			// call function by passing array and user inputs + final score
			genArray(shooting_results, &shootingAbility, &moneyRack, &score); 
			rackScore = 0; // each rack's score
			int rackNum = 2; 
			cout << "\nRack 1: "; // outputting the rack outcomes
			for(int i = 0; i < 27; i++)
			{
				if(i == 5 || i == 11 || i == 17 || i == 22){ // make a new line every rack
					cout << rackScore << " pts\nRack " << rackNum << ": ";
					++rackNum;
					rackScore = 0;
				}
				if(i == 10 || i == 16) // make  anew line for each starry shot
				{
					cout << rackScore << "pts\nStarry: ";
					rackScore = 0;
				}
				if(shooting_results[i] == 0) // output array by assiging characters depending on index value
					cout << "_ ";
				else if(shooting_results[i] == 1){
					cout << "X ";
					rackScore += 1;
				}
				else if(shooting_results[i] == 2){
					cout << "M ";
					rackScore += 2;
				}
				else if(shooting_results[i] == 3)
				{
					cout << "S ";
					rackScore += 3;
				}
			}
			cout << rackScore << " pts\nTotal Score: " << score << endl; // output player's total score

			if(score >= hiScore){  // to find winner
				hiScore = score;
				winner = player;
			}
			++player;
		}
		cout << "\nThe winner is Player " << winner << " with a score of " << hiScore << "!\n Would you like to play again? (y/n): "; // declare winner
		cin >> playAgain; // ask user to play again
	}while(playAgain == 'y');
}
