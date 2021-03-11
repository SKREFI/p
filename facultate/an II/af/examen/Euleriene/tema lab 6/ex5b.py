def path(start):
    path = [start]
    next = graph[start][0]

    while graph[next] != []:
        path.append(next)

        graph[start].remove(next)
        start = next
        next = graph[start][0]

    path.append(next)
    return path


f = open("graf_orientat1.in")

nr_nodes = int(f.readline())
graph = {}
g_ext = {}
g_int = {}

for node in range(nr_nodes):
    graph[node+1] = []
    g_ext[node+1] = 0
    g_int[node+1] = 0


for k in f.readlines():
    a, b = k.split()
    a, b = int(a), int(b)
    graph[a].append(b)
    g_ext[a] += 1
    g_int[b] += 1


extern = []
intern = []
for i in range(1, nr_nodes+1):
    if g_ext[i] - g_int[i] > 0:
        if g_ext[i] - g_int[i] == 1:
            extern.append(i)
        else:
            print("Nu exista drum eulerian deoarece nodul " + str(i) + " are grad exterior prea mare")
            exit()

    if g_int[i] - g_ext[i] > 0:
        if g_int[i] - g_ext[i] == 1:
            intern.append(i)
        else:
            print("Nu exista drum eulerian deoarece nodul " + str(i) + " are grad interior prea mare")
            exit()

if len(extern) > 1:
    print("Nu exista drum eulerian deoarece prea multe noduri au gradul exterior mai mare decat cel interior:")
    print(extern)
    exit()

if len(intern) > 1:
    print("Nu exista drum eulerian deoarece prea multe noduri au gradul interior mai mare decat cel exterior:")
    print(intern)
    exit()

# print(graph)
# print(extern)
# print(intern)

if len(extern) == 1:
    answer = path(extern[0])
else:
    answer = path(a)

for i in answer:
    print(i, end=" ")