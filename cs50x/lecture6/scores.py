scores = []
for _ in range(3):
    score = int(input("Score: "))
    scores.append(score)

average = sum(scores) / len(scores)
print(f"Averages: {average}")
