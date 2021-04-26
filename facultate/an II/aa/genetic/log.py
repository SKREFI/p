class Log:
    logging: bool = False

    @classmethod
    def d(cls, *objs, sep = ' ', end = '\n'):
        if (cls.logging):
            for obj in objs:
                print(obj, sep = sep, end = end)
