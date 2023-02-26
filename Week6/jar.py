import time

class Jar:
    def __init__(self, capacity=12):
        assert capacity > 0, f"Capacity {capacity} must be a non-negative integer"
        self._capacity = capacity
        self._size = 0

    def __str__(self):
        return u"\U0001f36a" * self._size

    def deposit(self, n):
        self.size = n

    def withdraw(self, n):
        self.size = -n

    @property
    def capacity(self):
        return self._capacity

    @property
    def size(self):
        return self._size

    @size.setter
    def size(self, number):
        new_number = self._size + number
        if new_number < 0 or new_number > self._capacity:
            raise ValueError

        else:
            self._size = new_number


def main():

    jar = Jar()

    while True:
        print(f"\nYour jar is currently with {jar.size} cookies. Maximum: {jar.capacity}")
        print(f"{str(jar)}\n")
        time.sleep(2)
        print("What to do?\n")
        print("Add cookies? Enter 'add' ")
        print("Remove cookies? Enter 'remove' ")
        print("Press enter to exit!\n")

        inp = input()

        if inp.lower().find("add") != -1:
            print("\nHow many cookies to add?")

            try:
                add = int(input())
                jar.deposit(add)

            except ValueError:
                print("You should have entered an integer")

        elif inp.lower().find("remove") != -1:
            print("\nHow many cookies to remove?")

            try:
                remove = int(input())
                jar.withdraw(remove)

            except ValueError:
                print("You should have entered an integer")

        elif inp == "":
            break

        else:
            print("Please input 'add' or 'remove'!")

        time.sleep(2)

main()