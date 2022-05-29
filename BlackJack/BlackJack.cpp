#include <iostream>
#include <string>
#include <array>
#include <stdlib.h> 
#include <time.h>

using namespace std;

class Card
{
public:
	enum class CardSuit
	{
		SUIT_CLUB,
		SUIT_DIAMOND,
		SUIT_HEART,
		SUIT_SPADE,
		MAX_SUITS
	};

	enum class CardRank
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
		RANK_JACK,
		RANK_QUEEN,
		RANK_KING,
		RANK_ACE,
		MAX_RANKS
	};

private:
	CardSuit m_suit;
	CardRank m_rank;
public:
	Card(CardRank rank = CardRank::MAX_RANKS, CardSuit suit = CardSuit::MAX_SUITS) 
		: m_suit(suit), m_rank(rank){}

	void printCard() const
	{
		switch (m_rank)
		{
		case CardRank::RANK_2:		cout << "2"; break;
		case CardRank::RANK_3:		cout << "3"; break;
		case CardRank::RANK_4:		cout << "4"; break;
		case CardRank::RANK_5:		cout << "5"; break;
		case CardRank::RANK_6:		cout << "6"; break;
		case CardRank::RANK_7:		cout << "7"; break;
		case CardRank::RANK_8:		cout << "8"; break;
		case CardRank::RANK_9:		cout << "9"; break;
		case CardRank::RANK_10:		cout << "T"; break;
		case CardRank::RANK_JACK:		cout << "V"; break;
		case CardRank::RANK_QUEEN:	cout << "D"; break;
		case CardRank::RANK_KING:		cout << "K"; break;
		case CardRank::RANK_ACE:		cout << "T"; break;
		}

		switch (m_suit)
		{
		case CardSuit::SUIT_CLUB:		cout << "TR"; break;
		case CardSuit::SUIT_DIAMOND:	cout << "B"; break;
		case CardSuit::SUIT_HEART:	cout << "CH"; break;
		case CardSuit::SUIT_SPADE:	cout << "P"; break;
		}
	}

	int getCardValue() const
	{
		switch (m_rank)
		{
		case CardRank::RANK_2:		return 2;
		case CardRank::RANK_3:		return 3;
		case CardRank::RANK_4:		return 4;
		case CardRank::RANK_5:		return 5;
		case CardRank::RANK_6:		return 6;
		case CardRank::RANK_7:		return 7;
		case CardRank::RANK_8:		return 8;
		case CardRank::RANK_9:		return 9;
		case CardRank::RANK_10:		return 10;
		case CardRank::RANK_JACK:	return 10;
		case CardRank::RANK_QUEEN:	return 10;
		case CardRank::RANK_KING:	return 10;
		case CardRank::RANK_ACE:	return 11;
		}

		return 0;
	}
};

class Desk
{
private:
	array <Card, 52> m_desk;
	int m_cardIndex = 0;

	static void swapCard(Card& card1, Card& card2)
	{
		Card temp = card1;
		card1 = card2;
		card2 = temp;
	}

	static int GetRandomNumber(int min, int max)
	{
		static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
		return static_cast<int>(rand() * fraction * (max - min + 1) + min);
	}

public:
	Desk()
	{
		int card = 0; 

		for (int i = 0; i < static_cast<int>(Card::CardSuit::MAX_SUITS); i++)
		{
			for (int j = 0; j < static_cast<int>(Card::CardRank::MAX_RANKS); j++)
			{
				m_desk[card] = { static_cast<Card::CardRank>(j), static_cast<Card::CardSuit> (i)};
				card++;
			}
		}
	}

	void printDesk() const
		{
			for (int i = 0; i < static_cast<int>(m_desk.size()); i++)
			{	
				if (i % 4 == 0)
				{
					cout << endl;
				}

				m_desk[i].printCard();
				cout << "\t";

				
			}

			cout << endl;
		}

	void suffleDesk()
	{
		for (int i = 0; i < 52; i++)
		{
			int randIndex = GetRandomNumber(0, 51);
			swapCard(m_desk[i], m_desk[randIndex]);
		}
		m_cardIndex = 0;
	}

	 const Card& dealCard()
	{
		return m_desk[m_cardIndex++];
	}
};

char getPlayerAnswer()
{
	char answer;

	do
	{
		cout << "(h) to hit, or (s) to stand: ";
		cin >> answer;
	} while (answer != 'h' && answer != 's');

	return answer;
}

bool playBlackJack(Desk& desk)
{
	int totalPlayer = 0;
	int totalDealer = 0;

	totalDealer += desk.dealCard().getCardValue();
	cout << "The dealer is showing: " << totalDealer << '\n';

	totalPlayer += desk.dealCard().getCardValue();
	totalPlayer += desk.dealCard().getCardValue();

	while (true)
	{
		cout << "You have: " << totalPlayer << endl;

		if (totalPlayer > 21)
		{
			return false;
		}

		char choice = getPlayerAnswer();
		if (choice == 's')
		{
			break;
		}
		else
		{
			totalPlayer += desk.dealCard().getCardValue();
		}
	}

	while (totalDealer < 17)
	{
		totalDealer += desk.dealCard().getCardValue();
	}
		cout << "The dealer now has: " << totalDealer << '\n';

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

	Desk desk;
	desk.suffleDesk();
	
	
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
