//
// Created by jorda on 5/30/2018.
//

#include "helper.hpp"

const char * INPUT_SETTINGS_LOCATION = "./inputs.cfg";
const char * SETTINGS_LOCATION = "./settings.cfg";

Selector * selector = new(rpmalloc(sizeof(Selector))) Selector();

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

VertexArray generateVertices(float xposition, float yposition, float xsize, float ysize, Texture texture) {
    VertexArray vertices = VertexArray(Quads, 4);

    /** Corner positions for the rendering box */
    vertices[0].position = Vector2f(xposition, yposition);
    vertices[1].position = Vector2f(xposition, yposition + ysize);
    vertices[2].position = Vector2f(xposition + xsize, yposition + ysize);
    vertices[3].position = Vector2f(xposition + xsize, yposition);

    /** Designates area of the texture that is used */
    vertices[0].texCoords = Vector2f(0, 0);
    vertices[1].texCoords = Vector2f(0, texture.getSize().y);
    vertices[2].texCoords = Vector2f(texture.getSize().x, texture.getSize().y);
    vertices[3].texCoords = Vector2f(texture.getSize().x, 0);

    return vertices;
}

VertexArray generateVertices(float xposition, float yposition, float xsize, float ysize) {
    VertexArray vertices = VertexArray(Quads, 4);

    /** Corner positions for the rendering box */
    vertices[0].position = Vector2f(xposition, yposition);
    vertices[1].position = Vector2f(xposition, yposition + ysize);
    vertices[2].position = Vector2f(xposition + xsize, yposition + ysize);
    vertices[3].position = Vector2f(xposition + xsize, yposition);

    return vertices;
}

Vector2f rotatePoint(float x, float y, double angle) {
    return Vector2f(int(x * cos(angle) - y * sin(angle)), int(x * sin(angle) + y * cos(angle)));
}

Vector2f * rotateRectangle(Vector2f pivot, VertexArray * rect, double angle) {
    auto *points = (Vector2f *)rpmalloc(sizeof(Vector2f) * 4);
    Vector2f pointOne = (*rect)[0].position - pivot;
    Vector2f pointTwo = (*rect)[1].position - pivot;
    Vector2f pointThree = (*rect)[2].position - pivot;
    Vector2f pointFour = (*rect)[3].position - pivot;
    points[0] = pivot + rotatePoint(pointOne.x, pointOne.y, angle);
    points[1] = pivot + rotatePoint(pointTwo.x, pointTwo.y, angle);
    points[2] = pivot + rotatePoint(pointThree.x, pointThree.y, angle);
    points[3] = pivot + rotatePoint(pointFour.x, pointFour.y, angle);
    return points;
}

bool intersectPointRect(Vector2f point, VertexArray *quad){
    Vector2f difference = (*quad)[1].position - (*quad)[0].position;
    double angle = (difference.y == 0) ? 0 : atan(difference.x/difference.y);
    Vector2f * points;
    if(angle == 0) {
        points = (Vector2f *)rpmalloc(sizeof(Vector2f) * 4);
        points[0] = (*quad)[0].position;
        points[1] = (*quad)[1].position;
        points[2] = (*quad)[2].position;
        points[3] = (*quad)[3].position;
    }
    else {
        points = rotateRectangle((*quad)[0].position, quad, angle);
        point -= (*quad)[0].position;
        point = rotatePoint(point.x, point.y, angle);
        point += (*quad)[0].position;
    }
    float left = min(points[0].x, points[2].x);
    float right = max(points[0].x, points[2].x);
    float top = min(points[0].y, points[2].y);
    float bottom = max(points[0].y, points[2].y);

    return point.x >= left && point.x <= right && point.y >= top && point.y <= bottom;
}

bool intersectRectRect(VertexArray *quadOne, VertexArray *quadTwo){
    // TODO: Modify this to not screw up in very specific cases. Likely just need to check centers
    for(int i = 0; i < 4; i++)
        if(intersectPointRect((*quadOne)[i].position, quadTwo))
            return true;
    for(int i = 0; i < 4; i++)
        if(intersectPointRect((*quadTwo)[i].position, quadOne))
            return true;
    return false;
}
