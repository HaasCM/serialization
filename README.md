# cmake_template
A template project for a C++/C Application using modern cmake

## Introduction
I created this cmake_template to have a fast and easy to use template for cmake projects, so I don't need to rewrite alot of the boiler plate code necessary for the build system.

Feel free to pull it, remove the .git file and use the template for whatever project you need. I just really hate having to rewrite the same code over and over again when I lose interest in one project and want to start another.

If you see anything wrong, or see a better way to organize the build system, please feel free to submit a pull request, I'll definetly accept any feedback.

## Build
If this is your first cmake build, don't worry; It's actually pretty easy and it's one build system that's actually growing on me. CMake forces good software architecture and modularity if done right.

When building a cmake project you have two options, an in-source build and an out-of-source build. Personally, I prefer the latter; it keeps your source code directories cleaner. However, whatever floats your boat; It's your project anyway.

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

So far we've built the application binaries, what do we do now? Let's install them. This is easy as well. Just follow the below steps.

```
cd {directory_where_your_build_is}
sudo make install
```

That's it, the binaries, libraries, and headers will be installed to wherever you specified in your CMakeLists.txt files.

## Building Documentation

The part we love, hate, and love to hate; Software Documentation. Personally, I always lean towards Doxygen for my documentation choice, it's simple, it can be used with various languages, and it just creates really clean documentation.

In this project I included a doxygen.cfg file in the doc directory, to build the documentation follow the below commands.

```
cd {directory_where_your_build_is}
make doc
```

This will output the documentation into doc. Checkout the top level CMakeLists.txt, that's where I placed the custom cmake rule to build the documentation.

### Comments

If anyone has any comments, please feel free to ask away. I'll try to answer them the best I can.
