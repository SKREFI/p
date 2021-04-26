def knapsack_b(filestream, solution=0):
    capacity = int(filestream.readline())                                                    # 1st: k
    while True:
        try: temp = int(filestream.readline())                                               # 2nd: temp
        except: break
        solution = max(solution, temp) if solution + temp > capacity else solution + temp    # 3rd: solution
    return solution


if __name__ == "__main__":
    print("Solution:", knapsack_b(open("knapsack_b_data.in")))