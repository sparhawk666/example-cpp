#ifndef CMAKE_DEMO_PLANTWATERER_H
#define CMAKE_DEMO_PLANTWATERER_H

#include <string>

class PlantWaterer
{
public:
    PlantWaterer();

    std::string getName();
    void setName(std::string newName);
    int getWaterPercentage();

    void fillWater();
    void sprayWater();

private:
    std::string mName;
    int mWaterPercentage;
};

#endif //CMAKE_DEMO_PLANTWATERER_H
