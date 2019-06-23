
// Reloaded.Core.Bootstrap.Example.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "CoreCLR.hpp"
#include <windows.h>
#include "framework.h"

// Global variables.
CoreCLR* CLR;

// Forward declarations
string_t get_current_directory();
bool file_exists(string_t file_path);
int exit(const char* message);

// Rest of code.
int main(int argc, char* argv[])
{
	int success = 0;
	CLR = new CoreCLR(&success);

	if (! success)
		return exit("Failed to load `hostfxr`");
		
	// Get file paths and verify them.
	const string_t current_directory = get_current_directory();
	const string_t runtime_config_path = current_directory + L"Reloaded.Core.Bootstrap.ExampleDll.runtimeconfig.json";

	if (!file_exists(runtime_config_path))
		return exit("The runtime configuration does not exist. Ensure you have compiled the Reloaded.Core.Bootstrap.ExampleDll project.");
		
	// Load runtime and execute our method.
	if (! CLR->load_runtime(runtime_config_path))
		return exit("Failed to load .NET Core Runtime");

	const string_t assembly_path = current_directory + L"Reloaded.Core.Bootstrap.ExampleDll.dll";
	const string_t type_name = L"Reloaded.Core.Bootstrap.ExampleDll.Hello, Reloaded.Core.Bootstrap.ExampleDll";
	const string_t method_name = L"SayHello";
	
	const string_t hello_message = L"Hello NET Core from C++";
	component_entry_point_fn say_hello = nullptr;

	if (!CLR->load_assembly_and_get_function_pointer(assembly_path.c_str(), type_name.c_str(), method_name.c_str(), 
		nullptr, nullptr, (void**)&say_hello))

		return exit("Failed to load C# assembly.");

	int message_size = hello_message.length();
	say_hello((void*)hello_message.c_str(), message_size);
}

bool file_exists(string_t file_path)
{
	std::ifstream file_stream;
	file_stream.open(file_path);
	return file_stream.good();
}

string_t get_current_directory()
{
	char_t host_path[MAX_PATH];
	int bufferSize = sizeof(host_path) / sizeof(char_t);
	GetModuleFileNameW(NULL, host_path, bufferSize);
	
	string_t root_path = host_path;
	auto pos = root_path.find_last_of('\\');
	root_path = root_path.substr(0, pos + 1);

	return root_path;
}

int exit(const char* message)
{
	std::cerr << message << std::endl;
	return -1;
}