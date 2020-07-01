


typedef unsigned char BYTE;
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <assert.h>
using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::string;
using std::vector;

//
// *** DATA STRUCTURES ***
//

// Each line data is stored in this structure
struct LineData
{
    // Store bytes read in current line
    vector<BYTE> Data;
};
struct pageData
{
    BYTE page[256];
    unsigned int pageNumber;
};
struct pageInf
{
    pageData mypageData[400];
    unsigned int extendedAddress;
};
pageInf myPageInf[10];
// struct vPageData
// {
//     BYTE page[256];
//     unsigned int pageNumber;
// };
// struct vPageInf
// {
    
//     vector<vPageData>vMyPageData;
//     unsigned int extendedAddress;
// };


unsigned int pageCounter = 0;

#define DATA_LENGTH 0
#define ADDRESS_START_INDEX DATA_LENGTH + 1
#define ADDRESS_NO_OF_BYTES 2
#define RECORD_DATA_TYPE_DATA 0  //DATA RECORED
#define RECORD_DATA_TYPE_EOF 1   //END OF FILE
#define RECORD_DATA_TYPE_ESA 2   //EXTENDED START ADDRESS
#define RECORD_DATA_TYPE_INDEX 3 //
#define RECORD_DATA_TYPE_ELA 4   //EXTENDED LINEAR ADDRESS
#define RECORD_DATA_TYPE_SLA 5   //START LINEAR ADDRESS
#define RECORD_DATA_STARTED_INDEX 4
int lineCounter = 0;
unsigned int address = 0;
//unsigned int pageCounter = 0;
;
unsigned int pageBuffer=0;
unsigned int dataLength = 0;
unsigned int extendedLinearAddress = 0; //
unsigned int extendedLAddress[10];
unsigned int extLACounter = 0;

unsigned int currentPageNumber = 0;

//
// *** DATA STRUCTURES ***
//

// Each line data is stored in this structure


BYTE CharToHex(char ch)
{
    // Convert to upper case
    ch = toupper(ch);

    // Parse nibble
    if (ch >= '0' && ch <= '9')
    {
        return (ch - '0');
    }
    else if (ch >= 'A' && ch <= 'F')
    {
        return (ch - 'A' + 10);
    }
    else
    {
        // Bad input character 
        assert(false);
        return 0; // to suppress warning C4715
    }
}
BYTE ParseByte(const char * str)
{
    char highNibbleChar = str[0];
    char lowNibbleChar = str[1];

    BYTE highNibble = CharToHex(highNibbleChar);
    BYTE lowNibble = CharToHex(lowNibbleChar);

    return (lowNibble + (highNibble << 4));
}


void ParseLine(const string & line, vector<BYTE> & data)
{
    // Clear vector content
    data.clear();

    // 
    const char *ptr = line.c_str();

    // Skip starting ":"
    assert(*ptr == ':');
    ptr++;

    // String length.
    // Process characters two-by-two; exclude starting ":" (so: length-1)
    int byteCount = (line.length() - 1) / 2;

    // Reserve storage in array
    data.reserve(byteCount);

    // Process each couple of hex chars in the string
    for (int i = 0; i < byteCount; i++)
    {
        // Parse couples of hex characters and convert them to bytes
        BYTE currByte = ParseByte(ptr);

        // Add byte to array
        data.push_back(currByte);

        // Go to next characters
        ptr += 2;
    }
    // printf("\n");
    // for(int i=0;i<byteCount;i++)
    // printf(" %.2X",data.at(i));
}

//
// *** MAIN PROGRAM ***
//
#include <cstring>
#define NUMBER_OF_EXTENDED_ADDRESSES 10
#define NUMBER_OF_PAGES 400
int pageIndex = 0;
int pageBufferLength = 0;
#define PAGE_BUFFER_MAX_LENGTH 256
int k = 0;

int main()
{

    for (int i = 0; i < NUMBER_OF_EXTENDED_ADDRESSES; i++)
        for (int j = 0; j < NUMBER_OF_PAGES; j++)
            memset(myPageInf[i].mypageData[j].page, 0xff, 256);
    // Try opening input text file
    ifstream inFile("0010603_FLASH.HEX"); //InputFile.txt");

    // Check for open failure
    if (!inFile)
    {
        cout << "Can't open file." << endl;
        exit(1);
    }

    // Line read from file
    string line;

    // Store data read from file, line by line
    vector<LineData> fileData;
    // struct pageData
    // {
    //     BYTE page[256];
    //     unsigned int pageNo;
    //     unsigned int exAddres;
    // };
    // vector <pageData> myPageData;
    // Read file line by line, and process it
    while (getline(inFile, line))
    {
        lineCounter++;
        LineData currLineData;
        ParseLine(line, currLineData.Data);
        fileData.push_back(currLineData);
    }
    printf("\nNumber of Lines=%d", lineCounter);
    printf("\n");
    //   #define DATA_LENGTH 0
    // #define ADDRESS_START_INDEX DATA_LENGTH + 1
    // #define ADDRESS_NO_OF_BYTES 2
    // #define RECORD_DATA_TYPE_DATA 0 //DATA RECORED
    //  #define RECORD_DATA_TYPE_EOF 1 //END OF FILE
    //  #define RECORD_DATA_TYPE_ESA 2 //EXTENDED START ADDRESS
    // #define RECORD_DATA_TYPE_INDEX 3 //
    // #define RECORD_DATA_TYPE_ELA 4 //EXTENDED LINEAR ADDRESS
    //  #define RECORD_DATA_TYPE_SLA 5 //START LINEAR ADDRESS

    // #define RECORD_DATA_TYPE_DATA 0
   ///  vector <vPageInf> vMyPageInformation;
    extLACounter = 0;
    for (int j = 0; j < lineCounter; j++)
    {
        /// printf("\n");

        switch (fileData.at(j).Data.at(RECORD_DATA_TYPE_INDEX))
        {
        case RECORD_DATA_TYPE_DATA:
        pageCounter=pageCounter=fileData.at(j).Data.at(1);//fileData.at(j).Data.at(1);
        
        address =  fileData.at(j).Data.at(2);
        pageIndex=address%256;
       /// pageBufferLength=0;
      /// printf("\nPC=%u address=%u pageIndex=%u",pageCounter,address,pageIndex);


for(int i=0;i<fileData.at(j).Data.at(DATA_LENGTH);i++)
{
//printf("%.2X",fileData.at(j).Data.at(4+i));
//if(temp%16==0)
//printf("\n");
 /// temp++;
    if(pageBuffer<256)
    {

        myPageInf[extLACounter-1].mypageData[pageCounter].page[pageIndex + i] = fileData.at(j).Data.at(4+i); ///RECORD_DATA_STARTED_INDEX
    pageBuffer++;
pageBufferLength=0;
    }
    else
    {//pageBuffer=0;
   /// printf("\nPageChanged=%u PageBufferL=%u Value=%.2X",pageCounter,pageBufferLength,fileData.at(j).Data.at(4+i));
     ///  myPageInf[extLACounter-1].mypageData[pageCounter+1].page[pageBufferLength] = fileData.at(j).Data.at(4+i); ///RECORD_DATA_STARTED_INDEX
    ///pageBufferLength++;
    }
    
}
//pageBuffer=0;
pageBuffer=pageBufferLength;
        
        
            break;
        case RECORD_DATA_TYPE_EOF:
            printf("\nFinished file");
            // exit(0);
            break;
        case RECORD_DATA_TYPE_ESA:
            printf("\nesa");
            break;
        case RECORD_DATA_TYPE_ELA:
   

            extendedLAddress[extLACounter] = ((unsigned int)fileData.at(j).Data.at(4)) * 16 + (unsigned int)fileData.at(j).Data.at(5);
            myPageInf[extLACounter].extendedAddress = extendedLAddress[extLACounter];
           //vMyPageInformation.push_back(extendedLAddress[extLACounter]);
            extLACounter++; //
            break;
        case RECORD_DATA_TYPE_SLA:
            printf("\nsla");
            break;
        }
    }


//     printf("\n-----------");
//     printf("\n***PageCounter=%u",pageCounter);

for(int x=0;x< extLACounter;x++)
{
     printf("\nextendedLAddress=%u", myPageInf[x].extendedAddress);
    for(k=0;k<2;k++)
   { 
       printf("\nPage Number=%u",k);
    for (int i = 0; i < 256; i++)
    {
        
        if (i % 16 == 0)
            printf("\n");
            printf("%.2X", myPageInf[x].mypageData[k].page[i]);
    }
    printf("\n-----------");
  }

}
    // for (int i = 0; i < extLACounter; i++)
    // //for(int j=0;j<pageCounter;j++)
    //     printf("\nextendedLAddress=%u", myPageInf[i].extendedAddress);

    // for (int j = 0; j < 5; j++)
    // {
    //     printf("\n");
    //     for (int i = 0; i < fileData.at(j).Data.at(0) + 5; i++)
    //     {
    //         // printf("\n");
    //         printf(" %.2X", fileData.at(j).Data.at(i));
    //     }
    // }
    // File closed by ifstream destructor

    // Put a break point on return statement and inspect
    // the load data in 'fileData' variable using STL visualizers.

    // All right
    return 0;
}
