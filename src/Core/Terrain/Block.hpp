#pragma once
#include <BuildCraft.hpp>

namespace BuildCraft {
namespace Core {

    /// <summary>
    /// Represets a individual block
    /// </summary>
    class Block
    {
    private:
        // If the block needs to appear in the scene
        bool isVisible = false;

        // Texture UV
        int u = -1;
        int v = -1;
    public:
        Block();
        Block(int u, int v);

        // Visible get and set
        bool IsVisible() const;
        void SetVisible(bool value);

        // UV coordinates, texture of the block
        glm::vec2 GetUV();

        // Blocks info
        static bool isEmpty(Block& block);
        static bool isFlower(Block& block);
    };
}}
