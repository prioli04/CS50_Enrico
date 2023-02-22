import pyfiglet
import random
import sys

# Checks the number of command line arguments
if len(sys.argv) not in [1, 3]:
    sys.exit('Invalid usage')

# If expected number of arguments
else:
    fonts = pyfiglet.FigletFont.getFonts()

    # If no arguments, print in a random font
    if len(sys.argv) == 1:
        n_fonts = len(fonts)
        n_rand = random.randint(0, n_fonts - 1)
        font = fonts[n_rand]
        text = input("Escreve ai!:")
        pyfiglet.print_figlet(text, font)

    else:
        mode = sys.argv[1]
        font = sys.argv[2]
        # Check the selected mode
        if mode not in ['-f', '--font']:
            sys.exit('Invalid usage')

        # Check if the font selected is valid
        elif font not in fonts:
            sys.exit('Invalid usage')

        else:
            text = input("Escreve ai!:")
            pyfiglet.print_figlet(text, font)