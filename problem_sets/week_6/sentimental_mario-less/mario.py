height = str()

while not height.isnumeric() or int(height) <= 0 or int(height) == 9:
    height = input("Height: ")

height = int(height)

for i in range(1, height + 1):
    print(" " * (height - i), end="")
    print("#" * i)
