//
//  main.cpp
//  Quiz_6_exercise_6
//
//  Created by Ashwin Dixit on 12/17/16.
//  Copyright © 2016 Ashwin Dixit. All rights reserved.
//

#include <iostream>
#include <array>

enum CardRank {
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

enum CardSuite {
    SUITE_HEARTS,
    SUITE_DIAMONDS,
    SUITE_CLUBS,
    SUITE_SPADES,
    MAX_SUITES
};

struct Card {
    CardRank rank;
    CardSuite suite;
};

char get_rank_code( CardRank cr ) {
    char x;
    switch ( cr ) {
        case RANK_2:
            x = '2';
            break;
        case RANK_3:
            x = '3';
            break;
        case RANK_4:
            x = '4';
            break;
        case RANK_5:
            x = '5';
            break;
        case RANK_6:
            x = '6';
            break;
        case RANK_7:
            x = '7';
            break;
        case RANK_8:
            x = '8';
            break;
        case RANK_9:
            x = '9';
            break;
        case RANK_10:
            x = '1';
            break;
        case RANK_JACK:
            x = 'J';
            break;
        case RANK_QUEEN:
            x = 'Q';
            break;
        case RANK_KING:
            x = 'K';
            break;
        case RANK_ACE:
            x = 'A';
            break;
        default:
            x = 'Z';
            break;
    }
    return x;
}

char get_suite_code( CardSuite cs ) {
    char x;
    switch ( cs ) {
        case SUITE_HEARTS:
            x = 'H';
            break;
        case SUITE_DIAMONDS:
            x = 'D';
            break;
        case SUITE_CLUBS:
            x = 'C';
            break;
        case SUITE_SPADES:
            x = 'S';
            break;
        default:
            x = 'Z';
            break;
    }
    return x;
}

void printCard( Card c ) {
    std::cout << get_rank_code(c.rank);
    std::cout << get_suite_code(c.suite);
}

void printDeck ( const std::array<Card, 52> &deck ) {
    for ( const auto &c : deck ) {
        printCard(c);
        std::cout << std::endl;
    }
}

void swapCard( Card &c1, Card &c2 ) {
    Card temp = c1;
    c1 = c2;
    c2 = temp;
}

int getRandomNumber(int min, int max) {
    // Generate a random number between min and max (inclusive)
    // Assumes srand() has already been called
    
    // static used for efficiency, so we only calculate this value once
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    
    // evenly distribute the random number across our range
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void shuffleDeck( std::array<Card, 52> &deck ) {
    for ( int x = 0; x < deck.size(); ++x ) {
        int i = getRandomNumber(0, 51);
        int j= getRandomNumber(0, 51);
        swapCard(deck[i], deck[j]);
    }
}

int getCardValue( const Card &c, const int &current_score) {
    int result;
    switch (c.rank) {
        case RANK_2:
            result = 2;
            break;
        case RANK_3:
            result = 3;
            break;
        case RANK_4:
            result = 4;
            break;
        case RANK_5:
            result = 5;
            break;
        case RANK_6:
            result = 6;
            break;
        case RANK_7:
            result = 7;
            break;
        case RANK_8:
            result = 8;
            break;
        case RANK_9:
            result = 9;
            break;
        case RANK_10:
        case RANK_JACK:
        case RANK_QUEEN:
        case RANK_KING:
            result = 10;
            break;
        case RANK_ACE:
            result = (current_score <= 10) ? 11 : 1;
            break;
        default:
            result = 0;
            break;
    }
    return result;
}

void printScores(const int dealer_score, const int player_score) {
    std::cout << "Dealer score: " << dealer_score << "\n";
    std::cout << "Player score: " << player_score << "\n";
}

bool playBlackjack( std::array<Card, 52> &deck ) {
    
    int dealer_score { 0 };
    int player_score { 0 };
    
    Card *cardPtr = &deck[0];

    // dealer gets a card
    dealer_score  = getCardValue(*cardPtr++, dealer_score);

    // player gets 2 cards
    player_score  = getCardValue(*cardPtr++, player_score);
    player_score += getCardValue(*cardPtr++, player_score);

    printScores(dealer_score, player_score);

    if ( player_score == 21 ) {
        return true;
    } else if (player_score > 21 ) {
        return false;
    }

    bool game_over { false };
    do {
        // Player goes first
        std::cout << "Enter H to hit, or S to stay. ";
        char choice;
        std::cin >> choice;
        if ( (choice == 'H') || (choice == 'h') ) {
            std::cout << "Card dealt: ";
            printCard(*cardPtr);
            std::cout << std::endl;
            player_score += getCardValue(*cardPtr++, player_score);
            printScores(dealer_score, player_score);
            if ( player_score == 21 ) {
                return true;
            } else if ( player_score > 21 ) {
                return false;
            }
        } else if ( (choice == 'S') || (choice == 's') ) {
            std::cout << "You have chosen to stay.\n";
            game_over = true;
        } else {
            // Keep looping back till a valid choice is entered
            continue;
        }
        
        // Dealer goes second
        while ( dealer_score < 17 ) {
            std::cout << "Card dealt to Dealer: ";
            printCard(*cardPtr);
            std::cout << std::endl;
            dealer_score += getCardValue(*cardPtr++, dealer_score);
            printScores(dealer_score, player_score);
            if ( dealer_score == 21 ) {
                return false;
            } else if ( dealer_score > 21 ) {
                return true;
            }
        }
    } while ( ! game_over );
    
    return (player_score > dealer_score) ? true : false;
}

void initialize_game(std::array<Card, 52> &deck) {
    srand(static_cast<unsigned int>(time(0))); // set initial seed value to system clock
 
    for ( int suite = 0; suite < MAX_SUITES; ++suite) {
        for ( int rank = 0; rank < MAX_RANKS; ++rank ) {
            int index = ( suite * MAX_RANKS ) + rank;
            deck[ index ] = { static_cast<CardRank>(rank), static_cast<CardSuite>(suite)  };
        }
    }
    
    /* ***********************
     printDeck(deck);
     std::cout << "============================shuffleDeck()\n";
     shuffleDeck(deck);
     printDeck(deck);
     ************************** */
    
}

int main() {
    std::array<Card, 52> deck;
    initialize_game(deck);
    bool play_again { true };
    do {
        shuffleDeck(deck);
    
        if ( playBlackjack(deck) ) {
            std::cout << "You win!\n";
        } else {
            std::cout << "You lose!\n";
        }
        
        std::cout << "Play again? [yn] ";
        char repeat_game;
        std::cin >> repeat_game;
        if ( ( repeat_game == 'n' ) || ( repeat_game == 'N' ) ) {
            play_again = false;
        }
    } while ( play_again );
    return 0;
}
