from sys import argv

if len(argv) == 2:
    name = argv[1]
    print(f"hello, {name}")
else:
    print("hello, world")
