import csv
import requests


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state


def calculate(reader):
    new_cases, previous_cases = {}, {}

    for row in reader:
        state = row["state"]
        cases = int(row["cases"])

        if state not in new_cases.keys():
            previous_cases.update({state: [cases]})
            new_cases.update({state: [cases]})

        else:
            if len(previous_cases[state]) == 14:
                previous_cases[state].pop(0)
                new_cases[state].pop(0)

            previous_cases[state].append(cases)
            calc_new_cases = previous_cases[state][-1] - previous_cases[state][-2]
            new_cases[state].append(calc_new_cases)

    return new_cases

# TODO: Calculate and print out seven day average for given state


def comparative_averages(new_cases, states):

    for state in states:
        this_week, last_week = 0, 0
        last_week = sum(new_cases[state][0:7]) / 7
        this_week = sum(new_cases[state][7:14]) / 7

        if this_week - last_week < 0:
            dec_inc = "a decrease"

        else:
            dec_inc = "an increase"

        try:
            change = ((this_week - last_week) / last_week) * 100

        except ZeroDivisionError:
            change = "-"

        print(f"{state} had a 7-day average of {round(this_week)} and {dec_inc} of {round(abs(change))}%.")


main()
