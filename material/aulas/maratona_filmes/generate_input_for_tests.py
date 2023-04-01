import subprocess
import os

numbers_of_movies = [10, 20, 25, 30, 40, 50, 60, 70, 80, 90, 100, 200]
numbers_of_categories = [3, 4, 6, 8, 10]

list_of_tests = []
for n in numbers_of_movies:
    for m in numbers_of_categories:
        list_of_tests.append((n, m))


def generate_input_for_tests():
    print("Generating input for tests...")

    if not os.path.exists("data"):
        os.makedirs("data")
        
    for test in list_of_tests:
        subprocess.run(
            ["./gerador", str(test[0]), str(test[1]), "./data/input-{}-{}.txt".format(test[0], test[1])],
            capture_output=True,
        )

    print("Done! :)")

if __name__ == "__main__":
    generate_input_for_tests()

