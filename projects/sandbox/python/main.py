# tranzactii, client -> at least one cont & card
# Sesiune:  - extragere sumei din cont
#           - afisare sold
#           - transfer in alt cont al clientului
# 
#

from collections import defaultdict

class Cont:
    def __init__(self, id, balance):
        self.id = id
        self.balance = balance

class Banca:
    def __init__(self, id, nume): # banca de la care face parte
        self.id = id
        self.nume = nume
        self.conturi = defaultdict(lambda: [])

#     1234 - > Cont Banca: 1000 Posesor: Andrei
#     5678 - > Cont Banca: 2000 

    def __repr__(self):
        return f''

class ATM:
    def __init__(self, id_banca): # banca de la care face parte
        self.id_banca = id_banca

    def __repr__(self):
        return f'-=ID Banca: {self.id_banca}=-'

class Card:
    def __init__(self, id, posesor):
        self.id = id 
        self.posesor = posesor 

    def __repr__(self):
        return f'__Card: {self.id}__'

class Client:
    def __init__(self, id, nume):
        self.id = id
        self.nume = nume
        self.lista_conturi = []
        self.lista_carduri = []

    def __repr__(self):
        return f"Client: {self.id}; Carduri: {self.lista_carduri}; Conturi: {self.lista_conturi}"

    def adaugaCard(self, id_card):
        self.lista_carduri.append(id_card)

    def adaugaCont(self, id_cont):
        self.lista_conturi.append(id_cont)

if __name__ == '__main__':
    BT = Banca(1, "Banca Transilvania")

    client = Client(1, "Andrei")
    card = Card(1234, client.nume)

    client.adaugaCard(card)

    print(client)