from Automaton import Automaton, Log
from CFG import CFG

if __name__ == "__main__":
    Log.enable = False
    Log.enable_print = False

    # automat = Automaton.buildFromFile('data/automat_input.in')
    # print(automat.getRegex())

    cfg = CFG.buildFromFile('data/cfg_input.in')
    print(cfg.getAllWords(4))


'''
a)
S A B
a b x y
S
A > xx<A>y | xxy
B > a<B>b | ab
'''
'''
b)
S B
a c b
S
S > aa<B>b | aa<S>b
B > b<B>ccc | bccc
'''
'''
c)
S B D C
a b d x z c w
S
S > a<S> | b<B>
B > c | d<D> | x<C>
C > a<S> | x<C> | z | c<B>
D > w
'''


'''
Input A)
0 1 2 3 4
a b c
0
2 4
0 a 1
1 b 1
1 c 2
0 b 3
3 a 4


Input B)
0 1 2 3 4 5 6
a b c
0
6
0 a 1
1 b 2
2 a 2
2 b 6
1 c 3
3 a 4
4 b 5
5 c 3
4 d 6


'''
'''
Problema 5 pe steroizi
A B C
a b c
A
A
A a A
A b A
A c A
A b C
C a A
C b B
A a B
B b A
B a B
'''
"""
Problem 2
1 2 3 4 5
a b
1
3 4 5
1 a 2
2 b 4
2 c 3
2 d 5
"""
"""
Problem 4
A B C D
a b
A
A B C
A b A
A a B
B a B
B b C
C b C
C a D
D a D
D b D
"""
"""
Problem 5
A B C
a b
A
A
A a B
A b C
B b A
C a A
C b B
"""
"""
My test
1 2 3 4 5 6 7 8 9
a
1
8
1 a 2
2 a 2
2 a 5
2 a 4
5 a 6
6 a 4
4 a 9
2 a 3
2 a 7
3 a 7
7 a 2
7 a 8
"""
'''
Problem-06
A B C
a b
A
C
A a C
A b B
C a B
B a B
B b B
'''
