#include <iostream>
#include <cstring>

#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

// Reaches the first significant digit in a phone number
// which means bypassing the first zero or the international +33 prefix
const char* bypassPrefix( const char* number )
{
    if ( !number ) return NULL;

    const char* pos = number;

    switch ( number[0] )
    {
    case '0':
        pos++;
        break;
    case '+':
        if ( *( pos + 1 ) == '3' && *( pos + 2 ) == '3' ) pos += 3;
        break;
    }

    return pos;
}

// Tells whether phone number are equal (modulo the international prefix)
// ie. 0612345678 and +33612345678 should be equal
bool equalNumbers( const char* str1, const char* str2 )
{
    if ( !str1 ) return !str2;

    const char* pos1 = bypassPrefix(str1);
    const char* pos2 = bypassPrefix(str2);

    return !strcmp( pos1, pos2 );
}

bool equalElements( const XMLElement * element1, const XMLElement * element2 )
{
    return false;
}

int main( void )
{
    XMLDocument doc;
    doc.LoadFile( "small_sms.xml" );

    const XMLNode * curSMS = doc.FirstChildElement( "smses" )->FirstChildElement("sms");
    cout << curSMS->ToElement()->Attribute("address") << endl;

    const XMLNode * nextSMS = curSMS->NextSiblingElement("sms");
    cout << nextSMS->ToElement()->Attribute("address") << endl;

    return 1;
}
