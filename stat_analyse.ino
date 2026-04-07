 void statistik (){
 

  // 1. Find maximum in RN array
  int maxVal = 0;
  for (unsigned int i = 0; i < loops; i++) {
    if (array[i] > maxVal) {
      maxVal = array[i];
    }
  }
  
  if (statswitch == false){
    Serial.print("\nThe maximum value is: ");
    Serial.println(maxVal);
    }
  
  // 2. Build array chiquadrat[25]
  int chiquadrat[bin] = {0};
  
  // 3. find bin size
  int rangeSize = maxVal / bin;
  if (rangeSize == 0) {
    rangeSize = 1; 
  }
  
  // 4. Sort values and count
  for (unsigned int i = 0; i < loops; i++) {
    int value = array[i];
    int index = value / rangeSize;
    if (index >= bin) {
      index = (bin-1); 
    }
    chiquadrat[index]++;
  }
  
  // 5. Output
  if (statswitch == false){
    Serial.println("\nDistribution of values in the bins:");
    }
  for (int i = 0; i < bin; i++) {
    int lowerBound = i * rangeSize;
    int upperBound = (i + 1) * rangeSize - 1;
    if (i == (bin-1)) {
      
      upperBound = maxVal;
    }
    if (statswitch == false){
      Serial.print("Bin boundaries ");
      Serial.print(lowerBound);
      Serial.print(" - ");
      Serial.print(upperBound);
      Serial.print(": ");
      
      Serial.println(chiquadrat[i]);
    }
  }
  if (statswitch == true){
    for (int i = 0; i < bin; i++) {
         Serial.println(chiquadrat[i]);
        }
      }
    
  statswitch = false; 
 }