#pragma once

#ifdef _WIN32
#define NOMINMAX 1
#endif

#include <pocket/components/animator.hpp>
#include <pocket/components/movement.hpp>
#include <pocket/components/player_controller.hpp>
#include <pocket/components/sprite.hpp>
#include <pocket/components/tilemap.hpp>

#include <pocket/containers/containers.hpp>

#include <pocket/core/engine.hpp>
#include <pocket/core/factory.hpp>
#include <pocket/core/time.hpp>
#include <pocket/core/types.hpp>
#include <pocket/core/window.hpp>
#include <pocket/core/world.hpp>

#include <pocket/debug/benchmark.hpp>

#include <pocket/graphics/batch.hpp>
#include <pocket/graphics/gfx_api.h>
#include <pocket/graphics/graphics.hpp>
#include <pocket/graphics/shader.hpp>
#include <pocket/graphics/texture.hpp>

#include <pocket/input/input.hpp>

#include <pocket/IO/pkfile.hpp>

#include <pocket/json/json.hpp>

#include <pocket/math/constants.hpp>
#include <pocket/math/matmath.hpp>
#include <pocket/math/rect.hpp>
#include <pocket/math/vecmath.hpp>

// should maybe remove them as they are very old
#include <pocket/util/crash.hpp>
#include <pocket/util/pkassert.h>

