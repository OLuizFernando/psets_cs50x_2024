from cs50 import get_float

coins = 0
change = get_float("Change: ")

while change < 0:
    change = get_float("Change: ")

change *= 100

while change // 25 > 0:
    coins += 1
    change -= 25

while change // 10 > 0:
    coins += 1
    change -= 10

while change // 5 > 0:
    coins += 1
    change -= 5

while change // 1 > 0:
    coins += 1
    change -= 1

print(coins)
