void csv_Daten() {

// RN array as CSV
  Serial.println("\nCSV-output of RN array:");
  for (unsigned int i = 0; i < loops; i++) {
    Serial.print(array[i]);
    if (i < loops - 1) {
      Serial.print(";"); // separator
    } else {
      Serial.println(); // line end
    }
  }
}