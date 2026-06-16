# Background
Microsoft's Detours library has been around for decades and yet I never really have had the chance to explore or use it. Essentially, this library allows a user to monitor API calls in Windows binaries and implement their own custom handling of calls via their own callbacks. This functionality can be used to secure existing or unknown binaries in a blue-team environment by allowing low level, granular control over callbacks of a binary of which the source code is unknown. 

# Functionality & Structure
This repository is really four Visual Studio sub-projects. Each project (EXXE/DLL) is used to outline functionality Detours. They can be broken down into the following subsections:

## Detour Own Functions
The simplest case; writing your own program, defining your own callbacks for certain APIs.

## Detour Functions via Binary Modifications
Taking an existing binary (of which the source is unknown) and modify it prior to running it so our custom callbacks are invoked for certain API calls.

## Detour Functions in New Process
Startup a new instance of a binary and use Detours to inject your custom DLL with callbacks that will be invoked. Done via setting the aforementioned process in a suspended state and importing ouur DLL prior to runtime, 

## Detour Functions in an Existing Process
A bit of a stretch, but attempt to inject our Detours DLL into an already running process.

# Getting Started
If one were to want to build everything from scratch, you would need to build the detours lib and link your DLL/EXE to it yourself. I've added the detours repository as a extern (found in detours folder) to try and make this easier for the user. In order to build it one would need to open a Visual Studio Developer command prompt, cd into the base of the directory and run 'nmake'. Once complete, you could find your compiled lib file in detours/lib.X86.

## Building Detours
Since Detours is a submodule, you'll want to pull those updates before building":

```
...path\to\\Wind-Detours > git submodule update 
```

Then, assuming the user has Visual Studio installed, they will need to launch an instance of the 'Developer Command Prompt for VS' and run nmake in the detours directory to build the dependency:

```
...\path\to\Win-Detours\detours > nmake
```

The output of this build can be found under ...\path\tp\Win-Detours\detours\lib.X86\

*Please note that detours only build x86 for free, so thats why we're building Debug x86 for this project*


TODO:
- Add functionality for possibly injecting into an already running process
- Make builds easier by automating a lot of the detours steps for the user 