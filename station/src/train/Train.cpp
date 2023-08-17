 #include "Train.h"
 
 namespace TrainData
 {
    Train* deserializeTrain(const std::string& jsonString)
    {
        const char* ConvertedjsonString = jsonString.c_str();

        DynamicJsonDocument doc(400);

        // Deserialize the JSON string
        DeserializationError error = deserializeJson(doc, ConvertedjsonString);
        
        if (error) {
        Serial.print("Failed to deserialize JSON: ");
        Serial.println(error.c_str());
        return nullptr;
        }

        // Extract values from the JSON object
        Train* myTrain = new Train();
        myTrain->ID = doc["ID"].as<int>();

        const JsonArray wagonArray = doc["wagon"].as<JsonArray>();
        for (const auto& wagonJson : wagonArray) {
        Wagon wagon;
        //Serial.println("tering");
        wagon.ID = wagonJson["ID"];
        wagon.length = wagonJson["length"];
        wagon.occupationLevel = wagonJson["occup"];

        myTrain->wagons[wagon.ID] = wagon;
        }
        
        return myTrain;
    }

    
}