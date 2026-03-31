import cs50

# get text from user
text = cs50.get_string("Text: ")

# calculate number of words, letters & sentences in the text
num_words = 1
num_letters = 0
num_sentences = 0
for char in text:
    if char == " ":
        # end of word
        num_words += 1
    elif char in ['.', '?', '!']:
        # end of sentence
        num_sentences += 1
    elif char.isalpha():
        # valid letter
        num_letters += 1
    else:
        # nothing here
        continue

# calculate L
L = (num_letters * 100) / num_words

# calculate S
S = (num_sentences * 100) / num_words

# calculate index and round
grade_level = round((0.0588 * L) - (0.296 * S) - 15.8)

# determine grade
if grade_level < 0:
    print("Before Grade 1")
elif grade_level >= 16:
    print("Grade 16+")
else:
    print(f"Grade {grade_level}")
