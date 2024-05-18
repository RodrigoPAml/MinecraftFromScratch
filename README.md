# Minecraft From Scratch
Minecraft implementation from scratch using C++ and OpenGL for advanced computer graphics final work

## Features

- Chunk division
- Level distance optimization
- Block face culling optimization
- Insert blocks and remove blocks
- Walk in the terrain

## Limitations

- Dont save modifications on the map, so if the chunk despawn the modifications are lost
- Only can remove and place block from the top of a chunk (for simplicity)
- Some shrubs and plants may change orientation when the chunk is rebuilt because of the use of randomness
  
## Libs

- GLFW https://github.com/glfw/glfw
- DB Perlin https://github.com/daniilsjb/perlin-noise
- GLM https://github.com/g-truc/glm
- GLAD https://github.com/Dav1dde/glad
- ImGUI https://github.com/ocornut/imgui
- STB IMAGE https://github.com/nothings/stb

## How to use

- You can change the movement speed
- Change the mode from fly or walk
- Change the mode from erase block to insert block
- You can select 4 types of block to insert

## Images

![image](https://github.com/RodrigoPAml/MinecraftFromScratch/assets/41243039/3a494b12-9efa-416c-8b8e-f54ccd177534)

![image](https://github.com/RodrigoPAml/MinecraftFromScratch/assets/41243039/13497e5e-3c24-4521-ac30-e5465fca9d99)

![image](https://github.com/RodrigoPAml/MinecraftFromScratch/assets/41243039/2b9a911a-8ca1-4413-8ded-ab268cece175)

![image](https://github.com/RodrigoPAml/MinecraftFromScratch/assets/41243039/1493d2ff-4565-46e6-a996-7f6f631ad2c9)

![image](https://github.com/RodrigoPAml/MinecraftFromScratch/assets/41243039/c2c0d13a-424a-429c-9ba3-baf80907a5b3)

## Videos

[![IMAGE ALT TEXT](http://img.youtube.com/vi/M17ZFMCRTgg/0.jpg)](https://www.youtube.com/watch?v=M17ZFMCRTgg "Sample 1")

[![IMAGE ALT TEXT](http://img.youtube.com/vi/duuMi9Sr-a8/0.jpg)](https://www.youtube.com/watch?v=duuMi9Sr-a8 "Sample 2")
