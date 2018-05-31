# Contents of Folder

This folder contains the bitmaps and textfiles representing different map layouts for the game.
Each map layout should have two files, <layout>.bmp and <layout>.txt.

Bitmaps are used to represent the tiles on the map. All bitmaps should be 24-bit and be made to
be a few hundred pixels in width and height. Each pixel is a tile, and only tiles should be
represented on these maps. Entities should be spawned separately.

Text files are used to represent initial spawn locations, and should be made with the format
"Entity::Types,xposition,yposition", where there are no spaces and each entry is separated by
a newline. Entity::Types is the type of entity to spawn, using the number directly instead of
the macros defined in Entity::Types. xposition and yposition are the starting locations of each
entity to spawn.

# Format of Bitmaps

Enter all color codes here

RGB(0, 128, 0) - PLAINS

RGB(192, 192, 0) - DESERT

RGB(128, 128, 64) - MOUNTAINS

RGB(0, 64, 128) - WATER

Use Windows Paint to draw each pixel for the bitmap, using precisely these RGB values for
representing each tile. Refer to basic.bmp for an example of the intended format.

# Format of Text Files

First number is type, then next is xposition, then yposition. Refer to basic.txt for an
example of the intended format.