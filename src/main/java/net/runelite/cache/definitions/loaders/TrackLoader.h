#pragma once

#include "../TrackDefinition.h"
#include "../../io/InputStream.h"
#include "../../io/OutputStream.h"
#include <vector>
#include <stdexcept>
#include <memory>

/*
 * Copyright (c) 2017, Adam <Adam@sigterm.info>
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
namespace net::runelite::cache::definitions::loaders
{

	using TrackDefinition = net::runelite::cache::definitions::TrackDefinition;
	using InputStream = net::runelite::cache::io::InputStream;

	class TrackLoader : public std::enable_shared_from_this<TrackLoader>
	{
		// Headers
	private:
		static constexpr int MTHD_MAGIC = 1297377380;
		static constexpr int MTRK_MAGIC = 1297379947;

		// Major MIDI Messages. Bottom 4 bits are the channel.
		static const int NOTE_ON = 0b1001'0000;
		static const int NOTE_OFF = 0b1000'0000;
		static const int CONTROL_CHANGE = 0b1011'0000;
		static const int PITCH_WHEEL_CHANGE = 0b1110'0000;
		static const int CHANNEL_PRESSURE = 0b1101'0000;
		static const int POLYPHONIC_KEY_PRESSURE = 0b1010'0000;
		static const int PROGRAM_CHANGE = 0b1100'0000;

		// Meta Events
		static constexpr int META = 255;
		static constexpr int END_OF_TRACK = 47;
		static constexpr int TEMPO = 81;

		// Controller messages
		static constexpr int CONTROLLER_BANK_SELECT = 0;
		static constexpr int CONTROLLER_MODULATION_WHEEL = 1;
		static constexpr int CONTROLLER_CHANNEL_VOLUME = 7;
		static constexpr int CONTROLLER_PAN = 10;
		static constexpr int CONTROLLER_BANK_SELECT_2 = 32;
		static constexpr int CONTROLLER_MODULATION_WHEEL2 = 33;
		static constexpr int CONTROLLER_CHANNEL_VOLUME_2 = 39;
		static constexpr int CONTROLLER_PAN_2 = 42;
		static constexpr int CONTROLLER_DAMPER_PEDAL = 64;
		static constexpr int CONTROLLER_PORTAMENTO = 65;
		static constexpr int CONTROLLER_NON_REGISTERED_PARAMETER_NUMBER_LSB = 98;
		static constexpr int CONTROLLER_NON_REGISTERED_PARAMETER_NUMBER_MSB = 99;
		static constexpr int CONTROLLER_REGISTERED_PARAMETER_NUMBER_LSB = 100;
		static constexpr int CONTROLLER_REGISTERED_PARAMETER_NUMBER_MSB = 101;
		static constexpr int CONTROLLER_ALL_SOUND_OFF = 120;
		static constexpr int CONTROLLER_RESET_ALL_CONTROLLERS = 121;
		static constexpr int CONTROLLER_ALL_NOTES_OFF = 123;

		static constexpr int JAG_NOTE_ON = 0;
		static constexpr int JAG_NOTE_OFF = 1;
		static constexpr int JAG_CONTROL_CHANGE = 2;
		static constexpr int JAG_PITCH_BEND = 3;
		static constexpr int JAG_CHANNEL_PRESSURE = 4;
		static constexpr int JAG_POLY_PRESSURE = 5;
		static constexpr int JAG_PROGRAM_CHANGE = 6;
		static constexpr int JAG_END_OF_TRACK = 7;
		static constexpr int JAG_TEMPO = 23;

	public:
		virtual std::shared_ptr<TrackDefinition> load(std::vector<signed char> &b);

	private:
		void load(std::shared_ptr<TrackDefinition> def, std::shared_ptr<InputStream> var1);
	};

}
