#include <help.hpp>
#include <Arduino.h>

cords help_convert_id_to_cordinates(int id,int columns){
      // Serial.println("\n--------------");
      // Serial.printf("\nColumns: %d", columns);
      // Serial.printf("\nId: %d", id);
      cords conv;
      conv.y = id % columns;
      conv.x= (id-conv.y)/columns;
      // Serial.printf("\nX: %d",conv.x);
      // Serial.printf("\nY: %d\n",conv.y);
      return conv;
}