import random
from faker import Faker

fake = Faker()

with open("in", "w+", encoding='utf-8') as f:
    for i in range(50):
        f.write("i\n")
        f.write(str(random.randint(1, 5)) + "\n") # key
        f.write(fake.first_name() + "\n") # content
    f.write('e\n')

