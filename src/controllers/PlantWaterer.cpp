#include "PlantWaterer.h"

PlantWaterer::PlantWaterer() :
    mName(""),
    mWaterPercentage(0)
{
}

std::string PlantWaterer::getName()
{
    return mName;
}

void PlantWaterer::setName(std::string newName)
{
    mName = newName;
}

int PlantWaterer::getWaterPercentage()
{
    return mWaterPercentage;
}

void PlantWaterer::fillWater()
{
    mWaterPercentage = 100;
}

void PlantWaterer::sprayWater()
{
    mWaterPercentage -= 15;
    if (mWaterPercentage < 0)
    {
        mWaterPercentage = 0;
    }
}
