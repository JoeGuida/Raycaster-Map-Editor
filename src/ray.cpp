#include <ray.hpp>

void Ray::setMaterial(const Material& m) {
    material = m;
}

void Ray::setTransform(const Transform& t) {
    transform = t;
}

void Ray::setup() {
    vertices = {
            origin.x, origin.y, origin.z,
            origin.x + direction.x * distance,
            origin.y + direction.y * distance,
            origin.z + direction.z * distance
    };
}