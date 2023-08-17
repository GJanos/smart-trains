#pragma once

#include <vector>
#include <ArduinoJson.h>
#include <stdlib.h>
#include <map>
#include <memory>

namespace TrainData {
  struct Wagon
  {
      int ID;
      int length;
      int occupationLevel;
  };

  struct Train
  {
      int ID;
      public:
      std::map<int, Wagon> wagons;
  };

  Train* deserializeTrain(const std::string& jsonString);
  
}