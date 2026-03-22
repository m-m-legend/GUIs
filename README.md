# 🎮 GUIs - Graphical Interface Programming

A repository dedicated to storing **graphical interface exercises** completed in the **Game Development** course by Professor **Francisco Sant'anna**, focusing on **Event-Oriented Programming** and **SDL2**.

## 📋 Description

This repository contains practical exercises developed to learn and master graphical interface (GUI) development with a focus on event-oriented programming. The exercises explore the SDL2 library (Simple DirectMedia Layer) in C, covering from basic rendering to complex interactive systems.

## 🎯 Objective

- 🎨 Learn GUI programming with SDL2
- 🎯 Understand the Event-Oriented Programming paradigm
- 💻 Master rendering and graphics manipulation
- 🎮 Prepare foundation for game development
- 🏆 Create interactive and responsive projects
- 📚 Document practical learning in GUIs

## 🎓 About the Course

- **Professor**: Francisco Sant'anna
- **University**: UERJ
- **Discipline**: Game Programming / Graphical Interfaces
- **Focus**: SDL2 and Event-Oriented Programming
- **Language**: C
- **Level**: Intermediate to Advanced

## 📂 Repository Structure

```
│   .gitignore
│   README.md
│   
├───.vscode
│       c_cpp_properties.json
│       
├───0.2
│       resposta.txt
│       
├───1.2.1
│       main.c
│       main.exe
│       main.o
│       Makefile
│       screenshot.png
│       SDL2.dll
│       
├───1.2.2
│       main.c
│       main.exe
│       main.o
│       Makefile
│       screenshot.png
│       SDL2.dll
│       
├───1.3.1
│       explicacao.txt
│       main.c
│       main.exe
│       main.o
│       Makefile
│       SDL2.dll
│       Trabalho 1.3.1.mp4
│
├───1.3.2
│       03-buffer.c
│       03-buffer.o
│       main.exe
│       Makefile
│       resposta.txt
│       SDL2.dll
│
├───1.4.1
│       main.c
│       main.exe
│       main.o
│       Makefile
│       screenshot.png
│       SDL2.dll
│
├───1.5.1
│       main.c
│       main.exe
│       main.o
│       Makefile
│       SDL2.dll
│
├───1.5.2
│       function.c
│
├───1.5.3
│       main.c
│       main.exe
│       main.o
│       Makefile
│       SDL2.dll
│
├───1.6
│       main.c
│       main.exe
│       main.o
│       Makefile
│       SDL2.dll
│
├───1.7
│       main.c
│       main.exe
│       main.o
│       warrior.bmp
│
├───2.1
│       explicacao.txt
│       main.c
│       main.exe
│       main.o
│       Makefile
│       maquina.txt
│       SDL2.dll
│
├───2.2
│       explicacao.txt
│       main.c
│       main.exe
│       main.o
│       Makefile
│       maquina.png
│       SDL2.dll
│
└───2.3
        main.c
        Makefile
        maquina.c
        maquina.h
        maquina_estado.png
        SDL2.dll
```

## 🚀 Content

### Topics Covered

#### 1. **SDL2 Initialization and Setup**
- Initialize SDL2
- Create windows
- Configure renderer
- Resource cleanup

#### 2. **Basic Rendering**
- Draw shapes (rectangles, circles, lines)
- Work with colors
- Load and render images
- Simple animation

#### 3. **Event-Oriented Programming**
- Event Loop
- Keyboard event handling
- Mouse event handling
- Custom events

#### 4. **User Input**
- Keyboard detection
- Mouse capture (movement, clicks)
- Text input
- Joystick/Controller (if applicable)

#### 5. **GUI Elements**
- Interactive buttons
- Text fields
- Menus
- Progress bars
- Dialog boxes

#### 6. **State Management**
- State machines
- Screen transitions
- Data persistence

#### 7. **Performance and Optimization**
- Frame rate control
- Double buffering
- Dirty rectangle rendering

## 🛠️ Technologies

- ![C](https://img.shields.io/badge/C-A8B9CC?style=flat&logo=c&logoColor=white)
- ![SDL2](https://img.shields.io/badge/SDL2-0E5A8C?style=flat&logo=sdl&logoColor=white)
- **Paradigm**: Event-Oriented Programming
- **Build**: Make/CMake

### Dependencies

```bash
# Debian/Ubuntu
sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev

# macOS
brew install sdl2 sdl2_image sdl2_ttf sdl2_mixer

# Windows
# Download from https://www.libsdl.org/download-2.0.php
```

## 📖 How to Use

### Compilation

```bash
# Navigate to the exercise
cd exercise

# Compile (with Makefile)
make

# Run
./main
```

## 💡 Key Concepts

### Rendering Structure

```c
// Typical rendering function
void render(void) {
    // Clear
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    // Draw
    draw_game_objects();
    draw_ui();
    
    // Update
    SDL_RenderPresent(renderer);
}
```

### 🎮 Complete Example: Interactive Button

```c
#include <SDL2/SDL.h>
#include <stdio.h>

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    
    SDL_Window* window = SDL_CreateWindow(
        "GUI Example",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN
    );
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    
    SDL_Rect button = {350, 275, 100, 50};
    SDL_bool mouse_over = SDL_FALSE;
    SDL_bool running = SDL_TRUE;
    
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = SDL_FALSE;
            }
        }
        
        int mouse_x, mouse_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);
        
        mouse_over = (mouse_x >= button.x && mouse_x <= button.x + button.w &&
                      mouse_y >= button.y && mouse_y <= button.y + button.h);
        
        // Render
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        SDL_SetRenderDrawColor(renderer, mouse_over ? 255 : 100, 100, 100, 255);
        SDL_RenderFillRect(renderer, &button);
        
        SDL_RenderPresent(renderer);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
```

## 🏗️ Best Practices

- **Separation of Concerns**: Event, rendering and logic code separated
- **Memory Management**: Properly free all SDL2 resources
- **Modular Structure**: Reusable and well-organized functions
- **Clear Naming**: Descriptive variable and function names
- **Comments**: Documentation of complex functions

## 📖 References

- **SDL2 Official Docs**: https://wiki.libsdl.org/FrontPage
- **Lazy Foo' Productions**: https://lazyfoo.net/tutorials/SDL/
- **Real-Time Rendering**: https://www.realtimerendering.com/
- **Game Programming Patterns**: https://gameprogrammingpatterns.com/

## 🤝 Contribution

This is a personal learning repository from the course. Suggestions, corrections and improvements are welcome through issues or pull requests.

## 📄 License

This project is under the [MIT](LICENSE) license - feel free to use it as a reference or basis for your own projects.

## 📞 Contact

- GitHub: [@m-m-legend](https://github.com/m-m-legend)
- Email: [nintendo_64m@outlook.com]

---

**Last update**: 2026  
**Status**: Finished
**Course**: Game Programming - Professor Francisco Sant'anna
