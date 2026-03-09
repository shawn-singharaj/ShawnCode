
def beam_search_decoder(probabilities, k, max_steps=5):
    """
    Performs beam search decoding on a simple language model.

    Args:
        probabilities (dict): A nested dictionary of conditional probabilities.
        k (int): The beam width.
        max_steps (int): The maximum number of decoding steps.

    Returns:
        list: A list of the top k completed sequences and their probabilities.
    """
    # Start with a beam containing only the start token '<s>' with a probability of 1.0
    # Each item in the beam is a tuple: (sequence_list, cumulative_probability)
    beams = [(["<s>"], 1.0)]
    completed_sequences = [] # To store completed sequences

    # Loop for a fixed number of steps to prevent infinite decoding
    for _ in range(max_steps):
        # If the beam is empty, it means all sequences have ended.
        if not beams:
            break

        all_candidates = []

        # 1. Expand each sequence in the current beam
        for sequence, prob in beams:
            last_token  = sequence[-1]

            # Iterate through all possible next tokens
            for next_token, cond_prob in probabilities[last_token].items():
                new_sequence = sequence + [next_token]
                new_prob = cond_prob * prob

                # If the next token is <eos>, it's a finished sentence. Add it to completed sequences
                # Otherwise, add it to the list of candidates for the next beam
                if next_token == '<eos>':
                    completed_sequences.append((new_sequence, new_prob))

                else:
                    all_candidates.append((new_sequence, new_prob))

        # 2. Prune the candidates to find the new beam
        # The new beam consists of the top k candidates
        sorted_candidates = sorted(all_candidates, key=lambda tup: tup[1], reverse = True)
        beams = sorted_candidates[:k]

    # After the loop, sort all completed sequences by probability
    # Then Return the top k completed sequences
    sorted_sequences = sorted(completed_sequences, key=lambda tup: tup[1], reverse = True)
    best_sequences = sorted_sequences[:k]
    return best_sequences


# --- Main Program ---

# Define the conditional probabilities from the problem description
model_probabilities = {
    '<s>': {'I': 0.7, 'cats': 0.1, 'dogs': 0.1, 'like': 0.1},
    'I': {'like': 0.6, 'love': 0.3, '<eos>': 0.1},
    'like': {'cats': 0.5, 'dogs': 0.4, '<eos>': 0.1},
    'love': {'cats': 0.6, 'dogs': 0.2, '<eos>': 0.2},
    'cats': {'and': 0.2, '<eos>': 0.8},
    'dogs': {'like': 0.3, '<eos>': 0.7},
    'and': {'cats': 0.5, 'dogs': 0.5}
}

beam_width = 2
max_steps = 100  # Limit the number of steps to avoid infinite loops
final_sentences = beam_search_decoder(model_probabilities, beam_width, max_steps=max_steps)

# Print the results
print(f"Beam Search Results (k={beam_width}):\n")
for i, (sentence_tokens, prob) in enumerate(final_sentences):
    sentence = " ".join(sentence_tokens)
    print(f"{i + 1}. Sentence: \"{sentence}\"")
    print(f"   Probability: {prob:.4f}\n")