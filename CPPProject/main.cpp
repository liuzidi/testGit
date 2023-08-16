#include <windows.h>
#include <dbghelp.h>
#include <iostream>

#pragma comment(lib, "dbghelp.lib")

void printStacktrace()


{


    HANDLE process = GetCurrentProcess();
    HANDLE thread = GetCurrentThread();
    DWORD threadId = GetCurrentThreadId();
    std::cout << "Thread ID: " << threadId << std::endl;
    STACKFRAME64 stackframe;
    ZeroMemory(&stackframe, sizeof(STACKFRAME64));

#ifdef _M_IX86
    stackframe.AddrPC.Offset = context.Eip;
    stackframe.AddrPC.Mode = AddrModeFlat;
    stackframe.AddrFrame.Offset = context.Ebp;
    stackframe.AddrFrame.Mode = AddrModeFlat;
    stackframe.AddrStack.Offset = context.Esp;
    stackframe.AddrStack.Mode = AddrModeFlat;
#elif _M_X64
    stackframe.AddrPC.Offset = context.Rip;
    stackframe.AddrPC.Mode = AddrModeFlat;
    stackframe.AddrFrame.Offset = context.Rsp;
    stackframe.AddrFrame.Mode = AddrModeFlat;
    stackframe.AddrStack.Offset = context.Rsp;
    stackframe.AddrStack.Mode = AddrModeFlat;
#else
#error "Unsupported architecture"
#endif

    while (StackWalk64(
#ifdef _M_IX86
            IMAGE_FILE_MACHINE_I386,
#elif _M_X64
            IMAGE_FILE_MACHINE_AMD64,
#else
#error "Unsupported architecture"
#endif
            process,
            thread,
            &stackframe,
            &context,
            nullptr,
            SymFunctionTableAccess64,
            SymGetModuleBase64,
            nullptr))
    {
        DWORD64 displacement = 0;
        char buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)];
        PSYMBOL_INFO symbol = (PSYMBOL_INFO)buffer;
        symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
        symbol->MaxNameLen = MAX_SYM_NAME;

        if (SymFromAddr(process, stackframe.AddrPC.Offset, &displacement, symbol))
        {
            std::cout << "Function name: " << symbol->Name << std::endl;
            std::cout << "Module name: " << symbol->ModBase << std::endl;
        }

        IMAGEHLP_LINE64 line;
        line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);

        if (SymGetLineFromAddr64(process, stackframe.AddrPC.Offset, (PDWORD)&displacement, &line))
        {
            std::cout << "File name: " << line.FileName << std::endl;
            std::cout << "Line number: " << line.LineNumber << std::endl;
        }
    }
}

int main()
{
    SymInitialize(GetCurrentProcess(), nullptr, TRUE);
    printStacktrace();
}
