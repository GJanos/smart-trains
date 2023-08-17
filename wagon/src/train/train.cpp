#include "Train.h"
namespace sendTrain {

std::string serialize(trainObj* myCurrentTrain){
// Create a JSON object
    DynamicJsonDocument doc(400);

    // Convert the trainObj struct to a JSON object
    doc["ID"] = myCurrentTrain->trainID;

    JsonArray wagonArray = doc.createNestedArray("wagon");
    for (const auto& wagon : myCurrentTrain->wagonInfos) {
        JsonObject wagonObj = wagonArray.createNestedObject();
        wagonObj["ID"] = wagon.wagonID;
        wagonObj["length"] = wagon.length;
        wagonObj["occup"] = wagon.occup;
    }


    // Serialize the JSON object to a string
    String jsonString;
    serializeJson(doc, jsonString);

    return {jsonString.c_str()};
}

}