#include <iostream>
#include <string>
#include <array>
#include <stdlib.h> 
#include <time.h>

using namespace std;


enum CardSuit
{
	SUIT_TREFU,
	SUIT_BYBNU,
	SUIT_CHERVU,
	SUIT_PIKI,
	MAX_SUITS
};

enum CardRank
{
	RANK_2,
	RANK_3,
	RANK_4,
	RANK_5,
	RANK_6,
	RANK_7,
	RANK_8,
	RANK_9,
	RANK_10,
	RANK_VALET,
	RANK_DAMA,
	RANK_KOROL,
	RANK_TYZ,
	MAX_RANKS
};

struct Card
{
	CardRank rank;
	CardSuit suit;
};

int GetRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void printCard(const Card& card)
{
	switch (card.rank)
	{
	case RANK_2:		cout << "2"; break;
	case RANK_3:		cout << "3"; break;
	case RANK_4:		cout << "4"; break;
	case RANK_5:		cout << "5"; break;
	case RANK_6:		cout << "6"; break;
	case RANK_7:		cout << "7"; break;
	case RANK_8:		cout << "8"; break;
	case RANK_9:		cout << "9"; break;
	case RANK_10:		cout << "T"; break;
	case RANK_VALET:	cout << "V"; break;
	case RANK_DAMA:	    cout << "D"; break;
	case RANK_KOROL:	cout << "K"; break;
	case RANK_TYZ:		cout << "T"; break;
	}

	switch (card.suit)
	{
	case SUIT_TREFU:	cout << "TR"; break;
	case SUIT_BYBNU:	cout << "B"; break;
	case SUIT_CHERVU:	cout << "CH"; break;
	case SUIT_PIKI:	    cout << "P"; break;
	}
}

void printDesk(const array<Card, 52>& arr)
{
	for (const auto& num : arr)
	{
		printCard(num);
		cout << " ";
	}
}

void swapCard(Card& card1, Card& card2)
{
	Card temp = card1;
	card1 = card2;
	card2 = temp;
}

void suffleDesk(array<Card, 52>& arr)
{
	for (int i = 0; i < 52; i++)
	{
		int randIndex = GetRandomNumber(0, 51);
		swapCard(arr[i], arr[randIndex]);
	}
}

int getCardValue(const Card& card)
{
	switch (card.rank)
	{
	case RANK_2:		return 2;
	case RANK_3:		return 3;
	case RANK_4:		return 4;
	case RANK_5:		return 5;
	case RANK_6:		return 6;
	case RANK_7:		return 7;
	case RANK_8:		return 8;
	case RANK_9:		return 9;
	case RANK_10:		return 10;
	case RANK_VALET:	return 10;
	case RANK_DAMA:	    return 10;
	case RANK_KOROL:	return 10;
	case RANK_TYZ:		return 11;
	}

	return 0;
}

char getAnswer()
{
	char answer;

	do
	{
		cout << "(h) to hit, or (s) to stand: ";
		cin >> answer;
	} while (answer != 'h' && answer != 's');

	return answer;
}

bool playBlackJack(const array<Card, 52>& arr)
{
	const Card* cardPtr = &arr[0];

	int totalPlayer = 0;
	int totalDealer = 0;

	totalDealer += getCardValue(*cardPtr++);
	cout << "The dealer is showing: " << totalDealer << '\n';

	totalPlayer += getCardValue(*cardPtr++);
	totalPlayer += getCardValue(*cardPtr++);

	while (true)
	{
		cout << "You have: " << totalPlayer << endl;

		if (totalPlayer > 21)
		{
			return false;
		}

		char choice = getAnswer();
		if (choice == 's')
		{
			break;
		}
		else
		{
			totalPlayer += getCardValue(*cardPtr++);
		}
	}

	while (totalDealer < 17)
	{
		totalDealer += getCardValue(*cardPtr++);
		cout << "The dealer now has: " << totalDealer << '\n';
	}

	if (totalDealer > 21)
	{
		return true;
	}
	else if (totalDealer < totalPlayer)
	{
		return true;
	}
	else
	{
		return false;
	}

	return true;
}

int main()
{
	srand(static_cast<unsigned int>(time(0)));
	rand();

	array <Card, 52> desk;

	int count = 0;
	for (int type = 0; type < MAX_SUITS; type++)
	{
		for (int rank = 0; rank < MAX_RANKS; rank++)
		{
			desk[count].suit = static_cast<CardSuit>(type);
			desk[count].rank = static_cast<CardRank>(rank);
			count++;
		}
	}

	suffleDesk(desk);

	if (playBlackJack(desk))
	{
		cout << "You win!";
	}
	else
	{
		cout << "You lose";
	}




	return 0;
}
