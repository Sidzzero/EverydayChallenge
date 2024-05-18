#include "BlockColor.h"

const Color darkGrey = { 26, 31, 40, 255 };
const Color LBlockColor = { 47, 230, 23, 255 };
const Color JBlockColor = { 232, 18, 18, 255 };
const Color IBlockColor = { 226, 116, 17, 255 };
const Color OBlockColor = { 237, 234, 4, 255 };
const Color SBlockColor = { 166, 0, 247, 255 };
const Color TBlockColor = { 21, 204, 209, 255 };
const Color ZBlockColor = { 13, 64, 216, 255 };
const Color lightBlue = { 59, 85, 162, 255 };
const Color darkBlue = { 44, 44, 127, 255 };


std::vector<Color> GetBlockColors()
{
    return { darkGrey, LBlockColor, JBlockColor, IBlockColor, OBlockColor, SBlockColor, TBlockColor, ZBlockColor };
}
