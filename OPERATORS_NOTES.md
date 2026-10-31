# Operators notes (Lab 11)

## My hand test table

| Hand | Expected value | Bust? | Blackjack? |
| --- | ---: | --- | --- |
| A K | 21 | No | Yes |
| A A | 12 | No | No |
| A A 9 | 21 | No | No |
| A 6 5 | 12 | No | No |
| A A A 8 | 21 | No | No |
| T T 5 | 25 | Yes | No |
| 9 7 5 | 21 | No | No |
| A K Q | 21 | No | No |

I counted each ace as 11 first, then changed an ace to 1 whenever the total went over 21.

## Design files

- `design/class_diagram.md`
- `design/hand_value.md`
- `design/dealer_turn.md`

## Ownership table

| Relationship | Type | Why |
| --- | --- | --- |
| Hand and Cards | Composition | The cards are stored inside the Hand, so its copies belong to that Hand and disappear with it. |
| Blackjack game and Deck/Hands | Composition | The game creates its own local deck and hands, which are destroyed when the game ends. |
| Player and current Room* | Association | The player only points at a room and does not own or delete it. |

## Checks

- [ ] I ran the build without warnings
- [ ] I ran all tests
- [ ] I checked the AddressSanitizer build
- [ ] I finished my own GDB observations
