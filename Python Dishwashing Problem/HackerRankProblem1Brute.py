import RecursivePairs
## Get subset functions from python file and use typedef equivalencies below to write them more easily
mapSet = RecursivePairs.mapPowerSet
subset = RecursivePairs.subset
### Total plates = n
### Can only wash k plates k < n
### Must wash k plates no less
### list1 is profits
### list2 is negations
### Each plate has both
## Either you can wash and get its profit
## Or not wash,choosing another, but being docked a negation for missing it
### Find optimal k plates to wash to maximize paycheck
## Brute Force via Subsets

##So lets do this
##make an index subset representing all the ways you can pick k plates from a
##total of n
##i.e k = 2 n = 4 means 6 ways to arrange them, assuming their profits or negations
##are different.
##so plates [1,2,3,4]
##can be arranged [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
##from each subset calculate net value by
##for example
##profits = [10,23,15,12]
##negations = [2,5,7,4]
##choosing [1,2] also means you didnt choose [3,4]
##so you add profits[0] (1st index) + profits[1] (second index)
##then subtract negations[2] (3rd index) and negations[3] (fourth index)

n = 2
k = 1
profits = [10,5]
losses = [5,1]

def findMissing(base,sub): ##finds missing items that are in base but no in sub
    missing = [] #initialize
    for i in range(len(base)): #for each item in base
        marked = 0 ##assumes its not in sub
        for e in range(len(sub)): ##Iterate through sub
            if(base[i] == sub[e]): #If element in base is in sub
                marked = 1 ##Set marked to 1 (FOUND) and break out of loop
                break
        if(marked == 0): ##If the whole sub list was iterated through without a match, add it to the list of missing items
            missing.append(base[i])
    return missing
def findMax(profits): ##Finds maximum value in a list
    high = profits[0]
    for i in range(len(profits)):
        if(profits[i] > high):
            high = profits[i]
    return high
def makePossibilities(constraint, total, gains, losses): ##Takes n plates, k limit, gains list, deductions list as args
    indexList = [] 
    for i in range(total):
        indexList.append(i)
    arrangements = subset(indexList, constraint) ##Make a list containing all combinations that can be made of length k from a base set of length n (usually k < n)
    pairLists = [] ##List containing profits (gains - losses) of each combination
    for i in arrangements:
        pair = [] ##Dishes chosen
        profit = 0
        loss = 0
        forgotten = [] ##Dishes not chosen
        for e in range(constraint):
            profit = profit + gains[i[e]] ## Add up gains of  each plate
        forgotten = findMissing(indexList,i) ##find the indexes of the plates that were not chosen for this combination
        for e in range(total - constraint): ## Number of plates not chosen
            loss = loss + losses[forgotten[e]] ##add the losses of each plate not chosen
        pair.append(profit)
        pair.append(loss)
        pairLists.append(profit - loss) ##Add profit to list
    return pairLists
        
print(findMax(makePossibilities(2,4,[10,23,54,22],[9,3,12,11])))                         
