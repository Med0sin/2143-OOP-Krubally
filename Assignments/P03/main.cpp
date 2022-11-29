/*****************************************************************************
 *
 *  programer:        Ahmed krubally
 *  Title:            Blackjack program
 *  Course:           2143- oop
 *  Semester:         Fall 2022
 *
 *  Description:
       Implements a game of Blackjack where the player
      can play multiple rounds as long as they have money to continue playing. 
 *        
 *
 *  Usage:
 *     To let the user/player play a game of blackjack against a dealer. 
 *
 * Files: main.cpp
 * Files: blackjack.hpp
 * Files: colors.h
 *****************************************************************************/



#include "blackjack.hpp"
#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


using namespace std;

/**
   * Purpose - count the number of cards in a given hand 
   *
   * param cards - vector of Card pointers, numCards 
   *  
   * returns: int -  number of cards in hand 
   */
  int countHand(vector<Card *> cards, int numCards)
  {
  int i = 0;
  int Total = 0;
  while (i < numCards) 
     {
       //the value of a face card is 10, so we need to add ten
      if (cards[i]->getRank() >= 10) {
        Total += 10;
      }
       else {
        Total += cards[i]->getRank() +1;// if not a face dont add ten
      }
        i++;
      }
  return Total;
}

/**
   * Purpose - print out a single card
   * parameters: vector of cards
   * returns: void
   */
  void printCard(vector<Card *> cards) 
  {
	showcard c;
	int count = 0;
  
  //prints our on single card
	while (count < 1) {
		for (int i = count; i < count + 1; i++) {
			c = cards[i]->cardmaker();
			cout << c["TOP"] << OFF;
		}
		cout << endl;
		for (int i = count; i < count + 1; i++) {
			c = cards[i]->cardmaker();
			cout << c["MID"] << OFF;
		}
		cout << endl;
		for (int i = count; i < count + 1; i++) {
			c = cards[i]->cardmaker();
			cout << c["BOT"] << OFF;
		}
		cout << endl;
		count++;	
	}
  cout << endl;
  }

/**
   * Purpose - print all cards from hand 
   *
   * param cards - vector of Card pointers,number of columns made when printed
   * 
   * returns: none
   */
  void printset(vector<Card *> cards, int cols = 2) 
  {
	showcard c;
	int count = 0;
	while (count < cards.size()) {
		for (int i = count; i < count + cols; i++) {
			c = cards[i]->cardmaker();
			cout << c["TOP"] << OFF;
		}
		cout << endl;
		for (int i = count; i < count + cols; i++) {
			c = cards[i]->cardmaker();
			cout << c["MID"] << OFF;
		}
		cout << endl;
		for (int i = count; i < count + cols; i++) {
			c = cards[i]->cardmaker();
			cout << c["BOT"] << OFF;
		}
		cout << endl;
		count += cols;
		if (count + cols >= 52) {
			cols = 52 % cols;
		}
	}

  cout << endl;
  }

int main() {

  //opening massage for the game 
cout  << "Welcome to Blackjack!" << endl<< "Aces count as 1 and the max cards to hold is 5" << endl;
cout<< "You begin the game with 100 dollars" << endl ;
cout <<"******************************************" << endl << endl;

  //variables used to determine if the player can continue playing 
  //how much they bet, and how much they can bet
  string PLAY = "y";
  int Betting = 0;
  int Cash = 100;

  //ONlY run if the player says Yes and has the funds to continue
  while (PLAY == "y" && !(Cash < 1))
    {
      cout << "Enter a betting amount: ";
      cin >> Betting;

      //make sure that a correct amount is entered, if not they will be asked to enter a valid amount
      while (Betting < 1 || Betting > Cash)
        {
          cout << endl << "Enter a valid amount: ";
          cin >> Betting;//enter a bet amount 
        }

    //sets columns to 2 for the format
  int Playcolms = 2;
  int Dealercolms = 2;

srand(time(0));//What is this for, i just copied this from the code from class

   //create instances of players and dealer "Hands"
	
	vector<Card *> PlayerHand;
    vector<Card *> DealerHand;
	for (int i = 0; i < 2; i++) {
		PlayerHand.push_back(new Card(rand()%52));
    DealerHand.push_back(new Card(rand()%52));
	}
      


    //show the cards for the player and the dealer for the beginnig of the game 
    cout << endl << endl << "Your initial cards:";
    cout << endl << endl;
    printset(PlayerHand, 2);
    cout << "The dealer's visible card:";
    cout << endl << endl;
    printCard(DealerHand);



  // determine if the player wants to Hit 
  string continue2= "Hit Me";
  int HandValue = 0;

  // keep going as the player wants "Hit me"/ continue and the hand value is not over 20
  
  while (continue2== "Hit Me" && !(HandValue > 20))
  {
    cout << endl;
    cout << "Enter \'Hit me\' to hit or type anything to stand: ";
    cin >> PLAY;
    cout << endl;
    // if the player wants to hit, draw them a new card and print it out
      if (continue2== "Hit Me")
      {
       cout << "Your new hand" << endl << endl;
       Playcolms++;
       PlayerHand.push_back(new Card(rand()%52));

        // if the card count has reached 10, divide columns by 2
        if (Playcolms > 9 && Playcolms % 2 == 0)
         {
         	printset(PlayerHand, Playcolms /2);
         }
         else 
         {
          printset(PlayerHand,Playcolms);
         }
        }
      // count the new value of the player hand
      HandValue = countHand(PlayerHand, Playcolms);

      }

  // compute the player's final hand value, and dealer's current
  // hand value
  int Dealertotalvalues = countHand(DealerHand, Dealercolms);  
  int Playerendvalues = countHand(PlayerHand, Playcolms);

  
      
  // if the player gets 21 , they  win
  if (countHand(PlayerHand, Playcolms) == 21)
  {
    cout << endl << "!!!You Win!!!";
    Cash += Betting;
    cout << endl << "Your new cash amount is: " << Cash << endl;
     
  }

  // if the player has more than 21, they  lose
  else if (countHand(PlayerHand, Playcolms) > 21)
  {
    cout << endl << "!!You have busted, You Lose!!";
    Cash -= Betting;
    cout << endl << "Your new cash amount is: " << Cash << endl;
  }

  // if the player has neither 21 nor > 21, then the dealer must try to get 21
  else 
  {
  
  // show the player's final cards, and the dealer's final cards
  // show the  initial 2 cards
    cout << endl << "Your final cards: " << endl;
    printset(PlayerHand, Playcolms);
    cout << endl << "The dealer's cards: " << endl;
    printset(DealerHand, Dealercolms);

    // while the dealer's hand value is less than 16 and  not greater 20, he will keep hitting and showing
    // his new hand
    
    while (Dealertotalvalues <= 16 && !(Dealertotalvalues > 20))
    {
        Dealercolms++;
        DealerHand.push_back(new Card(rand()%52));
        cout << "The dealer's new hand" << endl;
        printset(DealerHand, Dealercolms);
        Dealertotalvalues = countHand(DealerHand, Dealercolms);
    }
        
    
    // if the dealer gets more than 21
    if (Dealertotalvalues > 21)
    {
      cout << endl << "The dealer busted, and you win!" << endl;
      Cash += Betting;
      cout << "Your new cash amount is: " << Cash<< endl;
    }
    // if the dealer has a greater amount
     else if (Dealertotalvalues > Playerendvalues)
     {
      cout << endl << "The dealer has won" << endl;
      Cash -= Betting;
      cout << "Your new cash amount is: " << Cash<< endl;
     }
    // if the dealer has the same amount as the player,it will result in a tie
    else if (Dealertotalvalues == Playerendvalues)
     {
       cout << endl << "You have tied with the dealer" << endl;
       cout << "Your cash amount is: " << Cash<< endl;
     }
    // if the player has more than the dealer
    else 
    {
      cout << endl << "You won!" << endl;
      Cash += Betting;
      cout << "Your new cash amount is: " << Cash << endl;
    }

    }

     
    // if the player has more cash they can choose to keep playing 
      if (Cash > 0)
      {
      cout << endl;
      cout << "Enter Y to play again or anything else to stop: ";
      cin >> PLAY;
      cout << endl;
        }
    // if the player has no more money, the loop will end 
      else 
      {
      cout << endl;
      cout <<"Go back to work you dont need to be gambling your money anyways plus you trash anyway!";
      cout << endl;
      
      }

  }


  // end the game and present the player their final cash amount that they have
  cout << "Thanks for playing my Black jack game hope you lost" << endl;
  cout << "Your end cash amount is " << Cash;

  return 0;
}