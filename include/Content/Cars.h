#pragma once

#include <cstdint>
#include <string_view>
#include <ranges>
#include <variant>

#include <Common/Fraction.h>
#include <Content/Description.h>

namespace content {

using WholeNumber = std::uint32_t;

struct IDeliver
{
    virtual ~IDeliver() = default;

    WholeNumber speed;
    WholeNumber distance;
};

struct Plane : public IDeliver
{
    WholeNumber range;
    WholeNumber cargo_capacity;
};

struct Train : public IDeliver
{
    WholeNumber num_wagons;
};

struct Truck : public IDeliver
{
    WholeNumber cargo_capacity;
    Fraction body_volume;
};

using Content = std::variant<
    Plane,
    Train,
    Truck
>;

}
