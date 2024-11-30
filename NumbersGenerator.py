import numpy as np

random_numbers = np.random.randint(-2**31, 2**31, size=100, dtype=np.int32)

with open("InputTape", "w") as f:
    for number in random_numbers:
        f.write(f"{number}\n")
