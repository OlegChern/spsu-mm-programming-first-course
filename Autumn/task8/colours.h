#ifndef COLOURS_H
#define COLOURS_H

#pragma pack(push, 1)

typedef struct
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} BigEndianColour24;

typedef struct
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char alpha;
} BigEndianColour32;

typedef struct
{
    unsigned char blue;
    unsigned char green;
    unsigned char red;
} LittleEndianColour24;

typedef struct
{
    unsigned char alpha;
    unsigned char blue;
    unsigned char green;
    unsigned char red;
} LittleEndianColour32;

typedef struct
{
    double red;
    double green;
    double blue;
    double alpha;
} RealColour;

#pragma pack(pop)

RealColour multiplyBE24(BigEndianColour24, double);
RealColour multiplyBE32(BigEndianColour32, double);
RealColour multiplyLE24(LittleEndianColour24, double);
RealColour multiplyLE32(LittleEndianColour32, double);

void addToColour(RealColour*, RealColour);

#endif /* COLOURS_H */
