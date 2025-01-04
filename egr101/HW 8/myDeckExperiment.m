function [matches] = myDeckExperiment()
deck1 = randperm(52); % establish two shuffled decks
deck2 = randperm(52);
matches = sum(deck1 == deck2); % sum and output number of matches
end