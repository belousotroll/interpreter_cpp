#pragma once

#include <Content/Cars.h>

namespace content {

inline auto print(const content::Plane & plane)
{
    printf(description::plane, plane.speed, plane.distance, plane.range, plane.cargo_capacity);
    printf("\n");
}

inline auto print(const content::Train & train)
{
    printf(description::train, train.speed, train.distance, train.num_wagons);
    printf("\n");

}

inline auto print(const content::Truck & truck)
{
    printf(description::truck, truck.speed, truck.distance, truck.cargo_capacity, truck.body_volume.num(), truck.body_volume.den());
    printf("\n");
}


}
