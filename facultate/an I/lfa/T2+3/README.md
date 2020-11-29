# Automata Python Implementation
[Automata theory - Wikipedia](https://en.wikipedia.org/wiki/Automata_theory)

**Automat Input Format:**
```
1. All States (S and F reserved by the system as start and finish nodes)
2. Aplhabet
3. Start node
4. Final Nodes
5+ FROM_NODE TO_NODE EDGE
```
Exception will be raised if:
*Start node*, *Final Node* ∉ *All States*

*FROM_NODE* *TO_NODE* ∉ *All States*

*EDGE* ∉ *Aplhabet*


# Context-free grammar (CFG)
[CFG - Wikipedia](https://en.wikipedia.org/wiki/Context-free_grammar)

CFG Input Format:
```
1. Non Terminal Characters (NTS)
2. Terminal Characters (TS)
3. Start Char ∈ NTS
4+ nts > result1 | result2 | ... | resultN
```
**Note:** 
1. NTS must be surrounded by **<>** when part of the result
2. Spaces arround **>** (bigger symbol) and **|** (pipe symbol) must be respected.
3. 3 In the result set there must be 

**Example:**
CFG Accepting L1 = {a^ib^i ∣ i >= 0}
```
S
a b
S
s > a<S>b | <E>
```
