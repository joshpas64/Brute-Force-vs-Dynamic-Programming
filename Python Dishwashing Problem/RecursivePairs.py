##[1,2,3,4]
##[[],[1],[2],[3],etc]
## EX 0, 1 0,2 0,3 0,4 1,2 1,3 1,4 2,3 2,4 3,4 re
m = [1,2,3,4,5]
##Powerset or Subset examples
## 1,2 1,3 1,4 1,5 2,3 2,4 2,5 3,4 3,5 4,5
## 1,2,3 1,2,4 1,2,5 1,3,4 1,3,5 1,4,5 2,3,4 2,3,5 2,4,5 3,4,5
## 1,2,3 2,3,4 3,4,5
## 1,2,3,4 1,2,3,5 1,2,3,6 1,2,4,5 1,2,4,6 1,2,5,6 1,3,4,5 1,3,4,6 1,3,5,6 1,4,5,6 2,3,4,5 2,3,4,6 2,3,5,6 3,4,5,6
def mapPowerSet(data): ##Maps the index representations of a powerset to a specific list i.e. find the powerset of a = ['a','b','c','d']
    rangeSet = []
    for i in range(1,len(data) + 1):
        rangeSet.append(i)
    pSet = powerSet(rangeSet) ##Make an index list and get powerset of it
    for i in range(len(pSet)):
        if(pSet[i] == []):
            pass
        else:
            for e in range(len(pSet[i])): ##reassign all index's in the powerSet with index's with in data
                pSet[i][e] = data[pSet[i][e]-1]
    return pSet
## i.e. data = ['a','b','c','d']
## one subset in powerset is [0,2] which will be turned into ['a','c']           
def powerSet(lists): ## Creates a powerset of index ranges i.e. create a way to arrange a list of length of 4
    pSet = []
    ctr = len(lists)
    start = 0
    while(start <= ctr): 
        for i in subset(lists,start): ##Append each subset to the powerset ranging from 0 to the length of lists
            pSet.append(i)
        start = start + 1
    return pSet
        
def subset(lists,size):
    if(size == 0):
        return [[]] ##empty set
    totalSet = []
    start = []
    for i in range(0, size): ##Starting subset which will be first size indexes of lists
        start.append(i)
    orig = []
    for e in range(0,len(lists)): ##Reference Set of the original you want to Make subsets of
        orig.append(e)
    state = continueSubset(orig,lists,start,size) ##Generate the next subset of length(size) in the sequence
    totalSet.append(start) ##Add to the total amount of subsets of length size
    a = state[1] ## Determines if there are any more subsets left to find
    while(a == True): ##While there are still subsets to add
        totalSet.append(state[0]) ##Add to the totalSet of subsets
        state = continueSubset(orig,lists,state[0],size) ##Use that subset and pass it to continue to find the next subset and if there are any more to find after that
        a = state[1] ##New continue value 
    return(totalSet)
 
def continueSubset(orig,lists,array,length):
    n = [] ##Initialze subset
    if(array[0] == len(orig) - length): ##If this is the last subset of lists that can be made of size length, return it and give a False value to indicate its end
## To tell this is if the first element in the current subset is last one to make different arrangements for (remember with powersets order DOESNT MATTER)
## Example l = [0,1,2,3,4,5,6] so last subset in sequence would be [4,5,6] making the last first index to be 4 which is len(l) 7 - length 3 = 7-3 = 4
        return [array,False]
    else:
        marker = len(array) -1 ##This variable is used to mark where to start to change the subset to make the new subset
        bound = len(orig) - 1 ##To account for 0 based indexing
        if(array[marker] < orig[len(orig)-1]): ##if the last value of the current subset is still less than the last value of the original set skip to for loop
            pass
        else: ##For more unconventional combination of size:length like [1,3,4]
            marker = marker - 1 ## Decrement
            while(array[marker] >= orig[bound - 1]): ##Backwards iterate through both lists and compare
                ##if the subsets value is greater than the original's
                ## decrement both until it is less than
                ##Basically find the highest index where that value can still be incremented but not be higher than the length of the original list
                ## [1,2,3,4] k = 3 current = [1,2,4] since the last index value (4) is at its max the new new marker is index 1 (2nd item) of current
                ## so marker is now 1
                ## For current = [1,3,4] since last index value (4) is equal to the original lasts index value (4) AND the second to last index value (3) is ALSO
                ## equal to the original second to last index value (3) marker must be 0 since current[0] = 1 and original[originalslength - 2] = 2 and 1 is not greater
                ## than 2
               marker = marker - 1
               bound = bound - 1
        for i in range(length):
            if(i < marker):
                n.append(array[i]) ##Keep all indexes of below marker the same 
            elif(i == marker): ## At marker increment that value by 1
                newVal = array[i] + 1
                n.append(newVal)
            else:
                newVal = n[i-1] + 1 ##From after marker, make each value an incrementation of the previous index vale
                n.append(newVal)
        return [n,True] ##Since it passed first if statement, return the subset and make the continue mark equal to True, so the function that calls continueSubset
                        ##knows that it still has subsets left to generate

