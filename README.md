# First Black Jack Game Analysis
## A Project for the Stingiest Euchre Players in Existence
Given the total number of cards, the number of black jacks, and the number of teams playing, 
this script calculates the probability of each team winning the 'First Black Jack Game'.

### How to Use 
Just compile the code and run it. It runs in the terminal and will ask for the input it needs.\
Choice 1 Calculates the probabilities of each team winning the First Black Jack Game based on your following inputs.\

### Rules of the Game
Before a game of Euchre begins, a small game of luck is played to determine who will deal first.\
I call this the 'First Black Jack Game' and the rules are as follows:

1. One player (usually whoever brought the cards) is the dealer for the First Black Jack Game.
2. The dealer shuffles the cards and deals one card at a time face up starting with the player on their left and continuing clockwise.
3. The dealer continues until a black jack is turned up. Whoever got the black jack gets the first deal.

While this game seems fair, a close analysis reveals that with more than one black jack, this game is slightly biased.

### Game Generalization
This type of game can be generalized for
1. C = total number of cards in the deck
2. J = number of black jacks (winning cards) in the deck
3. T = number of teams

For a typical Euchre game, the values are C=24,J=2,T=2 (or T=4 if you care about which partner gets the deal).

### Important Probabilities
Yeah, I know what you're here for. I'll get to the point.

For a typical game of Euchre (C=24,J=2,T=2),
```
Team 1 wins 52.1739% of the time.
Team 2 wins 47.8261% of the time.
```
Team 1 being the first team that is dealt to, and Team 2 the second.

If your team happens to be the second that is dealt to, feel free to use this to justify your loss.
