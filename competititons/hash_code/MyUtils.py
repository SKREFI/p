class Book():
    def __init__(self, id, p):  # p = points
        self.id = id
        self.p = p

    def __repr__(self):
        return "Book(" + str(self.id) + ", " + str(self.p) + ")"


class Library():
    def __init__(self, id, no_books, signup, ship, books):
        self.id = id
        self.no_books = int(no_books)
        self.signup = signup
        self.ship = ship
        self.books = books

    def __repr__(self):
        id = str(self.id)
        n = str(self.no_books)
        s = str(self.signup)
        ship = str(self.ship)
        b = str(self.books)
        space = ", "
        return "Lib(" + id + space + n + space + s + space + ship + space + b + ")"


def readInp(filename):
    with open(filename, "r") as f:
        inp = f.readline().split()
        # important
        no_of_books, no_of_libs, deadline = int(
            inp[0]), int(inp[1]), int(inp[2])
        scores = f.readline().split()
        scores = [int(x) for x in scores]
        index = 0
        # important
        books_list = []
        for s in scores:
            b = Book(index, s)
            books_list.append(b)
            index += 1
        librarys = []
        for lib_index in range(no_of_libs):
            inp = f.readline().split()
            books_id = f.readline().split()
            books_id = [int(x) for x in books_id]
            books = []
            for id in books_id:
                books.append(books_list[int(id)])
            lib = Library(lib_index, int(inp[0]), int(
                inp[1]), int(inp[2]), books)
            librarys.append(lib)
        return no_of_books, no_of_libs, int(deadline), books_list, librarys


def removeDup(libs):
    unice = []
    for lib in libs:
        to_be_removed = []
        for book in lib.books:
            if book not in unice:
                unice.append(book)
            else:
                to_be_removed.append(book)
        for i in to_be_removed:
            lib.books.remove(i)
            lib.no_books -= 1
    return unice


files = [
    "a_example",
    # "b_read_on",
    # "c_incunabula",
    # "d_tough_choices",
    # "e_so_many_books",
    # "f_libraries_of_the_world"
]
