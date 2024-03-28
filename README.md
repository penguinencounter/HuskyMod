# DogTrainer
HuskyLens CFW toolkit and SDK. Based on the **Kendryte K210 standalone SDK**.
You'll need some C/C++ experience to use this.

## Setup
You'll need to **build your own RISC-V toolchain**. If you're on Linux.

### Linux
Go to [riscv-collab/riscv-gnu-toolchain](https://github.com/riscv-collab/riscv-gnu-toolchain) and clone the repository.
Follow the instructions in the toolchain's README to clone the repository and install the dependencies, alongside
`build-essential` (or your distro's equivalent)

The call to `configure` is **different from those in the README**. You'll need to setup an installation location
before running `make` - for example, `sudo mkdir /opt/riscv` and then `sudo chown <user> /opt/riscv`. It may be
preferred to install into a user directory to avoid `sudo`.
```bash
INSTALL_TO=/opt/riscv
./configure --host=riscv64-unknown-elf --with-arch=rv64gc --with-abi=lp64d --with-cmodel=medany --prefix=$INSTALL_TO

# consider doing this in tmux or screen so you can walk away from it
# takes a while
make
```

# Kendryte K210 standalone SDK

[![Build Status](https://travis-ci.org/kendryte/kendryte-standalone-sdk.svg)](https://travis-ci.org/kendryte/kendryte-standalone-sdk)
[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

This SDK is for Kendryte K210 without OS support.
If you have any questions, please be free to contact us.

## Usage

If you want to start a new project, for instance, `hello_world`, you only need to:

- Linux and OSX

`mkdir` your project in `src/`, `cd src && mkdir hello_world`, then put your codes in it, enter SDK root directory and build it.

```bash
mkdir build && cd build
cmake .. -DPROJ=<ProjectName> -DTOOLCHAIN=/opt/riscv-toolchain/bin && make
```

- Windows

Download and install latest CMake.

[Download cmake-3.14.1-win64-x64.msi](https://github.com/Kitware/CMake/releases/download/v3.14.1/cmake-3.14.1-win64-x64.msi)

Download and install latest toolchain.

[Download kendryte-toolchain-win-i386-8.2.0-20190409.tar.xz](https://github.com/kendryte/kendryte-gnu-toolchain/releases/download/v8.2.0-20190409/kendryte-toolchain-win-i386-8.2.0-20190409.tar.xz)

Open a Windows Powershell, cd to Project directory.

`mkdir` your project in `src/`, `cd src && mkdir hello_world`, then put your codes in it, and build it.

```powershell
$env:Path="E:\kendryte-toolchain\bin;C:\Program Files\CMak
e\bin" +  $env:Path

mkdir build && cd build
cmake -G "MinGW Makefiles" ../../../..
make
```

You will get 2 key files, `hello_world` and `hello_world.bin`.

1. If you are using JLink to run or debug your program, use `hello_world`
2. If you want to flash it in UOG, using `hello_world.bin`, then using flash-tool(s) burn <ProjectName>.bin to your flash.

This is very important, don't make a mistake in files.
