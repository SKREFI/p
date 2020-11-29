from random import randint
from graphics import *


def randomColor():
    return color_rgb(randint(0, 255),
                     randint(0, 255), randint(0, 255))


class CommandDest():
    def __init__(self, command, destination):
        self.command = command
        self.destination = destination

    def __repr__(self):
        return "{" + self.command + " -> " + self.destination + "}"


class COL:  # formatare text in python
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

    def blue(self, s):
        return self.OKBLUE+s+self.ENDC

    def green(self, s):
        return self.OKGREEN+s+self.ENDC

    def warning(self, s):
        return self.WARNING+s+self.ENDC

    def fail(self, s):
        return self.FAIL+s+self.ENDC

# Returneaza "litere" al limbajului invalide daca gaseste


def invalidCommands(commands, valid_commands):
    invalid = []
    for c in commands:
        if c not in valid_commands:
            invalid.append(c)
    if len(invalid) == 0:
        return None
    return invalid


def BackEnd(startingNode, word, target_list):
    C = COL()           # Initializare clasa culori
    d = {}              # Dictionar in care pun NOD -> {Matrici -> Rezultat}
    valid_comands = []  # Storez toate "literele" limabjului
    all_nodes = []

    with open("nodes.in", "r") as f:
        inp = f.readline().split()
        while inp:
            if inp[2] not in all_nodes:
                all_nodes.append(inp[2])
            if inp[0] not in all_nodes:
                all_nodes.append(inp[0])
            valid_comands.append(inp[1])
            if inp[0] in d.keys():
                c = CommandDest(inp[1], inp[2])
                d[inp[0]].append(c)
            else:
                d[inp[0]] = []
                c = CommandDest(inp[1], inp[2])
                d[inp[0]].append(c)
            inp = f.readline().split()

    vcs = set(valid_comands)                        # Valid Commands Set
    # Keyurile dictionarului reprezinta noduri neterminale
    print(C.blue("Nodes:"), *d.keys())
    # multimea de litere disponibile
    print(C.blue("Valid commands:"), *vcs)
    current = startingNode
    commands = word
    commands = [x for x in commands]
    # Intrucerea mai multor noduri ca "finale" este acceptata
    target = target_list
    if invalidCommands(commands, valid_comands) != None:
        print(C.fail("Invalids commands found:"), *
              invalidCommands(commands, valid_comands))

    # print(d)

    # Pentru vizualizarea optiunilor fiecarui nod (nodurile terminale sunt excluse logic)
    # for c in d.keys():
    #     print(C.blue("Optiuni pentru nodul "), c, sep="", end=":\n")
    #     for obj in d[c]:
    #         print(obj.command, obj.destination, sep=" -> ")

    path = []                           # traseu, optional, dar imi place sa-l vad daca vreau
    for c in commands:                  # pentru fiecare comanda
        commandFound = False            # tinem conta daca gasim pentru afisarea erori
        # pentru fiecare obiect in lista de obiecte in care se poate ajunge din current
        if current not in d.keys():
            return None
        for o in d[current]:
            if c == o.command:          # daca comanda convine
                commandFound = True     #
                current = o.destination       # current devine destinatia comenzii
        if commandFound == False:
            print(C.fail("Command not found"))
            return None
        path.append(current)
    good_word = False
    if current in target:
        good_word = True
    return good_word, path, d.keys(), all_nodes
