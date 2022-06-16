#include <gtest/gtest.h>

#include <controllers/PlantWaterer.h>

using namespace testing;

class PlantWatererTest : public ::testing::Test
{
public:
    PlantWatererTest() = default;
    ~PlantWatererTest() override = default;

protected:
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(PlantWatererTest, TestCorrectNameIsSet)
{
    //arrange
    PlantWaterer pw{};

    //act
    pw.setName("HydroMaatje");

    //assert
    ASSERT_EQ(pw.getName(), "HydroMaatje");

    //cleanup
}

TEST_F(PlantWatererTest, TestWaterIsFullyFilled)
{
    //arrange
    PlantWaterer pw{};

    //act
    pw.fillWater();

    //assert
    ASSERT_EQ(pw.getWaterPercentage(), 100);

    //cleanup
}

TEST_F(PlantWatererTest, TestSprayCausesLowerPercentage)
{
    //arrange
    PlantWaterer pw{};

    //act
    pw.fillWater();
    auto oldPercentage = pw.getWaterPercentage();
    pw.sprayWater();
    auto newPercentage = pw.getWaterPercentage();

    //assert
    ASSERT_EQ(oldPercentage, 100);
    ASSERT_EQ(newPercentage, 85);

    //cleanup
}
