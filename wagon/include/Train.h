#ifndef ITRAIN_H
#define ITRAIN_H

#include <vector>
#include <ArduinoJson.h>

namespace sendTrain{

    class wagonObj
    {
        public:
            wagonObj(int wagonID, int occup, int length): wagonID(wagonID), occup(occup), length(length){};
            int wagonID;
            int occup;
            int length;
        
    };

    class trainObj
    {
        public:
        int trainID;
        std::vector<wagonObj> wagonInfos;
        trainObj(int trainID): trainID(trainID){
            
        }
        
    };
    std::string serialize(trainObj* myCurrentTrain);
}

#endif