import random

choices = ["rock", "paper", "scissors"]

while True:
	computer = random.choice(choices)

	player = None


	while player not in choices:
		player = input("rock, paper, scissors?: ")

	print()


	print("computer: ", computer)
	print("player  : ", player)
	print()

	if player == computer:
		print("Tie!")
	elif player == "rock":
		if computer == "paper":
			print("Lose!")
		else:
			print("Win!")
	elif player == "paper":
		if computer == "scissors":
			print("Lose!")
		else:
			print("Win!")	
	else:
		if computer == "rock":
			print("Lose!")
		else:
			print("Win!")

	player_again = input("Play again? (yes/no): ").lower()

	if player_again != "yes":
		break

print("Bye!")