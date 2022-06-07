#include "PlantWaterer.h"

//!
//! \brief A PlantWaterer object, used to water plants (or other things you may find worth watering)
//!
PlantWaterer::PlantWaterer() :
    mName(""),
    mWaterPercentage(0)
{
}

//!
//! \brief Return name of PlantWaterer
//! \return name of PlantWaterer, or an empty string if name has not been set
//!
std::string PlantWaterer::getName()
{
    return mName;
}

//!
//! \brief Sets a new name for PlantWaterer
//! \param newName a string used to set new name of PlantWaterer
//!
void PlantWaterer::setName(std::string newName)
{
    mName = newName;
}

//!
//! \brief Return the percentage of water left in PlantWaterer
//! \return percentage of water in PlantWaterer
//!
int PlantWaterer::getWaterPercentage()
{
    return mWaterPercentage;
}

//!
//! \brief Fully fills up PlantWaterer
//!
void PlantWaterer::fillWater()
{
    mWaterPercentage = 100;
}

//!
//! \brief Use up a small amount of water to spray some water (preferably on plants)
//!
void PlantWaterer::sprayWater()
{
    mWaterPercentage -= 15;
    if (mWaterPercentage < 0)
    {
        mWaterPercentage = 0;
    }
}
