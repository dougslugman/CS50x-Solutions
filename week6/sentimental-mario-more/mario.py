cont = True
while cont:
    try:
        height = int(input("Height: "))
    except ValueError:
        continue
    if height > 8 or height < 1:
        pass
    else:
        cont = False
height+=1
for i in range(1, height):
    print((" " * (height - (i + 1))) + ("#" * i) + ("  ") + ("#" * i))


