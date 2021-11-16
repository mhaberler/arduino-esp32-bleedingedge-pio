#include <Arduino.h>
#include <Ticker.h>

RTOSTicker t1, t2, t3, t4;

int counter;

void first(void) { Serial.println("first called "); }

void second_with_arg(int answer) {
  Serial.printf("second. The answer is: %d\n", answer);
}

void third_with_arg(int answer) {
  Serial.printf("third. The answer is: %d\n", answer);
}

void periodic_with_arg(int c) {}

void setup() {
  Serial.begin(115200);
  int foo = 42;

  t1.once_ms(1000, first);
  t2.once_ms(2000, [foo](void) { return second_with_arg(foo); });
  t3.once_ms(
      3000, [foo](void) { Serial.printf("via lambda, captured arg=%d", foo); });
  foo = 4712;
  t4.attach_ms(1000, [&t4, foo](void) {
    static int countdown = 5;
    Serial.printf("via lambda with Timer captured, captured arg=%d active=%d "
                  "periodic=%d\n",
                  foo, t4.active(), t4.periodic());
    if (t4.periodic() && countdown == 0) {
      Serial.println("detaching..");
      t4.detach();
    }
    countdown--;
  });
}

void loop() {}