import cs50
alphabet = []
sentencenders = ['.', '!', '?']
wordcount = 1
lettercount = 0
sentencecount = 0
for i in range(97, 123):
    alphabet.append(chr(i))
text = cs50.get_string("Text: ")
for i in range(len(text)):
    for j in range(len(alphabet)):
        if text[i].lower() == alphabet[j]:
            lettercount += 1
    for j in range(len(sentencenders)):
        if text[i] == sentencenders[j]:
            sentencecount += 1
    if text[i] == ' ':
        wordcount += 1

ratio = (100.0 / wordcount)
L = (lettercount * ratio)
S = (sentencecount * ratio)
grade = (0.0588 * L - 0.296 * S - 15.8)
grade = round(grade)

if grade < 1:
    print("Before Grade 1\n")
if grade > 16:
    print("Grade 16+\n")
else:
    print(f"Grade {grade}\n")
