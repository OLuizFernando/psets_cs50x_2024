import re

text = input("Text: ")


words = len(text.split())
sentences = len(re.split("[.!?]", text)) - 1
letters = 0

for word in text.split():
    for letter in word:
        if letter.isalpha():
            letters += 1

l = letters / (words / 100)
s = sentences / (words / 100)

cl_index = round(0.0588 * l - 0.296 * s - 15.8)

if cl_index < 1:
    print("Before Grade 1")
elif cl_index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {cl_index}")
