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
bool  containsPair(const int hand[]); //1 line
bool  containsTwoPair(const int hand[]);//1 line
bool  containsThreeOfaKind(const int hand[]);//1 line
bool  containsStraight(const int hand[]);//1 line
bool  containsFullHouse(const int hand[]);//1 line
bool  containsFourOfaKind(const int hand[]);//1 line

//My helper functions
void inputCards(int hand[]);//5 lines
void countCardbyType(int hand[], int iIndex);//3 lines
int findMatches(const int hand[], int iHandType);//5 lines


int main()
{
	int hand[HIGHEST_NUM + 1] = { 0 };

	cout << "Enter " << HAND_SIZE << " numeric cards, no face cards. Use ";
	cout << LOWEST_NUM << " - " << HIGHEST_NUM << "." << endl;

	inputCards(hand);
	
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


//stores user input as an orgnized array eg, A hand of 5 5 5 8 8 is stored as
//hand[5]=3  hand[8]=2  hand[2]=0....hand[9]=0,
void inputCards(int hand[])
{
	int iIndex;

	for (int i = 0; i < HAND_SIZE; i++)
	{
		cout << "Card " << i + 1 << ": ";
		cin >> iIndex;
		countCardbyType(hand, iIndex);
	}
}







//This function stores the number of how many times of one card repeats
//eg, if hand is 5 5 5 8 8 and iIndex is 5, it will set arrCounts[5] to 3 
void countCardbyType(int hand[], int iIndex)
{
	hand[iIndex] = hand[iIndex] + 1;//increment repeating card

	if (hand[iIndex] > 4)
	{
		//if a card repeats 5 or 6 or 7...times, it is still 4-of-a-kind
		hand[iIndex] = 4;
	}
}







//the numbers of repeated cards are already saved in arrCounts. eg, a hand of 
//5 5 5 8 8 is stored as arrCounts[5]=3 arrCounts[8]=2   arrCounts[2]=0 ...  
//this function, if passing iHandType=2, it will find how many pairs are there
//if passing iHandType=3, it will find how many 3-of-a-kind are there...so on
int findMatches(const int hand[], int iHandType)
{
	int count = 0;
	for (int i = 0; i < HIGHEST_NUM + 1; i++)
	{
		if (hand[i] == iHandType)
		{
			count = count + 1;
		}
	}
	return count;
}









//post: returns true if and only if there are one or more pairs in the hand. Note that
//this function returns false if there are more than two of the same card(and no other pairs).  
bool  containsPair(const int hand[])
{
	//pairs, pass value 2 to check. If there is at least 1 pair, return true
	return (findMatches(hand, 2) > 0);
}







// post: returns true if and only if there are two or more pairs in the hand.  
bool  containsTwoPair(const int hand[])
{
	//pairs, pass value 2 to check. If there are at least 2 pairs, return true
	return (findMatches(hand, 2) > 1);
}







//post: returns true if and only if there are one or more three-of-a-kind's in the hand. 
bool  containsThreeOfaKind(const int hand[])
{
	//3-of-a-kind, pass value 3 to check. If there is at least one, return true
	return (findMatches(hand, 3) > 0);
}






//post: returns true if and only if there are one or more four-of-a-kind's in the hand. 
bool  containsFourOfaKind(const int hand[])
{
	//4-of-a-kind, pass value 4 to check. If there is at least one, return true
	return (findMatches(hand, 4) > 0);
}







//post: returns true if there are 5 consecutive cards in the hand.
bool  containsStraight(const int hand[])
{
	//To avoid out of bound, loop from 0 to HIGHEST_NUM + 1 - HAND_SIZE. 
	for (int i = 0; i <= HIGHEST_NUM + 1 - HAND_SIZE; i++)
	{
		//look for five consecutive numbers in hand
		if (hand[i] > 0 && hand[i + 1] > 0 && hand[i + 2] > 0 && hand[i + 3] > 0 
			&& hand[i + 4] > 0)
		{
			return true;
		}
	}
	return false;
}







//post:returns true if there is are one or more pairs and one or more three-of-a-kind's in the hand.  
bool  containsFullHouse(const int hand[])
{
	//pair, pass value 2 to check; 3-Of-a-Kind, pass value 3 to check.
	//If it has at least 1 pair and at least one 3-of-a-kind, it's a full house.
	return (findMatches(hand, 2) > 0) && (findMatches(hand, 3) > 0);
}

