def new_game():
	guesses = []
	correct_guesses = 0
	question_num = 1
	
	for key in questions:
		print("----------")
		print(key)

		for i in options[question_num - 1]:
			print(i)

		guess = input("Enter A, B, C, D: ").upper()
		guesses.append(guess)

		correct_guesses += check_answer(questions.get(key), guess)
		question_num += 1

	display_score(correct_guesses, guesses)

	score = int(correct_guesses / len(questions) * 100)
	print("your score is " + str(score) + "%")


def check_answer(answer, guess):
	if answer == guess:
		print("correct!")
		return 1
	else:
		print("wrong!")
		return 0


def display_score(correct_guesses, guesses):
	print("----------")
	print("results")
	print("----------")

	print("answers: ", end = "")

	for i in questions:
		print(questions.get(i), end = " ")
	print()

	print("guesses: ", end = "")

	for i in guesses:
		print(i, end = " ")
	print()

	
def play_again():
	resp = input("Do you want to play again? (yes/no)").lower()

	if resp == "yes":
		return True
	else:
		return False



questions = {
	"Who created Python?" : "A",
	"What year was Python created?" : "B",
	"Python is tributed to which comedy group?" : "C",
	"Is the Earth round?" : "A"
}

options = [
	["A. Guido van Rossum", "B. Elon Musk", "C. Bill Gates", "D. Mark Zuckerburg"],
	["A. 1989", "B. 1991", "C. 2000", "D. 2016"],
	["A. Lonely Island", "B. Smosh", "C. Monty Python", "D. SNL"],
	["A. True", "B. False", "C. sometimes", "D. What's Earth?"]
]

new_game()

while play_again():
	print()

	new_game()

print("Bye!")