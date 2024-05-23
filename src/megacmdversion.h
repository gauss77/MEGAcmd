#ifndef MEGACMDVERSION_H
#define MEGACMDVERSION_H

#ifndef MEGACMD_MAJOR_VERSION
#define MEGACMD_MAJOR_VERSION 1
#endif
#ifndef MEGACMD_MINOR_VERSION
#define MEGACMD_MINOR_VERSION 7
#endif
#ifndef MEGACMD_MICRO_VERSION
#define MEGACMD_MICRO_VERSION 0
#endif

#ifndef MEGACMD_BUILD_ID
#define MEGACMD_BUILD_ID 0
#endif

#ifndef MEGACMD_CODE_VERSION
#define MEGACMD_CODE_VERSION (MEGACMD_BUILD_ID+MEGACMD_MICRO_VERSION*100+MEGACMD_MINOR_VERSION*10000+MEGACMD_MAJOR_VERSION*1000000)
#endif
namespace megacmd {

const char * const megacmdchangelog =
        "Improved startup time""\n"
        "Reduced memory consumption: cached metadata is no longer loaded at startup""\n"
        "Fixes and improvements in whoami, ls, backup and export commands""\n"
        "Fixed several memory leaks and improved overall memory consumption""\n"
        "Fixed file permissions on Unix""\n"
        "Added support for the Apple silicon (M1)""\n"
        "Many other fixes and improvements"
        ;

}//end namespace
#endif // VERSION_H

