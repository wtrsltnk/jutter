#include "fileio.h"

#ifdef __ANDROID__

#include <sys/stat.h>

std::string writableGameFile(const std::string& filename)
{
    auto folder = std::string("/sdcard/.pass-perfect/");

    mkdir(folder.c_str(), 0770);

    return folder + filename;
}

#else

#if _WIN32
#include <direct.h>
#include <io.h>     // For access().
#endif // _WIN32

#include <sys/types.h>  // For stat().
#include <sys/stat.h>   // For stat().

bool DirectoryExists(const char* absolutePath)
{
#if _WIN32
    if(_access( absolutePath, 0) == 0)
#endif // _WIN32
    {
        struct stat status;
        stat(absolutePath, &status);

        return (status.st_mode & S_IFDIR) != 0;
    }
    return false;
}

#ifdef _WIN32
std::string writableGameFile(const std::string& filename)
{
    auto folder = std::string(getenv("APPDATA")) + std::string("/.pass-perfect/");
    if (!DirectoryExists(folder.c_str())) _mkdir(folder.c_str());
    return folder + filename;
}
#endif // _WIN32

#ifdef linux
std::string writableGameFile(const std::string& filename)
{
    auto folder = std::string("~/.pass-perfect/");
    if (!DirectoryExists(folder.c_str()))
#if _WIN32
        _mkdir(folder.c_str());
#else
        mkdir(folder.c_str(), 0777);
#endif // _WIN32
    return folder + filename;
}
#endif // linux

#endif // __ANDROID__
