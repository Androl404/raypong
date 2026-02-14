$ErrorActionPreference = "Stop"

# Ensure we're inside a Visual Studio Developer environment
if (-not (Get-Command cl.exe -ErrorAction SilentlyContinue)) {
    Write-Error "cl.exe not found. Make sure this runs inside a Visual Studio Developer shell."
}

# Create build folder
if (!(Test-Path "build")) {
    New-Item -ItemType Directory -Path "build" | Out-Null
}

# Build raylib with MSVC if not already built
if (!(Test-Path "raylib/build/raylib/Release/raylib.lib")) {

    if (!(Test-Path "raylib/build")) {
        New-Item -ItemType Directory -Path "raylib/build" -Force | Out-Null
    }

    Push-Location "raylib/build"

    cmake -G "Visual Studio 17 2022" `
          -A x64 `
          -DCUSTOMIZE_BUILD=ON `
          -DBUILD_EXAMPLES=OFF `
          ..

    cmake --build . --config Release

    Pop-Location
}

# Copy raylib header
if (!(Test-Path "build/raylib.h")) {
    Copy-Item `
        -Path "raylib/src/raylib.h" `
        -Destination "build/" `
        -Force
}

# Compile your game using MSVC
$SRC = Get-ChildItem "src/*.c" | ForEach-Object { $_.FullName }

cl.exe `
    /Zi `
    /std:c17 `
    /W4 `
    /I "build" `
    /I "raylib/src" `
    /Fe:build/raypong.exe `
    $SRC `
    "raylib/build/raylib/Release/raylib.lib" `
    opengl32.lib `
    gdi32.lib `
    winmm.lib `
    user32.lib `
    shell32.lib
