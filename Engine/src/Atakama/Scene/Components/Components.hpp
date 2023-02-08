
#ifndef ATAKAMA_ENGINE_COMPONENTS_HPP
#define ATAKAMA_ENGINE_COMPONENTS_HPP

#include "Atakama/Engine/Camera.hpp"

namespace Atakama
{

struct CameraComponent
{
    Camera Camera;
    bool Primary = false;
    CameraComponent(Camera::Mode mode): Mode(mode) { Camera.SetMode(mode); };
    Camera::Mode Mode { Camera::Mode::Perspective };
};

}


#endif
