# TODO
import re


def main():

    print("Number: ", end="")
    card_number_str = input()

    # Checks for an input that is a valid card number format
    if not re.search("\d{13,16}", card_number_str) or len(card_number_str) == 14 or not checksum(card_number_str):
        print("INVALID")
    # Checks for AMEX card
    elif card_number_str[0:2] in ["34", "37"] and len(card_number_str) == 15:
        print("AMEX")
    # Checks for MASTERCARD card
    elif card_number_str[0:2] in ["51", "52", "53", "54", "55"] and len(card_number_str) == 16:
        print("MASTERCARD")
    # Checks for VISA card
    elif card_number_str[0:1] == "4" and len(card_number_str) in [13, 16]:
        print("VISA")
    # If none of the above, must be a fake nunmber
    else:
        print("INVALID")


def checksum(number_str):

    digits_1 = [int(c) for c in number_str[-2::-2]]    # gets every other digit from right to left
    digits_2 = [int(c) for c in number_str[-1::-2]]    # get the rest of the digits

    mult_1 = [str(2 * i) for i in digits_1]            # multiplies digits_1's elements by 2 and cast to str
    concat_1 = "".join(mult_1)                         # concatenates the digits into one str

    sum_1 = sum([int(c) for c in concat_1[::1]])       # split the string into digits and sum them
    sum_2 = sum(digits_2) + sum_1                      # Step 2 of the Lhun's algorithm

    # Step 3: check if last digit is 0
    if sum_2 % 10 == 0:
        return True

    else:
        return False


main()