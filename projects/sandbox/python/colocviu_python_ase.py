


if __name__ == '__main__':
    with open('input.in', 'r') as f:
        adrese = []
        line = f.readline().strip('\n')
        while len(line) > 0:
            splited = line.split(' ')
            adrese.append(tuple([line, int(splited[-2])]))
            line = f.readline().strip('\n')
        
    adrese.sort(key=lambda x: x[1])

    total = adrese[0][1] 
    for i in range(1, len(adrese)):
        total += total + adrese[i-1][1] * 2 + adrese[i][1]

    print(*adrese, sep='\n')

    for a in adrese:
        print(a[1])

    # print(f'Total: {total}')


##########################################

# import re

# input = 'Avem,avem, mult de lucru . .. Dar nu  mai avem atat de mult timp !'
# input = input.lower()
# input = re.findall("[a-z]+", input)

# l = []

# for cuvant in input:
#     if cuvant[-1] in 'aeiou':
#         continue
#     else:
#         l.append(cuvant)

# l = list(set(l))
# count = []

# for cuvant in l:
#     count.append(tuple([cuvant, input.count(cuvant)]))

# count.sort(key = lambda x: x[1], reverse=True)

# for cuvant in count:
#     print(f'frecventa de aparitie a cuvantului \'{cuvant[0]}\' este {cuvant[1]}.')


# # numar = 147
# # binar = '{0:b}'.format(numar)
# # print(binar)

# # suma = 0

# # for digit in binar:
# #     if digit == '1':
# #         suma += 1

# # print('Total:', suma)

# # #############################################

# # # from collections import defaultdict

# # # if __name__ == '__main__':
# # #     f = open('input.in', 'r')
# # #     n = int(f.readline())
    
# # #     d = defaultdict(lambda: [])

# # #     for i in range(n):
# # #         line = f.readline()
# # #         # observ ca sunt mai multe spatii intre nume si data astfel despart dupa 2 spatii
# # #         nume, data = line.split('  ')
# # #         zi, luna, an = data.split('-')
# # #         an = an.strip()

# # #         d[luna].append(tuple([nume, zi, luna, an]))
    
# # #     for luna in d.keys():
# # #         # o sa-mi asum ca sambata cade pe 6, 13, 20, 27
# # #         s1, s2, s3, s4 = [], [], [], []
# # #         # pentru toti cei care sunt nascutii in aceeasi luna
# # #         for om in d[luna]:
# # #             if 0 <= int(om[1]) <= 6:
# # #                 s1.append(om)
# # #             elif 7 <= int(om[1]) <= 13:
# # #                 s2.append(om)
# # #             elif 14 <= int(om[1]) <= 20:
# # #                 s3.append(om)    
# # #             elif 21 <= int(om[1]):
# # #                 s4.append(om)

# # #         if len(s1) != 0:
# # #             print('06-' + luna + '-2021')
# # #             for om in s1:
# # #                 print(om, sep=' ', end='\n')

# # #         if len(s2) != 0:
# # #             print('13-' + luna + '-2021')
# # #             for om in s2:
# # #                 print(om, sep=' ', end='\n')

# # #         if len(s3) != 0:
# # #             print('20-' + luna + '-2021')
# # #             for om in s3:
# # #                 print(om, sep=' ', end='\n')

# # #         if len(s4) != 0:
# # #             print('27-' + luna + '-2021')
# # #             for om in s4:
# # #                 print(om, sep=' ', end='\n')





# # # ####################

# # # # from string import ascii_letters
# # # # print(sum([0 if x in ascii_letters + ' \t\v\n' else 1 for x in open('input.in', 'r').read()]))