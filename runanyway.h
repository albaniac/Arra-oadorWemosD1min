//aciona os pinos definidos na função
void runAndWait(int pin, int Status, int interval) // pino, status, invervalo
{
  digitalWrite(pin,  Status);
  delay(interval);
  digitalWrite(pin,  !Status);
  delay(100);
}

