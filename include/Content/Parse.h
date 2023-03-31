#ifndef INTERPRETER_CONTENT_PARSE_H
#define INTERPRETER_CONTENT_PARSE_H

#include <string_view>

#include <Common/Fraction.h>

#include <Content/Cars.h>

#include <Formats/To.h>

namespace content {
    
inline auto Parse(const std::string_view desc, formats::parse::To<content::Plane>)
{
    auto plane = Plane{};
    sscanf(desc.data(), description::plane, &plane.speed, &plane.distance, &plane.range, &plane.cargo_capacity);
    return plane;
}

inline auto Parse(const std::string_view desc, formats::parse::To<content::Train>)
{
    auto train = Train{};
    sscanf(desc.data(), description::train, &train.speed, &train.distance, &train.num_wagons);
    return train;
}

inline auto Parse(const std::string_view desc, formats::parse::To<content::Truck>)
{
    auto truck = Truck{};

    auto num = std::uint64_t{0};
    auto den = std::uint64_t{0};

    sscanf(desc.data(), description::truck, &truck.speed, &truck.distance, &truck.cargo_capacity, &num, &den);
    truck.body_volume = Fraction(num, den);

    return truck;
}

}

#endif //INTERPRETER_CONTENT_PARSE_H
