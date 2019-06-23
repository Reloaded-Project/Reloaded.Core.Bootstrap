using System;
using System.Diagnostics;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Runtime.Versioning;

namespace Reloaded.Core.Bootstrap.ExampleDll
{
    public static class Hello
    {
        public static int SayHello(IntPtr stringPtr, int size)
        {
            string message = Marshal.PtrToStringUni(stringPtr, size);
            Console.WriteLine($"Message: {message}, Architecture: {GetArchitecture()}, NET Core Version: {GetRuntimeVersion()}");
            return 0;
        }

        private static string GetRuntimeVersion()
        {
            string framework = Assembly.GetExecutingAssembly()?.GetCustomAttribute<TargetFrameworkAttribute>()?.FrameworkName;
            return framework;
        }

        private static string GetArchitecture()
        {
            switch (IntPtr.Size)
            {
                case 4:
                    return "x86";
                case 8:
                    return "x64";
                default:
                    return "The future is now";
            }
        }
    }
}
