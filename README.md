Wordle Clone

A simple, interactive game, this project is a clone of the popular word-guessing game, Wordle, implemented in C using the SDL 3 library. It provides a fun and engaging way to play Wordle as a standalone application.
✨ Features

    Classic Wordle Gameplay: Guess the hidden five-letter word in six attempts.

    Visual Feedback: Letters change color to indicate:

        Green: Correct letter in the correct spot.

        Yellow: Correct letter in the wrong spot.

        Gray: Letter not in the word.

    Graphical Interface: Built with SDL 3 for a native desktop experience.

    Intuitive Interface: Simple and clean user experience.

🚀 Installation & Setup

To build and run this project, you will need a C compiler and the SDL 3 development libraries, along with pkg-config to help locate the libraries.
Prerequisites

    C Compiler: GCC, Clang, or a compatible C compiler.

    make utility: For building the project using the provided Makefile.

    pkg-config: A utility used by the Makefile to find SDL3 library paths and flags.

        Linux (Debian/Ubuntu):

        sudo apt-get update
        sudo apt-get install pkg-config

        macOS (Homebrew): pkg-config is usually installed with Homebrew, or can be installed via brew install pkg-config.

        Windows: Typically comes with MSYS2/MinGW-w64 environments.

    SDL 3 Development Libraries:

        SDL3: Core SDL library.

        SDL3_image: For image loading (if used by the game, as suggested by the Makefile).

        SDL3_ttf: For TrueType Font rendering (if used by the game, as suggested by the Makefile).

        Installation commands:

            Linux (Debian/Ubuntu):

            sudo apt-get update
            sudo apt-get install libsdl3-dev libsdl3-image-dev libsdl3-ttf-dev

            macOS (Homebrew):

            brew install sdl3 sdl3_image sdl3_ttf

            Windows: Download the development libraries from the SDL website for SDL3, and similarly for SDL3_image and SDL3_ttf. Follow their installation instructions, or use a package manager like MSYS2/MinGW-w64.

Building the Project

    Clone the repository:

    git clone https://github.com/Ytsago/wordle.git

    Navigate to the project directory:

    cd wordle

    Compile the source code using make:
    This project uses a Makefile for compilation, which leverages pkg-config to find the necessary SDL3 libraries. Simply run make in the project's root directory.

    make

    The Makefile is configured to compile the C source files located in the src/ directory and link them against SDL3, SDL3_image, and SDL3_ttf.

Running the Game

After successful compilation, you can run the executable:

./wordle

🎮 How to Play

    Launch the compiled wordle executable.

    Type a five-letter word using your keyboard.

    Press Enter to submit your guess.

    Observe the color feedback on the letters to guide your next guess.

    Continue guessing until you find the word or run out of attempts!

🤝 Contributing

Contributions are welcome! If you'd like to improve the game, add new features, or fix bugs, please follow these steps:

    Fork the repository.

    Create a new branch (git checkout -b feature/your-feature-name).

    Make your changes.

    Commit your changes (git commit -m 'Add new feature').

    Push to the branch (git push origin feature/your-feature-name).

    Open a Pull Request.

👥 Collaborators

    rdesprez
    PabloBellissant
    secros
    

Note: Based on the public GitHub repository, Ytsago is currently the sole listed contributor. If there are other collaborators, please add their names here!
📄 License

This project currently does not have an explicit license. It is recommended to add a LICENSE file to specify how others can use, modify, and distribute your code.
