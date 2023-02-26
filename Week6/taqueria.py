def main():

    items = {
            "Baja Taco": 4.00,
            "Burrito": 7.50,
            "Bowl": 8.50,
            "Nachos": 11.00,
            "Quesadilla": 8.50,
            "Super Burrito": 8.50,
            "Super Quesadilla": 9.50,
            "Taco": 3.00,
            "Tortilla Salad": 8.00
            }

    total = 0.0


    while True:

        try:
            item = input()

        except EOFError:
            print("Total: ${:.2f}".format(total))
            break

        keys = items.keys()

        if item.title() not in keys:
            print("Item not found!")
            print("\nAvailable items:")
            for key in keys:
                print(key)

        else:
            total += items[item.title()]
            print("When finished, exit with Ctrl+D!")

main()