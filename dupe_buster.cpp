#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdlib>

#include "tinyxml2/tinyxml2.h"

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

bool equalSMSes( const XMLElement * sms1, const XMLElement * sms2 )
{
    return equalNumbers( sms1->Attribute("address"), sms2->Attribute("address") )
        && !strcmp( sms1->Attribute("date"), sms2->Attribute("date") )
        && !strcmp( sms1->Attribute("type"), sms2->Attribute("type") )
        && !strcmp( sms1->Attribute("body"), sms2->Attribute("body") );
}

bool equalMMSes( const XMLElement * mms1, const XMLElement * mms2 )
{
    return equalNumbers( mms1->Attribute("address"), mms2->Attribute("address") )
        && !strcmp( mms1->Attribute("date"), mms2->Attribute("date") )
        && !strcmp( mms1->Attribute("ct_t"), mms2->Attribute("ct_t") )
        && !strcmp( mms1->Attribute("sub"), mms2->Attribute("sub") )
        && !strcmp( mms1->Attribute("m_id"), mms2->Attribute("m_id") )
        && !strcmp( mms1->Attribute("tr_id"), mms2->Attribute("tr_id") );
}

int main( void )
{
    XMLDocument doc;
    doc.LoadFile( "small_sms.xml" );

    XMLNode * smses = doc.FirstChildElement( "smses" );
    if ( !smses ) return 0;

    int msgCount = smses->ToElement()->IntAttribute("count");
    int dupeCount = 0;

    // SMS
    XMLNode * curSMS = smses->FirstChildElement( "sms" );
    do
    {
        XMLNode * nextSMS = curSMS->NextSiblingElement("sms");
        while ( nextSMS != NULL && equalSMSes( curSMS->ToElement(), nextSMS->ToElement() ) )
        {
            smses->DeleteChild( nextSMS );
            --msgCount;
            ++dupeCount;
            nextSMS = curSMS->NextSiblingElement("sms");
        }
        curSMS = curSMS->NextSiblingElement("sms");
    } while ( curSMS != NULL );

    // MMS
    XMLNode * curMMS = smses->FirstChildElement( "mms" );
    do
    {
        XMLNode * nextMMS = curMMS->NextSiblingElement("mms");
        while ( nextMMS != NULL && equalMMSes( curMMS->ToElement(), nextMMS->ToElement() ) )
        {
            smses->DeleteChild( nextMMS );
            --msgCount;
            ++dupeCount;
            nextMMS = curMMS->NextSiblingElement("mms");
        }

        curMMS = curMMS->NextSiblingElement("sms");
    } while ( curMMS != NULL );

    // Update message count
    string newCountStr;
    stringstream countSStream;
    countSStream << msgCount;
    newCountStr = countSStream.str();
    smses->ToElement()->SetAttribute("count", newCountStr.c_str());

    cout << "Successfully deleted " << dupeCount << " duplicates." << endl;

    doc.SaveFile("new.xml");

    return 1;
}
