#include<bits/stdc++.h>
using namespace std;

class QNS {
private:
    int powerlevel, durability, energystorage, heatlevel;
public:
    QNS(int p = 1000, int d = 500, int e = 300, int h = 0) : powerlevel(p), durability(d), energystorage(e), heatlevel(h) {}
    QNS(const QNS& other) : powerlevel(other.powerlevel), durability(other.durability), energystorage(other.energystorage), heatlevel(other.heatlevel) {}

    QNS operator+(const QNS& other) {
        powerlevel=powerlevel+other.energystorage;
        if(powerlevel>5000){powerlevel=5000;}
        return QNS(powerlevel, durability + other.durability, energystorage + other.powerlevel, heatlevel);
    }

    QNS operator-(int damage) {
        int newdurability = durability - damage;
        int newheat = heatlevel + damage;
        return QNS(powerlevel, newdurability, energystorage + damage, newheat);
    }

    QNS operator*(int factor) {
        int newpower = powerlevel + ((powerlevel * factor) / 100);
        if(newpower>5000){newpower=5000;}
        int newheat = heatlevel + factor;
        return QNS(newpower, durability, energystorage + 5 * factor, newheat);
    }

    QNS operator/(int factor) {
        int newheat = heatlevel - factor;
        if (newheat < 0) {
            newheat = 0;
        }
        return QNS(powerlevel, durability + factor, energystorage, newheat);
    }

    bool operator==(const QNS& other) {
        return (powerlevel == other.powerlevel && durability == other.durability);
    }

    bool operator<(const QNS& other) {
        return (powerlevel + durability) < (other.powerlevel + other.durability);
    }

    int getPowerLevel() {
        return powerlevel;
    }

    int getDurability() {
        return durability;
    }

    int getEnergystorage() {
        return energystorage;
    }

    int getHeatLevel() {
        return heatlevel;
    }

    void setpowerlevel(int p) {
        powerlevel = p;
        if (powerlevel > 5000) {
            powerlevel = 5000;
        }
    }

    void setenergystorage(int e) {
        energystorage = e;
    }

    void setheatlevel(int h) {
        heatlevel = h;
        if (heatlevel < 0) {
            heatlevel = 0;
        }
    }

    bool overheated() {
        return heatlevel > 500;
    }

    bool destroyed() {
        return durability <= 0;
    }
};

class Avenger {
public:
    string name;
    QNS suit;
    int attackstrength;

    Avenger(string avname, QNS avsuit, int strength) : name(avname), suit(avsuit), attackstrength(strength) {}

    void attack(Avenger& enemy) {
        if ((!suit.destroyed() && !suit.overheated()) && !enemy.suit.destroyed()) {
            enemy.suit = enemy.suit - attackstrength;
        }
    }

    void upgradesuit(QNS& extrasuit) {
        suit = suit + extrasuit;
    }

    void repair(int x) {
        suit = suit / x;
    }

    void boostpower(int factor) {
        suit = suit * factor;
    }

    void boostpower(QNS othersuit) {
        suit = suit + othersuit;
    }

    void printstatus() {
        cout << name << " " << suit.getPowerLevel() << " " << suit.getDurability() << " " << suit.getEnergystorage() << " " << suit.getHeatLevel() << endl;
    }

    string getname() {
        return name;
    }

    QNS getsuit() const {
        return suit;
    }

    int getattackstrength() {
        return attackstrength;
    }
};

class Battle {
private:
    vector<Avenger> heroes;
    vector<Avenger> enemies;
    vector<string> battlelog;

public:
    void addhero(const Avenger& hero) {
        heroes.push_back(hero);
    }

    void addenemy(const Avenger& enemy) {
        enemies.push_back(enemy);
    }

    void startbattle() {
    }

    void attack(const string& attackername, const string& defendername) {
        auto attacker = findavenger(attackername);
        auto defender = findavenger(defendername);

        if (attacker != nullptr && defender != nullptr) {
            if ((!attacker->getsuit().destroyed() && !attacker->getsuit().overheated()) && !defender->getsuit().destroyed()) {
                battlelog.push_back(attackername + " attacks " + defendername);
                attacker->attack(*defender);
                if (defender->getsuit().destroyed()) {
                    battlelog.push_back(defendername + " suit destroyed");
                }
                else if (defender->getsuit().overheated()) {
                    battlelog.push_back(defendername + " suit overheated");
                }
            }
        }
    }

    void repair(const string& avengername, int x) {
        auto avenger = findavenger(avengername);
        if (avenger != nullptr) {
            avenger->repair(x);
            battlelog.push_back(avengername + " repaired");
        }
    }

    void boostpowerbyfactor(const string& avengername, int factor) {
        auto avenger = findavenger(avengername);
        if (avenger != nullptr) {
            avenger->boostpower(factor);
            battlelog.push_back(avengername + " boosted");
            if (avenger->getsuit().overheated()) {
                battlelog.push_back(avengername + " suit overheated");
            }
        }
    }

    void upgradesuit(const string& avengername, QNS& extrasuit) {
        auto avenger = findavenger(avengername);
        if (avenger != nullptr) {
            avenger->upgradesuit(extrasuit);
            battlelog.push_back(avengername + " upgraded");
        }
    }
    void upgradefail(const string& avengername) {
        battlelog.push_back(avengername + " upgrade Fail");
    }

    void printbattlelog() {
        for (const auto& log : battlelog) {
            cout << log << endl;
        }
    }

    int result() {
        int herosum = 0, enemysum = 0;
        for (const auto& hero : heroes) {
            if (!hero.getsuit().destroyed()) {
                herosum += (hero.getsuit().getPowerLevel() + hero.getsuit().getDurability());
            }
        }
        for (const auto& enemy : enemies) {
            if (!enemy.getsuit().destroyed()) {
                enemysum += ( enemy.getsuit().getPowerLevel() + enemy.getsuit().getDurability());
            }
        }
        if (herosum > enemysum) {
            return 1;
        } else if (herosum < enemysum) {
            return -1;
        } else {
            return 0;
        }
    }

    Avenger* findavenger(const string& name) {
        for (auto& hero : heroes) {
            if (hero.getname() == name) {
                return &hero;
            }
        }
        for (auto& enemy : enemies) {
            if (enemy.getname() == name) {
                return &enemy;
            }
        }
        return nullptr;
    }
};

int main() {
    int k, n, m;
    cin >> k >> n >> m;
    int a = n + m;
    vector<QNS> suits;
    for (int i = 0; i < k; i++) {
        int p, d, e, h;
        cin >> p >> d >> e >> h;
        p = min(p,5000);
        suits.push_back(QNS(p, d, e, h));
    }

    Battle battle;
    vector<Avenger> avengers;
    for (int i = 0; i < n + m; i++) {
        string name;
        int strength;
        cin >> name >> strength;
        if (i < k) {
            avengers.push_back(Avenger(name, suits[i], strength));
            if (i < n) {
                battle.addhero(avengers.back());
            } else {
                battle.addenemy(avengers.back());
            }
        } else {
            cout << name << " is out of fight" << endl;
        }
    }

    string input;
    while (cin >> input) {
        if (input == "BattleBegin") {
            battle.startbattle();
        } else if (input == "Attack") {
            string attacker, defender;
            cin >> attacker >> defender;
            battle.attack(attacker, defender);
        } else if (input == "Repair") {
            string avengername;
            int factor;
            cin >> avengername >> factor;
            battle.repair(avengername, factor);
        } else if (input == "BoostPowerByFactor") {
            string avengername;
            int factor;
            cin >> avengername >> factor;
            battle.boostpowerbyfactor(avengername, factor);
        } else if (input == "Upgrade") {
            string avengername;
            cin >> avengername;
            // if (k > n + m) {
            if(a <= k -1 )
            {
                  battle.upgradesuit(avengername, suits[a]);
                  a++;
            }
            else 
            {
                battle.upgradefail(avengername);
            }
            // } else {
            //     cout << avengername << " upgrade Fail" << endl;
            // }
        } else if (input == "AvengerStatus") {
            string avengername;
            cin >> avengername;
            auto avenger = battle.findavenger(avengername);
            if (avenger != nullptr) {
                avenger->printstatus();
            }
        } else if (input == "PrintBattleLog") {
            battle.printbattlelog();
        } else if (input == "BattleStatus") {
            int Result = battle.result();
            if (Result == 1) {
                cout << "heroes are winning" << endl;
            } else if (Result == -1) {
                cout << "enemies are winning" << endl;
            } else {
                cout << "tie" << endl;
            }
        } else if (input == "End") {
            break;
        }
    }
}
