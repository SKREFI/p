class Log():
    end = '\033[0m'
    enable = True
    enable_print = True

    def __init__(self, enable: bool = True):
        self.enable = enable

    @classmethod
    def print(cls, inp, sep: str = ' ', end: str = '\n'):
        if cls.enable_print:
            print(inp, sep=sep, end=end)
        

    @classmethod
    def warning(cls, inp):
        if not cls.enable:
            return
        print('\033[93m' + str(inp) + cls.end)

    @classmethod
    def fail(cls, inp):
        if not cls.enable:
            return
        print('\033[91m' + str(inp) + cls.end)

    @classmethod
    def succes(cls, inp):
        if not cls.enable:
            return
        print('\033[92m' + str(inp) + cls.end)

    @classmethod
    def debug(cls, inp):
        if not cls.enable:
            return
        print('\033[94m' + str(inp) + cls.end)

    @classmethod
    def getAllStyles(cls):
        for i in range(100):
            print(f'\033[{i}mNumber{i}\033[0m')
