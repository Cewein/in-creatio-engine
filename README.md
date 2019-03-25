# In creatio #
### **we are not even in Alpha, not even in pre-Alpha.**
### intro
**In creatio** is (as of now) a OpenGL 4.5 game engine. It will have a lot of feature.

the architecture for the engine look like this :
![Imgur](https://i.imgur.com/ibXJIEE.png)

- The window or main thread andle all render call and GUI/Input call.
- Maths thread andle huge computation, it split computation between cpu and Nvidia gpu thread.
- File i/o are used for openning all the file, from save file to log file or 3d model, texture, ect... <br>This is usefull for large file that halt the main thread while they are loading.
- Shader and script thread is use for as the name say scripting and shader. <br> Normally logical programing and event programing will be done with Lua

### Corrucent feature

here a list of all the feature of In Creatio engine

- Input detection
- GLSL Shader usage

### Working on

- 3d object creation

### Futre plan

- add a GUI
- add a commande line debugger
- add loading and file managing
- a nice loading screen
- file multi threading
