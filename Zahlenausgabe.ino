void zufallszahlen() {
 // Output of RN-array
 
  Serial.println("\nOutput of RN-array:");
  for (unsigned int i = 0; i < loops; i += 10) {
    for (unsigned int j = i; j < i + 10 && j < loops; j++) {
      Serial.print(array[j]);
      Serial.print("\t");
    }
    Serial.println(); 
  }
}