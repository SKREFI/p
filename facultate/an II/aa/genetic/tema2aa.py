import random as rdm
import math as m
from log import Log

# By default the logger is off
Log.logging = True
f = open("evolutie.in")
g = open("evolutie.out", "w")


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


if __name__ == "__main__":
    dim_pop = int(f.readline())
    a = int(f.readline())
    b = int(f.readline())
    c = int(f.readline())
    domeniu_de_definitie = list(domeniu_de_definitie(a, b, c))
    precizie = float(f.readline())
    prob_recomb = float(f.readline())
    prob_mut = float(f.readline())
    nr_generatii = int(f.readline())

    lg_crom = lungime_cromozom()

    populatie = initializare_populatie()

    ok = True

    for generatie in range(nr_generatii):
        x = []
        fitness = []
        cromozomi = []

        if ok:
            g.write("Populatie intiala:\n")

        for i in range(dim_pop):
            cromozomi.append("".join(str(gena) for gena in populatie[i]))
            x.append(transformare_x(cromozomi[i]))
            fitness.append(rezolvare_f_de_x(x[i]))
            if ok:
                g.write(
                    "    "
                    + str(i + 1)
                    + " -> "
                    + str(cromozomi[i])
                    + " "
                    + str(x[i])
                    + " "
                    + str(fitness[i])
                    + "\n"
                )

        fitness_total = 0
        for i in range(dim_pop):
            fitness_total += fitness[i]

        max_fit = max(fitness)
        medie = fitness_total / dim_pop
        fitness_total -= max(fitness)
        indice_cromozom_elitist = fitness.index(max(fitness))
        cromozom_elitist = populatie[indice_cromozom_elitist].copy()
        populatie.remove(populatie[indice_cromozom_elitist])
        cromozomi.remove(cromozomi[indice_cromozom_elitist])
        fitness.remove(fitness[indice_cromozom_elitist])
        x.remove(x[indice_cromozom_elitist])
        dim_pop -= 1
        prob_select = []

        if ok:
            g.write("Populatie cu probabilitatile de selectie fiecare:" + "\n")
        for i in range(dim_pop):
            prob_select.append(fitness[i] / fitness_total)
            if ok:
                g.write("    " + str(i + 1) + " -> " + str(prob_select[i]) + "\n")

        if ok:
            g.write("Intervalele create:" + "\n")

        intervale = [0]

        for i in range(dim_pop):
            intervale.append(intervale[i] + prob_select[i])

        if ok:
            g.write(str(intervale) + "\n")
        indice_interval = []
        populatie_selectata = []
        cromozomi_selectati = []
        for i in range(dim_pop):
            u = rdm.random()
            indice_interval.append(cautare_binara(intervale, u))
            if ok:
                g.write(str(u) + str(indice_interval[i] + 1) + "\n")
            populatie_selectata.append(populatie[indice_interval[i]])

        for i in range(dim_pop):
            cromozomi_selectati.append(
                "".join(str(gena) for gena in populatie_selectata[i])
            )

        if ok:
            g.write("Cromozomii dupa selectia facuta:" + "\n")
            for i in range(dim_pop):
                g.write(
                    str(i + 1)
                    + " "
                    + str(cromozomi_selectati[i])
                    + " "
                    + str(x[indice_interval[i]])
                    + " "
                    + str(fitness[indice_interval[i]])
                    + "\n"
                )
        if ok:
            g.write("Probabilitate de recombinare data:" + str(prob_recomb))

        indici_recombinare = []
        indici_mutatie = []

        for i in range(dim_pop):
            u = rdm.random()
            if ok:
                g.write(str(i + 1) + str(cromozomi_selectati) + str(u))
            if u < prob_recomb:
                if ok:
                    g.write("participa" + "\n")
                indici_recombinare.append(i)

        recombinari = len(indici_recombinare)

        while recombinari > 1:
            c1 = indici_recombinare.pop()
            c2 = indici_recombinare.pop()
            punct_rup = rdm.randrange(0, lg_crom + 1)
            cromozomi_selectati[c1], cromozomi_selectati[c2] = recombinare(
                cromozomi_selectati[c1], cromozomi_selectati[c2], punct_rup
            )
            recombinari -= 2
        if ok:
            g.write("Dupa recombinarea efectuata:" + "\n")

        #             cromozomi.append(''.join(str(gena) for gena in populatie[i]))
        #             x.append(transformare_x(populatie[i]))
        #             fitness.append(rezolvare_f_de_x(x[i]))
        x_nou = []
        fitness_nou = []

        for i in range(dim_pop):
            # return round(((transformare_lista_binar_decimal(x) * (domeniu_de_definitie[1] - domeniu_de_definitie[0])) / (2 ** lg_crom - 1) + domeniu_de_definitie[0]), int(precizie))
            x_nou.append(
                round(
                    (
                        (
                            int(cromozomi_selectati[i], 2)
                            * (domeniu_de_definitie[1] - domeniu_de_definitie[0])
                        )
                        / (2 ** lg_crom - 1)
                        + domeniu_de_definitie[0]
                    ),
                    int(precizie),
                )
            )
            fitness_nou.append(rezolvare_f_de_x(x_nou[i]))

        if ok:
            Log.d(
                "Cromozomii selectati: ", *cromozomi_selectati, len(cromozomi_selectati)
            )
            for i in range(dim_pop):
                g.write(
                    str(i + 1)
                    + " "
                    + str(cromozomi_selectati[i])
                    + " "
                    + str(x_nou[i])
                    + " "
                    + str(fitness_nou[i])
                    + "\n"
                )

        if ok:
            g.write(f"Probabilitate de mutatie:" + str(prob_mut) + "\n")

        for i in range(dim_pop):
            u = rdm.random()
            if u < prob_mut:
                indici_mutatie.append(i)

        for i in range(len(indici_mutatie)):
            u = rdm.randrange(0, lg_crom)
            if populatie_selectata[indici_mutatie[i]][u] == 1:
                populatie_selectata[indici_mutatie[i]][u] = 0
            else:
                populatie_selectata[indici_mutatie[i]][u] = 1

        if ok:
            if len(indici_mutatie):
                g.write("Au fost modificati" + "\n")
                for i in range(len(indici_mutatie)):
                    g.write(str(i + 1) + "\n")

        if ok:
            g.write("Dupa mutatie:\n")

        cromozomi_etapa_urmatoare = []
        x__etapa_urmatoare = []
        fitness_etapa_urmatoare = []

        for i in range(dim_pop):
            cromozomi_etapa_urmatoare.append(
                "".join(str(gena) for gena in populatie_selectata[i])
            )
            x__etapa_urmatoare.append(transformare_x((cromozomi_etapa_urmatoare[i])))
            fitness_etapa_urmatoare.append(rezolvare_f_de_x(x__etapa_urmatoare[i]))

        if ok:
            for i in range(dim_pop):
                g.write(
                    "    " + str(i + 1)
                    + str(cromozomi_etapa_urmatoare[i])
                    + " "
                    + str(x__etapa_urmatoare[i])
                    + " "
                    + str(fitness_etapa_urmatoare[i])
                    + "\n"
                )

        populatie_selectata.append(cromozom_elitist)
        populatie = populatie_selectata.copy()
        dim_pop += 1
        if ok:
            g.write("Evolutia maximului:" + "\n")
        ok = False
        g.write("    " + str(max_fit) + " " + str(medie) + "\n")
