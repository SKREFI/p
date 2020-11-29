
db = ['vreme in ...', 'weather in bucharest',
      'weather in botosani', 'weather in craiova', 'weather in bacau', 'wbnumaintreba ce e asta']


def bucket(inp, nth=0):
    d = {}
    for i in inp:
        try:
            key = i[nth]
            if key in d.keys():
                d[key].append(i[1:])
            else:
                d[key] = [i[1:]]
        except:
            return d
    return d


def funct(d):
    for k in d.keys():
        d[k] = bucket(d[k])
        funct(d[k])


if __name__ == "__main__":
    db = bucket(db)
    funct(db)

    inp = 'weat'
    inp = [x for x in inp]

    for i in inp:
        try:
            db = db[i]
        except:
            asd = 0

    # print(db.keys())
    print(db['h'])
