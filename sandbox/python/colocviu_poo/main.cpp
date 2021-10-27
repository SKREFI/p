// #include <bits/stdc++.h>

// #include <cstdint>
// #include <iostream>

// BEGIN Clasele voastre aici

using namespace std;

class AccessPoint {
    bool mUnlocked;

   public:
    bool isUnlocked() { return this->mUnlocked; }
    void toggle() { this->mUnlocked = !this->mUnlocked; }

    AccessPoint() {
        this->mUnlocked = false;
    }
};

class AccessDeniedException : exception {};

class User {
    string mUserId;
    set<uint64_t> mCards;
    vector<AccessPoint*> mAccessPoints;
    uint32_t mActivity;

   public:
    User(const string& userId) {
        this->mUserId = userId;
    }

    void toggleDoor(AccessPoint* accessPoint) {
        for (auto ap : this->mAccessPoints) {
            if (accessPoint == ap) {  // sper ca nu o sa fie probleme la operatorul ==
                accessPoint->toggle();
                return;  // l-as face bool si return 1 daca s-a deschis si 0 daca nu
            }
        }
        throw AccessDeniedException();
    }

    void addAccessPoint(AccessPoint* accessPoint) {
        if (!count(this->mAccessPoints.begin(), this->mAccessPoints.end(), accessPoint))
            this->mAccessPoints.push_back(accessPoint);
    }

    void addCard(uint64_t card) {
        // nu trebuie sa verificam intrucat este set
        this->mCards.insert(card);
    }

    bool hasCard(uint64_t card) {
        // cout << "Has card? " << count(this->mCards.begin(), this->mCards.end(), card) << endl;
        for (auto x : this->mCards) {
            // cout << x << ' ';
        }
        // cout << endl;
        if (count(this->mCards.begin(), this->mCards.end(), card)) return true;
        return false;
    }

    uint32_t countCards() {
        return this->mCards.size();
    }

    uint32_t getActivity() {
        return this->mActivity;
    }
};

class AdminUser : public User {
   public:
    void toggleDoor(AccessPoint* accessPoint) {
        accessPoint->toggle();
    }

    AdminUser(const string& userId) : User(userId){};
};

class Database {
    map<string, User*> mUsers;
    unordered_map<uint64_t, AccessPoint*> mAccesPoints;

   public:  //sau mergea bool isAdmin
    void addUser(const string& userId, char userOrAdmin) {
        if (this->mUsers.find(userId) == this->mUsers.end()) {
            if (userOrAdmin == 'U') {
                this->mUsers.insert(pair<string, User*>(userId, new User(userId)));
            } else if (userOrAdmin == 'A') {
                this->mUsers.insert(pair<string, AdminUser*>(userId, new AdminUser(userId)));
            } else {
                cout << "Error. Wrong use of parameters.\n";
            }
        }
    }

    void addAccessPoint(uint64_t accessPoint) {
        if (this->mAccesPoints.find(accessPoint) == this->mAccesPoints.end()) {
            this->mAccesPoints[accessPoint] = new AccessPoint();
        }
    }

    void addCardToUser(const string& userId, uint64_t cardId) {
        this->mUsers[userId]->addCard(cardId);
    }

    void addAccessPointToUser(const string& userId, uint64_t accessPointId) {
        this->mUsers[userId]->addAccessPoint(this->mAccesPoints[accessPointId]);
    }

    void parseEvent(uint64_t cardId, uint64_t doorId) {
        // map<string, User*>::iterator it;
        for (auto const& user : this->mUsers) {
            if (user.second->hasCard(doorId)) {
                // this->mAccesPoints[doorId]->toggle();
                user.second->toggleDoor(this->mAccesPoints[doorId]);
                // return;
            }
        }
        throw AccessDeniedException();
    }

    uint32_t countUnlockedDoors() {
        uint32_t total = 0;
        for (auto const& door : this->mAccesPoints) {
            // cout << door.second->isUnlocked() << " ";
            total += int(door.second->isUnlocked());
        }
        cout << endl;
        return total;
    }

    uint32_t countActivity() {
        uint32_t total = 0;
        for (auto const& user : this->mUsers) {
            total += user.second->getActivity();
            // cout << total << endl;
        }
        return total;
    }

    vector<string> findUsersWithNoCards() {
        vector<string> users;
        for (auto const& user : this->mUsers)
            if (user.second->countCards() == 0)
                users.push_back(user.first);
        return users;
    }

    uint32_t countCards() {
        uint32_t total = 0;
        for (auto const& user : this->mUsers)
            total += user.second->countCards();
        return total;
    }
};

// END Clasele voastre aici

int main() {
    // AccessPoints / Users / Events
    // cout << "N, M, K: ";
    uint32_t n, m, k;
    std::cin >> n >> m >> k;
    Database database;
    // pentru fiecare usa
    while (n--) {
        // creeam un acces point si-l adaugam in db
        // cout << "Insert ID for door no. " << n << ": ";
        uint64_t accessPointId;
        std::cin >> accessPointId;
        database.addAccessPoint(accessPointId);
    }
    while (m--) {
        std::string userId;
        char type;
        // cout << "Insert UserId and Type (U/A) for user no. " << m << ": ";
        std::cin >> userId >> type;
        database.addUser(userId, type);
        uint32_t c;
        // cout << "Inser number of cards for the user with ID " << userId << ": ";
        std::cin >> c;
        while (c--) {
            // cout << "Insert ID for card no. " << c << " of user with ID " << userId << ": ";
            uint64_t cardId;
            std::cin >> cardId;
            database.addCardToUser(userId, cardId);
        }
        uint32_t u;
        // cout << "Inser number of doors for the user with ID " << userId << ": ";
        std::cin >> u;
        while (u--) {
            // cout << "Insert ID for door no. " << u << " of user with ID " << userId << ": ";
            uint64_t accessPointId;
            std::cin >> accessPointId;
            database.addAccessPointToUser(userId, accessPointId);
        }
    }
    uint32_t errors = 0;

    while (k--) {
        uint64_t accessPointId, cardId;
        // cout << "Event no. " << k << ".\nInsert accesPointId and cardId: ";
        std::cin >> accessPointId >> cardId;
        try {
            database.parseEvent(cardId, accessPointId);
        } catch (AccessDeniedException& ex) {
            errors++;
        }
    }

    cout << "Subiect: ";
    uint32_t subject;
    std::cin >> subject;
    cout << "RESULT:\n";
    switch (subject) {
        case 1: {
            std::cout << database.countUnlockedDoors();
            break;
        }
        case 2: {
            std::cout << database.countActivity();
            break;
        }
        case 3: {
            auto users = database.findUsersWithNoCards();
            // afisam newline daca nu exista
            if (users.size() == 0) {
                cout << '\n';
            }
            // si sortam inainte
            sort(users.begin(), users.end());

            for (const auto& user : users) std::cout << user << " ";
            break;
        }
        case 4: {
            std::cout << database.countCards();
            break;
        }
        case 5: {
            std::cout << errors;
            break;
        }
    }
    cout << "\n";
    return 0;
}

//test

// 2 1 3 10 11 20 U 3 31 32 33 1 10 10 31 11 31 11 33