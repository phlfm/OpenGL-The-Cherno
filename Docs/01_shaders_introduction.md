# Introduction to Shaders

There are quite a few steps in the rendering pipeline but for simplicity we will start by looking at Vertex shader and Fragment shader. These two compose about 80~90% of what all games and engines do, so definitely we can do a lot of stuff with them.

1. Vertex shader
Gets called once per **vertex** and basically tells the GPU where the vertex is positioned. For example if we are seeing the vertex through a camera, we have to apply transformations to the vertex so it's seen in the correct position.


2. Fragment shader
Gets called once per **pixel** to tell what color the pixel should be. It's used for lighting and stuff like that. Remember that Full HD = 1920x1080 = +2 mi pixels. Thus if something could be calculated in the vertex shader, it will perform better because the vertex shader is called less frequently than the fragment shader.
