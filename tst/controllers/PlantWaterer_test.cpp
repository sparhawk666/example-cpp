#include <gtest/gtest.h>

#include <controllers/PlantWaterer.h>

using namespace testing;

class Gieter
{
public:
    [[nodiscard]] int getVolume() const { return 10; }
};

class Fles
{
public:
    [[nodiscard]] int getVolume() const { return 1; }
};

class Spuit
{
public:
    [[nodiscard]] int getVolume() const { return 5; }
};

class PlantWatererTest : public ::testing::Test
{
public:
    PlantWatererTest() = default;
    ~PlantWatererTest() override = default;

protected:
    void SetUp() override {}

    void TearDown() override {}
};

using var_t = std::variant<Gieter, Fles, Spuit>;

// helper type for the visitor #4
template<class... Ts>
struct overloaded : Ts...
{
    using Ts::operator()...;
};
// explicit deduction guide (not needed as of C++20)
template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

//!
//! \brief CertificateManagerWhenTransferRequestIsReceived
//! Objective: Evaluate flow in TransferRequest function. CSR generation fails.
//!
TEST_F(PlantWatererTest, TransferRequestFlow)
{
    //arrange
    std::vector<var_t> vec = {Gieter(), Fles(), Spuit(), Gieter()};

    //act
    for (auto& v : vec)
    {
        auto caller = [](const auto& obj) {
            std::cout << "Volume: " << obj.getVolume() << std::endl;
        };
        std::visit(caller, v);
    }

    std::cout << std::endl;

    for (auto& v : vec)
    {
        std::visit(overloaded{//
                              [](Gieter& arg) { std::cout << " G "; },
                              [](Fles& arg) { std::cout << arg.getVolume() << " F "; },
                              [](Spuit& arg) { std::cout << typeid(arg).name() << " S "; },
                              [](auto arg) { std::cout << "Unknown type "; }},
                   v);
    }

    std::cout << std::endl;

    int totalVolume = 0;
    for (auto& v : vec)
    {
        totalVolume += std::visit([](const auto& arg) { return arg.getVolume(); }, v);
    }
    std::cout<< "Total volume " << totalVolume << "L" << std::endl;
    //assert

    //cleanup
}
