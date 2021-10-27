class Solution:
    def reverse(self, n: int) -> int:

        rev = str(n)[::-1]
        if len(rev) == 0:
            return 0
        while len(rev) and rev[0] == '0':
            rev = rev[1:]

        if len(rev) == 0:
            return 0

        if not rev[-1] != '-':
            rev = '-' + rev[:len(rev) - 1]

        if abs(int(rev)) > ((1 << 31) - 1):
            return 0

        return rev
