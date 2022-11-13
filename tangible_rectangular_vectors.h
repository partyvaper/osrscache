#pragma once

//----------------------------------------------------------------------------------------
//	Copyright © 2007 - 2022 Tangible Software Solutions, Inc.
//	This class can be used by anyone provided that the copyright notice remains intact.
//
//	This class includes methods to convert multidimensional arrays to C++ vectors.
//----------------------------------------------------------------------------------------
#include <vector>

class RectangularVectors
{
public:
    static std::vector<std::vector<int>> RectangularIntVector(int size1, int size2)
    {
        std::vector<std::vector<int>> newVector(size1);
        for (int vector1 = 0; vector1 < size1; vector1++)
        {
            newVector[vector1] = std::vector<int>(size2);
        }

        return newVector;
    }

    static std::vector<std::vector<std::vector<std::shared_ptr<Tile>>>> RectangularTileVector(int size1, int size2, int size3)
    {
        std::vector<std::vector<std::vector<std::shared_ptr<Tile>>>> newVector(size1);
        for (int vector1 = 0; vector1 < size1; vector1++)
        {
            newVector[vector1] = std::vector<std::vector<std::shared_ptr<Tile>>>(size2);
            if (size3 > -1)
            {
                for (int vector2 = 0; vector2 < size2; vector2++)
                {
                    newVector[vector1][vector2] = std::vector<std::shared_ptr<Tile>>(size3);
                }
            }
        }

        return newVector;
    }

    static std::vector<std::vector<std::vector<int>>> RectangularIntVector(int size1, int size2, int size3)
    {
        std::vector<std::vector<std::vector<int>>> newVector(size1);
        for (int vector1 = 0; vector1 < size1; vector1++)
        {
            newVector[vector1] = std::vector<std::vector<int>>(size2);
            if (size3 > -1)
            {
                for (int vector2 = 0; vector2 < size2; vector2++)
                {
                    newVector[vector1][vector2] = std::vector<int>(size3);
                }
            }
        }

        return newVector;
    }

    static std::vector<std::vector<std::vector<signed char>>> RectangularSignedCharVector(int size1, int size2, int size3)
    {
        std::vector<std::vector<std::vector<signed char>>> newVector(size1);
        for (int vector1 = 0; vector1 < size1; vector1++)
        {
            newVector[vector1] = std::vector<std::vector<signed char>>(size2);
            if (size3 > -1)
            {
                for (int vector2 = 0; vector2 < size2; vector2++)
                {
                    newVector[vector1][vector2] = std::vector<signed char>(size3);
                }
            }
        }

        return newVector;
    }

    static std::vector<std::vector<std::vector<short>>> RectangularShortVector(int size1, int size2, int size3)
    {
        std::vector<std::vector<std::vector<short>>> newVector(size1);
        for (int vector1 = 0; vector1 < size1; vector1++)
        {
            newVector[vector1] = std::vector<std::vector<short>>(size2);
            if (size3 > -1)
            {
                for (int vector2 = 0; vector2 < size2; vector2++)
                {
                    newVector[vector1][vector2] = std::vector<short>(size3);
                }
            }
        }

        return newVector;
    }
};
