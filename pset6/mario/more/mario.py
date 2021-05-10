def construct_pyramid():
    try:
        height = int(input("What is the height of the pyramid that you want?\n"))
        if 1 <= height <= 8:
            for i in range(1, height+1):
                for h in range(height - i, 0, -1):
                    print(" ", end='', sep='')
                for j in range(1, i+1):
                    print("#", end='', sep='')
                print("  ", end='', sep='')
                for k in range(1, i+1):
                    print("#", end='', sep='')
                print("\n", end='', sep='')
        else:
            construct_pyramid()
    except:
        construct_pyramid()

def main():
    construct_pyramid()

if __name__ == "__main__":
    main()