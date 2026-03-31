import cs50

# get input from user
height = cs50.get_int("Height: ")

while (height < 1 or height > 8):
    # reprompt
    height = cs50.get_int("Height: ")

for h in range(1, height + 1):
    # print leading spaces
    for spaces in range(height - h, 0, -1):
        print(" ", end="")

    # print left hashes
    for hashes in range(h):
        print("#", end="")

    # print middle two spaces
    print("  ", end="")

    # print right hashes
    for hashes in range(h):
        print("#", end="")

    # move to next line
    print()
