// Chi-Quadrat-Test für chiquadrat[i]

bool chi_quadrat() {

  bin=10; 
  // 1. Find maximum in array
  int maxVal = 0;
  for (unsigned int i = 0; i < loops; i++) {
    if (array[i] > maxVal) {
      maxVal = array[i];
    }
  }
  
  Serial.print("\nThe maximum value is: ");
  Serial.println(maxVal);
  
  // 2. build arry chiquadrat[25]
  int chiquadrat[bin] = {0};
  
  // 3. find bin-size
  int rangeSize = maxVal / bin;
  if (rangeSize == 0) {
    rangeSize = 1; 
  }
  
  // 4. sort values and count them
  for (unsigned int i = 0; i < loops; i++) {
    int value = array[i];
    int index = value / rangeSize;
    if (index >= bin) {
      index = (bin-1); 
    }
    chiquadrat[index]++;
  }
  
  // exspected nr density
  int expected[bin];

  // calculate probability
  for (int i = 0; i < bin; i++) {
    expected[i] = loops / bin; // uniformly distributed = exspectation
  }

  // calculate chi-square
  double chiSquare = 0.0;
  for (int i = 0; i < bin; i++) {
    double diff = chiquadrat[i] - expected[i];
    chiSquare += (diff * diff) / expected[i];
  }

  // Ouput
  Serial.println("\nChi-square test at level of significance 𝛂 = 0,01 [1%]\n");
  Serial.print("Chi-square Value: ");
  Serial.print(chiSquare, 2);Serial.println("   |  critical value for this setup = 21,67");

  // Lookup other values in chi-square table if you want another setup
  double criticalValue = 21.67;

  if (chiSquare < criticalValue) {
    Serial.println("Your RNs seem to be uniformly distributed.");
    Go_noGo = true; // Test positive!
  } else {
    Serial.println("Your RNs seem to NOT be uniformly distributed.");
  }
  return Go_noGo;
}