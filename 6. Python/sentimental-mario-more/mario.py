while True:
    try:
        height = int(input("Height: "))
        if (height in range(1, 9)):
            break
        continue
    except:
        pass

width = height * 2 + 2
for i in range(height):
    j = 0
    while j < width - height + i + 1:
        if ((j >= height - i - 1) and (j < height)) or ((j >= height + 2) and (j <= width - height + i)):
            print("#", end="")
        else:
            print(" ", end="")

        j += 1
    print()
