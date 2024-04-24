#include <help.hpp>
#include <Arduino.h>

cords help_convert_id_to_cordinates(int id,int columns){
      cords conv;
      conv.y = id % columns;
      conv.x= (id-conv.y)/columns;
      return conv;
}