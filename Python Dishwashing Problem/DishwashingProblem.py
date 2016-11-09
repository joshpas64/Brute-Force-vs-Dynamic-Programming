###Dynamic Programming Approach

##Here we go
##n items with individual value v and weight w
##max weight of W
##vals = sums of all v's taken'
##maximize vals but dont go over W
##
##
##My understanding is from this lecture slides
##url:   http://www.es.ele.tue.nl/education/5MC10/Solutions/knapsack.pdf
##So to start you make a 2d array with dimensions [values][constraint range] table V
##in classic knapsack it is [value] [weight all the way to weight W]
##W is constraint
##First make V[0][w] = 0 for all w's in range W'
##There are two tables whose indexes corresponding to each other
##item p = [list of values]
##item wt = [list of weights]
##for e in range(1,n):
##    for j in range(0,W):
##        make V[i][w] = max(V[i-1][w], v[e] (#individual val of i) + V[i-1][w - w[e]])
##        so first argument argues for leaving file alone, keeping the current w where it is, leaving room for better items
##        second argument argues for taking the items increasing the current value by the value of said item but decreasing available weight left
##        by the weight of that item
##
##
##Example Cases Make this much clearer
##
##W = 10
##vals = [10,40,30,50]
##wgt = [5,4,6,3]
##i is range(5) = 0,1,2,3,4
##Table
##V[i][w]   0 1 2 3  4  5   6  7  8  9 10
##    i = 0 0 0 0 0  0  0   0  0  0  0  0  
##        1 0 0 0 0  0  10 10 10 10 10 10
##        2 0 0 0 0  40 40 40 40 40 50 50
##        3 0 0 0 0  40 40 40 40 40 50 70
##        4 0 0 0 50 50 50 50 90 90 90 90
##Psuedocode for finding optimum value only
##def knapsack(vals,n,wght,W):
##    ## n x n table
##    V = []
##    for i in range(n):
##        V.append([])
##    for i in range(W+1):
##        V[0][i] = 0 
##    for i in range(1,n+1):
##        for e in range(W+1):
##            if(wght[e] <= e): if 
##                V[i][e] = max(V[i - 1][e], vals[e] + V[i-1][w-wght[e]])
##            else:
##                V[i][e] = V[i-1][e]
##    return V[n][W]
## Brute force complexity time
## nCk
##  n!
##(k!)(n-k)!
## so it goes n * n - 1 * n-2 * ... * k * k-1 * .. * 1
## a lot gets cut out because the bigger denominator (k) or (n-k) gets cut out of the top n! factorial
## that n! gets cut down even further by the smaller denominator
## so with whatever is larger k or (n-k) time complexity
## so if k = 3 n = 14 n - k = 11
## 14! gets reduced to 14 * 13 * 12 / (3 * 2)
## this would be approximately (14^3)/3!
## making complexity n^(min(k,n-k))/(min(k,n-k)!
## Polynomial time complexity
## For 14 and 3 or 11 it would be 14^3 approximately, cubic time growth
## Worst case would be if k, and n - k are very close either the half or close to it
## To continue n = 14 k = 7 n-k = 7
## Makes time complexity 14*13*12*11*10*9*8/7!
## approaches somewhere to n^(convert to int(n/2))/k!
## Probably cause of approximation error to be n^(n/2 - 2)
## Still pretty bad for large n's used with certain k's
##how do i apply this to the dish problem
##so function arguments are definitely k, n, deduct list, gain list
##what would table look like
##difference which is key is that the washer must always wash k plates no less
##i is range(n+1): 0,1, ... , n,n+1 (the rows)
##what would cols be?
##what is a clean way to implement the choosing structure to denote value and loss?
#example n = 4 k = 2 deduct = [3,18,8,10] ways to deduct 
# vals = [12,43,32,22]
# sum of deduct is 39
# current profit = 0
# max deduct is 39 
# 39 36 21 31 29 
# starting weight is 0 to lim W
# maybe start from sum of deduct list choosing no plates and go from there
# for each value you pick add the val from gains and sub the index (39) from losses
# add vals together? in total 6 ways 12 + (-39 + 3) -24 + 43 + 18
# n**2
##
##          +15 +61 +40 +32 Table makes it more obvious now that the best is index 1 and 2
##      -24  n   37           
##      +22      n
##      +01           n       
##      -07               n   39-26 = 14
## -39 + 18 + 8 
##Calculations: 
##    12 + 43 = 55 - 18 = 37 
##    12 + 32 = 44 - 28 = 16
##    12 + 22 = 34 - 26 = 6  -24 - 7 = -31 + 39 = 6
##    43 + 32 = 75 - 13 = 62 22+1 +18 +8  = 23 + 39 = 64
##    43 + 22 = 65 - 11 = 54
##    32 + 22 = 54 - 21 = 43
###lets try 3 = k
##        +15 +61 +40 +32 at k = 2 index 1 and 2 are best two choices but where now is it index 3 the third base??
##    -24
##    +22
##    +01
##    -07
##
##Lets check, starting from beginning,
##subset 4,3 [1,2,3,4]== [[1,2,3],[1,2,4],[1,3,4],[2,3,4]]
##    12 + 43 + 32 = 87 - 10 = 77    -1 + 
##    12 + 32 + 22 = 76 - 18 = 58 
##    12 + 43 + 22 = 77 - 8 = 69
##    43 + 32 + 22 = 97 - 3 = 94
##hmmmmmmm
##Perhaps application of this algorithm could be this alternative




## Simple Iterative Version of the Dishwashing problem from HackerRank
## Dishwasher has n plates but can only wash k of them ( 0 < k < n)
## Each plate has a payment of x dollars if it washed
## Same plate has a deduction of y dollats if it isnt washed
## Not necessarily a knapsack problem because it is in dishwasher's
## best interest to always wash k plates but it's just which ones to choose
## plates n
## gainslist = x[] 
## losslist = y[]
## Each index in gainslist will correspond to the index in loss list
## Meaning plate in index 3 (4th plate) has a gain of gainslist[3] == persay 43 dollars (If he washes this plate he'll be paid 43 dollars)
## Also plate in index3 of losses will have a loss value of losslist[3] == persay 12 dollats (If he doesnt wash this plate he'll be deducted 12 dollars at the end of the day)
## So for plate 3, dishwasher could choose plate 3 and gain 43 dollars or not choose it, to choose another plate, but have 12 dollars deducted from his paycheck at the end


def getMax(profits,length): ## Returns Max Value and index of the highest value in a list, ## Length is given
    print(length)
    currentMax = profits[0] ## Set defaults
    index = 0
    for i in range(length):
        if(profits[i] > currentMax): ##If item in list is higher than the current maximum
            currentMax = profits[i] ##Set the new maximum
            index = i ##Set the new maximum index
    return currentMax, index
def findMax(n,k,gains,losses): ###Main function to solve problem, if using built in sorting isnt allowed
##n ** k time complexity, fairly poor still
    profitlist = [] ##Profits for each index
    count = n ##initialize for while loop
    deductions = sum(losses) * -1 ##Basically the sum of all deductions, relevance shown later
    totalMax = 0 ##initialize max paycheck
    for i in range(n): 
        profit = (gains[i] + losses[i] + deductions) ##Total profit choosing just 1 plate is its gains value + (deductions + plate's loss value)
        profitlist.append(profit)                    ## Since when chooosing a plate it also means you wont have its deduction value docked from pay
    while(count > (n-k)): ##Depending on how large k ..... (n-k) because loop must iterate k times but length of each profitlist must be decremented from n
        currentMax, e = getMax(profitlist,count) ##Get Max value and index
        profitlist.remove(profitlist[e]) ##Remove that value from list
        totalMax += currentMax ##Increment
        count = count - 1  ##Decrement
    totalMax += (deductions*-1*(k-1)) ##Basically if k is greater than 1 add an extra deduction value * (k - 1) to compensate for being able to choose more than 1 plate
    ## Because subtracting the deduction total from the gains to create the initial profit list was for the case of choosing only 1 plate, the deduction obviously gets
    ## smaller as you can choose more
    ## Note this only give the maximum value not which plates to specifically choose
    return totalMax
def findMaxwSort(n,k,gains,losses): ##n time complexity but thats not include time it takes to sort
    profitlist = []
    deductions = sum(losses) * -1
    totalMax = 0 ##All same find max
    for i in range(n):
        profit = gains[i] + losses[i] + deductions
        profitlist.append(profit)
    profitlist.sort()
    profitlist.reverse() ##Now that range is sorted only have to add profits from range k of the profitlist
    for e in range(k): 
        totalMax = totalMax + profitlist[e]
    totalMax += (deductions*-1*(k-1)) ##Value correction for k's > 1
    return totalMax

n = 4
k = 2
gains = [12,43,32,22]
losses = [3,18,8,10]
print(findMaxwSort(n,k,gains,losses))

        
    
      
      
    
    
    

