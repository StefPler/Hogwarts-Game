#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>

#define DASHES "------------------------------"
#define TILDAS "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
#define HASHTAG "#############################"

/**
 * The spell class
 *
 **/
class Spell {

private:
  Lambda action;

public:
  string name;
  static map<string, Lambda> Spells;
  Spell() {}

  Spell(string name, Lambda lambda) {
    this->name = name;
    this->action = lambda;

    Spells.insert(pair<string, Lambda>(name, lambda));
  }

  void operator[](Spell obj) {}
};

/**
 * The Wizard class
 *
 **/
class Wizard {

private:
  static vector<Wizard> Wizards;

public:
  string name, house;
  int startingHP, currentHP;
  bool hasWand;
  vector<string> spells;

  Wizard() {}

  Wizard(string name, string house, int health_points) {
    this->hasWand = true;
    this->name = name;
    this->house = house;
    this->startingHP = health_points;
    this->currentHP = health_points;
    this->spells = {};
    Wizards.push_back(*this);
  }

  // copy constructor
  Wizard(const Wizard &rhs) {
    this->hasWand = rhs.hasWand;
    this->name = rhs.name;
    this->house = rhs.house;
    this->startingHP = rhs.startingHP;
    this->currentHP = rhs.currentHP;
    this->spells = rhs.spells;
    // cout << "Copy constructor called for wizard \n";
  }

  // overloading = for copy constructor
  Wizard &operator=(const Wizard &rhs) {
    this->hasWand = rhs.hasWand;
    this->name = rhs.name;
    this->house = rhs.house;
    this->startingHP = rhs.startingHP;
    this->currentHP = rhs.currentHP;
    this->spells = rhs.spells;
    // cout << "copy = operator called";
    return *this;
  }

  void operator[](Wizard obj) {}

  Wizard operator-() { return Wizard(); }

  Wizard operator-(Wizard obj) { return obj; }

  static Wizard learnSpell(string WizardName, string SpellName) {
    try {
      Lambda lambda = Spell::Spells.at(SpellName);
    } catch (exception e) {
      cout << "Spell \"" << SpellName
           << "\" is not registed and can not be learned." << endl;
      return Wizard();
    }

    for (vector<Wizard>::iterator it = Wizards.begin(); it != Wizards.end();
         it++)
      if (it->name == WizardName)
        it->spells.push_back(SpellName);
    return Wizard();

    cout << "Wizard \"" << WizardName << "\" is not registed." << endl;
    return Wizard();
  }

  static Wizard getWizard(string name) {
    for (vector<Wizard>::iterator it = Wizards.begin(); it != Wizards.end();
         it++)
      if (it->name == name)
        return *it;

    return Wizards[0];
  }

  static void printWizards() {
    for (auto it = Wizards.begin(); it != Wizards.end(); it++) {
      if (it->name == "potato")
        continue;
      cout << it->name << endl;
    }
  }

  string getSpell(string spellname) {
    string toReturn = "starch";

    for (auto it = spells.begin(); it != spells.end(); it++) {
      if (*it == spellname) {
        toReturn = spellname;
      }
    }
    return toReturn;
  }

  void printSpells() {
    for (auto it = spells.begin(); it != spells.end(); it++) {
      cout << *it << endl;
    }
  }

  string print() {
    string wand = hasWand ? "Wand equipped" : "Wand not equipped";
    return "Name: " + this->name + "\n" + "HP: " + to_string(this->currentHP) +
           "\n" + wand + "\n";
  }
};

/**
 * The Player class
 *
 **/
class Player {

private:
public:
  Wizard *wizard;

  Player(Wizard *wizard) { this->wizard = wizard; }
};

/**
 * The Game class
 *
 **/
class Game {

private:
  Player *attacker, *defender, *playerTurn;
  int round, turn;

public:
  Game() {}

  Game(Player *player1, Player *player2) {
    this->attacker = player1;
    this->defender = player2;
    round = 1;
    turn = 1;
  }

  Game(const Game &rhs) {
    this->attacker = rhs.attacker;
    this->defender = rhs.defender;
    this->round = rhs.round;
    this->turn = rhs.turn;
    // cout << "Copy constructor called for Game" << endl;
  }

  void damage(string player, int dmg) {
    int dealingDmg = 0, dmgReduction = 0;
    Player *p;
    if (player == "attacker") {
      p = attacker;
    } else {
      p = defender;
    }

    if (attacker->wizard->house == "Gryffindor") {
      dealingDmg = dmg;
    } else if (attacker->wizard->house == "Slytherin") {
      dealingDmg = dmg * 1.15;
      if (defender->wizard->house == "Gryffindor") {
        dealingDmg = dmg * 1.2;
      }
    } else if (attacker->wizard->house == "Ravenclaw") {
      dealingDmg = dmg;
      if (round % 2 != 0) {
        dealingDmg = dmg * 1.07;
      }
    } else {
      dealingDmg = dmg * 1.07;
    }

    if (defender->wizard->house == "Gryffindor") {
      dmgReduction = dmg * 0.2;
      if (attacker->wizard->house == "Slytherin") {
        dmgReduction = dmg * 0.3;
      }
    } else if (defender->wizard->house == "Slytherin") {
      dmgReduction = 0;
    } else if (defender->wizard->house == "Ravenclaw") {
      dmgReduction = 0;
    } else {
      dmgReduction = dmg * 0.07;
    }

    int finalDmg = dealingDmg - dmgReduction;
    p->wizard->currentHP -= finalDmg;
  }

  void heal(string player, int heal) {
    Player *p;
    if (player == "attacker") {
      p = attacker;
    } else {
      p = defender;
    }

    if (p->wizard->currentHP + heal > p->wizard->startingHP) {
      p->wizard->currentHP = p->wizard->startingHP;
    } else {
      p->wizard->currentHP += heal;
    }
  }

  void equipWand(string player, bool equip) {
    Player *p;
    if (player == "attacker") {
      p = attacker;
    } else {
      p = defender;
    }

    p->wizard->hasWand = equip;
  }

  bool endGame(){
    if(attacker->wizard->currentHP < 0){
      cout << endl << endl << "Wizard " << defender->wizard->name << " wins!" << endl;
      return true;
    }else if(defender->wizard->currentHP <0){
      cout << endl << endl << "Wizard " << attacker->wizard->name << " wins!" << endl;
      return true;
    }

    return false;

  }

  void startGame() {
    bool inside= false;
    playerTurn = attacker;
    while (attacker->wizard->currentHP > 0 && defender->wizard->currentHP > 0) {

      cout << TILDAS << endl << "Round: " << round << endl << TILDAS << endl;

      playerActions();

      if(endGame()){
        inside = true;
        break;
      }

      playerActions();

      round++;
    }

    if(!inside){
      endGame();
    }
  }

  void RavenclawAutoHeal(){
    
    int heal;
    if(attacker->wizard->house == "Ravenclaw"){
      heal = attacker->wizard->startingHP * 0.05;
      if(round%2==0){
        if(attacker->wizard->currentHP + heal > attacker->wizard->startingHP){
          heal = attacker->wizard->startingHP - attacker->wizard->currentHP;
          attacker->wizard->currentHP = attacker->wizard->startingHP;
          cout << "Ravenclaw House gives you strength, you heal for " << heal << endl;
        }else{
          attacker->wizard->currentHP += heal;
          cout << "Ravenclaw House gives you strength, you heal for " << heal << endl;
        }
      }
    }
  }

  void playerActions() {
    string player = (turn % 2 == 0) ? "Player2" : "Player1";

    if (playerTurn->wizard->hasWand) {
      cout << playerTurn->wizard->name << "(" << player << ")"
           << " select spell:" << endl;
    } else {
      cout << playerTurn->wizard->name << "(" << player << ")"
           << " you lost your wand, rest for now." << endl;
    }

    RavenclawAutoHeal();

    if (playerTurn->wizard->hasWand) {
      cout << DASHES << endl;
      playerTurn->wizard->printSpells();
      cout << DASHES << endl;

      Lambda spell = pickSpell(playerTurn);
      spell();
      cout << endl;
      cout << HASHTAG << endl;
      cout << playerTurn->wizard->print();
      cout << HASHTAG << endl;
    }

    playerTurn = swapAD();
    cout << endl << endl;

    if (defender->wizard->hasWand) {
      cout << HASHTAG << endl;
      cout << playerTurn->wizard->print();
      cout << HASHTAG << endl << endl;
    }

    turn++;
  }

  Lambda pickSpell(Player *p) {
    string input;
    cin >> input;

    string spellName = p->wizard->getSpell(input);
    while (spellName == "starch") {
      cout << "This spells is unknown to this wizard! Choose again." << endl;
      cin >> input;
      spellName = p->wizard->getSpell(input);
    }

    Lambda lambda = Spell::Spells.at(input);
    return lambda;
  }

  Player *swapAD() {
    Player *tmp = attacker;
    attacker = defender;
    defender = tmp;
    return attacker;
  }

  Player *getAttacker() { return attacker; }

  Player *getDefender() { return defender; }
};

/**
 * Wand class
 * Class to support equip syntax
 **/
class Wands {

public:
  bool equip;

  Wands() {}
  Wands(bool equip) { this->equip = equip; }

  Wands operator-() { return this; }

  Wands operator--() { return this; }
};

/**
 * AD(Atttacker/Deffender) class
 * To support equip,dmg,heal and getters syntax
 **/
class AD {

public:
  string att_def;
  Game *game;
  bool AH;

  AD() {}
  AD(string ad, Game *tmp, bool AH) {
    att_def = ad;
    game = tmp;
    this->AH = AH;
  }

  AD operator-() { return AD(); }

  Wands operator-(Wands obj) { return obj; }

  void operator,(const int &number) {
    if (AH == 1) {
      game->damage(att_def, number);
    } else if(AH == 0) {
      game->heal(att_def, number);
    }
  }

  void operator,(const Wands &equip) { game->equipWand(att_def, equip.equip); }

  bool getWand() {
    if (att_def == "attacker") {
      return game->getAttacker()->wizard->hasWand;
    } else {
      return game->getDefender()->wizard->hasWand;
    }
  }

  string getName() {
    if (att_def == "attacker") {
      return game->getAttacker()->wizard->name;
    } else {
      return game->getDefender()->wizard->name;
    }
  }

  string getHouse() {
    if (att_def == "attacker") {
      return game->getAttacker()->wizard->house;
    } else {
      return game->getDefender()->wizard->house;
    }
  }

  int getHP() {
    if (att_def == "attacker") {
      return game->getAttacker()->wizard->currentHP;
    } else {
      return game->getDefender()->wizard->currentHP;
    }
  }
};

class SpellInfo {

  public:
  int duration;
  string parentSpell;

  SpellInfo(){}
  SpellInfo(int duration, string parentSpell){
    this->duration = duration;
    this->parentSpell = parentSpell;
  }

};
class AliveSpell {

  public:
  SpellInfo* spellInfo;
  Lambda subSpell;

  AliveSpell(int duration, string parentSpell, Lambda subSpell){
    this->spellInfo = new SpellInfo(duration, parentSpell);
    this->subSpell = subSpell;
  }

};