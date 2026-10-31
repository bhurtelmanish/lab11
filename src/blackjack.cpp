#include "blackjack.h"

#include <iostream>
#include <random>
#include <string>

#include "deck.h"
#include "hand.h"

namespace {
// I use one helper for reading hit/stand and play/quit choices.
char ask(const std::string &prompt, char first, char second) {
  std::string answer;
  while (true) {
    std::cout << prompt;
    if (!(std::cin >> answer)) return second;
    if (answer.size() == 1 && (answer[0] == first || answer[0] == second))
      return answer[0];
    std::cout << "Please enter " << first << " or " << second << ".\n";
  }
}
}

void play_blackjack() {
  std::random_device device;
  std::mt19937 gen{device()};
  Deck deck;
  deck.shuffle(gen);
  int bankroll = 100;
  std::cout << "\n--- Blackjack ---\n";

  while (bankroll > 0) {
    std::cout << "Bankroll: " << bankroll << "\n";
    if (ask("Play a round? (p/q): ", 'p', 'q') == 'q') break;
    if (deck.remaining() < 15) deck.shuffle(gen);
    const int bet = bankroll < 10 ? bankroll : 10;
    bankroll -= bet;
    Hand player;
    Hand dealer;
    player += deck.deal();
    dealer += deck.deal();
    player += deck.deal();
    dealer += deck.deal();
    std::cout << "Dealer shows: " << dealer[0] << "\n";
    std::cout << "Your hand: " << player << " (" << player.value() << ")\n";

    if (!player.is_blackjack() && !dealer.is_blackjack()) {
      while (!player.is_bust() && player.count() < max_hand &&
             ask("Hit or stand? (h/s): ", 'h', 's') == 'h') {
        player += deck.deal();
        std::cout << "Your hand: " << player << " (" << player.value() << ")\n";
      }
    }
    if (!player.is_bust() && !player.is_blackjack() && !dealer.is_blackjack()) {
      while (dealer.value() < 17 && dealer.count() < max_hand)
        dealer += deck.deal();
    }
    std::cout << "Dealer: " << dealer << " (" << dealer.value() << ")\n";
    if (player.is_bust()) {
      std::cout << "You busted. Lost " << bet << ".\n";
    } else if (player.is_blackjack() && !dealer.is_blackjack()) {
      bankroll += bet + bet * 3 / 2;
      std::cout << "Blackjack! You win.\n";
    } else if (dealer.is_blackjack() && !player.is_blackjack()) {
      std::cout << "Dealer has blackjack. You lose.\n";
    } else if (dealer.is_bust() || player.value() > dealer.value()) {
      bankroll += bet * 2;
      std::cout << "You win!\n";
    } else if (player.value() == dealer.value()) {
      bankroll += bet;
      std::cout << "Push. Bet returned.\n";
    } else {
      std::cout << "Dealer wins.\n";
    }
  }
  std::cout << "Final bankroll: " << bankroll << "\n";
}
