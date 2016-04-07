/*
  
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
const int ETAT_0_DUREE_LED_VOITURE_VERTE = 3000;
const int ETAT_0_DUREE_LED_VOITURE_ROUGE = 3000;
const int ETAT_0_DUREE_LED_VOITURE_ORANGE = 1000;
// - Etat 1: mode "requête d'un piéton pour traverser"
// -> Durée pour les LEDs des voitures
const int ETAT_1_DUREE_LED_VOITURE_ORANGE = 1000;
const int ETAT_1_DUREE_LED_VOITURE_ROUGE = 5000;

// Déclaration des variables :
int buttonState = 0;  // variable qui sera utilisée pour stocker l'état du bouton

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
  // indique que la broche buttonPin est une entrée :
  pinMode(BUTTON_PIETON, INPUT);     
}
 
// le code dans cette fonction est exécuté en boucle
void loop() {
    digitalWrite(LED_PIETON_ROUGE, HIGH);
    
    digitalWrite(LED_VOITURE_ORANGE, HIGH);
    delay(ETAT_0_DUREE_LED_VOITURE_ORANGE);
    digitalWrite(LED_VOITURE_ORANGE, LOW);
  
    digitalWrite(LED_VOITURE_ROUGE, HIGH);
    delay(ETAT_0_DUREE_LED_VOITURE_ROUGE); 
    digitalWrite(LED_VOITURE_ROUGE, LOW);

    // lit l'état du bouton et stocke le résultat
    // dans buttonState :
    buttonState = digitalRead(BUTTON_PIETON);

    // Si buttonState est à 5V (HIGH→bouton appuyé)
    if (buttonState == HIGH) {
      // Etat: 1
      digitalWrite(LED_VOITURE_ORANGE, HIGH);
      delay(ETAT_1_DUREE_LED_VOITURE_ORANGE);
      digitalWrite(LED_VOITURE_ORANGE, LOW);
            
      digitalWrite(LED_PIETON_ROUGE, LOW);      
      digitalWrite(LED_PIETON_VERTE, HIGH);
 
      digitalWrite(LED_VOITURE_ROUGE, HIGH);
      delay(ETAT_1_DUREE_LED_VOITURE_ROUGE);
      digitalWrite(LED_VOITURE_ROUGE, LOW);
      
      digitalWrite(LED_PIETON_VERTE, LOW);
      digitalWrite(LED_PIETON_ROUGE, HIGH);
    } 
    else {
      // Etat: 0
      digitalWrite(LED_VOITURE_VERTE, HIGH);
      delay(ETAT_0_DUREE_LED_VOITURE_VERTE);
      digitalWrite(LED_VOITURE_VERTE, LOW);
    }
}