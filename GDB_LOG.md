# GDB log - Week 11

Name: __________________

## My prediction

I expect hands 3, 4, 6, 7, and 8 to be wrong because the buggy code checks for a bust before adding the next card, but not after the last card.

## Commands to run and record

```sh
cmake -S . -B build
cmake --build build --target hand_bug
./build/hand_bug
gdb ./build/hand_bug
```

In GDB:

```gdb
break Hand::value if m_count == 3
run 4
display total
display aces_as_eleven
next
print *this
finish
```

I used a conditional breakpoint to stop only when the hand has three cards. `display` shows how the total and soft ace count change while I step through. `print *this` inspects the current Hand and `finish` shows the returned value.

## My observed results (fill in after running GDB)

- Wrong hand and printed total: __________
- Total and soft aces at failing step: __________
- `print *this` output: __________
- `finish` return value: __________

## Cause and fix

The original code checks `total > 21` at the beginning of the loop. If the final card causes a bust, there is no next loop iteration to correct an ace. I moved the ace adjustment after the loop, where it can repeat until the total is valid or no soft aces remain.

- Results after I ran all ten hands: __________
