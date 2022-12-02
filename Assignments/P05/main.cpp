/*****************************************************************************
 *
 *  Author:           ahmed krubally
 *  Title:            BolNiverse Fight Club
 *  Course:           2143
 *  Semester:         Fall 2022
 *
 *  Description:
 *    creates a game where two armies are simulated in a war where the attackers have the advantage. 
 *    The armies are of composed of wizards, warriors,
 *    archers, elves, and dragonBorn, each with differnt attack points and health totals.
 *    A random array of multiples of 100 will be selected for the attacking side 
 *    and the defending side will be set to 1/20th the size of the attacking side.
 *   The winner and the aftermath states are displayed after the war is completed.
 *        
 *
 *  Usage:
 *   allows the user to create a war simulation for two sides
 *
 *
 * Files: main.cpp
 *        dice.hpp
 *         fighter.hpp
 *         helpers.hpp
 *         weapon.hpp
 *****************************************************************************/


#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <fstream>
#include "dice.hpp"
#include "weapon.hpp"
#include "helpers.hpp"
#include "fighter.hpp"



//array pick a random size from for the attacking side
const int armySize[] = {100, 500, 1000, 1500, 2000, 2500, 3000};


/*
Name : makechoice
Purpose    : create list of possible dievalues for a given character
Parameters : string denoting character typevector to hold the die choices
Returns    : Void          
*/
void makechoice(string w, vector<string> & VectorChoices);



/*
Name       : Addarmy1
Purpose    : fill attacking army with eachcharacter type, each with an appropriate distribution
Parameters : the vector of basefightersint size of the armyvector of choices for unit 
typestring to denote what character is added
Returns    : Void         
*/
void Addarmy1(vector<BaseFighter*> & Army, int armySize, vector<string> & VectorChoices, string character);



/*
Name : Addarmy2
Purpose fill defending army with each character type, each with an appropriate distribution
Parameters : the vector of basefighters int size of the army
vector of choices for unit typestring to denote what character is added
Returns : Void     
*/
void Addarmy2(vector<BaseFighter*> & Army, int armySize, vector<string> & VectorChoices, string character);


/*
Name: CheckBattle
Purpose: to increment the number of Battles
and add point to who won the round
Parameters : the addresses of the variables that
store the Battles and wins
Returns: Void        
*/
void CheckBattle(int & BattlesFought, int & teamWhoWon);



/*
Name       : deadsoul
Purpose    : once a unit is below health,remove unit from battle and 
change unit to a new one ifthe army is not empty
Parameters : vector of army unitsbasefighter pointer for current fighter
Returns    : Void     
*/
void deadsoul(vector<BaseFighter*> & Army, BaseFighter * & Unit);



/*
Name       : showaftermath
Purpose    : to print the final results of battle
Parameters : the values for team wins, total Battles, and the winner
Returns    : Void     
*/
void showaftermath(int, int, int, string, ofstream &);





int main() 
  {
    srand(time(0));

    //open outfile
    ofstream outfile;
    outfile.open("output.txt");
    
    
    //initialize the values for end results
    int Battles = 0;
    int army1wins = 0;
    int army2wins = 0;  
    string winner = "";

    //create the army 1 by choosing a random amount from the 
    //array of army sizes
    // the army size of defenders should be the attackers amount divided by 20 
    int armysize1 = armySize[rand() % 10];
    int armysize2 = armysize1 / 20;
    outfile << "Size of attcking army is: " << armysize1 << endl;// prints out the attacking size 
    outfile << "Size of defending army is: " << armysize2 << endl << endl;// prints out the defending size

   
    //create a vector for possible die rolls for each class
    vector<string>warriorChoices;
    vector<string>wizardChoices;
    vector<string>archerChoices;
    vector<string>elfChoices;
    vector<string>dragonBornChoices;

   //initialize a vector of basefighter pointer for each side
   vector<BaseFighter*> Defenders;
   vector<BaseFighter*> Attackers;

    //fill the attacking army ranks and shuffle them
    Addarmy1(Attackers, armysize1, dragonBornChoices, "dragonBorn");
    Addarmy1(Attackers, armysize1, warriorChoices, "warrior");
    Addarmy1(Attackers, armysize1, wizardChoices, "wizard");
    Addarmy1(Attackers, armysize1, elfChoices, "elf");
    Addarmy1(Attackers, armysize1, archerChoices, "archer");
    random_shuffle(Attackers.begin(), Attackers.end());
    //fill the defending army ranks and shuffle them
    Addarmy2(Defenders, armysize2, dragonBornChoices, "dragonBorn");
    Addarmy2(Defenders, armysize2, warriorChoices, "warrior");
    Addarmy2(Defenders, armysize2, wizardChoices, "wizard");
    Addarmy2(Defenders, armysize2, elfChoices, "elf");
    Addarmy2(Defenders, armysize2, archerChoices, "archer");
    random_shuffle(Defenders.begin(), Defenders.end());
    
 //initialize the choice list for each class
   makechoice("warrior", warriorChoices);
   makechoice("wizard", wizardChoices);
   makechoice("archer", archerChoices);
   makechoice("elf", elfChoices);
   makechoice("dragonBorn", dragonBornChoices);

     //pointer to dictate which unit is in the fight in an instance
     BaseFighter * defender = Defenders.back();
     BaseFighter * attacker = Attackers.back();



    //while loop that runs so long as there is a unit to fight for each army
    while (attacker->Health() > 0 && defender->Health() > 0)
      { //The defender always attacks first 
        attacker->takeDamage(defender->attack());

    //if the defenders attack fails to kill the attacker then the attaker will strike
    if (attacker->Health() > 0)
    {//strike the defender
    defender->takeDamage(attacker->attack());
    }

      // if the attacker is killed then add a new unit to take its place
      if (attacker->Health() <= 0)
      {
         deadsoul(Attackers, attacker);// add the dead unit to the grave yard(deadsoul)/ add a new unit
        CheckBattle(Battles, army1wins);// checks the results after the turn has ended and counts who has die
        // and who is still alive
        defender->regenHealth();// regenerates the health lost in the previous battle
      }
   //if the defend died to the attacker add a new defend to take its place if possibel
      else if (defender->Health() <= 0)
      {
        deadsoul(Defenders, defender);//add the dead unit to the grave yard( deadsoul)/ add a new unit
        CheckBattle(Battles, army2wins);// check the results after the turn has ended and count who has die and 
        //who is still alive
        attacker->regenHealth();// regenerate the healther lost in the previous battle
      }
        //if neither died they just regen
        else
      {
        defender->regenHealth();//regen defender
        deadsoul(Defenders, defender);//add an additional defender to turn the tide, prevent stale mates
        attacker->regenHealth();//regen attacker
      }
        
      }

    //when the war is over determine the winner 
    // if the defenders are empty the attakers win
    // if the attacker are empty the defender win
    if (Defenders.empty())
    {
      winner = "Attackers";
    }
    else
    {
      winner = "Defenders";
    }

    //print out the amount of wins for both sides and the over all winner to an output file
    showaftermath(army1wins, army2wins, Battles, winner, outfile);

    return 0;
    
  }


void Addarmy2(vector<BaseFighter*> & Army, int armySize, vector<string> & Choices, string characterType)
{
  //make each unit a fifth of the army total
  int warriorSize = armySize / 5;
  int wizardSize = armySize / 5;
  int archerSize = armySize / 5;
  int elfSize = armySize / 5;
  int dragonBornSize = armySize / 5;

  //make a proportionate amount of characters
  if (characterType == "warrior")
  {
  for (int i = 0; i < warriorSize; i++)
    {
    Army.push_back(new Warrior(Choices));
    }
   }
   else if (characterType == "wizard")
  {
  for (int i = 0; i < wizardSize; i++)
    {
    Army.push_back(new Wizard(Choices));
    }
    }
  else  if (characterType == "archer")
  {
  for (int i = 0; i < archerSize; i++)
    {
      Army.push_back(new Archer(Choices));
    }
    }
   else if (characterType == "elf")
   {
  for (int i = 0; i < elfSize; i++)
    {
      Army.push_back(new Elf(Choices));
    }
    }
  else if (characterType == "dragonBorn")
  {
  for (int i = 0; i < dragonBornSize; i++)
    {
      Army.push_back(new DragonBorn(Choices));
    }
    }
  
}


void Addarmy1(vector<BaseFighter*> & Army, int armySize, vector<string> & Choices, string characterType)
{
  //make warriors, wizards and archers equal to
  //75% of army, and the elf and dragonborn equal
  //to the remaining amount
  int warriorSize = armySize / 4;
  int wizardSize = armySize / 4;
  int archerSize = armySize / 4;
  int elfSize = armySize / 8;
  int dragonBornSize = armySize / 8;

  //make a proportionate amount of fighters
  if (characterType == "warrior")
  {
  for (int i = 0; i < warriorSize; i++)
    {
    Army.push_back(new Warrior(Choices));
    }
   }
  else if (characterType == "wizard")
  {
  for (int i = 0; i < wizardSize; i++)
    {
    Army.push_back(new Wizard(Choices));
    }
    }
 else  if (characterType == "archer")
  {
  for (int i = 0; i < archerSize; i++)
    {
      Army.push_back(new Archer(Choices));
    }
    }
  //procs if leading number is odd, letting an elf fill
  //in the empty slot
  else if (characterType == "elf" && !(armySize % 8 == 0))
   {
  for (int i = 0; i < elfSize + 1; i++)
    {
      Army.push_back(new Elf(Choices));
    }
    }
   else if (characterType == "elf" && (armySize % 8 == 0))
    {
  for (int i = 0; i < elfSize; i++)
    {
      Army.push_back(new Elf(Choices));
    }
      }
 else if (characterType == "dragonBorn")
  {
  for (int i = 0; i < dragonBornSize; i++)
    {
      Army.push_back(new DragonBorn(Choices));
    }
    }
}

void CheckBattle(int & BattlesFought, int & teamWhoWon)
{
  BattlesFought++;
  teamWhoWon++;
}

void deadsoul(vector<BaseFighter*> & Army, BaseFighter * & Unit)
{
  Army.pop_back();
  if (Army.size() > 0)
  {
    Unit = Army.back();
  }
}

void showaftermath(int army1wins, int army2wins, int BattlesFought, string winner, ofstream & outfile)
{
     outfile << "Final Stats" << endl;
    outfile << "-------------------------" << endl;
    outfile << "Team One Round Wins: " << army1wins << endl;
    outfile << "Team Two Round Wins: " << army2wins << endl;
    outfile  << "Battles fought: " << BattlesFought << endl;
    outfile << "The Winner is " << winner << endl;
    outfile << "percent of battle won by Defenders: " <<
    ((double)army1wins / BattlesFought) * 100 << "%" << endl;
    outfile << "percent of battle won by Attackers: " <<
    ((double)army2wins / BattlesFought) * 100 << "%";
}


void makechoice(string character, vector<string> & Choices)
{
  //create choice list for character type put in
  if (character == "warrior")
  {
  Choices.push_back("1.d.12");
  Choices.push_back("2.d.6");
  Choices.push_back("3.d.4");
    }
  else if (character == "wizard")
  {
  Choices.push_back("1.d.20");
  Choices.push_back("2.d.10");
  Choices.push_back("3.d.6");
  Choices.push_back("5.d.4");

  }
  else if (character == "archer")
  {
  Choices.push_back("1.d.8");
  Choices.push_back("2.d.4");
  Choices.push_back("1.d.10");
  }
  else if (character == "elf")
  {
  Choices.push_back("1.d.4");
  Choices.push_back("1.d.6");
  }
  else if (character == "dragonBorn")
  {
  Choices.push_back("1.d.6");
  Choices.push_back("1.d.8");
  }
}

