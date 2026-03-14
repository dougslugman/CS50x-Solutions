import cs50, sys
money = [25, 10, 5, 1]
cont = True
while cont == True:
    change = cs50.get_float("change: ")
    if change > 0:
        change*=100
        change = int(change)
        cont = False
coincount = 0
currentcoin = 0
while currentcoin < len(money):
    if change - money[currentcoin] < 0:
        currentcoin+=1
        continue
    else:
        change -= money[currentcoin]
        coincount+=1
print(coincount)
