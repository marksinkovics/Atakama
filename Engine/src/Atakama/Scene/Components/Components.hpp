
#ifndef ATAKAMA_ENGINE_COMPONENTS_HPP
#define ATAKAMA_ENGINE_COMPONENTS_HPP

#include "Atakama/Engine/Camera.hpp"

namespace Atakama
{

struct CameraComponent
{
    Camera Camera;
    bool Primary = false;
    CameraComponent(Camera::Mode mode) { Camera.SetMode(mode); };
};

}


#endif
