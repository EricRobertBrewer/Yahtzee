/*
main.cpp
Eric Brewer
1-19-10
Yahtzee - 
*/

#include <iostream>
#include <string>
using namespace std;
#include <iomanip>

#include "Die.hpp"

#define NUM_CHOICES 13
#define NUM_DICE 5

// Graphical display of values of dice
void displayDice();

// Asks the user which dice to hold
void holdPrompt();

// Roll whichever dice aren't being held
int shoot();

// Sort the array of dice values. Used to determine validity of lower scores
void bsort();

// Used with bsort()
void bswap( Die &a, Die &b );

// Displays the table of scores; namely, _values[]
void displayTable();

// Ask the player under which mark they want this combination of dice to be written
void choicePrompt();

// Returns the total of the upper scores - Ones through Sixes
int upperTotal();

// Returns 0 or 35 depending on if upperTotal() >= 63
int upperBonus();

// Returns the total of the lower scores - Three of a Kind through Chance
int lowerTotal();

// Returns the sum of upperTotal(), upperBonus(), and lowerTotal()
int grandTotal();


// The five dice in a game of Yahtzee
Die _dice[NUM_DICE];

// The dice that the player has chosen to hold
bool _holding[NUM_DICE];

// The thirteen marking choices in a game - Ones through Chance
bool _choices[NUM_CHOICES];

// The score for all a player's choices - initially 0
int _values[NUM_CHOICES];

// The names of every marking choice
string _names[NUM_CHOICES] = { "Ones",
			      "Twos",
			      "Threes",
			      "Fours",
			      "Fives",
			      "Sixes",
			      "Three of a Kind",
			      "Four of a Kind",
			      "Full House",
			      "Small Straight",
			      "Large Straight",
			      "YAHTZEE",
			      "Chance" };


int main(){
  for( int i = 0; i < NUM_CHOICES; i++ ){
    _choices[i] = false;
    _values[i] = 0;
  }

  cout << "\nYahtzee: ";
  
  for( int round = 1; round <= NUM_CHOICES; round++ ){
    
    cout << "\nROUND " << round << ":";

    for( int i = 0; i < NUM_DICE; i++ )
      _holding[i] = false;
    
    shoot();
    displayDice();
    holdPrompt();
    if( shoot() ){
      displayDice();
      holdPrompt();
    }
    if( shoot() )
      displayDice();
    displayTable();
    choicePrompt();
    displayTable();
  }
  
  cout << endl;

  return 0;
}


void displayDice(){
  cout << "\n " 
       << setw(5) << left << "1st"
       << setw(5) << left << "2nd"
       << setw(5) << left << "3rd"
       << setw(5) << left << "4th"
       << setw(5) << left << "5th";
  cout << "\n "
       << setw(5) << left << "---"
       << setw(5) << left << "---"
       << setw(5) << left << "---"
       << setw(5) << left << "---"
       << setw(5) << left << "---";
  cout << "\n  "
       << setw(5) << left << _dice[0].value()
       << setw(5) << left << _dice[1].value()
       << setw(5) << left << _dice[2].value()
       << setw(5) << left << _dice[3].value()
       << setw(5) << left << _dice[4].value()
       << "\n";
}

void holdPrompt(){
  char c;
  for( int i = 0; i < NUM_DICE; i++ ){
    cout << "Do you want to hold die " << i+1 << "? ( y or n ) ";
    cin >> c;
    if( !cin.fail() ){
      if( c == 'y' )
	_holding[i] = true;
      else if( c == 'n' )
	_holding[i] = false;
      else
	i--;
    }
    else
      i--;
  }
}

int shoot(){
  int a = 0;
  for( int i = 0; i < NUM_DICE; i++ )
    if( !_holding[i] ){
      _dice[i].roll();
      a++;
    }
  return a;
}

void bsort(){
  for( int i = 0; i < NUM_DICE - 1; i++ )
    for( int j = 1; j < NUM_DICE - i; j++ )
      if( _dice[j].value() < _dice[j-1].value() )
	bswap( _dice[j], _dice[j-1] );
}

void bswap( Die &a, Die &b ){
  Die t = a;
  a = b;
  b = t;
}

void displayTable(){
  cout << "\n+---------------------+-+------+";
  cout << "\n| 1| " << setw(16) << left << _names[0] << " |" << ( _choices[0] ? 'X' : ' ' ) << "| " << setw(4) << right << _values[0] << " |";
  cout << "\n| 2| " << setw(16) << left << _names[1] << " |" << ( _choices[1] ? 'X' : ' ' ) << "| " << setw(4) << right << _values[1] << " |";
  cout << "\n| 3| " << setw(16) << left << _names[2] << " |" << ( _choices[2] ? 'X' : ' ' ) << "| " << setw(4) << right << _values[2] << " |";
  cout << "\n| 4| " << setw(16) << left << _names[3] << " |" << ( _choices[3] ? 'X' : ' ' ) << "| " << setw(4) << right << _values[3] << " |";
  cout << "\n| 5| " << setw(16) << left << _names[4] << " |" << ( _choices[4] ? 'X' : ' ' ) << "| " << setw(4) << right << _values[4] << " |";
  cout << "\n| 6| " << setw(16) << left << _names[5] << " |" << ( _choices[5] ? 'X' : ' ' ) << "| " << setw(4) << right << _values[5] << " |";
  cout << "\n|--| " << setw(16) << left << "   Upper Level:  |-| " << setw(4) << right << upperTotal() << " |";
  cout << "\n|--| " << setw(16) << left << "         BONUS:  |-| " << setw(4) << right << upperBonus() << " |";
  cout << "\n| 7| " << setw(16) << left << _names[6] << " |" << ( _choices[6] ? 'X' : ' ' ) << "| " << setw(4) << right << _values[6] << " |";
  cout << "\n| 8| " << setw(16) << left << _names[7] << " |" << ( _choices[7] ? 'X' : ' ' ) << "| " << setw(4) << right << _values[7] << " |";
  cout << "\n| 9| " << setw(16) << left << _names[8] << " |" << ( _choices[8] ? 'X' : ' ' ) << "| " << setw(4) << right << _values[8] << " |";
  cout << "\n|10| " << setw(16) << left << _names[9] << " |" << ( _choices[9] ? 'X' : ' ' ) << "| " << setw(4) << right << _values[9] << " |";
  cout << "\n|11| " << setw(16) << left << _names[10] << " |" << ( _choices[10] ? 'X' : ' ' ) << "| " << setw(4) << right << _values[10] << " |";
  cout << "\n|12| " << setw(16) << left << _names[11] << " |" << ( _choices[11] ? 'X' : ' ' ) << "| " << setw(4) << right << _values[11] << " |";
  cout << "\n|13| " << setw(16) << left << _names[12] << " |" << ( _choices[12] ? 'X' : ' ' ) << "| " << setw(4) << right << _values[12] << " |";
  cout << "\n|--| " << setw(16) << left << "   Lower Level:  |-| " << setw(4) << right << lowerTotal() << " |";
  cout << "\n|--| " << setw(16) << left << "   Grand Total:  |-| " << setw(4) << right << grandTotal() << " |";
  cout << "\n+---------------------+-+------+\n";
}

void choicePrompt(){
  int selection;
  cout << "\nWhere will you mark your score? ( 1 through 13 )";
  cin >> selection;

  if( !cin.fail() ){
    if( selection >= 1 && selection <= NUM_CHOICES ){
      if( !_choices[selection-1] ){

	int score = 0;
	bool found = false;

	switch( selection ){

	  // Ones
	case 1: 
	  for( int i = 0; i < NUM_DICE; i++ )
	    if( _dice[i] == 1 )
	      score += 1;
	  break;

	  // Twos
	case 2: 
	  for( int i = 0; i < NUM_DICE; i++ )
	    if( _dice[i] == 2 )
	      score += 2;
	  break;

	  // Threes
	case 3: 
	  for( int i = 0; i < NUM_DICE; i++ )
	    if( _dice[i] == 3 )
	      score += 3;
	  break;

	  // Fours
	case 4: 
	  for( int i = 0; i < NUM_DICE; i++ )
	    if( _dice[i] == 4 )
	      score += 4;
	  break;

	  // Fives
	case 5: 
	  for( int i = 0; i < NUM_DICE; i++ )
	    if( _dice[i] == 5 )
	      score += 5;
	  break;

	  // Sixes
	case 6: 
	  for( int i = 0; i < NUM_DICE; i++ )
	    if( _dice[i] == 6 )
	      score += 6;
	  break;

	  // Three of a Kind
	case 7:
	  bsort();
	  if( _dice[0] == _dice[1] && _dice[1] == _dice[2] || 
	      _dice[1] == _dice[2] && _dice[2] == _dice[3] ||
	      _dice[2] == _dice[3] && _dice[3] == _dice[4] )
	    score = _dice[0].value() + _dice[1].value() + _dice[2].value() + _dice[3].value() + _dice[4].value();
	  break;

	  // Four of a Kind
	case 8:
	  bsort();
	  if( _dice[0] == _dice[1] && _dice[1] == _dice[2] && _dice[2] == _dice[3] ||
	      _dice[1] == _dice[2] && _dice[2] == _dice[3] && _dice[3] == _dice[4] )
	    score = _dice[0].value() + _dice[1].value() + _dice[2].value() + _dice[3].value() + _dice[4].value();
	  break;

	  // Full House
	case 9:
	  bsort();
	  if( _dice[0] == _dice[1] && _dice[2] == _dice[3] && _dice[3] == _dice[4] ||
	      _dice[0] == _dice[1] && _dice[1] == _dice[2] && _dice[3] == _dice[4] )
	    score = 25;
	  break;

	  // Small Straight
	case 10:
	  bsort();
	  for( int i = 1; i < NUM_DICE && !found; i++ )
	    if( _dice[i] == _dice[i-1] ){
	      for( i; i < NUM_DICE - 1; i++ )
		_dice[i] = _dice[i+1];
	      found = true;
	    }
	  if( _dice[0] == 1 && _dice[1] == 2 && _dice[2] == 3 && _dice[3] == 4 || 
	      _dice[0] == 2 && _dice[1] == 3 && _dice[2] == 4 && _dice[3] == 5 || 
	      _dice[0] == 3 && _dice[1] == 4 && _dice[2] == 5 && _dice[3] == 6 ||
	      _dice[1] == 3 && _dice[2] == 4 && _dice[3] == 5 && _dice[4] == 6 )
	    score = 30;
	  break;

	  // Large Straight
	case 11:
	  bsort();
	  if( _dice[0] == 1 && _dice[1] == 2 && _dice[2] == 3 && _dice[3] == 4 && _dice[4] == 5 || 
	      _dice[0] == 2 && _dice[1] == 3 && _dice[2] == 4 && _dice[3] == 5 && _dice[4] == 6 )
	    score = 40;
	  break;

	  // Yahtzee
	case 12:
	  if( _dice[0] == _dice[1] && 
	      _dice[1] == _dice[2] && 
	      _dice[2] == _dice[3] && 
	      _dice[3] == _dice[4] )
	    score = 50;
	  break;

	  // Choice
	case 13:
	  score = _dice[0].value() + _dice[1].value() + _dice[2].value() + _dice[3].value() + _dice[4].value();
	  break;
	}

	_values[selection-1] = score;
	_choices[selection-1] = true;

      }
      else
	choicePrompt();
    }
    else
      choicePrompt();
  }
  else
    choicePrompt();
}

int upperTotal(){
  int t = 0;
  for( int i = 0; i < 6; i++ )
    t += _values[i];
  return t;
}

int upperBonus(){
  if( upperTotal() >= 63 )
    return 35;
  return 0;
}

int lowerTotal(){
  int t = 0;
  for( int i = 6; i < NUM_CHOICES; i++ )
    t += _values[i];
  return t;
}

int grandTotal(){
  return upperTotal() + upperBonus() + lowerTotal();
}
