def solve(first, second):
    return any([(lambda p, m: any([a == b for (a, b) in [*zip(p, m)]]))(x, y) for (x, y) in [*zip(first, second)]])


if __name__ == '__main__':
    print(solve([[1,2,3],[1,2,3],[1,2,3]], [[7,8,9],[7,8,9],[7,8,3]]))