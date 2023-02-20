prize = [0, 20, 100]
greeting = input('Greeting: ')
greeting = (greeting.lstrip()).lower()

if greeting.startswith('hello'):
    print(f'${prize[0]}')

elif greeting.startswith('h'):
    print(f'${prize[1]}')

else:
    print(f'${prize[2]}')