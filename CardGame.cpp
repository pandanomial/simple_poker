/*

Write a program that reads HAND_SIZE cards from the user, then analyzes the cards
and prints out the type of poker hand that they represent. (HAND_SIZE will be a 
global constant, typically 5, but the program must still work if it is NOT 5.)
To simplify the program we will ignore card suits, and face cards. The values that
the user inputs will be integer values from LOWEST_NUM to HIGHEST_NUM.
*/

  
#include <iostream>
using namespace std;

//required
const int HAND_SIZE = 5;// 6; //8;
const int LOWEST_NUM = 2;//1; //1; //1;
const int HIGHEST_NUM = 9;// 13; //13; //13;

//required functions and parameters
bool  containsPair(const int hand[]); //3 lines
bool  containsTwoPair(const int hand[]);//3 lines
bool  containsThreeOfaKind(const int hand[]);//3 lines
bool  containsStraight(const int hand[]);//3 lines
bool  containsFullHouse(const int hand[]);//3 lines
bool  containsFourOfaKind(const int hand[]);//3 lines

//helper functions for this long version HW by using 2 arrays. 
//array hand stores orgional user input cards, in case for other purposes.
//array arrCounts stores counted cards for identifying the hand in this project
void inputCards(int hand[], int iHandSize);//5 lines
void countCardsbyType(const int hand[], int arrCounts[]);//2 lines
void countCardbyType(const int hand[], int arrCounts[], int iIndex);//5 lines
int findMatches(const int arrCounts[], const int iHandType);//5 lines
bool isStraight(const int hand[], const int arrCounts[]);//4 lines


int main()
{
	int hand[HAND_SIZE];
	inputCards(hand, HAND_SIZE);//call function to collect cards input

	if (containsFourOfaKind(hand))
	{
	cout << "Four of a kind!" << endl;
	}
	else if (containsFullHouse(hand))
	{
		cout << "Full house!" << endl;
	}
	else if (containsStraight(hand))
	{
		cout << "Straight!" << endl;
	}
	else if (containsThreeOfaKind(hand))
	{
		cout << "Three of a kind" << endl;
	}
	else if (containsTwoPair(hand))
	{
		cout << "Two pair!" << endl;
	}
	else if (containsPair(hand))
	{
		cout << "Pair!" << endl;
	}
	else
	{
		cout << "High card!" << endl;
	}
}







//This function asks user input cards as integer numbers. hand size, low, high
//numbers are all fixed. Then the cards are stored in array hand.
void inputCards(int hand[], int iHandSize)
{
	cout << "Enter " << iHandSize << " numeric cards, no face cards. Use ";
	cout << LOWEST_NUM << " - " << HIGHEST_NUM << "." << endl;

	for (int i = 0; i < iHandSize; i++)
	{
		cout << "Card " << i + 1 << ": ";
		cin >> hand[i];
	}
}







//This function stores all cards' repeating times. eg, A hand of 5 5 5 8 8 is 
//stored as arrCounts[5]=3  arrCounts[8]=2  arrCounts[2]=0....arrCounts[9]=0
//After this, arrCounts will be ready to be used for identifying the hand.
void countCardsbyType(const int hand[], int arrCounts[])
{
	//the largest card number is HIGHEST_NUM, arrCounts's index ends at HIGHEST_NUM
	for (int i = 0; i < HIGHEST_NUM + 1; i++)
	{
		countCardbyType(hand, arrCounts, i);//to save each card's repeating times 
	}
}







//This function saves the number of how many times of one card repeats
//eg, if hand is 5 5 5 8 8 and iIndex=5, it will set arrCounts[5] to 3 
void countCardbyType(const int hand[], int arrCounts[], int iIndex)
{
	for (int i = 0; i < HAND_SIZE; i++)
	{
		if (hand[i] == iIndex)
		{
			arrCounts[iIndex] = arrCounts[iIndex] + 1;//increment repeating card
			
			if (arrCounts[iIndex] > 4)
			{
				//if a card repeats 5 or 6 or 7...times, it's still 4-of-a-kind
				arrCounts[iIndex] = 4; 
			}
		}
	}
}







//the numbers of repeated cards are stored in arrCounts. eg, a hand of 5 5 5 8 8
//is stored as arrCounts[5]=3 arrCounts[8]=2 arrCounts[2]=0 arrCounts[9]=0
//...
//this function, if passing iHandType=2, it will find how many pairs are there
//if passing iHandType=3, it will find how many 3-of-a-kind are there...so on
int findMatches(const int arrCounts[], int iHandType)
{
	int count = 0;
	for (int i = 0; i < HIGHEST_NUM + 1; i++)
	{
		if (arrCounts[i] == iHandType)
		{
			count = count + 1;
		}
	}
	
	return count;
}








//the numbers of repeated cards are stored in arrCounts. eg, a hand of 5 9 7 8 6
//is stored as arrCounts[5]=1 arrCounts[6]=1 ... arrCounts[9]=1 
// 
//this function is to check if 5 cards are consecutive. if so, return true
bool isStraight(const int hand[], const int arrCounts[])
{
	//To avoid out of bound, loop from 0 to HIGHEST_NUM + 1 - HAND_SIZE. 
	for (int i = 0; i <= HIGHEST_NUM + 1 - HAND_SIZE; i++)
	{
		//look for five consecutive numbers in hand
		if (arrCounts[i] > 0 && arrCounts[i + 1] > 0 && arrCounts[i + 2] > 0
			&& arrCounts[i + 3] > 0 && arrCounts[i + 4] > 0)
		{
			return true;
		}
	}
	
	return false;
}







//the numbers of repeated cards are stored in arrCounts. eg, a hand of 5 5 9 8 6
//is stored as arrCounts[5]=2 arrCounts[6]=1...arrCounts[9]=1 arrCounts[2]=0
//then call findMatches
//post: returns true if and only if there are one or more pairs in the hand. Note that
//this function returns false if there are more than two of the same card(and no other pairs).  
bool  containsPair(const int hand[])
{
	//the largest card number is HIGHEST_NUM, arrCounts's index ends at HIGHEST_NUM
	int arrCounts[HIGHEST_NUM + 1] = { 0 };
	
	countCardsbyType(hand, arrCounts);//call function to count

	//pairs, pass value 2 to check. If there is at least 1 pair, return true
	return ( findMatches(arrCounts, 2) > 0 );
}







//the numbers of repeated cards are stored in arrCounts. eg, a hand of 5 5 8 8 6
//is stored as arrCounts[5]=2 arrCounts[6]=1 arrCounts[8]=2 arrCounts[2]=0...
//then call findMatches
//post: returns true if and only if there are two or more pairs in the hand.  
bool  containsTwoPair(const int hand[])
{
	//the largest card number is HIGHEST_NUM, arrCounts's index ends at HIGHEST_NUM
	int arrCounts[HIGHEST_NUM + 1] = { 0 };
	
	countCardsbyType(hand, arrCounts);//call function to count

	//pairs, pass value 2 to check. If there are at least 2 pairs, return true
	return ( findMatches(arrCounts, 2) > 1 );
}







//the numbers of repeated cards are stored in arrCounts. eg, a hand of 5 8 8 8 6 
//is stored as arrCounts[5]=1 arrCounts[6]=1 arrCounts[8]=3 arrCounts[2]=0...
// 
//post: returns true if and only if there are one or more three-of-a-kind's in the hand. 
bool  containsThreeOfaKind(const int hand[])
{
	//the largest card number is HIGHEST_NUM, arrCounts's index ends at HIGHEST_NUM
	int arrCounts[HIGHEST_NUM + 1] = { 0 };
	
	countCardsbyType(hand, arrCounts);//call function to count

	//3-of-a-kind, pass value 3 to check. If there is at least one, return true
	return ( findMatches(arrCounts, 3) > 0 );
}







//the numbers of repeated cards are stored in arrCounts. eg, a hand of 8 8 8 8 6
//is stored as arrCounts[6]=1 arrCounts[8]=4 arrCounts[2]=0...arrCounts[9]=0
//then call findMatches 
//post: returns true if and only if there are one or more 4-of-a-kind's in the hand. 
bool  containsFourOfaKind(const int hand[])
{
	//the largest card number is HIGHEST_NUM, arrCounts's index ends at HIGHEST_NUM
	int arrCounts[HIGHEST_NUM + 1] = { 0 };
	
	countCardsbyType(hand, arrCounts);//call function to count

	//4-of-a-kind, pass value 4 to check. If there is at least one, return true
	return ( findMatches(arrCounts, 4) > 0 );
}







//the numbers of repeated cards are stored in arrCounts. eg, a hand of 5 9 7 8 6
//is stored as arrCounts[5]=1 arrCounts[6]=1...arrCounts[9]=1 arrCounts[2]=0...
//then call findMatches 
//post: returns true if there are 5 consecutive cards in the hand.
bool  containsStraight(const int hand[])
{
	//the largest card number is HIGHEST_NUM, arrCounts's index ends at HIGHEST_NUM 
	int arrCounts[HIGHEST_NUM + 1] = { 0 };
	
	countCardsbyType(hand, arrCounts);//call function to count
	
	return ( isStraight(hand, arrCounts) );
}







//the numbers of repeated cards are stored in arrCounts. eg, hand 5 5 8 8 8
//is stored as arrCounts[5]=2 arrCounts[8]=3 ... arrCounts[9]=0 
//then call findMatches
//post:returns true if there is are one or more pairs and one or more 3-of-a-kind's in the hand.  
bool  containsFullHouse(const int hand[])
{
	//the largest card number is HIGHEST_NUM, arrCounts's index ends at HIGHEST_NUM
	int arrCounts[HIGHEST_NUM + 1] = { 0 };
	
	countCardsbyType(hand, arrCounts);//call function to count

	//pair, pass value 2 to check; 3-Of-a-Kind, pass value 3 to check.
	//If it has at least 1 pair and at least one 3-of-a-kind, it's a full house.
	return ( findMatches(arrCounts, 2) > 0) && (findMatches(arrCounts, 3) > 0 );
}

