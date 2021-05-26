from GA import fitness, newChromosome, mutation, crossover, bestFits, lottery, GARunner

print("--- Testing newChromosome ---")
new_chromosome = newChromosome()
print(new_chromosome)
print(len(new_chromosome))
print()

print("--- Testing mutation ---")
print(mutation(new_chromosome))
print(len(new_chromosome))
print()

print("--- Testing crossover ---")
newer_chromosome = newChromosome()
print("Newer chromosome: " + newer_chromosome)
result = crossover(new_chromosome, newer_chromosome, True)
print("Child1: " + result[0])
print("Child2: " + result[1])
print(len(result[0]))
print(len(result[1]))
bit = int(result[2])
original1 = str()
original2 = str()
for index in range(0,32):
    if index <= bit:
        original1 += result[0][index]
        original2 += result[1][index]
    else:
        original1 += result[1][index]
        original2 += result[0][index]
print(original1 == new_chromosome)
print(original2 == newer_chromosome)
print()

print("--- Testing bestFits ---")
pop = []
for x in range(10):
    pop.append(newChromosome())
print(pop)
print(bestFits(pop,25))
print(bestFits(pop,75))
print()

print("--- Testing lottery ---")
print("Testing 10111101010011000010101101110000")
print(fitness('10111101010011000010101101110000', 60))
print("444 // 10 = " + str(444//10))
print(len(lottery(['10111101010011000010101101110000'], 60)))
print("Testing 11101011001001101100010001001110")
print(fitness('11101011001001101100010001001110', 60))
print("286 // 10 = " + str(286//10))
print(len(lottery(['11101011001001101100010001001110'], 60)))
print("28 + 44 = " +str(28+44))
print(len(lottery(['11101011001001101100010001001110','10111101010011000010101101110000'],60)))
print()

print("--- Testing bestFits (empahsis on the plurality!) extension ---")
print(bestFits(pop,400,3))
print(len(bestFits(pop,1,1)))
print(len(bestFits(pop,400,10)))
print(len(bestFits(pop,400,11)))
print()

print("--- Testing rankFits ---")
def rankFits(lst,key):
    for agent in lst:
        print(fitness(agent,key))
rankFits(bestFits(pop,200,3),200)

print("--- Testing GARunner ---")
print(GARunner(20,15,5,2,3,5,300))
