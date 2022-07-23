
#include <functional>
#include <iostream>
#include <map>

using namespace std;
using Lambda = function<void(void)>;
int rounds = 0;
int AH; // attack or heal
string wizardName;
// stringify 
#define str(x) #x
// program main
#define BEGIN_GAME int main() {SHOW "";Game tmp;Wands wand1(false),wand2(true);AD tempAD;
#define END_GAME }

// keywords
#define CREATE ;
#define START [&]() -> void {
#define END ;}

// objects
#define WIZARD Wizard
#define WIZARDS tmpWizard
#define SPELL Spell
#define SPELLS tmpSpell

// attributes
#define NAME false ? "never gonna"
#define HOUSE false ? "give you up"
#define HP false ? 1

// Functors?
#define ACTION false ? (Lambda)[&]() -> void {}
#define EQUIP ;
#define _ wand1
#define a wand2

#define HEAL ;AH=0;
#define DAMAGE ;AH=1;
#define ATTACKER tempAD = AD("attacker", &tmp, AH),
#define DEFENDER tempAD = AD("defender", &tmp, AH),
#define MR ;wizardName = 
#define MRS ;wizardName =
#define LEARN ;tmpWizard

// functions
#define GET_HOUSE(A_D) (AH=2,A_D tempAD.getHouse())
#define GET_NAME(A_D) (AH=2,A_D tempAD.getName())
#define GET_HP(A_D) (AH=2,A_D "xd", tempAD.getHP())
#define HAS_WAND(A_D) (AH=2,A_D "xd", tempAD.getWand())      
#define SPELL_NAME(spellName) -Wizard::learnSpell(wizardName, #spellName)


// primitives and logic
template <typename T> bool AND(T first, T second) { return (first && second); }

template <typename T, typename... arguments>
bool AND(T first, T second, arguments... args) {
  return AND((first && second) ? 1 : 0, args...);
}

template <typename T> bool OR(T first, T second) { return (first || second); }

template <typename T, typename... arguments>
bool OR(T first, T second, arguments... args) {
  return OR((first || second) ? 1 : 0, args...);
}

#define NOT(a) (!a)

#define IF ;if(
#define DO ){
#define ELSE_IF ;}else if(
#define ELSE ;}else{

#define FOR ;int duration =
#define ROUNDS ;Lambda tmpLambda = [&](

#define AFTER ;for(int tmp=
#define SHOW ;cout << "\x1B[32m" <<

#define DUEL ;tmp = setGame();Game* new_game = &tmp;new_game->startGame();

#include "HogwartsClasses.h"
// ---------------------- Initializations --------------------------------

// instance of Wizard class so I can use [] operator on it.
Wizard tmpWizard;
// initialization of 0th wizard of the static member of the class, will be used
// as a refference and should remain hidden.
vector<Wizard> Wizard::Wizards = {{"potato", "potat", 1000}};

// instance of Spell class so I can use [] operator on it.
Spell tmpSpell;
// initialization of 0th spell of the static member of the class, will be used
// as a refference and should remain hidden.
map<string, Lambda> Spell::Spells = {
    {"starch", []() { cout << "Starches will make you fat\n"; } }
};

map<string, AliveSpell> AliveSpells;
// ---------------- Helper functions ----------------------------------------

string pickWizard() {
  string wizardInput;
  string wizardFirstName, wizardLastName;
  cin >> wizardFirstName >> wizardLastName;
  wizardInput = wizardFirstName + " " + wizardLastName;
  while (Wizard::getWizard(wizardInput).name == "potato") {
    cout << wizardInput << endl;
    cout << "Invalid wizard, please choose again a valid wizard from the "
            "above "
            "list."
          << endl;
    cin >> wizardFirstName >> wizardLastName;
    wizardInput = wizardFirstName + " " + wizardLastName;
  }
  return wizardInput;
}

Game setGame() {
    cout << "---------------------------- HARRY POTTER THE GAME "
            "----------------------------"
        << endl
        << endl;
    cout << "Player1 select wizard:" << endl << DASHES << endl;

    Wizard::printWizards();

    cout << DASHES << endl;
    string wizardInput = pickWizard();

    // creating wizard copy for player1
    Wizard *tmp1 = new Wizard(Wizard::getWizard(wizardInput));
    Wizard *wizard1 = tmp1;
    Player *player1 = new Player(wizard1);
    Player *p1 = player1;
    cout << endl << "Player 2 select wizard: " << endl << DASHES << endl;

    Wizard::printWizards();

    cout << DASHES << endl;

    wizardInput = pickWizard();

    // creating wizard copy for player2
    Wizard *tmp2 = new Wizard(Wizard::getWizard(wizardInput));
    Wizard *wizard2 = tmp2;
    Player *player2 = new Player(wizard2);
    Player *p2 = player2;

    Game new_game(p1, p2);

    cout << endl;

    return new_game;
}