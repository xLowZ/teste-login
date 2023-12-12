#include "../include/Functions.h"

int main()
{
    UserManager usermanager;
    fnc::Flags flags;

    while( flags.control )
    {
        fnc::printMenu(flags);
        fnc::management(usermanager, flags);
    }

    return 0;
}
