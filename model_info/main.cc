#include "model.h"

int main() {
  Model model;
  model.Deserialize("test_little2.obj");
  model.SerializeBinary("b_test.bin");

  Model new_model;
  new_model.DeserializeBinary("b_test.bin");
  new_model.Serialize("t_test.obj");

  return 0;
}