#pragma once

#include "../definitions/LocationsDefinition.h"
#include "../definitions/MapDefinition.h"
#include "Location.h"
#include <vector>
#include <memory>
#include "../../../../../../../tangible_rectangular_vectors.h"

/*
 * Copyright (c) 2016-2017, Adam <Adam@sigterm.info>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
namespace net::runelite::cache::region
{

	using ArrayList = java::util::ArrayList;
	using List = java::util::List;
	using LocationsDefinition = net::runelite::cache::definitions::LocationsDefinition;
	using MapDefinition = net::runelite::cache::definitions::MapDefinition;

	class Region : public std::enable_shared_from_this<Region>
	{

	public:
		static constexpr int X = 64;
		static constexpr int Y = 64;
		static constexpr int Z = 4;

	private:
		const int regionID;
		const int baseX;
		const int baseY;

//JAVA TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: private final int[][][] tileHeights = new int[Z][X][Y];
		const std::vector<std::vector<std::vector<int>>> tileHeights = RectangularVectors::RectangularIntVector(Z, X, Y);
//JAVA TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: private final byte[][][] tileSettings = new byte[Z][X][Y];
		const std::vector<std::vector<std::vector<signed char>>> tileSettings = RectangularVectors::RectangularSignedCharVector(Z, X, Y);
//JAVA TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: private final short[][][] overlayIds = new short[Z][X][Y];
		const std::vector<std::vector<std::vector<short>>> overlayIds = RectangularVectors::RectangularShortVector(Z, X, Y);
//JAVA TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: private final byte[][][] overlayPaths = new byte[Z][X][Y];
		const std::vector<std::vector<std::vector<signed char>>> overlayPaths = RectangularVectors::RectangularSignedCharVector(Z, X, Y);
//JAVA TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: private final byte[][][] overlayRotations = new byte[Z][X][Y];
		const std::vector<std::vector<std::vector<signed char>>> overlayRotations = RectangularVectors::RectangularSignedCharVector(Z, X, Y);
//JAVA TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: private final short[][][] underlayIds = new short[Z][X][Y];
		const std::vector<std::vector<std::vector<short>>> underlayIds = RectangularVectors::RectangularShortVector(Z, X, Y);

//JAVA TO C++ CONVERTER WARNING: C++ has no equivalent to a 'final' collection which allows modification of internal state:
//ORIGINAL LINE: private final java.util.List<Location> locations = new java.util.ArrayList<>();
		std::vector<std::shared_ptr<Location>> locations = std::vector<std::shared_ptr<Location>>();

	public:
		Region(int id);

		Region(int x, int y);

		virtual void loadTerrain(std::shared_ptr<MapDefinition> map);

		virtual void loadLocations(std::shared_ptr<LocationsDefinition> locs);

		virtual int getRegionID();

		virtual int getBaseX();

		virtual int getBaseY();

		virtual int getTileHeight(int z, int x, int y);

		virtual signed char getTileSetting(int z, int x, int y);

		virtual int getOverlayId(int z, int x, int y);

		virtual signed char getOverlayPath(int z, int x, int y);

		virtual signed char getOverlayRotation(int z, int x, int y);

		virtual int getUnderlayId(int z, int x, int y);

		virtual std::vector<std::shared_ptr<Location>> getLocations();

		virtual int getRegionX();

		virtual int getRegionY();
	};

}
