void werterfassung() {

  // get analog value of noise signal
  unsigned int count = 0;
  randomSeed(analogRead(14));
  while (count < loops) {
    zufall = analogRead(14);
    delay(random(1,100));
    if (zufall >10 && zufall <= 410){ // subtract DC-level
      array[count] = zufall-10;
      count++;
    }
  }    
}