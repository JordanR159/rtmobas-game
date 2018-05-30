//
// Created by jorda on 5/30/2018.
//

#include <helper.hpp>

using namespace std;

int *readBMP(char *filename)
{
    /** Note - bmps are stored upside down compared to the rendering canvas, (0, 0) in bottom left */
    FILE* f = fopen(filename, "rb");

    if(f == NULL)
        throw "Argument Exception";

    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f);

    /** Extract image height and width from header */
    int width = *(int*)&info[18];
    int height = *(int*)&info[22];

    int row_padded = (width*3 + 3) & (~3);
    unsigned char* data = new unsigned char[row_padded];
    unsigned char tmp;

    /** First two entries contain width and height of world in tiles, other width * height indicate which tiles to use */
    int *tile_info = new int[width * height + 2];
    tile_info[0] = width;
    tile_info[1] = height;

    for(int i = height-1; i >= 0; i--)
    {
        /** Flips the map data to be the correct orientation */
        int k = i*width + 2;
        fread(data, sizeof(unsigned char), row_padded, f);
        for(int j = 0; j < width*3; j += 3)
        {
            /** Convert (B, G, R) to (R, G, B) */
            tmp = data[j];
            data[j] = data[j+2];
            data[j+2] = tmp;

            tile_info[k++] = (data[j] * 256 * 256) + (data[j + 1] * 256) + data[j + 2];
        }
    }

    fclose(f);
    return tile_info;
}
