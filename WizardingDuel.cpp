#include "Hogwarts.h"

BEGIN_GAME

	SHOW "test " << AND(1, 0, 0) << "\n"

	CREATE WIZARD {
		NAME: "Big Boi",
		HOUSE: "Gryffindor",
		HP: 100
	}

	CREATE WIZARDS [
		WIZARD {
			NAME: "Banana Banania",
			HOUSE: "Hufflepuff",
			HP: 80
		},
		WIZARD {
			NAME: "Yolo Swag",
			HOUSE: "Ravenclaw",	
			HP: 75
		},
		WIZARD {
			NAME: "Salamander Solemn",
			HOUSE: "Slytherin",
			HP: 200
		}
	]

	CREATE SPELL {
		NAME: "Avada_Kadavra",
		ACTION: START
			DAMAGE DEFENDER 50

			IF( AND(GET_HOUSE(DEFENDER)== "Gryffindor", GET_HOUSE(ATTACKER) == "Slytherin") ) DO
				DAMAGE DEFENDER 50
			END

		END
	}
	
	CREATE SPELLS [
		SPELL {
			NAME: "Expelliarmus_Maxima",
			ACTION: START	
				EQUIP DEFENDER _
			END
		},
		SPELL {
			NAME: "Hocus_Pocus",
			ACTION: START
				EQUIP DEFENDER ---a
				// FOR 3 ROUNDS DO
				// 	SHOW "HELP" << endl
					
				// END

			END
		},
		SPELL{
			NAME: "Anapneo",
			ACTION: START

				SHOW GET_HOUSE(ATTACKER) << endl
				SHOW GET_HOUSE(DEFENDER) << endl
				SHOW GET_NAME(ATTACKER) << endl
				SHOW GET_NAME(DEFENDER) << endl
				SHOW HAS_WAND(ATTACKER) << endl
				SHOW HAS_WAND(DEFENDER) << endl
				SHOW GET_HP(ATTACKER) << endl
				SHOW GET_HP(DEFENDER) << endl
				
				HEAL ATTACKER 20;
			END
		}
	]

	MR "Yolo Swag" LEARN [
	  	SPELL_NAME(Hocus_Pocus)
	]

	MR "Yolo Swag" LEARN [
		SPELL_NAME(Avada_Kadavra)
		SPELL_NAME(Anapneo)
		SPELL_NAME(Expelliarmus_Maxima)
	]
	
	MR "Salamander Solemn" LEARN [
		SPELL_NAME(Avada_Kadavra)
		SPELL_NAME(Expelliarmus_Maxima)
		SPELL_NAME(Hocus_Pocus)
		SPELL_NAME(Anapneo)
		SPELL_NAME(Expulso)
	]

	MRS "Banana Banania" LEARN [
		SPELL_NAME(Anapneo)
		SPELL_NAME(Avada_Kadavra)
	]

	MR "Big Boi" LEARN [
		SPELL_NAME(Anapneo)
		SPELL_NAME(Avada_Kadavra)
	]

	DUEL

END_GAME
