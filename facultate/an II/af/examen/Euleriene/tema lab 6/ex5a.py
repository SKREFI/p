def cicle(start):
    cicle = [start]
    current = start
    next = graph[current][0]

    while next != start:
        cicle.append(next)

        graph[current].remove(next)
        graph[next].remove(current)
        if len(graph[current]) == 0:
            has_edges.remove(current)
        if len(graph[next]) == 0:
            has_edges.remove(next)

        current = next
        next = graph[current][0]

    # print(current, next)
    graph[current].remove(next)
    graph[next].remove(current)
    if len(graph[current]) == 0:
        has_edges.remove(current)
    if len(graph[next]) == 0:
        has_edges.remove(next)

    return cicle


f = open("graf_neorientat2.in")

nr_nodes = int(f.readline())
graph = {}
has_edges = set()

for node in range(nr_nodes):
    graph[node+1] = []


for k in f.readlines():
    a, b = k.split()
    a, b = int(a), int(b)
    graph[a].append(b)
    graph[b].append(a)

    has_edges.add(a)
    has_edges.add(b)


odd_nodes = []
for i, k in graph.items():
    # print(i, k)
    if len(k) % 2 != 0:
        odd_nodes.append(i)

# print(odd_nodes)
if len(odd_nodes) != 0:
    print("Graful nu este eulerian deoarece exista " + str(len(odd_nodes)) + " noduri cu grad impar:")
    for i in odd_nodes:
        print(i)
    exit()

if odd_nodes == []:
    start = list(has_edges)[0]
else:
    start = odd_nodes[0]


answer = cicle(start)

# print(graph, has_edges)
# print(answer)
while True:
    if len(has_edges) == 0:
        break
    remained = list(has_edges)[0]
    partial_cicle = cicle(remained)
    # print(partial_cicle)

    index = answer.index(remained)

    for element in partial_cicle:
        answer.insert(index, element)
        index += 1

answer.append(start)
for i in answer:
    print(i, end=" ")