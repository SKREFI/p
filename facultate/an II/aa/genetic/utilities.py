import random as rdm
import math as m

def lungime_cromozom():
    return (
        m.floor(
            m.log2(
                (domeniu_de_definitie[1] - domeniu_de_definitie[0]) * (10 ** precizie)
            )
        )
        + 1
    )


def rezolvare_f_de_x(x):
    return a * (x ** 2) + b * x + c


def initializare_populatie():
    return [[rdm.randint(0, 1) for i in range(lg_crom)] for j in range(dim_pop)]


def transformare_lista_binar_decimal(x):
    y = int("".join(str(e) for e in x))
    sol = 0
    cf = 0
    n = 0
    while y != 0:
        sol = sol + (y % 10) * pow(2, cf)
        y = y // 10
        cf += 1
    return sol


def domeniu_de_definitie(a, b, c):
    return (-b + m.sqrt(pow(b, 2) - 4 * a * c)) / 2 * a, (
        -b - m.sqrt(pow(b, 2) - 4 * a * c)
    ) / 2 * a


def transformare_x(x):
    return round(
        (
            (
                transformare_lista_binar_decimal(x)
                * (domeniu_de_definitie[1] - domeniu_de_definitie[0])
            )
            / (2 ** lg_crom - 1)
            + domeniu_de_definitie[0]
        ),
        int(precizie),
    )


def cautare_binara(lista, elem):
    i = 0
    j = len(lista) - 1
    while i < j:
        mijloc = (i + j) // 2
        if lista[mijloc] <= elem < lista[mijloc + 1]:
            return mijloc
        elif elem >= lista[mijloc]:
            i = mijloc + 1
        else:
            j = mijloc
    return -1


def recombinare(crom1, crom2, rup):
    return crom1[:rup] + crom2[rup:], crom2[:rup] + crom1[rup:]