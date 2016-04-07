/*
  Bouton
 
 Allume une LED branchée sur la broche 13 lorsque le bouton
 branché sur la broche 2 est appuyé.
 */

// Initialisation des constantes :
const int buttonPin = 2;     // Numéro de la broche à laquelle est connecté le bouton poussoir
const int ledPin =  13;      // Numéro de la broche à laquelle est connectée la LED

// Déclaration des variables :
int buttonState = 0;         // variable qui sera utilisée pour stocker l'état du bouton

// le code dans cette fonction est exécuté une fois au début
void setup() {
  // indique que la broche ledPin est une sortie :
  pinMode(ledPin, OUTPUT);      
  // indique que la broche buttonPin est une entrée :
  pinMode(buttonPin, INPUT);     
}

// le code dans cette fonction est exécuté en boucle
void loop(){
  // lit l'état du bouton et stocke le résultat
  // dans buttonState :
  buttonState = digitalRead(buttonPin);

  // Si buttonState est à 5V (HIGH→bouton appuyé)
  if (buttonState == HIGH) {     
    // on allume la LED
    digitalWrite(ledPin, HIGH);  
  } 
  else {
    // sinon on éteint
    digitalWrite(ledPin, LOW); 
  }
}
