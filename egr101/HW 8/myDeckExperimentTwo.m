function [matches] = myDeckExperimentTwo()
deck1 = randperm(52); % establish two shuffled decks
deck2 = randperm(52);
deck1 = mod(deck1,13); % modified decks disregarding suits
deck2 = mod(deck2,13); % modulus 13
matches = sum(deck1 == deck2); % sum and output number of matches
end