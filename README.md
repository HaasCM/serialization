# Serialization - What the standard library for C++11 is missing.
Serialization is a small serialization library I use for small projects, which leverages the C++11 standard library. Serialization applies a good spin on serialization encapsulating all of the pointer arithematic used in traditional serialization.

## Introduction
Serialization is easey to use:
```C++
void function_to_serialize() {
    ByteArray array;
    ByteStream stream(&array, OpenMode::ReadWrite);
    int i = 1;
    int j = 6;
    
    stream << 1;
    stream << 6;
}
```

## Build
Serialization is a simple library, there are no dependencies! It's a cmake3 build system too. So you've got two easy choices for building:

### In-Source Build

An in-source build does just that, it builds the project in the source directory. It's pretty easy to do with the following steps

```
cd {project_root_directory}
cmake .
make
```

That's it the binaries and libraries will be built in place, and not installed yet. We'll cover installation later.

### Out-of-Source Build

An out-of-source build will generate your Makefiles and binaries outside the source directory in a directory of your choice.
I like this build option more, it keeps things neat and clean, and it's pretty easy to rm -rf you build directory, and nuke your current build. You can do this with the following steps.

```
mkdir build
cd build
cmake {path_to_source_directory}
make
```

You can place the build directory wherever you'd like, and you can name it whatever you like, I generally choose build, because that's what it is; It's a build. Keep it simple.

## Installation

Just run make install, its that easy

```
cd {directory_where_your_build_is}
sudo make install
```

## Building Documentation

In source doxygen documentation can be found in serialization. You can build it by installing Doxygen, and running the below command

```
cd {directory_where_your_build_is}
make doc
```

### Comments

If anyone has any comments, please feel free to ask away. I'll try to answer them the best I can.
