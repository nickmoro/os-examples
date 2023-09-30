import random

N = 100_000

with open("test.txt", "w") as f:
    f.write(str(N) + "\n")
    for i in range(N):
        if i % 100_000 == 0:
            print(str(i / 1_000_000) + " millions")
        f.write(str(random.randint(1, 2**30)) + " ")
