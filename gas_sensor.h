#ifdef CLASSES
#include "classes.h"
#define CLASSES
#endif

class Gas_Sensor {
  public:
    bool static aboveRed(int gas_level) {
      const int RED = 800;

      return gas_level > RED;
    }

    bool static aboveYellow(int gas_level) {
      const int YELLOW = 400;

      return gas_level > YELLOW;
    }
};

