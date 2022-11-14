//Program 4 rock paper scissors lizard spock- this program creates a game of rock paper scissors that is only played by the cpu. 
//There will be 2 players and they will play agasint each other and there will be a function to determines who wins 
#include <algorithm>
#include <ctime>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <vector>

using namespace std;

#define ROCK u8"\U0000270A"
#define PAPER u8"\U0000270B"
#define SCISSORS u8"\U0001F44C"
#define LIZARD u8"\U0001F918"
#define SPOCK u8"\U0001F596"

#define ROCK2 u8"\U0001F5FB"
#define PAPER2 u8"\U0001F4C3"
#define SCISSORS2 u8"\U0001F52A"
#define LIZARD2 u8"\U0001F438"
#define SPOCK2 u8"\U0001F596"

/**
 * the rules for the game:
 *      Scissors cuts Paper
 *      Paper covers Rock
 *      Rock crushes Lizard
 *      Lizard poisons Spock
 *      Spock smashes Scissors
 *      Scissors decapitates Lizard
 *      Lizard eats Paper
 *      Paper disproves Spock
 *      Spock vaporizes Rock
 *      Rock crushes Scissors
 */


// Use a string name to lookup emoji
map< string, string > Emojis = {
    {"rock", ROCK2},
    {"paper", PAPER2},
    {"scissors", SCISSORS2},
    {"lizard", LIZARD2},
    {"spock", SPOCK2}};

// Use an emoji to lookup the string name
map< string, string > Names = {
    {ROCK2, "rock"},
    {PAPER2, "paper"},
    {SCISSORS2, "scissors"},
    {LIZARD2, "lizard"},
    {SPOCK2, "spock"}};

// use a string emoji name to lookup who it beats
map< string, vector< string > > rules = {
    {"rock", {"lizard", "scissors"}},
    {"paper", {"rock", "spock"}},
    {"scissors", {"paper", "lizard"}},
    {"lizard", {"spock", "paper"}},
    {"spock", {"rock", "scissors"}}};


/*
 * purpose: Returns a random emoji from the map of emojis
 * Parameters: Pair<string, string>
 * return: a random emoji
 */
pair< string, string > RandomEmoji() {
    auto it = Emojis.begin();                  // iterator to front of map
    std::advance(it, rand() % Emojis.size());  // move a random amount with in the emoji map
    string random_emoji = it->second;         // grab emoji from map
    return make_pair(it->first, it->second);  // return rand emoji
}


/*
 * purpose: Determines which emoji will win based off the rules map 
 * parameters: string hand1  : string emoji name,string hand2  : other emoji name
 * 
 * return: true / false : true if the hand 1 wins over hand 2 and false if hand 2 wins over hand 1
 */
bool beats(string hand1, string hand2) {
    if (find(rules[hand1].begin(), rules[hand1].end(), hand2) != rules[hand1].end()) {
        cout<<"Player 1 wins"<<endl;//shows that player 1 wins
      return 1;
    }
    cout<< "Player 2 wins"<<endl;//shows that player 2 wins 
    return 0;
}


 //  overloaded beats function to pass in the maps for both hands to ensure that both hands holds a random emoji
 
bool beats(pair< string, string > hand1, pair< string, string > hand2) {
    return beats(hand1.first,hand2.first);
}

int main() {
    srand(time(0));
int rounds;
  cout<<"How many rounds would you like to sim?"<<endl;//ask the user how many rounds they wanna see 
  cin>> rounds;// in puts the number of rounds
  cout<< endl;
  for(int i = 0;i<rounds; i++ ){
    cout<<"Round:"<<rounds;
    pair< string, string > r1 = RandomEmoji();
    pair< string, string > r2 = RandomEmoji();

    cout <<endl<< r1.second << " vs " << r2.second << endl;
    cout << beats(r1, r2) << endl<<endl;
  }
  return 0;
  }
