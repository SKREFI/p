#include <bits/stdc++.h>
using namespace std;

#define ui uint8_t

class Player {
   public:
    bool continua = 1;
    int puncte = 0;
    string nume;
    uint32_t bani;

    Player(string nume, uint32_t bani) : bani(bani), nume(nume) {}

    friend ostream& operator<<(ostream& os, const Player& player) {
        os << player.nume << " " << player.bani;
        return os;
    }
};

class Card {
   public:
    int numar;  // nu stiu ce ce dar nu mergea cu uint8_t
    string stema;

    Card(ui nr, string stema) : numar(nr), stema(stema) {}

    friend ostream& operator<<(ostream& os, const Card& card) {
        os << card.numar << "," << card.stema;
        return os;
    }

    friend bool operator==(const Card& a, const Card& b) {
        return a.numar == b.numar && a.stema == b.stema;
    }

    // bool operator==(const Card& c) const {
    //     return this->numar == c.numar && this->stema == c.stema;
    // }

    // pentru set, dar nu merge :/
    // struct HashFunction {
    //     size_t operator()(const Card& c) const {
    //         size_t xHash = std::hash<int>()(c.numar);
    //         size_t yHash;

    //         if (c.stema == "rosu") {
    //             yHash = std::hash<int>()(1);
    //         } else if (c.stema == "romb") {
    //             yHash = std::hash<int>()(2);
    //         } else if (c.stema == "negru") {
    //             yHash = std::hash<int>()(3);
    //         } else if (c.stema == "trefla") {
    //             yHash = std::hash<int>()(4);
    //         }
    //         return xHash ^ yHash;
    //     }
    // };
};

int main() {
    srand(time(NULL));

    string subiect;
    ifstream citire_fisier("blackjack.in");
    // cout << "Subiect: ";
    cin >> subiect;

    vector<Card> play_deck;

    for (int i = 2; i < 15; i++) {
        if (i == 11) continue;
        play_deck.push_back(Card(i, "rosu"));
    }
    for (int i = 2; i < 15; i++) {
        if (i == 11) continue;
        play_deck.push_back(Card(i, "negru"));
    }
    for (int i = 2; i < 15; i++) {
        if (i == 11) continue;
        play_deck.push_back(Card(i, "romb"));
    }
    for (int i = 2; i < 15; i++) {
        if (i == 11) continue;
        play_deck.push_back(Card(i, "trefla"));
    }

    if (subiect == "check_cards") {
        string temp;

        int no_cards = 0;
        vector<Card> deck;

        while (cin >> temp) {
            if (no_cards > 52) {
                // chiar daca nu trebuie sa verific pentru ca 13 * 4 = 52 si verificam daca bagi aceleasi carti, adica nu exista 53 de carti, daca exista
                // ori s-au bagat duplicate ori carti care nu exista.
                cout << "Pachet masluit" << endl;
                return -1;
            }

            int card_num = stoi(temp.substr(0, temp.find(",")));
            string card_stema = temp.substr(temp.find(",") + 1, temp.length());

            if (card_num < 2 || card_num > 14) {
                cout << "Pachet masluit" << endl;
                return -1;
            }
            if (card_stema == "romb" || card_stema == "rosu" || card_stema == "negru" || card_stema == "trefla") {
                // all good
                Card c(card_num, card_stema);

                // if (find(deck.begin(), deck.end(), c) != deck.end()) {
                //     cout << "Pachet masluit" << endl;
                //     return -1;
                // }

                deck.push_back(c);
                no_cards++;

                // cout << "Card number " << no_cards << ": " << c << endl;
                continue;
            } else {
                cout << "Pachet masluit" << endl;
                return -1;
            }
        }
        if (no_cards == 52)
            cout << "Pachet OK" << endl;
        else
            cout << "Pachet pentru Backjack" << endl;
    } else if (subiect == "shuffle_cards") {  // imi asum ca deckul a fost verificat
        string temp;

        vector<Card> deck;

        int a1, c1, x1;
        int a2, c2, x2;

        //     1    5    4     2     2     3
        cin >> a1 >> c1 >> x1 >> a2 >> c2 >> x2;

        while (cin >> temp) {
            int card_num = stoi(temp.substr(0, temp.find(",")));
            string card_stema = temp.substr(temp.find(",") + 1, temp.length());
            deck.push_back(Card(card_num, card_stema));
        }

        for (int i = 0; i < 50; i++) {
            x1 = (a1 * x1 + c1) % deck.size();
            x2 = (a2 * x2 + c2) % deck.size();

            swap(deck[x1], deck[x2]);
        }

        for (auto card : deck) {
            cout << card << endl;
        }

    } else if (subiect == "play_game") {
        int n;
        cin >> n;

        vector<Player> players;

        for (int i = 0; i < n; i++) {
            string nume;
            uint32_t bani;
            cin >> nume >> bani;

            players.push_back(Player(nume, bani));
        }

        int a1, c1, x1;
        int a2, c2, x2;

        //                      10
        while (cin >> a1) {
            //               26    33    34    37    45
            cin >> c1 >> x1 >> a2 >> c2 >> x2;

            for (int i = 0; i < 50; i++) {
                x1 = (a1 * x1 + c1) % play_deck.size();
                x2 = (a2 * x2 + c2) % play_deck.size();

                swap(play_deck[x1], play_deck[x2]);
            }

            for (int i = 0; i < players.size(); i++) {
                if (players[i].bani < 10) {
                    players.erase(players.begin() + i);
                }
            }

            Player dealer("Dealer", 10000);

            dealer.puncte = 0;
            for (int i = 0; i < players.size(); i++) {
                players[i].puncte = 0;
            }

            int carte = 0;
            dealer.puncte += play_deck[carte++].numar;
            dealer.puncte += play_deck[carte++].numar;

            for (int i = 0; i < players.size(); i++) {
                players[i].puncte += play_deck[carte++].numar;
                players[i].puncte += play_deck[carte++].numar;
            }

            bool stop = 0;
            vector<int> stoped_playing;

            while (dealer.puncte <= 21) {
                if (stop == 1) break;
                for (int i = 0; i < players.size(); i++) {
                    if (find(stoped_playing.begin(), stoped_playing.end(), i) == stoped_playing.end()) {
                        if (players[i].puncte < 17) {
                            players[i].puncte += play_deck[carte++].numar;
                        } else {
                            stoped_playing.push_back(i);
                        }
                    }
                    if (stoped_playing.size() == players.size()) {
                        stop = 1;
                    }
                }
            }

            for (int i = 0; i < players.size(); i++) {
                if (players[i].puncte > 21) {
                    players[i].bani -= 10;
                    continue;
                }
                if (players[i].puncte < dealer.puncte) {
                    players[i].bani -= 10;
                } else {
                    players[i].bani += 10;
                }
            }
        }
        for (auto player : players) {
            cout << player.nume << ": " << player.bani << endl;
        }
    }
}

// check_cards
// 4,romb
// 3,rosu
// 12,trefla
// 10,negru
// 7,rosu
// 9,romb
// 7,negru
// 3,rosu

// shuffle_cards
// 1 5 4
// 2 2 3
// 4,romb
// 3,rosu
// 12,trefla
// 10,negru
// 7,rosu
// 9,romb
// 7,negru
// 4,rosu

// Test 5: Test #1.5
// Incorrect program output
// --- Input ---
// check_cards
// 4,romb
// 3,rosu
// 3,negru
// 4,negru
// 5,romb
// 6,rosu
// 7,negru
// 8,negru
// 9,negru
// 9,negru
// 9,negru
// 7,negru
// 3,rosu
// 12,trefla
// 10,negru
// 7,rosu
// 9,romb
// 7,negru
// 3,rosu

// --- Program output ---
// Pachet masluit

// --- Expected output (exact text)---
// Pregatit pentru Blackjack