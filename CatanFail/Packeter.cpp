#include "Packets.h"
#include <string>

using namespace std;

std::string PacketMaker(PacketHeader Header, char* data)
{
    char a = (char)NAME_IS;
    char* p = &a;
    string ret(p);

}
