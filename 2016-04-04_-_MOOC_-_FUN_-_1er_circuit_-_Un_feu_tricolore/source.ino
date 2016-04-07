/*
  Feu tricolore
  1) Allume la LED verte pendant 3 secondes,
  2) 
  gerber/a) Eteindre la LED verte
    b) Allumer la LED orange pendant 1 seconde
  3)
  gerber/a) Eteindre la LED orange
    b) Allumer la LED rouge pendant 3 secondes
  4) Eteindre la LED rouge
  -> Boucle (retour à 1)
*/
 
// Numéros des broches qui sont
// connectées aux LEDs
// 3 LEDs rouge/orange/vert
// => 3 broches: 13/12/11
int led_RED= 13;
int led_ORANGE= 12;
int led_GREEN= 11;

// Variables stockant les timings 
// d'allumage des différentes LEDs (vert/rouge/orange)
int timing_for_GREEN gerber/= 3000;
int timing_for_RED gerber/= 3000;
int timing_for_ORANGE gerber/= 1000;

// le code dans cette fonction est exécuté une fois au début
void setup() {
  // on indique les broches (13/12/11) des LEDs (rouge/orange/vert)
  // qui vont être mises sous tension
  pinMode(led_RED, gerber/OUTPUT);
  pinMode(led_ORANGE, gerber/OUTPUT);
  pinMode(led_GREEN, gerber/OUTPUT);
}
 
// le code dans cette fonction est exécuté en boucle
void loop() {
  // 1) Allume la LED verte pendant 3 secondes,
  digitalWrite(led_GREEN, HIGH);   // allumer la LED vert (tension 5V sur la broche (11))  
  delay(timing_for_GREEN);         // attendre 3000ms = 3s (timing pour la LED verte)  
  // 2)
  //   a) Eteindre la LED verte
  digitalWrite(led_GREEN, LOW);dre la LED vert (tension 0V sur la broche (11))
  //   b) Allumer la LED orange pendant 1 seconde
  digitalWrite(led_ORANGE, HIGH);// allumer la LED orange (tension 5V sur la broche (12))  
  delay(timing_for_ORANGE);         // attendre 1000ms = 1s (timing pour la LED orange)
  // 3)
  //   a) Eteindre la LED orange
  digitalWrite(led_ORANGE, LOW);   // éteindre la LED orange (tension 0V sur la broche (12))
  //   b) Allumer la LED rouge pendant 3 secondes
  digitalWrite(led_RED, HIGH);   // allumer la LED rouge (tension 5V sur la broche (13))
  delay(timing_for_RED);            // attendre 3000ms = 3s (timing pour la LED rouge)  
  // 4) Eteindre la LED rouge
  digitalWrite(led_RED, LOW);   // éteindre la LED rouge (tension 0V sur la broche (13))
  // -> Boucle (retour à 1)
}

