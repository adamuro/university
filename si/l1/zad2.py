valid_words = set()
with open("./words.txt", "r") as words_file:
  for word in words_file:
    valid_words.add(word.strip())


def best_sentence(line):
  best_sentences = []
  for i in range(len(line) + 1):
    best_sentences.append([0, ""])
    word = ""
    for j in range(i - 1, max(i - 40, -1), -1):
      word = line[j] + word
      if word in valid_words:
        word_len_sqr = len(word) ** 2
        if best_sentences[j][0] + word_len_sqr > best_sentences[i][0]:
          best_sentences[i] = [best_sentences[j][0] + word_len_sqr, best_sentences[j][1] + " " + word]
  return best_sentences[len(line) - 1][1]

with open("./zad2_input.txt", "r") as f:
    with open("./zad2_output.txt", "w") as out:
        for line in f:
          out.write(best_sentence(line)[1:] + "\n")
