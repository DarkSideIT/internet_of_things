

class LedController{
  bool state;
public:
  LedController() {
    state = false;
    digitalWrite(LED_BUILTIN, HIGH);
  }
  void On() {
    state = true;
    digitalWrite(LED_BUILTIN, LOW);
  }

  void Off() {
    state = false;
    digitalWrite(LED_BUILTIN, HIGH);
  }
};