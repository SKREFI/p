# Context Free Grammar (CFG)
from collections import defaultdict
from Logging import Log
from string import ascii_lowercase, ascii_uppercase

E = ''
S_NTS = 'S'


class CFG():
    def __init__(self, non_terminal_symbols, terminal_symbols, S, P):
        self.n = non_terminal_symbols
        self.t = terminal_symbols
        self.s = S
        self.p = P
        self.words = set()

    def __repr__(self):
        ret = ''
        for k, v in self.p.items():
            ret += k + ' -> ' + ' | '.join(v) + '\n'
        return ret

    @classmethod
    def buildFromFile(cls, filename):
        with open(filename, 'r') as f:
            # non terminal symbols
            nts = [x.strip() for x in f.readline().split()]
            # terminal symbols (letters)
            ts = [x.strip() for x in f.readline().split()]
            # start symbol
            S = f.readline().strip()
            # if nts and ts have common elements raise exception
            if len(set(nts).intersection(set(ts))) > 0:
                raise Exception(
                    'Terminals and non-terminals have common elements.')
            if S not in nts:
                raise Exception(
                    'Start non-terminal-symbol not found in NTS list.')
            if 'E' in nts:
                raise Exception(
                    'E found in NTS list, sorry, name reserved for the Epsilon')
            # read a new rule
            rule = f.readline()
            # create a new dict defaulting an empty list for the production rules
            p = defaultdict(lambda: [])
            while rule:
                if len(rule) > 1 and rule[0] != '#':
                    # check cfg_input.in for formating rules
                    rule = [x.strip() for x in rule.split(' > ')]
                    left = rule[0]
                    if left not in nts:
                        raise Exception(
                            'Left NTS not part of the non terminal symbol list.')
                    right = [x.strip() for x in rule[1].split(' | ')]
                    p[left] = right
                rule = f.readline()
            p['E'].append('')
            return CFG(nts, ts, S, p)

    def __countTS(self, string) -> int:
        counter = 0
        for letter in string:
            if letter in ascii_lowercase:
                counter += 1
        return counter

    def __countNTS(self, string) -> int:
        counter = 0
        for letter in string:
            if letter in ('<', '>'):
                counter += 1
        return counter // 2

    def __getNTS(self, string):
        i = 0
        while i < len(string):
            if string[i] == '<':
                start = i
                while string[i] != '>':
                    i += 1
                end = i
                symbol = string[start:end+1]
                return (symbol)
            i += 1

    def __getAllWordsHelper(self, word: str, max_length: int) -> None:
        # has no more nts so we add if it if not bigger then max_length
        Log.print('Proccessing: ' + word)
        if self.__countNTS(word) == 0:
            if len(word) <= max_length:
                self.words.add(word)
        if self.__countTS(word) <= max_length:
            nts = self.__getNTS(word)
            if nts is not None:
                for right in self.p[nts[1:-1]]:
                    self.__getAllWordsHelper(
                        word.replace(nts, right), max_length)

    def getAllWords(self, max_length: int = 5) -> list:
        for word in self.p[S_NTS]:
            self.__getAllWordsHelper(word, max_length)
        return sorted(self.words)


if __name__ == "__main__":
    Log.enable = False
    Log.enable_print = False

    cfg = CFG.buildFromFile('data/cfg_input.in')
    print(cfg.getAllWords(6))

    
'''
Exemplu PDF Tema:
S A
a b
S
S > b<S><S>bb | <A>
A > a<A> | <E>
'''
'''
'''
'''
'''
'''
'''
'''
'''
'''
'''
'''
'''
'''
'''
