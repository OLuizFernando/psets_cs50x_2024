def luhns_algorithm(number):
    every_other_digit = []

    # iterates alternately starting with the second-to-last digit
    for i in range(2, len(number) + 1, 2):

        # checks if the number has more than 2 digits
        if int(number[-i]) * 2 < 10:
            # multiply the number by 2
            every_other_digit.append(int(number[-i]) * 2)

        # if it has more than 2 digits, the digits will be appended to the list separately
        else:
            # multiply the number by 2 and append the digits separately
            every_other_digit.append(int(str(int(number[-i]) * 2)[0]))
            every_other_digit.append(int(str(int(number[-i]) * 2)[1]))

    result = sum(every_other_digit)

    # now let's add to "result" every digit that weren't multiplied by 2
    for i in range(1, len(number) + 1, 2):
        result += int(number[-i])

    if result % 10 == 0:
        return True

    else:
        return False


# prompt the user for a number and auto corrects blank spaces, dashes and periods
number = input("Number: ").replace(" ", "").replace("-", "").replace(".", "")
while not number.isnumeric() or int(number) < 0:
    number = input("Number: ").replace(" ", "").replace("-", "").replace(".", "")

valid = luhns_algorithm(number)

# American Express: 15 digits and starts with 34 or 37
is_amex = len(number) == 15 and (int(str(number)[0:2]) == 34 or int(str(number)[0:2]) == 37)

# MasterCard: 16 digits and starts with 51, 52, 53, 54 or 55
is_mastercard = len(number) == 16 and (int(str(number)[0:2]) >= 51 and int(str(number)[0:2]) <= 55)

# Visa: 13 or 16 digits and starts with 4
is_visa = (len(number) == 13 or len(number) == 16) and int(str(number)[0]) == 4

if valid:
    if is_amex:
        print("AMEX")
    elif is_mastercard:
        print("MASTERCARD")
    elif is_visa:
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")
