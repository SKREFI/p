from copy import deepcopy as dc


l = [1, 2, 3]
l2 = [*l, 4, 5]


l2[0] = 3

print(l2)
