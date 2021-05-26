import random

def fitness(genome,key):
    seed = 'ztVvDguRAQDaSXXmLeJkUxRejhCGKfRjWDJCwowiSioIwtDqDHwelMnDfsXlhceWgMKXBUbsqlDVvXhpXXgtTjNmdBQfVsacmEvbHxQXodqKLaeFsrwlyMTkvziWPOAbgDjMXZRpUyrMVRmKhZotMIQtZHuzkvrlpgYgYAjFgOHYhrDquFTKxfargRnZDtISDpvEZqQJgLmRlyJrnqMiampUBMlcyyLqKJypCAiKhFIxuYlZkiYeOtVQCktDJAvgjiickEOvISfiaJqHUjOfuaRpdGFysIgoyXnVbjIVfDQhpgtVDIvHRmRnApMTDFQIPFWLNMkCWoMPgvNCpAFFDIEzxIWAodRAOrErfuTzdbRjMroKhomBBEzvraoKpAMeQXlzantpvUhWPNNCodmpJaThVTFYevCCwVahUpUncRDKpWhoogIUcpBcSSudgHrsIjQAcNjWFjOITSBWeASqotPMBIjzomMsdWEnyIkrfPgnbnYXgrwfZlNfYyAvBsUxQgVoLnHkWtXaKrGiDjEbJeMcOqTpCzFuSmRhIwPd'
    mult = list(range(-33,0))+list(range(1,33))
    s = 0
    for x in range(len(genome)):
        s+=(ord(seed[x+key])-ord(seed[key-1]))*(mult[int(genome[x])+32])+10
    return s


######################################################
#  Do not change the code above this section
#  Modify the code BELOW this section
######################################################


"""
Part One
Method:  newChromosome() 
Inputs:  None
Outputs: A single, length 32 string of 1s and 0s
"""
def newChromosome():
    chromosome = ""
    for index in range(0,32):
        chromosome += str(random.randint(0,1))
    return chromosome
    

"""
Part Two
Method:  mutation() 
Inputs:  A length 32 string
Outputs: A length 32 string that only differs by one "bit" from the input
"""
def mutation(originalChromosome):
    mutatedChromosome = ""
    bit = random.randint(0,32)
    index = 0
    while index < len(originalChromosome):
        if index == bit:
            if originalChromosome[bit] == "0":
                mutatedChromosome += "1"
            else:
                mutatedChromosome += "0"
        else:
            mutatedChromosome += originalChromosome[index]
        index += 1
    return mutatedChromosome


"""
Part Three
Method:  crossover() 
Inputs:  Two length 32 strings
Outputs: Two length 32 strings that were formed by using a random crossover point
NOTE: Crossover point should be a number from 1-31 and the point should indicate HOW MANY
      characters to take from the front of one string.  Obviously, you would take 32-Crossover point
      characters from the second string
"""
def crossover(orig1, orig2, test = False):
    select1 = ""
    select2 = ""
    bit = random.randint(1,32)
    select1 += orig1[0]
    select2 += orig2[0]
    for index in range(1,32):
        if index <= bit:
            select1 += orig1[index]
            select2 += orig2[index]
        else:
            select1 += orig2[index]
            select2 += orig1[index]
    if test == True:
        return (select1, select2, bit)
    return select1,select2


        
"""
Part Four
Method:  bestFits() 
Inputs:  A list of chromosomes - one population
         The key to be used by the fitness function
Outputs: A single chromsome from the list of chromsomes
         The fitness score for that chromosome
NOTE: The outputs should be the BEST score found in the list of chromosomes
"""
def bestFits(population,key,sample = None):
    bestChromosome=None
    bestScore=-1000
    for agent in population:
        newGenome = agent
        newScore = fitness(agent,key)
        if bestChromosome == None:
            bestChromosome = newGenome
            bestScore = newScore    
        else:
            if newScore > bestScore:
                bestChromosome = newGenome
                bestScore = newScore
    if type(sample) == int:
        #...Not sure if I like duplicating the list considering runtime
        listCopy = list(population)
        if len(listCopy) == 1:
            return [bestChromosome]
        elif sample == 1:
            return [bestChromosome]
        else:
            listCopy.remove(bestChromosome)
            return [bestChromosome] + bestFits(listCopy,key,(sample - 1))
    return bestChromosome,bestScore



"""
Part Five
Method:  lottery() 
Inputs:  A list of chromosomes - one population
         The key to be used by the fitness function
Outputs: A significantly larger list of chromsomes.  
NOTE: The length of the output list is variable depending on the chromsomes in the input
       population and their fitness functions.
       Each chromosome from the input population will likely occur
       multiple times in the output list.
"""
def lottery(population,key):
    outputList=[]
    for agent in population:
        score = fitness(agent,key)
        if score >=10:
            score = score // 10
        for i in range(0,score):
            outputList.append(agent)
    return outputList


"""
Part Six
Method:  GARunner()
Inputs: pSize - an int, the number of chromsomes in each population
        gen - the number of generations for which the GA is run
        sel - the number of members of gen N who automatically pass to gen N+1 (selection)
        mut - the number of members of gen N who are mutated and moved on to gen N+1 (mutation)
        nb  - the number of brand new chromosomes introduced each generation (new blood)
        co  - the number of PAIRS of chromosomes that undergo crossover each generation (crossover)
        key - the key used by the fitness function
Outputs:    bestChromosome - The best length 32 chromsome from the final generation
            bestScore - The fitness value of that best Chromosome
NOTE : sel + mut + nb + 2*co must equal pSize.  If not, you should return "" and -1000 for the output values
"""

def GARunner(pSize,gen,sel,mut,nb,co,key):
    population = []
    bestChromosome=""
    bestScore = -1000
    if (sel + mut + nb + 2*co) == pSize:
        #initial generation is new blood: 
        generation = 0
        for i in range(1,pSize):
            population.append(newChromosome())
            
        bestFit = bestFits(population,key)
        bestChromosome = bestFit[0]
        bestScore = bestFit[1]
        
        generation = 1
        while generation < gen:
            #start new generation based on best fits
            selected = bestFits(population,key,sel)
            
            #incur mutations
            mutated = list()
            for i in range(0,mut):
                choice = random.randint(1,len(population)-1)
                genome = population[choice]
                mutated.append(mutation(genome))
                
            #incur new blod
            newBlood = list()
            for i in range(0,nb):
                newBlood.append(newChromosome())
                
            offspring = list()
            for i in range(0,co):
                choice1 = selected[random.randint(0,(len(selected)-1))]
                choice2 = population[random.randint(0,(len(population)-1))]
                pair = crossover(choice1,choice2)
                offspring.append(pair[0])
                offspring.append(pair[1])
            
            population = selected + mutated + newBlood + offspring
            generation += 1
        return bestFits(population,key)
    else:
        return bestChromosome, bestScore
    

    return bestChromosome,bestScore
 


