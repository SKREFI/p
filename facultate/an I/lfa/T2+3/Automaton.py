from collections import defaultdict
from Logging import Log
from copy import deepcopy as dc

E = ''
F_NODE = 'F'
S_NODE = 'S'


class Automaton():
    def __init__(self, states, alphabet, initial, finals, edges):
        self.states = states
        self.alphabet = alphabet
        self.initial = initial
        self.finals = finals
        self.edges = edges

    def __repr__(self):
        ret = ''
        for k, v in self.edges.items():
            ret += k + ' -> ' + \
                ', '.join(
                    ['(' + edge[0] + ', ' + edge[1] + ')' for edge in v]) + '\n'
        return ret

    def addEdge(self, start_node, letter, destination_node):
        edge = [letter, destination_node]
        if edge not in self.edges[start_node]:
            self.edges[start_node].append(edge)
        else:
            Log.warning(
                f'Treid to add an already existing edge to the node {start_node}')

    def getAllEdges(self):
        edges = []
        for state in [S_NODE] + self.states:
            cse = self.edges[state]
            cse = [[state] + x for x in cse]
            edges.extend(cse)
        return edges

    def __createNewInitialState(self):
        # 2. creating new initial state
        self.addEdge(S_NODE, E, self.initial)
        self.initial = S_NODE

    def __createUniqFinalState(self):
        # 1. pointing finals to a new uniq final state
        for f_state in self.finals:
            self.addEdge(f_state, E, F_NODE)
            # print(f'Found {f_state} with {len(automat.edges[f_state])}. Fixed')
        self.finals = [F_NODE]

    def getAliveStates(self, layer=['F'], total=[]):
        newLayer = []
        for state in self.states:
            if state not in total:
                for edge in self.edges[state]:
                    if edge[1] in layer:
                        newLayer.append(state)
        total.extend(newLayer)
        if len(newLayer) > 0:
            return self.getAliveStates(newLayer, total)
        else:
            return total

    def removeState(self, state):
        try:
            self.states.remove(state)
            self.edges.pop(state)
            for s in self.states:
                for edge in self.edges[s]:
                    if edge[1] == state:
                        self.edges[s].remove(edge)
            Log.succes(f'Removed {state}')
        except Exception:
            Log.fail(
                f'Failed to remove {state}. Probabily not part of the list.')

    def removeDeadStates(self):
        deadStates = list(set(self.states).difference(self.getAliveStates()))
        Log.warning(f'Dead states: {deadStates}')
        for state in self.states:
            i = 0
            while i < len(self.edges[state]):
                if self.edges[state][i][1] in deadStates:
                    self.edges[state].remove(self.edges[state][i])
                else:
                    i += 1
        for state in deadStates:
            Log.succes(f'Removed (dead) {state}')
            self.removeState(state)

    def getPredecessors(self, state):
        ret = []
        for s in [S_NODE] + self.states:
            for edge in self.edges[s]:
                if edge[1] == state:
                    ret.append(s)
                    break
        return ret

    def getSuccessors(self, state):
        return list(set([x[1] for x in self.edges[state]]))

    def sumSelfDirectionEdges(self):
        for state in self.states:
            self_edge = []
            for edge in self.edges[state]:
                if edge[1] == state:
                    self_edge.append(edge)
            for se in self_edge:
                self.edges[state].remove(se)
            self_edge = list(set([x[0] for x in self_edge]))
            if len(self_edge) > 0:
                self.addEdge(state, '(' + ' + '.join(self_edge) + ')', state)

    def __spreadSelfPointingEdge(self):
        ''' No node should have more than one self pointing edge
            We want to remove that edge and add the <cost>* to each outgoing edge 
        '''
        for state in self.states:
            for edge in self.edges[state]:
                # we look for the self pointing one here
                if edge[1] == state:
                    save = edge[0] + '*'
                    self.edges[state].remove(edge)
                    for outgoing in self.edges[state]:
                        outgoing[0] = save + outgoing[0]

    def __moveCostsToNextEdges(self):
        # Final step, remove each state one by one, note S and F are consider "buildin" or "default"
        # and are not part of the autoamt.states
        for state in self.states:
            # for each edge of the current state
            for edge in self.edges[state]:
                # if the edge is not pointing to the final state
                if edge[1] != F_NODE:
                    # we cycle through the destination edge's edges. Hope this aint confusing
                    for next_edge in self.edges[edge[1]]:
                        next_edge[0] = edge[0] + next_edge[0]
                    # Eged price equals to epsilon, we remove it as we have passed the cost it to the next edges
                    edge[0] = E

    def getRegex(self) -> str:
        """ Filtering
        0. Delte dead states
        1. For each finals wich have an outgoing edge, point them
        with E(psilon) (empty string) to a new uniq final state
        2. If initial state has incoming edges, create a new one """

        self.__createNewInitialState()
        self.__createUniqFinalState()
        self.removeDeadStates()
        self.sumSelfDirectionEdges()
        self.__spreadSelfPointingEdge()

        while len(self.states) > 0:
            state = self.states[0]
            for going in [x for x in self.edges[state] if x[1] != state]:
                for coming in [x for x in self.getAllEdges() if x[2] == state]:
                    self.addEdge(coming[0], coming[1] + going[0], going[1])
            self.removeState(state)
            self.__spreadSelfPointingEdge()

        try_it, i = True, 0
        while try_it:
            try:
                if self.edges[S_NODE][i][1] != F_NODE:
                    self.edges[S_NODE].remove(self.edges[S_NODE][i])
                else:
                    i += 1
            except:
                try_it = False

        Log.print(self)

        solution = ''
        for edge in self.edges[S_NODE]:
            if edge[1] == F_NODE:
                solution += edge[0] + ' + '
        solution = solution[:-3]
        return solution

    @classmethod
    def buildFromFile(cls, input_file):
        """ Format:
            Note: Don't use 'F' and 'S' as state names as those will be used as start and final by the system
            Row 1: states splited by a space
            Row 2: alphabet
            Row 3: only one state, the initial one, must be in row one
            Row 4: Finals, all must be included in row one
            Till EOF: edges, having the next format: STATE_ONE part_of_alphabet STATE_TWO
                                            example: 1 a 2
                                            from node 1 to node 2 with 'a' on the edge"""
        with open(input_file, 'r') as f:
            states = [x.strip() for x in f.readline().split(' ')]
            alphabet = [x.strip() for x in f.readline().split(' ')]
            initial = f.readline().strip()
            finals = [x.strip() for x in f.readline().split(' ')]
            if not initial in states:
                raise Exception('Initial state not included in the states')
            if not set(finals).issubset(set(states)):
                raise Exception('Final states list not a subset of states')
            if 'F' in states or 'S' in states:
                raise Exception(
                    'F and S used in the states. Names alocated by the system, please use other names.')
            edges = defaultdict(lambda: [])
            line = [x.strip() for x in f.readline().split()]
            while line:
                edges[line[0]].append([line[1], line[2]])
                line = [x.strip() for x in f.readline().split()]
            return Automaton(states, alphabet, initial, finals, edges)


if __name__ == "__main__":
    automat = Automaton.buildFromFile('data/automat_input.in')
    Log.enable = False
    Log.enable_print = False
    print(automat.getRegex())
