#pragma once

// GLM
#include <glm/glm.hpp>
#include <glm/ext.hpp>

// GLAD
#include <glad/glad.h>

// GLFW3
#include <GLFW/glfw3.h>

// C++ Headers
#include <iostream>
#include <string>
#include <functional>
#include <filesystem>
#include <unordered_map>
#include <sstream>
#include <vector>
#include <ostream>
#include <fstream>
#include <memory>
#include <set>
#include <map>

// Perlin noise from https://github.com/daniilsjb/perlin-noise
#define DB_PERLIN_IMPL
#include <../lib/db_perlin/db_perlin.hpp>

// Implementation Headers
#include <Base/Debug/Debug.hpp>

#include <Base/Utils/Path.hpp>
#include <Base/Utils/Time.hpp>

#include <Base/Camera/Camera2D.hpp>
#include <Base/Camera/Camera3D.hpp>

#include <Base/Input/Definitions.hpp>
#include <Base/Input/Keyboard.hpp>
#include <Base/Input/Mouse.hpp>

#include <Base/GPU/Shader.hpp>
#include <Base/GPU/Vertex.hpp>
#include <Base/GPU/Command.hpp>
#include <Base/GPU/Texture.hpp>
#include <Base/GPU/Framebuffer.hpp>

#include <Base/Utils/MeshGenerator.hpp>

#include <Base/Window/Window.hpp>
#include <Base/Window/GUI.hpp>

#include <Base/Drawing/TextureRenderer.hpp>
#include <Base/Drawing/Primitives2D.hpp>
#include <Base/Drawing/Primitives3D.hpp>

#include <Core/Utils/PerlinNoise.hpp>
#include <Core/Utils/CameraController.hpp>
#include <Core/Utils/RayBox.hpp>

#include <Core/Terrain/TerrainUtils.hpp>
#include <Core/Terrain/Block.hpp>
#include <Core/Terrain/Chunk.hpp>
#include <Core/Terrain/TerrainRenderer.hpp>
#include <Core/Terrain/TerrainGenerator.hpp>
#include <Core/Terrain/Terrain.hpp>