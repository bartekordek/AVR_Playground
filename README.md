# AVR Playground

A simple AVR microcontroller playground project with automated toolchain setup for Windows.

![Platform](https://img.shields.io/badge/platform-AVR-blue)
![Windows](https://img.shields.io/badge/os-Windows-0078D6)
![License](https://img.shields.io/badge/license-MIT-lightgrey)

[![WindowsBuild](https://github.com/bartekordek/AVR_Playground/actions/workflows/BuildWindows.yml/badge.svg)](https://github.com/bartekordek/AVR_Playground/actions/workflows/BuildWindows.yml)

---

## 🚀 Features

- Automatic AVR GNU Toolchain download & setup
- Automatic AVRDUDE download & setup
- No manual installation required
- Self-contained development environment in `3rd_party/`
- Ready for AVR firmware development and flashing

---

## 📦 Included Tools

The setup script automatically downloads and installs:

- AVR GNU Toolchain (Microchip distribution)
- AVRDUDE (GitHub release)

All tools are stored in:
`3rd_party/`


---

## ⚙️ Setup (Windows)

Run:

```bat
Setup.bat
```

🧠 What the setup does
- Downloads AVR GNU Toolchain
- Downloads AVRDUDE
- Extracts both into 3rd_party/
- Uses fastest available extraction method:
    - tar (fastest on Windows 10/11)
    - 7z (if installed)
    - PowerShell fallback

## 🧩 VS Code Integration

This project includes preconfigured VS Code build tasks for AVR development.

You can find them in:

`.vscode/tasks.json`

⚙️ Available Tasks
* 🏗 Build project [Windows][Build]
    * Compiles firmware using your Build.bat script:
    * Run via: `Ctrl + Shift + B`
* 🚀 Build and Flash [Windows][BuildAndPush]
    * Builds firmware and uploads it to the microcontroller:

You can also directly call `Build.bat` or `BuildAndPush.bat`.