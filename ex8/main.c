#include "util.h"

int main(int argc, char *argv[])
{
    char *input = argv[1];
    char *output = argv[2];
    char *filter = argv[3];

    if (checkArguments(filter, argc))
    {
        return 0;
    }

    FILE *in = fopen(input, "rb");
    FILE *out = fopen(output, "wb");

    struct header *BITMAPFILEHEADER = malloc(sizeof(struct header));

    struct map *BITMAPINFO = malloc(sizeof(struct map));

    int bit_base = readFile(BITMAPFILEHEADER, BITMAPINFO, in);

    if (!bit_base)
    {
        if (in != NULL) fclose(in);
        if (out != NULL) fclose(out);
        return 0;
    }

    int padding;
    struct RGBTRIPLE **rgb_triple = NULL;

    switch (bit_base)
    {
        case 24:
        {
            rgb_triple = readArrayX24(&padding, BITMAPINFO, in);
            break;
        }
        case 32:
        {
            rgb_triple = readArrayX32(&padding, BITMAPINFO, in);
            break;
        }
        default:
        {
            break;
        }
    }

    struct RGBTRIPLE **rgb_new = cpyArray(rgb_triple, BITMAPINFO);

    applyFilter(filter, rgb_triple, rgb_new, BITMAPINFO->biWidth, BITMAPINFO->biHeight);

    switch (bit_base)
    {
        case 24:
        {
            writeFIleX24(rgb_new, &padding, BITMAPFILEHEADER, BITMAPINFO, output, out);
            break;
        }
        case 32:
        {
            writeFIleX32(rgb_new, &padding, BITMAPFILEHEADER, BITMAPINFO, output, out);
            break;
        }
        default:
        {
            break;
        }
    }

    free(BITMAPFILEHEADER);
    free(BITMAPINFO);
    free(rgb_triple);
    free(rgb_new);

    return 0;
}





