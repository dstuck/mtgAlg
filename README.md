# mtgAlg
This project is a game engine for Magic: The Gathering.
It is intended as a test case for my genetic algorithm code optimizing decks and AI

BasicGame is the top level driver:
  -Sets up intialization of game given two Controller classes (AI or human)
  -Manages zones of game (Battlefield, Hand, Graveyard, and Exile)
  -Handle game stack and state-based action queue
  -Run through phases of game (upkeep, main, combat, and end) and enforce legal plays
Controller classes must be able to make plays and choose attackers and blocker
Cards contain many specialized rules and currently many of the standard rules like flying and reach are implemented


The AI are described below:
TestController
    v1: no strategy, simply plays a land and makes legal plays in the order drawn
        -attacks with everything
        -always blocks first attacker possible
    v2: Values boards state based on values preassigned to permanents
        -for blocks, predict crackback from opponent, value the new board state, and pick the best
        -for attacks, predict best block (including crackback) and pick best value for yourself
        -rudementary assessment of number of calculations needed to predict crackback and reduce recursion if necessarily
        -exponentially scales with number of attackers and blockers
    v3: Implementing heuristics to remove exponential scaling
        -for attacks consider no attacks, each single attack, combo of all single attacks that weren't bad, and alpha strike
            -scaling = N_a+3
X        -consider no blocks, all single double or all blocks on each single creature, and then considering all ordering of attackers pick best possible blocks for each one at a time until no blockers left
X            -scaling = N_a*N_b^(max_blocks)*N_a!
        -or all single and double (maybe triple?) blocks on individual attackers, then determine the one set of blocks with maximal value and minimal # of blockers then repeat (maximally N_b times)
            -scaling = N_a*N_b^(max_blocks)*N_repetitions
