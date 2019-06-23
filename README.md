# Reloaded.Core.Bootstrap

Reloaded.Core.Bootstrap is a tiny Visual C++ library wrapping the `nethost` library that allows you to inject CoreCLR (the .NET Core Runtime) into the current unmanaged process and execute a .NET library.

## Requirements

### Building
- Visual Studio 2019 or newer (2017 may work, not tested).
- .NET Core 3 Preview 6 SDK (or newer).

### Running
- Requires .NET Core 3 Preview 6 Runtime or newer.

Logically, the x86 runtime is necessary to host CoreCLR in an x86 process and the x64 runtime is necessary to run CoreCLR in an x64 process.

The "Hosting Bundle" contains both the x86 and x64 runtime.

## Example Usage

See the Visual Studio solution file under the `Source` directory, it contains a usage example from both the native C++ and managed C# side.

## How does it work (Summary)

The project uses the `nethost` library provided by CoreCLR (the .NET Core Runtime) in order to locate the `hostfxr` library.

We then load the `hostfxr` library and obtain function addresses from hostfxr's DLL Exports.

Using exports we load CoreCLR by providing a path to the runtime configuration JSON file. The loaded CoreCLR is then asked for a function (pointer) used to load an assembly and obtain function pointer of .NET function.

For a more comprehensive description, refer to the official guide for .NET Core hosting: https://docs.microsoft.com/en-us/dotnet/core/tutorials/netcore-hosting


## Operating System Support

Like the other libraries in this organization, this library was made with Reloaded (Mod Loader) II in mind and thus provides a Windows-only implementation.

That said it is very easy to extend this to Linux and OSX with less than 50 lines of code. I, the author just lack the resources (time) to learn alternative tooling/build systems *(CMake/Premake etc.)* and make a solution that can be built and tested on more platforms.

## Troubleshooting

### No runtime configuration (runtimeconfig.json) generated on build of .NET project.

It means that you are probably building a class library project (as opposed to console application) that you would like to execute.

To generate the config for a class library project, simply add
`<GenerateRuntimeConfigurationFiles>true</GenerateRuntimeConfigurationFiles>`  to the first property group of your .NET project's `.csproj` files.

## Additional Licenses

`nethost, hostfxr & coreclr_delegates`: 

```
// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.
// See the LICENSE file in the project root for more information.
```