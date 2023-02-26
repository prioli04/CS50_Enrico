# TODO

gap_size = 2    # Defines the middle gap size

while True:
    print("Height: ", end="")

    try:
        height = int(input())

    except ValueError:    # Handles a non-integer input
        height = 0

    if height < 1 or height > 8:    # If outside the [1,8] range, reprompts the user for a valid height
        pass

    else:                        # If a valid height was given, break from the while loop
        break
# Prints the pyramid
for i in range(height):
    spaces = " " * (height - i - 1)
    blocks = "#" * (i + 1)
    print(spaces + blocks + " "*gap_size + blocks)