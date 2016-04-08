//  _ ___ _______     ___ ___ ___  ___ _   _ ___ _____ ___ 
// / |_  )__ /   \   / __|_ _| _ \/ __| | | |_ _|_   _/ __| 
// | |/ / |_ \ |) | | (__ | ||   / (__| |_| || |  | | \__ \ 
// |_/___|___/___/   \___|___|_|_\\___|\___/|___| |_| |___/ 
// 
// 2016-04-07_-_MOOC_FUN_-_TP2_Feux_Voiture_Pieton_BoutonPoussoir
// 
// Made by Lionel Atty
// License: CC-BY-SA 3.0
// Downloaded from: https://123d.circuits.io/circuits/1908987-2016-04-07_-_mooc_fun_-_tp2_feux_voiture_pieton_boutonpoussoir

/*
  TP2: Feu Tricolores + bouton piéton (feu bicolores)

  J'ai essayé de mettre en place d'un Automate Fini (SM:`States Machine` => https://fr.wikipedia.org/wiki/Automate_fini).

  La SM est définie par 3 états/states et ces transitions:
    - Etat 0: Mode "normal". Active le fonctionnement des feux/leds orange et rouge du feu VOITURE.
    - Etat 1: Gère le fonctionnement (normal) du feu vert VOITURE
    - Etat 2: Gère le fonctionnement des feux orange/rouge VOITURE et vert/rouge PIETON
  Transitions:
    E0 -> E1: Sans condition                          [always pass]
    E1 -> E0: Si le bouton poussoir n'est pas appuyé  [conditionnal pass]
    E1 -> E2: Si le bouton poussoir est appuyé        [conditionnal pass]
    E2 -> E0: Sans condition                          [always pass]  
  -> Cette défintion est un peu formelle, mais normalement vous devez pouvoir reconstruire le diagramme d'état lié à cet automate.

  J'ai essayé autant que possible de suivre les consignes du TP.
  Des extraits de ces consignes sont présents dans les commentaires du code,
  pour suivre l'enchainements des contraintes/consignes.

  ps: Il y a une notion d'interprétation et choix par rapport aux consignes.
  Cette partie de consigne "Si le bouton est maintenu appuyé pendant que le feu voiture est au vert"
  est assez ambigüe car on ne sait pas (encore) gérer la notion temporelle de "pendant" (il faudrait un mécanisme d'interruption
  pour stocker le changement d'état du bouton poussoir (pendant le délai du feu vert VOITURE)).
  J'ai choisi comme point de mise à jour du changement de statut du bouton poussoir (ou validation de la requête piéton)
  le moment ou le feu/led vert VOITURE s'éteint. 
  Mais c'est un choix, j'aurais pu choisir (peut être ce que vous avez fait) de vérifier l'état du bouton poussoir 
  avant l'allumage du feu vert VOITURE.

  Bonne lecture :-)
*/

// Initialisation des constantes :
const int LED_VOITURE_VERTE = 10;   // Numéro de la broche à laquelle est connecté la led verte pour le feu voiture
const int LED_VOITURE_ORANGE = 11;  // Numéro de la broche à laquelle est connecté la led orange pour le feu voiture
const int LED_VOITURE_ROUGE = 12;   // Numéro de la broche à laquelle est connecté la led rouge pour le feu voiture
//
const int LED_PIETON_VERTE = 8;   // Numéro de la broche à laquelle est connecté la led verte pour le feu piéton
const int LED_PIETON_ROUGE = 9;   // Numéro de la broche à laquelle est connecté la led rouge pour le feu piéton
//
const int BUTTON_PIETON = 2;      // Numéro de la broche à laquelle est connecté le bouton poussoir pour le feu piéton

// Constantes stockant les durées
// d'allumage des différentes LEDs
// selon l'état/mode de fonctionnement:
//
// - Etat 0: mode "normal" (TP1 - Feu Tricolore)
// -> Durée pour les LEDs des voitures
const int ETAT_0_DUREE_LED_VOITURE_VERTE = 3000;    // => 3 secondes
const int ETAT_0_DUREE_LED_VOITURE_ROUGE = 3000;    // => 3 secondes
const int ETAT_0_DUREE_LED_VOITURE_ORANGE = 1000;   // => 1 seconde
// - Etat 1: mode "requête d'un piéton pour traverser"
// -> Durée pour les LEDs des voitures
const int ETAT_1_DUREE_LED_VOITURE_ORANGE = 1000;   // => 1 seconde
const int ETAT_1_DUREE_LED_VOITURE_ROUGE = 5000;    // => 5 secondes
// à noter que `ETAT_1_DUREE_LED_VOITURE_ROUGE` correspond aussi au timing
// du feu vert pour les piétons (synchronisation directe entre le feu rouge voiture et vert piéton)

// Déclaration des variables :
int buttonState = 0;  // variable qui sera utilisée pour stocker l'état du bouton
int currentState = 0;

// le code dans cette fonction est exécuté une fois au début
void setup() {
  // ---------------------------------------------------------------------------------
  // Setup des broches en sorties 
  // pour les LEDs pour le feu tricolor lié au voiture
  // ---------------------------------------------------------------------------------
  // indique que la broche LED_VOITURE_VERTE est une sortie :
  pinMode(LED_VOITURE_VERTE, OUTPUT);
  // indique que la broche LED_VOITURE_ORANGE est une sortie :
  pinMode(LED_VOITURE_ORANGE, OUTPUT);
  // indique que la broche LED_VOITURE_ROUGE est une sortie :
  pinMode(LED_VOITURE_ROUGE, OUTPUT);
  
  // ---------------------------------------------------------------------------------
  // Setup des broches en sorties 
  // pour les LEDs pour le feu tricolor lié au piéton
  // ---------------------------------------------------------------------------------
  // indique que la broche LED_PIETON_VERTE est une sortie :
  pinMode(LED_PIETON_VERTE, OUTPUT);
  // indique que la broche LED_PIETON_ROUGE est une sortie :
  pinMode(LED_PIETON_ROUGE, OUTPUT);  

  // ---------------------------------------------------------------------------------
  // Setup de la broches en entrée
  // pour le bouton poussoir piéton
  // ---------------------------------------------------------------------------------
  // indique que la broche BUTTON_PIETON est une entrée :
  pinMode(BUTTON_PIETON, INPUT);     
}
 
// le code dans cette fonction est exécuté en boucle
void loop() {
  if (currentState == 0) {
    // *******************************************************************************
    // Machine-State
    // -> Etat courant = Etat 0
    // *******************************************************************************
    // -------------------------------------------------------------------------------
    // | - Consignes TP -
    // -------------------------------------------------------------------------------
    // - Le feu piéton est constamment rouge (rouge→9 et vert→8) [tant que le bouton (broche 2) n'est pas appuyé]
    // -------------------------------------------------------------------------------
    // => On utilise la 1ère partie de la consigne de l'énoncé: "Le feu piéton est constamment rouge"
    //
    // - Une LED rouge PIETON (branchée sur la broche 9) reste allumée
    digitalWrite(LED_PIETON_ROUGE, HIGH);    
    //
    // - Une LED orange VOITURE (branchée sur la broche 11) allumée pendant 1 seconde
    digitalWrite(LED_VOITURE_ORANGE, HIGH);
    delay(ETAT_0_DUREE_LED_VOITURE_ORANGE);
    digitalWrite(LED_VOITURE_ORANGE, LOW);
    //
    // - Une LED rouge VOITURE (branchée sur la broche 12) allumée pendant 3 secondes
    digitalWrite(LED_VOITURE_ROUGE, HIGH);
    delay(ETAT_0_DUREE_LED_VOITURE_ROUGE); 
    digitalWrite(LED_VOITURE_ROUGE, LOW);

    // *******************************************************************************
    // Machine-State
    // -> Transition: Etat 0 -> Etat 1
    // *******************************************************************************
    currentState = 1;
  }
  else if (currentState == 1) {
    // *******************************************************************************
    // Machine-State
    // -> Etat courant = Etat 1
    // *******************************************************************************
    // - Une LED verte VOITURE (branchée sur la broche 10) allumée pendant 3 secondes
    digitalWrite(LED_VOITURE_VERTE, HIGH);
    delay(ETAT_0_DUREE_LED_VOITURE_VERTE);
    digitalWrite(LED_VOITURE_VERTE, LOW);

    // -------------------------------------------------------------------------------
    // | - Consignes TP -
    // -------------------------------------------------------------------------------
    // - [Le feu piéton est constamment rouge (rouge→9 et vert→8)] tant que le bouton (broche 2) n'est pas appuyé
    // -------------------------------------------------------------------------------
    // => On utilise la 2nde partie de la consigne de l'énoncé: "tant que le bouton (broche 2) n'est pas appuyé"
    //
    // lit l'état du bouton et stocke le résultat
    // dans buttonState :
    buttonState = digitalRead(BUTTON_PIETON);

    // -------------------------------------------------------------------------------
    // | - Consignes TP -
    // -------------------------------------------------------------------------------
    //  Si le bouton est maintenu appuyé pendant que le feu voiture est au vert
    // -------------------------------------------------------------------------------
    // Si buttonState est à 5V (HIGH→bouton appuyé)
    if (buttonState == HIGH) {
      // *******************************************************************************
      // Machine-State
      // -> Transition: Etat 1 -> Etat 2
      // *******************************************************************************
      currentState = 2;
    }
    else {
      // *******************************************************************************
      // Machine-State
      // -> Transition: Etat 1 -> Etat 0
      // *******************************************************************************
      currentState = 0;
    }
  }
  else {  // currentState = 2
    // *******************************************************************************
    // Machine-State
    // -> Etat courant = Etat 2
    // -------------------------------------------------------------------------------
    // | - Consignes TP -
    // -------------------------------------------------------------------------------
    //  alors le feu tricolore passe au orange allumé pendant 1 seconde
    // -------------------------------------------------------------------------------
    // - Une LED orange VOITURE (branchée sur la broche 11) allumée pendant 1 seconde
    digitalWrite(LED_VOITURE_ORANGE, HIGH);
    delay(ETAT_1_DUREE_LED_VOITURE_ORANGE);
    digitalWrite(LED_VOITURE_ORANGE, LOW);

    // -------------------------------------------------------------------------------
    // | - Consignes TP -
    // -------------------------------------------------------------------------------
    //  puis rouge pendant 5 secondes durant lesquelles le feu vert piéton passe au vert
    // -------------------------------------------------------------------------------
    // => on doit traiter les deux actions dans la même séquence,
    // car c'est le feu rouge VOITURE qui détermine le timing/synchronisation temporelle
    // (le delay), donc controle le temps pour son feu rouge et le feu vert PIETON
    //
    // - Une LED rouge PIETON (branchée sur la broche 9) éteinte
    // - Une LED verte PIETON (branchée sur la broche 8) allumée pendant 5 secondes (liée au rouge VOITURE)
    digitalWrite(LED_PIETON_ROUGE, LOW);      
    digitalWrite(LED_PIETON_VERTE, HIGH); 
    //
    // - Une LED rouge VOITURE (branchée sur la broche 12) allumée pendant 5 secondes
    digitalWrite(LED_VOITURE_ROUGE, HIGH);
    delay(ETAT_1_DUREE_LED_VOITURE_ROUGE);
    digitalWrite(LED_VOITURE_ROUGE, LOW);

    // - Une LED rouge PIETON (branchée sur la broche 9) allumée
    // - Une LED verte PIETON (branchée sur la broche 8) éteinte
    digitalWrite(LED_PIETON_ROUGE, HIGH);
    digitalWrite(LED_PIETON_VERTE, LOW);

    // *******************************************************************************
    // Machine-State
    // -> Transition: Etat 2 -> Etat 1
    // *******************************************************************************
    currentState = 1;
  }
}