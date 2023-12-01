# 🧪 Kedarium

⚠️ Guide for Windows setup is not yet available.

## 📦 Programs and Packages

To compile and run the project, you'll need to have the following programs and
packages installed:

- CMake
- GLEW
- GLFW
- libPNG

### 🍎 MacOS

```
brew install cmake glew glfw libpng
```

If your compiler cannot find the libraries during the compilation process, it
is possible that it can't locate the packages installed with Homebrew. To address
this, you can run the following commands when launching a new terminal instance
or add them to your shell startup file (.bashrc, .zshrc, or similar):

```
export CPATH=/opt/homebrew/include
export LIBRARY_PATH=/opt/homebrew/lib
```

### 🐧 Linux

Use the following commands to install the required packages on different Linux
distributions:

**Debian and derivates (Ubuntu, Linux Mint, ...)**

```
sudo apt install cmake libglew-dev libglfw3-dev libpng-dev
```

**Fedora**

```
sudo dnf install cmake glew-devel glfw-devel libpng-devel
```

**Arch Linux and derivates (Manjaro, EndeavourOS, ...)**

```
sudo pacman -S cmake glew glfw libpng
```

⚠️ Make sure to install the correct GLFW package depending on whether you're running X11
or Wayland.

## ⚙️ How to compile and run

### 🛠️ Compiling

To compile the project manually, create a build folder, navigate into it, run `cmake ..`,
and then `make` to compile the source code. Alternatively, use the provided build script.
To execute the script, add execute permissions and run:

```
chmod +x ./build.sh
./build.sh
```

### 🚀 Running

If the source code was compile without any issues, you can now run it from the root
directory of the project:

```
./build/examples/example
```

## Special thanks

- [@Orange4Broom](https://github.com/Orange4Broom/) - testing the engine on MacOS
