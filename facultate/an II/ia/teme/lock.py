import copy


class State:
    def __init__(self, dimension, maxuses, numberofkeys):
        self.lock = [1] * dimension
        self.usesleft = [maxuses] * numberofkeys
        self.history = []

    def __eq__(self, other):
        return self.lock == other.lock and self.usesleft == other.usesleft and self.history == other.history

    def __str__(self):
        return f"Lock:{self.lock} Uses:{self.usesleft} History:{self.history}"

    def getchildren(self, keylist, trickdict):
        childrenlist = []
        for key_index in range(len(keylist)):                       # every key can be applied, to spawn a new child
            if not self.usesleft[key_index]:
                continue
            child = copy.deepcopy(self)
            child.usesleft[key_index] -= 1
            child.history.append(key_index)
            applykey(child.lock, keylist[key_index], trickdict)
            if child.lock == self.lock:                             # if the lock didnt change
                continue
            childrenlist.append(child)
        return childrenlist


def applykey(lock, key, trickdict):
    for i in range(len(key)):                                       # first apply all tricks
        if i in trickdict.keys() and key[i] == -1:
            lock[trickdict[i]] += 1
    for i in range(len(key)):                                       # then apply the actual key
        lock[i] = max(0, lock[i] + key[i])


def readfile():
    with open('lock.in') as f:
        k = int(f.readline())
        dim = int(f.readline())
        trickdict = {}
        keylist = []

        line = f.readline()
        while line:
            if '->' in line:
                trigger, affected = int(line.split('->')[0].strip()), int(line.split('->')[1].strip())
                trickdict[trigger] = affected
            else:
                keylist.append(tuple(map(lambda char: {"d": -1, "g": 0, "i": 1}[char], line.strip())))
            line = f.readline()

        return k, dim, trickdict, keylist


def heuristic(openstates):
    """
    The heuristic used by A* to determine the next step/state.
    Here simply the one with the smallest sum over the lock is chosen (the closest to beeing open).
    """
    current_sum = -1
    current_index = -1
    for state_index in range(len(openstates)):
        if sum(openstates[state_index].lock) < current_sum or current_sum == -1:
            current_index = state_index
            current_sum = sum(openstates[state_index].lock)
    return openstates.pop(current_index)


def astar(root, keys, tricks):
    openstates = [root]                                             # States to explore
    closedstates = []                                               # Explored States

    while openstates:                                               # While there are still states to explore...
        working_state = heuristic(openstates)                       # ...pick one according to the chosen heuristic
        if sum(working_state.lock) == 0:                            # If the lock is open...
            print("Finished A-Star")
            print(f"Explored states: {len(closedstates) + 1}\n")
            return working_state.history
        children = working_state.getchildren(keys, tricks)          # Get all possible children/key applications ....
        for child in children:
            if child not in closedstates:
                openstates.append(child)                            # ...and add them to be explored
        closedstates.append(working_state)                          # This state is now explored

    return None                                                     # If no more states to explore => there is no solution


def printsolution(sol, keys, tricks, dim):
    if sol is None:
        print("No Solution Possible")
        return
    lock = [1] * dim
    print(f"Initial Lock: {lock}")
    for sol_index in range(len(sol)):
        print(f"Step {sol_index + 1}:")
        print(f"\tApply Key #{sol[sol_index]}: {keys[sol[sol_index]]}")
        applykey(lock, keys[sol[sol_index]], tricks)
        print(f"\tResulting Lock: {lock}")


if __name__ == '__main__':
    maxuse, n, trick_dict, key_list = readfile()
    rootstate = State(n, maxuse, len(key_list))
    solution = astar(rootstate, key_list, trick_dict)
    printsolution(solution, key_list, trick_dict, n)
