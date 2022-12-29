#include <iostream>
#include <string>
#include <string_view>
#include <memory>
#include <filesystem>
#include <stdint.h>
#include <chrono>
#include <vector>

#define  GLM_FORCE_RADIANS
#define  GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

#include "Macro.hpp"
#include "Utils/Utils.hpp"
#include "Log/LogSystem.hpp"
#include "GlobalContext.hpp"

