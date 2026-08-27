# 🌐 http-server-cpp

A lightweight HTTP server built from scratch in C++ using raw POSIX sockets.

---

## 📁 Project Structure

```
http-server-cpp/
├── CMakeLists.txt          # Build configuration
├── CMakePresets.json        # One-command build presets (debug/release)
├── README.md
├── .gitignore
└── src/
    ├── socket.cpp           # Socket server  (port 8080)
    └── client.cpp           # Socket client   (connects to server)
```

---

## 🛠️ Why CMake?

### Before CMake (manual compilation)
```bash
# You had to remember and type these every single time:
g++ -o socket src/socket.cpp
g++ -o client src/client.cpp

# Adding warnings? Type them every time:
g++ -Wall -Wextra -o socket src/socket.cpp

# Debug flags? More to remember:
g++ -g -fsanitize=address -Wall -Wextra -o socket src/socket.cpp

# New file added? Edit every script manually.
```

### After CMake (automated)
```bash
cmake --preset debug        # Configure once
cmake --build --preset debug   # Build everything — done!
```

### Key Benefits

| # | Benefit | What It Means |
|---|---------|---------------|
| 1 | **Single command builds** | `cmake --build --preset debug` compiles ALL targets at once. No need to run separate g++ commands. |
| 2 | **Incremental compilation** | Only recompiles files you changed. Saves time as the project grows. |
| 3 | **Debug vs Release modes** | Switch between debug (with sanitizers) and optimized release builds by changing one word. |
| 4 | **Automatic sanitizers** | Debug mode enables AddressSanitizer — catches memory bugs like buffer overflows and use-after-free automatically. |
| 5 | **Strict warnings** | `-Wall -Wextra -Wpedantic` applied globally to every file. Catches bugs at compile time. |
| 6 | **Clean source folder** | All compiled binaries go into `build/` — your `src/` folder stays clean with only `.cpp` files. |
| 7 | **Cross-platform** | Same CMakeLists.txt works on Linux, Windows, and macOS without changes. |
| 8 | **Scalable** | Adding a new source file = adding one line (`add_executable`). Adding a library = one line (`find_package`). |
| 9 | **IDE support** | VS Code, CLion, Visual Studio all understand CMake natively — one-click build/debug. |

---

## 🚀 How to Use

### Prerequisites

| Tool | Check | Install |
|------|-------|---------|
| CMake ≥ 3.16 | `cmake --version` | [cmake.org/download](https://cmake.org/download/) |
| g++ (MinGW) | `g++ --version` | [mingw.org](https://mingw.org/) |

### Step 1: Configure the Build

Choose **debug** (for development) or **release** (for performance):

```bash
# Debug build — includes sanitizers and debug symbols
cmake --preset debug

# OR Release build — optimized, no debug overhead
cmake --preset release
```

This creates a `build/` folder with all the build system files.

### Step 2: Build the Project

```bash
# Build debug
cmake --build --preset debug

# OR Build release
cmake --build --preset release
```

Binaries are placed in `build/debug/bin/` or `build/release/bin/`.

### Step 3: Run the Programs

```bash
# Terminal 1 — Start the server
./build/debug/bin/socket_server.exe

# Terminal 2 — Connect the client
./build/debug/bin/socket_client.exe
```

**Expected output:**

```
# Server terminal:
Waiting for a client to connect...
Client connected!

# Client terminal:
Connected to server!
Server says: Hello from server!
```

### Rebuilding After Code Changes

Just run the build command again — CMake only recompiles changed files:

```bash
cmake --build --preset debug
```

No need to reconfigure unless you edit `CMakeLists.txt`.

### Cleaning the Build

```bash
# Delete everything and start fresh
rm -rf build/

# Then reconfigure + rebuild
cmake --preset debug
cmake --build --preset debug
```

---

## 📝 Adding New Source Files

To add a new executable, edit `CMakeLists.txt` and add one line:

```cmake
# Example: adding a new "http_handler" target
add_executable(http_handler src/http_handler.cpp)
```

Then rebuild:
```bash
cmake --build --preset debug
```

That's it — CMake handles the rest.

---

## ⚙️ Build Modes Explained

| Mode | Flag | What It Does |
|------|------|-------------|
| **Debug** | `-g -O0 -fsanitize=address,undefined` | No optimization, full debug info, memory sanitizers ON. Use during development. |
| **Release** | `-O2 -DNDEBUG` | Full optimization, no debug info, asserts disabled. Use for final/production builds. |

---

## 📄 License

This project is for learning purposes.
