/******************************************************************************
** Program Filename: Farkle.cpp
** Author: Ben Johnson
** Date: February 26, 2018
** Description: Creates a text based game that emulates the dice game Farkle.
** Input: Various user inputs for the number of players and their names.
** Output: Various text displaying the state of the game.
******************************************************************************/

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

//global constants
const int SINGLE_1 = 1;
const int SINGLE_5 = 2;
const int THREE_1 = 3;
const int THREE_2 = 4;
const int THREE_3 = 5;
const int THREE_4 = 6;
const int THREE_5 = 7;
const int THREE_6 = 8;
const int FOUR_OF_KIND = 9;
const int FIVE_OF_KIND = 10;
const int SIX_OF_KIND = 11;
const int STRAIGHT = 12;
const int THREE_PAIR = 13;
const int FOUR_OF_KIND_WITH_PAIR = 14;
const int TWO_TRIPLES  = 15;

//All fucntions in the program.
void start_game();
void play_game(int* scores, string* names, int& num_players);
void end_game(int* scores, string* names, int& num_players);
void next_turn(int* scores, string* names, int num_players, int &count);
int get_reroll_input(int* &options);
int get_another_option(int* &options);
int get_option(int* &options);
void print_dice(int* dice, int num_dice);
void print_running_total(int running_total);
void print_scoreboard(int* scores, string* names, int num_players);
void resize_dice(int* options, int option, int* &dice, int num_dice);
bool reroll_func(int reroll_input, int &num_dice, int* &dice, bool &reroll, 
int &running_total, int* &scores, int &count);
void remove_single_1(int* &dice, int num_dice);
void remove_single_5(int* &dice, int num_dice);
void remove_three(int* &dice, int num_dice, int num);
void remove_four(int* &dice, int num_dice);
void remove_five(int* &dice, int num_dice);
void remove_sixes(int* &dice);
void add_running_total(int* options, int option, int &running_total);
bool check_option(string input, int* options);
void remove_option(int* options, int option);
void remove_dice(int* options, int option, int &num_dice);
void reset_options(int* options);
bool check_reroll(string input);
void add_score(int running_total, int* scores, int count);
bool farkle(int* options);
int* get_options(int* dice, int num_dice);
void print_options(int* options);
void print_specials(int* options, int &count);
void print_fours_and_up(int* options, int &count);
void print_triples(int* options, int &count);
void print_singles(int* options, int &count);
void get_specials(int* options, int* dice, int num_dice, int &count);
void get_fours_and_up(int* options, int* dice, int num_dice, int &count);
void get_triples(int* options, int* dice, int num_dice, int &count);
void get_singles(int* options, int* dice, int num_dice, int &count);
bool check_straight(int* dice, int num_dice);
bool check_three_pairs(int* dice, int num_dice);
bool check_four_with_pair(int* dice, int num_dice);
bool check_two_triples(int* dice, int num_dice);
bool check_sixes(int* dice, int num_dice);
bool check_fives(int* dice, int num_dice);
bool check_fours(int* dice, int num_dice);
int check_triples(int* dice, int num_dice, int num);
bool check_single_1(int* dice, int num_dice);
bool check_single_5(int* dice, int num_dice);
void final_round(int* scores, string* names, int num_players, int &count);
int* roll_dice(int num_dice);
void sort_scores(int* scores, string* names, int num_players);
void sort_dice(int* dice, int num_dice);
string* init_names(int num_players);
bool check_name(string input);
int* init_scores(int num_players);
int get_num_players();
bool check_num(string input);
int get_int(string input);

/******************************************************************************
** Function: Start Game
** Description: Gets the number of playes and the names of every player and
**	starts the game.
** Parameters: None.
** Pre-Conditions: None.
** Post-Conditions: playes are initalized and game is started.
******************************************************************************/
void start_game()
{
	cout << "\n*********************************************************" << endl;
	cout << "                     Welcome to Farkle!" << endl;
	cout << "                       By Ben Johson" << endl;
	cout << "*********************************************************" << endl;
	
	int num_players = get_num_players();
	int* scores = init_scores(num_players);
	string* names = init_names(num_players);

	play_game(scores, names, num_players);
}

/******************************************************************************
** Function: Play Game
** Description: Initializes the main game loop and checks for the end of
**	the game.
** Parameters: int* scores: the array of scores creaetd in start_game.
**	string* names: the array of names created in start_game.
**	int& num_players: the number of players playing the game.
** Pre-Conditions: scores and names must be the same length as num_players
** 	and they both must be initalized.
** Post-Conditions: the game has ended.
******************************************************************************/
void play_game(int* scores, string* names, int& num_players)
{
	bool flag = false;
	int count = 0;
	while(!flag)
	{
		print_scoreboard(scores, names, num_players);
		cout << "*********************************************************" << endl;
		cout << "Player " << count + 1 << " " << names[count] << "'s turn:" << endl;
		cout << "*********************************************************" << endl;
		next_turn(scores, names, num_players, count);
		for(int i = 0; i < num_players; i++)
		{
			if(scores[i] >= 10000)
				flag = true;
		}
		if(count == num_players)
			count = 0;
	}

	final_round(scores, names, num_players, count);
	end_game(scores, names, num_players);
}

/******************************************************************************
** Function: End Game
** Description: prints the winner of the game along with all of the
**	players funal scores. Also frees dynamic memory for names and scores.
** Parameters: int* scores: the array of scores created in start_game.
**	string* names: the array of names created in start_game.
**	int& num_players: the number of players playing the game.
** Pre-Conditions: scores and names must have the same length as num_players
** 	and be initalized.
** Post-Conditions: all of the players final scores are printed.
******************************************************************************/
void end_game(int* scores, string* names, int& num_players)
{
	sort_scores(scores, names, num_players);
	cout << "\nWinner is: " << names[0] << " with " << scores[0] << endl;
	for(int i = 0; i < num_players; i++)
	{
		cout << "Player " << i + 1 << " " << names[i];
		cout << " scored: " << scores[i] << endl;
	}
	cout << "Thanks for playing!" << endl;
	delete[] scores;
	delete[] names;
}

/******************************************************************************
** Function: Next Turn
** Description: goes through an entire turn for one player. At the end the
**	running total for the turn is added to the player's total score.
** Parameters: int* scores: the array of total scores of the players.
** 	string* names: the array of all the names of players.
**	int num_players: the number of players.
** 	int &count: the reference of the count variable to increment.
** Pre-Conditions: scores and names should be the same length as num_players.
** Post-Conditions: one turn has been played, the scores were updated and
**	and the count variable was incremented.
******************************************************************************/
void next_turn(int* scores, string* names, int num_players, int &count)
{
	int num_dice = 6, running_total = 0;
	bool turn_over = false, reroll = true;
	int* dice = NULL;
	int* options = NULL;
	while(!turn_over)
	{
		print_running_total(running_total);
		if(reroll) { dice = roll_dice(num_dice); reroll = false; }
		sort_dice(dice, num_dice);
		options = get_options(dice, num_dice);
		print_dice(dice, num_dice);
		if(farkle(options)) break;
		print_options(options);
		int option = get_option(options);
		add_running_total(options, option, running_total);
		remove_dice(options, option, num_dice);
		resize_dice(options, option, dice, num_dice);
		print_dice(dice, num_dice);
		if(num_dice != 0)
		{
			reset_options(options);
			options = get_options(dice, num_dice);
			bool flag = false;
			for(int i = 0; i < 20; i++)
			{
				if(options[i] != -1)
				{
					flag = true;
				}
			}
			if(flag)
			{
				int input_option = get_another_option(options);
				if(input_option == 1)
				{
					if(num_dice == 0) { num_dice = 6; reroll = true; }
					continue;
				}
			}
		}
		cout << endl;
		reset_options(options);
		if(reroll_func(get_reroll_input(options), num_dice, dice, reroll, running_total, scores, count))
			break;
	}
	count++;
	delete[] dice;
	delete[] options;
}

/******************************************************************************
** Function: Reroll function
** Description: checks if user wants to reroll.
** Parameters: int* reroll_input: the user input.
** Pre-Conditions: None.
** Post-Conditions: None.
******************************************************************************/
bool reroll_func(int reroll_input, int &num_dice, int* &dice, bool &reroll, 
	          int &running_total, int* &scores, int &count)
{
	if(reroll_input == 1)
	{
		if(num_dice == 0) num_dice = 6;
		reroll = true;
		delete [] dice;
		return false;
	}
	if(reroll_input == 2)
	{
		add_score(running_total, scores, count);
		return true;
	}
}

/******************************************************************************
** Function: Get Reroll Input
** Description: takes in user input until the option is valid.
** Parameters: int* options: the possible options.
** Pre-Conditions: None.
** Post-Conditions: return a valid option.
******************************************************************************/
int get_reroll_input(int* &options)
{
	string input = "";
	cout << "Do you want to reroll?" << endl;
	cout << "Enter 1 to reroll." << endl;
	cout << "Enter 2 to end your turn." << endl;
	getline(cin, input);
	while(!check_reroll(input))
	{
		cout << "You entered an invalid option." << endl;
		cout << "Please enter a valid option." << endl;
		getline(cin, input);
	}
	return get_int(input);
}

/******************************************************************************
** Function: Get Another Option.
** Description: takes in user input until the option is valid.
** Parameters: int* options: the possible options.
** Pre-Conditions: None.
** Post-Conditions: return a valid option.
******************************************************************************/
int get_another_option(int* &options)
{
	string input = "";
	cout << "Do you want to remove another option?"<< endl;
	cout << "Enter 1 to remove another option." << endl;
	cout << "Enter 2 to not remove another option." << endl;
	getline(cin, input);
	while(!check_reroll(input))
	{
		cout << "You entered an invalid option." << endl;
		cout << "Please enter a valid option." << endl;
		getline(cin, input);
	}
	return get_int(input);
}

/******************************************************************************
** Function: Get Option.
** Description: takes in user input until the option is valid.
** Parameters: int* options: the possible options.
** Pre-Conditions: None.
** Post-Conditions: Return a valid option.
******************************************************************************/
int get_option(int* &options)
{
	cout << "Which options would you like to remove?" << endl;
	string input = "";
	getline(cin, input);
	while(!check_option(input, options))
	{
		cout << "You entered an invalid option." << endl;
		cout << "Please enter a valid option." << endl;
		getline(cin, input);
	}
	return get_int(input);
}

/******************************************************************************
** Function: Print Dice
** Description: prints out thre dice rolled.
** Parameters: int running_total: the running total.
** Pre-Conditions: None.
** Post-Conditions: None.
******************************************************************************/
void print_dice(int* dice, int num_dice)
{
	cout << "Dice: ";
	for(int i = 0; i < num_dice; i++)
	{
		cout << dice[i] << " ";
	}
	cout << endl;
}

/******************************************************************************
** Function: Print Running Total
** Description: prints out the running total for the turn.
** Parameters: int running_total: the running total.
** Pre-Conditions: None.
** Post-Conditions: None.
******************************************************************************/
void print_running_total(int running_total)
{
	cout << "\nRunning Total for the Turn: " << running_total << endl;
}

/******************************************************************************
** Function: Print Scoreboard
** Description: prints out the total scores of all of players.
** Parameters: int* scores:	 the array of scores.
** 	string* names: the array of player names.
** 	int num_players: the number of players.
**	int num_dice: the number of dice.
** Pre-Conditions: None.
** Post-Conditions: None.
******************************************************************************/
void print_scoreboard(int* scores, string* names, int num_players)
{
	cout << "\n*********************************************************" << endl;
	cout << "                       Scoreboard" << endl;
	cout << "*********************************************************" << endl;
	for(int i = 0; i < num_players; i++)
	{
		cout << "Player " << i + 1 << " " << names[i] << ": " << scores[i] << endl;
	}
	cout << "*********************************************************" << endl;
	cout << endl;
}

/******************************************************************************
** Function: Resize Dice
** Description: removes the appropriate dice for the given option.
** Parameters: int* dice:	 the array of dice to moidfy.
** 	int* options: the array of posisble options.
** 	int option: the user picked option.
**	int num_dice: the number of dice.
** Pre-Conditions: None.
** Post-Conditions: dice is the resized.
******************************************************************************/
void resize_dice(int* options, int option, int* &dice, int num_dice)
{
	if(num_dice == 0)
		remove_sixes(dice);
	if(options[option-1] == 1)
		remove_single_1(dice, num_dice);
	else if(options[option-1] == 2)
		remove_single_5(dice, num_dice);
	else if(options[option-1] == 9)
		remove_four(dice, num_dice);
	else if(options[option-1] == 10)
		remove_five(dice, num_dice);
	for(int i = 0; i < 6; i++)
	{
		if(options[option-1] == i+3)
			remove_three(dice, num_dice, i+1);
	}
}

/******************************************************************************
** Function: Remoce Sixes
** Description: removes the appropriate dice for an option with six dice.
** Parameters: int* dice:	 the array of dice to moidfy.
** Pre-Conditions: None.
** Post-Conditions: dice is the resized.
******************************************************************************/
void remove_sixes(int* &dice)
{
	delete [] dice;
	dice = NULL;
}

/******************************************************************************
** Function: Remove Sixes
** Description: removes the appropriate dice for a single 1 option.
** Parameters: int* dice:	 the array of dice to moidfy.
**	int num_dice: the number of dice.
** Pre-Conditions: None.
** Post-Conditions: dice is the resized.
******************************************************************************/
void remove_single_1(int* &dice, int num_dice)
{
	int* temp = new int[num_dice];
	for(int i = 0; i < num_dice; i++)
	{
		temp[i] = dice[i+1];
	}
	delete [] dice;
	dice = temp;
}

/******************************************************************************
** Function: Remoce Sixes
** Description: removes the appropriate dice for a sginle 5 option.
** Parameters: int* dice:	 the array of dice to moidfy.
**	int num_dice: the number of dice.
** Pre-Conditions: None.
** Post-Conditions: dice is the resized.
******************************************************************************/
void remove_single_5(int* &dice, int num_dice)
{
	int* temp = new int[num_dice];
	int i = 0, j = 0, count = 0;
	while(i < num_dice)
	{
		if(dice[j] == 5) count++;
		if(dice[j] != 5 || dice[j] == 5 && count > 1)
		{
			temp[i] = dice[j];
			i++;
		}
		j++;
	}
	delete[] dice;
	dice = temp;
}

/******************************************************************************
** Function: Remoce Three
** Description: removes the appropriate dice for an option with three dice.
** Parameters: int* dice:	 the array of dice to moidfy.
**	int num_dice: the number of dice.
** Pre-Conditions: None.
** Post-Conditions: dice is the resized.
******************************************************************************/
void remove_three(int* &dice, int num_dice, int num)
{
	int* temp = new int[num_dice];
	int i = 0, j = 0, count = 0;
	while(i < num_dice)
	{
		if(dice[j] == num) count++;
		if(dice[j] != num || (dice[j] == num && count > 3))
		{
			temp[i] = dice[j];
			i++;
		}
		j++;
	}
	delete[] dice;
	dice = temp;
}

/******************************************************************************
** Function: Remoce Four
** Description: removes the appropriate dice for an option with four dice.
** Parameters: int* dice:	 the array of dice to moidfy.
**	int num_dice: the number of dice.
** Pre-Conditions: None.
** Post-Conditions: dice is the resized.
******************************************************************************/
void remove_four(int* &dice, int num_dice)
{
	int* temp = new int[num_dice];
	int num= 0, i = 0, j = 0, count = 0;
	for(int k = 0; k < 3; k++)
	{
		if(dice[k] == dice[k+1] && dice[k] == dice[k+2])
		{
			num = dice[k];
			break;
		}
	}
	while(i < num_dice)
	{
		if(dice[j] == num) count++;
		if(dice[j] != num || (dice[j] == num && count > 4))
		{
			temp[i] = dice[j];
			i++;
		}
		j++;
	}
	delete[] dice;
	dice = temp;
}

/******************************************************************************
** Function: Remoce Five
** Description: removes the appropriate dice for an option with five dice.
** Parameters: int* dice:	 the array of dice to moidfy.
**	int num_dice: the number of dice.
** Pre-Conditions: None.
** Post-Conditions: dice is the resized.
******************************************************************************/
void remove_five(int* &dice, int num_dice)
{
	int* temp = new int[num_dice];
	int num= 0, i = 0, j = 0, count = 0;
	for(int k = 0; k < 2; k++)
	{
		if(dice[k] == dice[k+1] && dice[k] == dice[k+2] && dice[k] == dice[k+3])
		{
			num = dice[k];
			break;
		}
	}
	while(i < num_dice)
	{
		if(dice[j] == num) count++;
		if(dice[j] != num || (dice[j] == num && count > 5))
		{
			temp[i] = dice[j];
			i++;
		}
		j++;
	}
	delete[] dice;
	dice = temp;
}


/******************************************************************************
** Function: Add Running Total
** Description: adds the option points to the running total.
** Parameters: int running_total: the total score for the turn.
** 	int* options: the array of posisble options.
** 	int option: the user picked option.
** Pre-Conditions: None.
** Post-Conditions: running_total is incremented properly.
******************************************************************************/
void add_running_total(int* options, int option, int &running_total)
{
	if(options[option-1] == 1) running_total += 100;
	if(options[option-1] == 2) running_total += 50;
	if(options[option-1] == 3) running_total += 300;
	if(options[option-1] == 15) running_total += 2500;
	for(int i = 0; i < 5; i++)
	{
		if(options[option-1] == i + 4)
			running_total += (i + 2) * 100;
	}
	for(int i = 0; i < 3; i++)
	{
		if(options[option-1] == i + 12)
			running_total += 1500;
		if(options[option-1] == i + 9)
			running_total += (i + 1) * 1000;
	}
	print_running_total(running_total);
}

/******************************************************************************
** Function: Add Score
** Description: adds the running total to the score if valid score.
** Parameters: int running_total: the total score for the turn.
** 	int* scores: the array of tatal scores for the players.
** Pre-Conditions: None.
** Post-Conditions: None.
******************************************************************************/
void add_score(int running_total, int* scores, int count)
{
	if(scores[count] == 0 && running_total >= 500)
	{
		scores[count] += running_total;
	}
	else if(scores[count] > 0)
	{
		scores[count] += running_total;
	}
}

/******************************************************************************
** Function: Check Reroll
** Description: checks if user input is a valid option.
** Parameters: string input: the user input.
** Pre-Conditions: None.
** Post-Conditions: None.
******************************************************************************/
bool check_reroll(string input)
{
	if(input.length() != 1)
		return false;
	if(input[0] == '1' || input[0] == '2')
		return true;
	return false;
}

/******************************************************************************
** Function: Reset Options
** Description: resets all values of options to -1.
** Parameters: int* options: the array of options.
** Pre-Conditions: None.
** Post-Conditions: options is reset.
******************************************************************************/
void reset_options(int* options)
{
	for(int i = 0; i < 20; i++)
	{
		options[i] = -1;
	}
}

/******************************************************************************
** Function: Remove Dice
** Description: remvoes the appropriate amount of dice for the given options.
** Parameters: int option: the user chosen option.
** 	int &num_dice: the number of dice intitally rolled.
**	int* options: the array of possible options.
** Pre-Conditions: None.
** Post-Conditions: num_dice is the proper amount after removing dice.
******************************************************************************/
void remove_dice(int* options, int option, int &num_dice)
{
	if(options[option-1] == 1 || options[option-1] == 2)
		num_dice -= 1;
	if(options[option-1] >= 3 && options[option-1] <= 8)
		num_dice -= 3;
	if(options[option-1] == 9)
		num_dice -= 4;
	if(options[option-1] == 10)
		num_dice -= 5;
	if(options[option-1] >= 11 && options[option-1] <= 15)
		num_dice -= 6;
}

/******************************************************************************
** Function: Check Option
** Description: checks if the input is a valid option.
** Parameters: string input: the user input to check.
** Pre-Conditions: None.
** Post-Conditions: Input is a valid option.
******************************************************************************/
bool check_option(string input, int* options)
{
	for(int i = 0; i < input.length(); i++)
	{
		if(input[i] < '0' || input[i] > '9')
			return false;
	}
	int option = get_int(input), i = 0, count = 0;
	while(options[i] != -1)
	{
				count++;
				i++;
	}
	if(option < 1 || option > count)
		return false;
	return true;
}

/******************************************************************************
** Function: Farkle
** Description: checks if the dice roll was a farkle.
** Parameters: int* options: the array of possible options.
** Pre-Conditions: None.
** Post-Conditions: None.
******************************************************************************/
bool farkle(int* options)
{
	for(int i = 0; i < 20; i++)
	{
		if(options[i] > 0)
			return false;
	}
	cout << "Farkle!" << endl;
	return true;
}

/******************************************************************************
** Function: Get Options
** Description: Creates an array of options possible for the inputed dice.
** Parameters: int num_dice: the number of dice rolled.
**	int* dice: the array of rolled dice.
** Pre-Conditions: the length of dice is the same as num_dice.
** Post-Conditions: options is filled with all possible options of single
**	combinations of dice.
******************************************************************************/
int* get_options(int* dice, int num_dice)
{
	int* options = new int[20];
	for(int i = 0; i < 20; i++)
	{
		options[i] = -1;
	}
	int count = 0;
	get_singles(options, dice, num_dice, count);
	get_triples(options, dice, num_dice, count);
	get_fours_and_up(options, dice, num_dice, count);
	get_specials(options, dice, num_dice, count);
	cout << endl;
	return options;
}

/******************************************************************************
** Function: Print Options
** Description: prints all possible options.
** Parameters: int* options: all of the possible options.
** Pre-Conditions: the length of options is less than 20.
** Post-Conditions: None.
******************************************************************************/
void print_options(int* options)
{
	int count = 1;
	cout << "\nOptions of Dice with Points: " << endl;
	print_singles(options, count);
	print_triples(options, count);
	print_fours_and_up(options, count);
	print_specials(options, count);
	cout << endl;
}

/******************************************************************************
** Function: Print Singles
** Description: prints all possible singles options.
** Parameters: int* options: all of the possible options.
** Pre-Conditions: the length of options is less than 20.
** Post-Conditions: None.
******************************************************************************/
void print_singles(int* options, int &count)
{
	for(int i = 0 ; i < 20; i++)
	{
		if(options[i] == SINGLE_1)
		{
			cout << count << ".) Single 1 for 100 points" << endl;
			count++;
		}
		if(options[i] == SINGLE_5)
		{
			cout <<count << ".) Single 5 for 50 points" << endl;
			count++;
		}
	}
}

/******************************************************************************
** Function: Print Triples
** Description: prints all possible triples options.
** Parameters: int* options: all of the possible options.
** Pre-Conditions: the length of options is less than 20.
** Post-Conditions: None.
******************************************************************************/
void print_triples(int* options, int &count)
{
	for(int i = 0; i < 20; i++)
	{
		if(options[i] == THREE_1)
		{
			cout << count << ".) Three 1's for 300 points" << endl; count++;
		}
		if(options[i] == THREE_2)
		{
			cout << count << ".) Three 2's for 200 points" << endl; count++;
		}
		if(options[i] == THREE_3)
		{
			cout << count << ".) Three 3's for 300 points" << endl; count++;
		}
		if(options[i] == THREE_4)
		{
			cout << count << ".) Three 4's for 400 points" << endl; count++;
		}
		if(options[i] == THREE_5)
		{
			cout << count << ".) Three 5's for 500 points" << endl; count++;
		}
		if(options[i] == THREE_6)
		{
			cout << count << ".) Three 6's for 600 points" << endl; count++;
		}
	}
}

/******************************************************************************
** Function: Print Fours and up
** Description: prints all possible fours, fives, and sixes options.
** Parameters: int* options: all of the possible options.
** Pre-Conditions: the length of options is less than 20.
** Post-Conditions: None.
******************************************************************************/
void print_fours_and_up(int* options, int &count)
{
	for(int i = 0; i < 20; i++)
	{
		if(options[i] == FOUR_OF_KIND)
		{
			cout << count << ".) Four of a kind for 1,000 ponts" << endl;
			count++;
		}
		if(options[i] == FIVE_OF_KIND)
		{
			cout << count << ".) Five of a kind for 2,000 ponts" << endl;
			count++;
		}
		if(options[i] == SIX_OF_KIND)
		{
			cout << count << ".) Six of a kind for 3,000 ponts" << endl;
			count++;
		}
	}
}

/******************************************************************************
** Function: Print Specials
** Description: prints all possible special options.
** Parameters: int* options: all of the possible options.
** Pre-Conditions: the length of options is less than 20.
** Post-Conditions: None.
******************************************************************************/
void print_specials(int* options, int &count)
{
	for(int i = 0; i < 20; i++)
	{
		if(options[i] == STRAIGHT)
		{
			cout << count << ".) Straight for 1,500 ponts" << endl;
			count++;
		}
		if(options[i] == THREE_PAIR)
		{
			cout << count << ".) Three pair for 1,500 ponts" << endl;
			count++;
		}
		if(options[i] == FOUR_OF_KIND_WITH_PAIR)
		{
			cout << count << ".) Four of a kind with a pair for 1,500 ponts" << endl;
			count++;
		}
		if(options[i] == TWO_TRIPLES)
		{
			cout << count << ".) Two triples for 2,500 ponts" << endl;
			count++;
		}
	}
}

/******************************************************************************
** Function: Get Specials
** Description: checks if there is a straight, three pairs, four of a kind
** 	with a pair or two triples.
** Parameters: int num_dice: the number of dice rolled.
**	int* dice: the array of rolled dice.
**	int* options: the array of possible options.
**	int &count: the index of options.
** Pre-Conditions: the length of dice is the same as num_dice.
** Post-Conditions: options is filled with all possible options of special
**	combinations.
******************************************************************************/
void get_specials(int* options, int* dice, int num_dice, int &count)
{
	if(check_straight(dice, num_dice))
	{
		options[count] = STRAIGHT;
		count++;
	}
	if(check_three_pairs(dice, num_dice))
	{
		options[count] = THREE_PAIR;
		count++;
	}
	if(check_four_with_pair(dice, num_dice))
	{
		options[count] = FOUR_OF_KIND_WITH_PAIR;
		count++;
	}
	if(check_two_triples(dice, num_dice))
	{
		options[count] = TWO_TRIPLES;
		count++;
	}
}

/******************************************************************************
** Function: Get Fours and Up
** Description: checks if there are any fours, fives, or sixes of any number.
** Parameters: int num_dice: the number of dice rolled.
**	int* dice: the array of rolled dice.
**	int* options: the array of possible options.
**	int &count: the index of options.
** Pre-Conditions: the length of dice is the same as num_dice.
** Post-Conditions: options is filled with all possible options of fours
**	fives, or sixes.
******************************************************************************/
void get_fours_and_up(int* options, int* dice, int num_dice, int &count)
{
	if(check_fours(dice, num_dice))
	{
		options[count] = FOUR_OF_KIND;
		count++;
	}
	if(check_fives(dice, num_dice))
	{
		options[count] = FIVE_OF_KIND;
		count++;
	}
	if(check_sixes(dice, num_dice))
	{
		options[count] = SIX_OF_KIND;
		count++;
	}
}

/******************************************************************************
** Function: Get Singles
** Description: checks if there are any triples of any number.
** Parameters: int num_dice: the number of dice rolled.
**	int* dice: the array of rolled dice.
**	int* options: the array of possible options.
**	int &count: the index of options.
** Pre-Conditions: the length of dice is the same as num_dice.
** Post-Conditions: options is filled with all possible options of triples.
******************************************************************************/
void get_triples(int* options, int* dice, int num_dice, int &count)
{
	for(int i = 1; i <= 6; i++)
	{
		if(check_triples(dice, num_dice, i) == i)
		{
			options[count] = i + 2;
			count++;
		}
	}
}

/******************************************************************************
** Function: Get Singles
** Description: checks if there are any single 1's or 5's.
** Parameters: int num_dice: the number of dice rolled.
**	int* dice: the array of rolled dice.
**	int* options: the array of possible options.
**	int &count: the intdex of options.
** Pre-Conditions: the length of dice is the same as num_dice.
** Post-Conditions: options is filled with all possible options of single
**	combinations of dice.
******************************************************************************/
void get_singles(int* options, int* dice, int num_dice, int &count)
{
	if(check_single_1(dice, num_dice))
	{
		options[count] = SINGLE_1;
		count++;
	}
	if(check_single_5(dice, num_dice))
	{
		options[count] = SINGLE_5;
		count++;
	}
}

/******************************************************************************
** Function: Check Straight
** Description: checks if there is a straight.
** Parameters: int num_dice: the number of dice rolled.
**	int* dice: the array of rolled dice.
** Pre-Conditions: the length of dice is the same as num_dice.
** Post-Conditions: None.
******************************************************************************/
bool check_straight(int* dice, int num_dice)
{
	if(num_dice < 6)
		return false;
	for(int i = 0; i < 6; i++)
	{
		if(dice[i] != i+1)
			return false;
	}
	return true;
}

/******************************************************************************
** Function: Check Three Pair
** Description: checks if there are three pairs.
** Parameters: int num_dice: the number of dice rolled.
**	int* dice: the array of rolled dice.
** Pre-Conditions: the length of dice is the same as num_dice.
** Post-Conditions: None.
******************************************************************************/
bool check_three_pairs(int* dice, int num_dice)
{
		if(num_dice < 6)
			return false;
		for(int i = 0; i < 6; i += 2)
		{
			if(dice[i] != dice[i+1])
				return false;
		}
		return true;
}

/******************************************************************************
** Function: Check Four With a Pair
** Description: checks if there is four of a kind with a pair.
** Parameters: int num_dice: the number of dice rolled.
**	int* dice: the array of rolled dice.
** Pre-Conditions: the length of dice is the same as num_dice.
** Post-Conditions: None.
******************************************************************************/
bool check_four_with_pair(int* dice, int num_dice)
{
	if(num_dice < 6)
		return false;
	if(dice[0] == dice[1] && dice[0] == dice[2] && dice[0] == dice[3] &&
		 dice[4] == dice[5])
		 return true;
	if(dice[2] == dice[3] && dice[2] == dice[4] && dice[2] == dice[5] &&
		 dice[0] == dice[1])
		 return true;
	return false;
}

/******************************************************************************
** Function: Check Two Triples
** Description: checks if there are two triples.
** Parameters: int num_dice: the number of dice rolled.
**	int* dice: the array of rolled dice.
** Pre-Conditions: the length of dice is the same as num_dice.
** Post-Conditions: None.
******************************************************************************/
bool check_two_triples(int* dice, int num_dice)
{
	if(num_dice < 6)
		return false;
	if(dice[0] == dice[1] && dice[0] == dice[2] &&
		 dice[3] == dice[4] && dice[3] == dice[5])
		 return true;
	return false;
}

/******************************************************************************
** Function: Check Sixes
** Description: checks if there are six of a kind.
** Parameters: int num_dice: the number of dice rolled.
**	int* dice: the array of rolled dice.
** Pre-Conditions: the length of dice is the same as num_dice.
** Post-Conditions: None.
******************************************************************************/
bool check_sixes(int* dice, int num_dice)
{
	if(num_dice < 6)
		return false;
	bool flag = false, flag1 = true;
	for(int i = 1; i <= 6; i++)
	{
		flag1 = true;
		for(int j = 0; j < 6; j++)
		{
			if(dice[j] != i)
				flag1 = false;
		}
		if(flag1)
			flag = true;
	}
	return flag;
}

/******************************************************************************
** Function: Check Fives
** Description: checks if there are any five of a kind.
** Parameters: int num_dice: the number of dice rolled.
**	int* dice: the array of rolled dice.
** Pre-Conditions: the length of dice is the same as num_dice.
** Post-Conditions: None.
******************************************************************************/
bool check_fives(int* dice, int num_dice)
{
	bool flag = false;
	for(int i = 1; i <= 6; i++)
	{
		for(int j = 0; j <= num_dice - 5; j++)
		{
			if(dice[j] == i && dice[j+1] == i &&
				 dice[j+2] == i && dice[j+3] == i &&
			   dice[j+4] == i)
				flag = true;
		}
	}
	return flag;
}

/******************************************************************************
** Function: Check Fours
** Description: checks if there are any four of a kind.
** Parameters: int num_dice: the number of dice rolled.
**	int* dice: the array of rolled dice.
** Pre-Conditions: the length of dice is the same as num_dice.
** Post-Conditions: None.
******************************************************************************/
bool check_fours(int* dice, int num_dice)
{
	bool flag = false;
	for(int i = 1; i <= 6; i++)
	{
		for(int j = 0; j <= num_dice - 4; j++)
		{
			if(dice[j] == i && dice[j+1] == i && dice[j+2] == i && dice[j+3] == i)
				flag = true;
		}
	}
	return flag;
}

/******************************************************************************
** Function: Check Triples
** Description: checks if there are any triples.
** Parameters: int num_dice: the number of dice rolled.
**	int* dice: the array of rolled dice.
** 	int num: the number to search for a triple of.
** Pre-Conditions: the length of dice is the same as num_dice.
** Post-Conditions: returns the number of triple dice.
******************************************************************************/
int check_triples(int* dice, int num_dice, int num)
{
	for(int i = 0; i < num_dice - 2; i++)
	{
		if(dice[i] == num && dice[i+1] == num && dice[i+2] == num)
			return num;
	}
	return 0;
}

/******************************************************************************
** Function: Check Single 1
** Description: checks if there are any single 1's.
** Parameters: int num_dice: the number of dice rolled.
**	int* dice: the array of rolled dice.
** Pre-Conditions: the length of dice is the same as num_dice.
** Post-Conditions: options is filled with all possible options of single 1's.
******************************************************************************/
bool check_single_1(int* dice, int num_dice)
{
	for(int i = 0; i < num_dice; i++)
	{
		if (dice[i] == 1) {
			return true;
		}
	}
	return false;
}

/******************************************************************************
** Function: Check Single 1
** Description: checks if there are any single 1's.
** Parameters: int num_dice: the number of dice rolled.
**	int* dice: the array of rolled dice.
** Pre-Conditions: the length of dice is the same as num_dice.
** Post-Conditions: options is filled with all possible options of single 5's.
******************************************************************************/
bool check_single_5(int* dice, int num_dice)
{
	for(int i = 0; i < num_dice; i++)
	{
		if (dice[i] == 5) {
			return true;
		}
	}
	return false;
}

/******************************************************************************
** Function: Final Round
** Description: goes through the last round of turns for all of the players
**	that don't have 10,000 points.
** Parameters: int* scores: the array of scores created in start_game.
**	string* names: the array of names created in start_game.
**	int num_players: the number of players.
** 	int &count: the reference of the count variable to increment.
** Pre-Conditions: scores and names must have the same length as num_players
** 	and be initalized.
** Post-Conditions: all turns of the game are over and teh final scores are
** 	stored in the scores array.
******************************************************************************/
void final_round(int* scores, string* names, int num_players, int &count)
{
	for(int i = 0; i < num_players - 1; i++)
	{
		print_scoreboard(scores, names, num_players);
		cout << "*********************************************************" << endl;
		cout << "Player " << count + 1 << " " << names[count] << "'s turn:" << endl;
		cout << "*********************************************************" << endl;
		next_turn(scores, names, num_players, count);
	}
}

/******************************************************************************
** Function: Roll Dice
** Description: Creates an array of size num_dice and populates it with
**	random number from 1-6.
** Parameters: int num_dice: the number of dice to roll.
** Pre-Conditions: none.
** Post-Conditions: dice is filled with valid random numbers.
******************************************************************************/
int* roll_dice(int num_dice)
{
	int* dice = new int[num_dice];
	for(int i = 0; i < num_dice; i++)
	{
		dice[i] = rand() % 6 + 1;
	}
	return dice;
}

/******************************************************************************
** Function: Sort Scores
** Description: reorders the scores array to be in order from highest to
**	lowest. Reorders the names array accordingly.
** Parameters: int* scores: the array of scores to sort.
**	string* names: the array of names to sort.
**	int& num_players:  the number of players.
** Pre-Conditions: scores and names must be the same length of num_players
**	and both must be initalized.
** Post-Conditions: scores and names are sorted from highest to lowest.
******************************************************************************/
void sort_scores(int* scores, string* names, int num_players)
{
	int i = 1;
	for(i; i < num_players; i++)
	{
		int temp = scores[i];
		string temp_name = names[i];
		int j = 0;
		for(j; j <= i-1; j++)
		{
			if(scores[i] > scores[j])
				break;
		}
		for(int k = i; k >= j + 1; k--)
		{
			scores[k] = scores[k-1];
			names[k] = names[k-1];
		}
		scores[j] = temp;
		names[j] = temp_name;
	}
}

/******************************************************************************
** Function: Sort Dice
** Description: reorders the dice array to be in order from lowest to
**	highest.
** Parameters: int* dice: the array of dice to sort.
**	int num_players:  the number of dice.
** Pre-Conditions: dice must be initalized and greater than 1.
** Post-Conditions: dice is ordered from lowest to highest.
******************************************************************************/
void sort_dice(int* dice, int num_dice)
{
	int i = 1;
	for(i; i < num_dice; i++)
	{
		int temp = dice[i];
		int j = 0;
		for(j; j <= i-1; j++)
		{
			if(dice[i] < dice[j])
				break;
		}
		for(int k = i; k >= j + 1; k--)
		{
			dice[k] = dice[k-1];
		}
		dice[j] = temp;
	}
}

/******************************************************************************
** Function: Initialize Names
** Description: creates and intializes an array of strings to the inputed
**	names of the players.
** Parameters: int num_players: the number of players playing the game.
** Pre-Conditions: num_players must be a valid number of players.
** Post-Conditions: names is initalized to the inputed names.
******************************************************************************/
string* init_names(int num_players)
{
	string* names = new string[num_players];
	for(int i = 0; i < num_players; i++)
	{
		cout << "\nEnter the name of player " << i + 1 << endl;
		string input = "";
		getline(cin, input);
		while (!check_name(input)) {
			cout << "You entered an invalid name." << endl;
			cout << "Please enter a valid name between 1 and 25 characters.\n";
			getline(cin, input);
		}
		names[i] = input;
	}
	return names;
}

/******************************************************************************
** Function: Check Names
** Description: checks that the user inputed name is a valid name between
**	1 and 25 characters.
** Parameters: string input: the user input to check.
** Pre-Conditions: None.
** Post-Conditions: the user input is a valid name.
******************************************************************************/
bool check_name(string input)
{
	if(input.length() < 1 || input.length() > 25)
	{
		return false;
	}
	return true;
}

/******************************************************************************
** Function: Initialize Scores
** Description: creates and intializes an array of ints all to 0 that holds
**	as many scores as there are players.
** Parameters: int num_players: the number of players playing the game.
** Pre-Conditions: num_players must be a valid number of players.
** Post-Conditions: scores is initalized to all zeros.
******************************************************************************/
int* init_scores(int num_players)
{
	int* scores = new int[num_players];
	for(int i = 0; i < num_players; i++)
	{
		scores[i] = 0;
	}
	return scores;
}

/******************************************************************************
** Function: Get Number of Players
** Description: takes in user input until the number of players is valid.
** Parameters: None.
** Pre-Conditions: None.
** Post-Conditions: Num is a valid number of players.
******************************************************************************/
int get_num_players()
{
	cout << "\nHow many players are going to play?" << endl;
	string input = "";
	getline(cin, input);
	while (!check_num(input)) {
		cout << "You entered an invalid number of players." << endl;
		cout << "Please enter a valid number of players." << endl;
		cout << "There must be at least 2 players." << endl;
		getline(cin, input);
	}
	int num = get_int(input);
	return num;
}

/******************************************************************************
** Function: Check Number
** Description: checks if the inputed sting is a valid number of players.
** Parameters: string input: the user inputed string to check.
** Pre-Conditions: None.
** Post-Conditions: None.
******************************************************************************/
bool check_num(string input)
{
	if(input.length() == 0)
			return false;
	if(input.length() == 1 && (input[0] < '2' || input[0] > '9'))
			return false;
	int count = 0;
	for(int i = 0; i < input.length(); i++)
	{
		if(input[i] < '0' || input[i] > '9')
			return false;
		if(input[i] == '0') count++;
	}
	if(count == input.length() ||
		 (count == input.length()-1 && (input[input.length()-1] == '1')))
		return false;
	return true;
}

/******************************************************************************
** Function: Get Integer
** Description: converts the user inputed string to an integer value.
** Parameters: string input: the user inputed string to convert.
** Pre-Conditions: input must be a valid integer.
** Post-Conditions: None.
******************************************************************************/
int get_int(string input)
{
	int result = 0;
	for(int i = 0; i < input.length(); i++)
	{
		result += (input[i] - 48) * pow(10,input.length() - i -1);
	}
	return result;
}

/******************************************************************************
** Function: Main
** Description: The main function of the program, intializes the game.
** Parameters: None.
** Pre-Conditions: None.
** Post-Conditions: None.
******************************************************************************/
int main()
{
	srand(time(NULL));
	start_game();

	return 0;
}
