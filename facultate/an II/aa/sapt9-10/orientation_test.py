# def readPair():
#     return (int(input()), int(input()))
# rp = readPair()

# p, q, r = rp, rp, rp
p, q, r = (2, 3), (1, 1), (0, 0) # right
p, q, r = (3, 3), (1, 1), (0, 0) # coliniare
# p, q, r = (2, 3), (1, 1), (1, 0) # left

def determinant(first, second):
    print(first[0], first[1], second[0], second[1])
    return (first[0] * second[1]) - (first[1] * second[0])

def TminusT(firstTupleOf2, seconTupleOf2):
    return (firstTupleOf2[0] - seconTupleOf2[0], firstTupleOf2[1] - seconTupleOf2[1])

def result(choice):
    if choice == 0:
        return "Coliniare"
    if choice < 0:
        return "Left"
    return "Right"

if __name__ == "__main__":
    p = TminusT(p, q) # x1 y2
    q = TminusT(r, q) # x2 y2


    print(determinant(p, q))
    print(result(determinant(p, q)))
























