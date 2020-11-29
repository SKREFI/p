from MyUtils import *
import time
# CONSTANTS:

RADIUS = 20
PADDING = 10
WIDTH = 1800
HEIGHT = 900


class MyPoint():
    def __init__(self, point, name, isFinal, arrow, stop):
        self.point = point
        self.name = name
        self.isFinal = isFinal
        self.arrow = arrow
        self.stop = stop

    def __repr__(self):
        space = ", "
        return "Nod(" + self.name + space + self.arrow + space + self.stop + ")"


class NodeDest():
    def __init__(self, id, point):
        self.id = id
        self.point = point


def setup():
    s = GraphWin('LFA T1', WIDTH, HEIGHT)
    s.setBackground(color_rgb(128, 128, 128))
    return s


s = setup()


def isInside(p, rect):
    ll = rect.getP1()
    tr = rect.getP2()
    return ll.getX() < p.getX() < tr.getX() and ll.getY() > p.getY() > tr.getY()


def CreateRectangle(ll, tr, message="", collor="white"):
    global s
    button = Rectangle(ll, tr)
    message = Text(button.getCenter(), message)
    button.setFill(collor)
    button.draw(s)
    # print("Rectangle created with coords:")
    # print(ll.getX(), ll.getY())
    # print(tr.getX(), tr.getY())
    message.draw(s)
    return button


def drawLine(p1, p2, text=""):
    line = Line(p1, p2)
    middle = Point((p1.x + p2.x) / 2, (p1.y + p2.y) / 2)
    middle.y -= 15
    middle.x += 15
    t = Text(middle, text)
    t.setFill("black")
    t.draw(s)
    line.setWidth(3)
    line.setArrow("last")
    line.draw(s)


def drawNodes(nodes):
    for n in nodes:
        nod = n.id
        p = n.point
        c = Circle(p, 30)
        c.setFill("white")
        c.setWidth(3)
        c.draw(s)
        if nod in starting:
            marc = Circle(p, 23)
            marc.setWidth(12)
            marc.setOutline("green")
            marc.draw(s)
        if nod in targets:
            marc = Circle(p, 23)
            marc.setWidth(12)
            marc.setOutline("red")
            marc.draw(s)
        p.y += 50
        t = Text(p, nod)
        t.setFill("white")
        t.draw(s)
        p.y -= 50


if __name__ == "__main__":
    # setup
    C = COL()

    collumn = CreateRectangle(
        Point(WIDTH - 300, HEIGHT - PADDING),
        Point(WIDTH - PADDING, PADDING),
        "",
        color_rgb(100, 100, 100)
    )

    pathBtn = CreateRectangle(
        Point(PADDING, HEIGHT - PADDING),
        Point(150, HEIGHT - 70),
        "Show Path",
        "yellow"
    )

    previousWordBtn = CreateRectangle(
        Point(150 + PADDING, HEIGHT - PADDING),
        Point(300 + PADDING, HEIGHT - 70),
        "Previous Word",
        color_rgb(0, 100, 255)
    )

    nextWordBtn = CreateRectangle(
        Point(2 * PADDING + 300, HEIGHT - PADDING),
        Point(450, HEIGHT - 70),
        "Next Word",
        "blue"
    )

    words = []
    wordsTextObjects = []
    startingListPoint = Point(collumn.getCenter().getX(), 30 + PADDING)
    with open("words.in", "r") as f:
        inp = f.readline().strip("\n")
        while inp:
            words.append(inp)
            text = Text(startingListPoint, inp)
            text.setTextColor("white")
            text.setSize(20)
            text.draw(s)
            wordsTextObjects.append(text)
            startingListPoint.y += 30
            inp = f.readline().strip("\n")

    targets = []
    with open("targets.in", "r") as f:
        inp = f.readline().strip("\n")
        while inp:
            targets.append(inp)
            inp = f.readline().strip("\n")

    starting = ""
    with open("starting.in", "r") as f:
        starting = f.readline()

    nodes = []
    with open("nodes.in", "r") as f:
        inp = f.readline().split()
        while inp:
            nod = MyPoint(None, inp[0],
                          inp[0] in targets, inp[1], inp[2])
            nodes.append(nod)
            inp = f.readline().split()

    if BackEnd(starting, words[0], targets) == None:
        print(C.fail(""))
    else:
        isGood, path, arrow_from_nodes, all_nodes = BackEnd(
            starting, words[0], targets)
    all_nodes.sort()

    indicationNod = Text(
        Point(700, HEIGHT - 40), "Please place nod:")
    indicationNod.setSize(36)
    indicationNod.setTextColor("White")
    indicationNod.draw(s)
    nodes_id_p = []
    for nod in all_nodes:
        drawNowText = Text(Point(920, HEIGHT - 40), nod)
        drawNowText.setTextColor("blue")
        drawNowText.setSize(36)
        drawNowText.draw(s)
        p = s.getMouse()
        nodes_id_p.append(NodeDest(nod, p))
        c = Circle(p, 30)
        c.setFill("white")
        c.setWidth(3)
        c.draw(s)
        if nod == starting:
            marc = Circle(p, 23)
            marc.setWidth(12)
            marc.setOutline("green")
            marc.draw(s)
        if nod in targets:
            marc = Circle(p, 23)
            marc.setWidth(12)
            marc.setOutline("red")
            marc.draw(s)
        p.y += 50
        t = Text(p, nod)
        t.draw(s)
        drawNowText.undraw()
        p.y -= 50
    indicationNod.undraw()

    print(*nodes)
    self_pointing = []
    for nod in nodes:
        for n in nodes_id_p:
            if n.id == nod.name:
                p1 = n.point.clone()
            if n.id == nod.stop:
                p2 = n.point.clone()

        changeX = 23
        changeY = 23
        if (p1.x < p2.x):
            p2.x -= changeX
        else:
            p2.x += changeX
        if (p1.y < p2.y):
            p2.y -= changeY
        else:
            p2.y += changeY
        drawLine(p1, p2, nod.arrow)

    drawNodes(nodes_id_p)

    for p in nodes:
        if p.name == p.stop:
            for n in nodes_id_p:
                if n.id == p.name:
                    l = []
                    l.append(n.point)
                    l.append(p.arrow)
                    self_pointing.append(tuple(l))

    for t in self_pointing:
        Text(t[0], t[1]).draw(s)
        marc = Circle(t[0], 23)
        marc.setWidth(12)
        marc.setOutline("yellow")
        marc.draw(s)

    leftListArrowPoint = Point(collumn.getCenter().getX() - 120, 30 + PADDING)
    rightListArrowPoint = Point(collumn.getCenter().getX() - 80, 30 + PADDING)
    listArrow = Line(leftListArrowPoint, rightListArrowPoint)
    listArrow.setArrow("last")
    listArrow.setFill("blue")
    listArrow.setWidth(6)
    listArrow.draw(s)

    wordIndex = 0

    if isGood:
        wordsTextObjects[wordIndex].setFill("#33ff00")
    else:
        wordsTextObjects[wordIndex].setFill("red")

    # run
    while True:
        p = s.getMouse()
        print(p)
        if isInside(p, pathBtn):
            print("pathBtn pressed")
            print(C.warning("Path for word: " + words[wordIndex]))
            print(*[C.warning(x) + " " for x in path])
            for nod in nodes_id_p:
                if starting == nod.id:
                    c = Circle(nod.point, 35)
                    c.setWidth(5)
                    c.setOutline("#a0ff10")
                    c.draw(s)
                    time.sleep(0.8)
                    c.undraw()
                    break
            nthNodeIndex = 1
            for ni in path:
                p = Point(0, 0)
                for nod in nodes_id_p:
                    if ni == nod.id:
                        p = nod.point
                        print(C.warning(str(nthNodeIndex) + ": " + ni))
                        nthNodeIndex += 1
                        time.sleep(0.25)
                        c = Circle(p, 35)
                        c.setWidth(5)
                        c.setOutline("#a0ff10")
                        c.draw(s)
                        time.sleep(0.6)
                        c.undraw()
                        break

            continue
        elif isInside(p, nextWordBtn):
            print("nextWordBtn pressed")
            if wordIndex < len(words) - 1:
                listArrow.move(0, 30)
                wordIndex += 1
                if BackEnd(starting, words[wordIndex], targets) != None:
                    isGood, path, arrow_from_nodes, all_nodes = BackEnd(
                        starting, words[wordIndex], targets)
                else:
                    print(C.fail("Command not found for node: " + starting))
                    isGood = False

                if isGood:
                    wordsTextObjects[wordIndex].setFill("#33ff00")
                else:
                    wordsTextObjects[wordIndex].setFill("red")
            else:
                print(C.fail("List of words completed!"))
        elif isInside(p, previousWordBtn):
            print("previousWordBtn pressed")
            if wordIndex > 0:
                listArrow.move(0, -30)
                wordIndex -= 1

                if BackEnd(starting, words[wordIndex], targets) != None:
                    isGood, path, arrow_from_nodes, all_nodes = BackEnd(
                        starting, words[wordIndex], targets)
    s.close()
