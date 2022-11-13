#include "TrackLoader.h"

namespace net::runelite::cache::definitions::loaders
{
	using TrackDefinition = net::runelite::cache::definitions::TrackDefinition;
	using InputStream = net::runelite::cache::io::InputStream;
	using OutputStream = net::runelite::cache::io::OutputStream;

	std::shared_ptr<TrackDefinition> TrackLoader::load(std::vector<signed char> &b)
	{
		std::shared_ptr<TrackDefinition> def = std::make_shared<TrackDefinition>();
		load(def, std::make_shared<InputStream>(b));
		return def;
	}

	void TrackLoader::load(std::shared_ptr<TrackDefinition> def, std::shared_ptr<InputStream> var1)
	{
		// Some of the names are from https://www.rune-server.ee/runescape-development/rs-503-client-server/snippets/311669-rs-music-file-structure-conversion.html
		var1->setOffset(var1->getLength() - 3);
		int tracks = var1->readUnsignedByte();
		int division = var1->readUnsignedShort();
		int offset = 14 + tracks * 10;
		var1->setOffset(0);
		int tempoOpcodes = 0;
		int ctrlChangeOpcodes = 0;
		int noteOnOpcodes = 0;
		int noteOffOpcodes = 0;
		int wheelChangeOpcodes = 0;
		int chnnlAfterTchOpcodes = 0;
		int keyAfterTchOpcodes = 0;
		int progmChangeOpcodes = 0;

		int var13;
		int opcode;
		int controlChangeIndex;
		for (var13 = 0; var13 < tracks; ++var13)
		{
			opcode = -1;

			while (true)
			{
				controlChangeIndex = var1->readUnsignedByte();
				if (controlChangeIndex != opcode)
				{
					++offset;
				}

				opcode = controlChangeIndex & 15;
				if (controlChangeIndex == JAG_END_OF_TRACK)
				{
					break;
				}

				if (controlChangeIndex == JAG_TEMPO)
				{
					++tempoOpcodes;
				}
				else if (opcode == JAG_NOTE_ON)
				{
					++noteOnOpcodes;
				}
				else if (opcode == JAG_NOTE_OFF)
				{
					++noteOffOpcodes;
				}
				else if (opcode == JAG_CONTROL_CHANGE)
				{
					++ctrlChangeOpcodes;
				}
				else if (opcode == JAG_PITCH_BEND)
				{
					++wheelChangeOpcodes;
				}
				else if (opcode == JAG_CHANNEL_PRESSURE)
				{
					++chnnlAfterTchOpcodes;
				}
				else if (opcode == JAG_POLY_PRESSURE)
				{
					++keyAfterTchOpcodes;
				}
				else if (opcode == JAG_PROGRAM_CHANGE)
				{
					++progmChangeOpcodes;
				}
				else
				{
//JAVA TO C++ CONVERTER TODO TASK: This exception's constructor requires an argument:
//ORIGINAL LINE: throw new RuntimeException();
					throw std::runtime_error();
				}
			}
		}

		offset += 5 * tempoOpcodes;
		offset += 2 * (noteOnOpcodes + noteOffOpcodes + ctrlChangeOpcodes + wheelChangeOpcodes + keyAfterTchOpcodes);
		offset += chnnlAfterTchOpcodes + progmChangeOpcodes;
		var13 = var1->getOffset();
		opcode = tracks + tempoOpcodes + ctrlChangeOpcodes + noteOnOpcodes + noteOffOpcodes + wheelChangeOpcodes + chnnlAfterTchOpcodes + keyAfterTchOpcodes + progmChangeOpcodes;

		for (controlChangeIndex = 0; controlChangeIndex < opcode; ++controlChangeIndex)
		{
			var1->readVarInt();
		}

		offset += var1->getOffset() - var13;
		controlChangeIndex = var1->getOffset();
		int modulationWheelSize = 0;
		int modulationWheel2Size = 0;
		int channelVolumeSize = 0;
		int channelVolume2Size = 0;
		int panSize = 0;
		int pan2Size = 0;
		int nonRegisteredMsbSize = 0;
		int nonRegisteredLsbSize = 0;
		int registeredNumberMsb = 0;
		int registeredLsbSize = 0;
		int commandsSize = 0;
		int otherSize = 0;
		int controllerNumber = 0;

		int var29;
		for (var29 = 0; var29 < ctrlChangeOpcodes; ++var29)
		{
			controllerNumber = controllerNumber + var1->readUnsignedByte() & 127;
			if (controllerNumber == CONTROLLER_BANK_SELECT || controllerNumber == CONTROLLER_BANK_SELECT_2)
			{
				++progmChangeOpcodes;
			}
			else if (controllerNumber == CONTROLLER_MODULATION_WHEEL)
			{
				++modulationWheelSize;
			}
			else if (controllerNumber == CONTROLLER_MODULATION_WHEEL2)
			{
				++modulationWheel2Size;
			}
			else if (controllerNumber == CONTROLLER_CHANNEL_VOLUME)
			{
				++channelVolumeSize;
			}
			else if (controllerNumber == CONTROLLER_CHANNEL_VOLUME_2)
			{
				++channelVolume2Size;
			}
			else if (controllerNumber == CONTROLLER_PAN)
			{
				++panSize;
			}
			else if (controllerNumber == CONTROLLER_PAN_2)
			{
				++pan2Size;
			}
			else if (controllerNumber == CONTROLLER_NON_REGISTERED_PARAMETER_NUMBER_MSB)
			{
				++nonRegisteredMsbSize;
			}
			else if (controllerNumber == CONTROLLER_NON_REGISTERED_PARAMETER_NUMBER_LSB)
			{
				++nonRegisteredLsbSize;
			}
			else if (controllerNumber == CONTROLLER_REGISTERED_PARAMETER_NUMBER_MSB)
			{
				++registeredNumberMsb;
			}
			else if (controllerNumber == CONTROLLER_REGISTERED_PARAMETER_NUMBER_LSB)
			{
				++registeredLsbSize;
			}
			else if (controllerNumber != CONTROLLER_DAMPER_PEDAL && controllerNumber != CONTROLLER_PORTAMENTO && controllerNumber != CONTROLLER_ALL_SOUND_OFF && controllerNumber != CONTROLLER_RESET_ALL_CONTROLLERS && controllerNumber != CONTROLLER_ALL_NOTES_OFF)
			{
				++otherSize;
			}
			else
			{
				++commandsSize;
			}
		}

		var29 = 0;
		int commandsIndex = var1->getOffset();
		var1->skip(commandsSize);
		int polyPressureIndex = var1->getOffset();
		var1->skip(keyAfterTchOpcodes);
		int channelPressureIndex = var1->getOffset();
		var1->skip(chnnlAfterTchOpcodes);
		int pitchWheelHighIndex = var1->getOffset();
		var1->skip(wheelChangeOpcodes);
		int modulationWheelOffset = var1->getOffset();
		var1->skip(modulationWheelSize);
		int channelVolumeOffset = var1->getOffset();
		var1->skip(channelVolumeSize);
		int panOffset = var1->getOffset();
		var1->skip(panSize);
		int notesIndex = var1->getOffset();
		var1->skip(noteOnOpcodes + noteOffOpcodes + keyAfterTchOpcodes);
		int notesOnIndex = var1->getOffset();
		var1->skip(noteOnOpcodes);
		int otherIndex = var1->getOffset();
		var1->skip(otherSize);
		int notesOffIndex = var1->getOffset();
		var1->skip(noteOffOpcodes);
		int modulationWheel2Offset = var1->getOffset();
		var1->skip(modulationWheel2Size);
		int channelVolume2Offset = var1->getOffset();
		var1->skip(channelVolume2Size);
		int pan2Offset = var1->getOffset();
		var1->skip(pan2Size);
		int programChangeIndex = var1->getOffset();
		var1->skip(progmChangeOpcodes);
		int pitchWheelLowIndex = var1->getOffset();
		var1->skip(wheelChangeOpcodes);
		int nonRegisteredMsbIndex = var1->getOffset();
		var1->skip(nonRegisteredMsbSize);
		int nonRegisteredLsbIndex = var1->getOffset();
		var1->skip(nonRegisteredLsbSize);
		int registeredMsbIndex = var1->getOffset();
		var1->skip(registeredNumberMsb);
		int registeredLsbIndex = var1->getOffset();
		var1->skip(registeredLsbSize);
		int tempoOffset = var1->getOffset();
		var1->skip(tempoOpcodes * 3);
		std::shared_ptr<OutputStream> var51 = std::make_shared<OutputStream>(offset);
		var51->writeInt(MTHD_MAGIC); // MThd header
		var51->writeInt(6); // length of header
		var51->writeShort(tracks > 1 ? 1 : 0); // format
		var51->writeShort(tracks); // tracks
		var51->writeShort(division); // division
		var1->setOffset(var13);
		int channel = 0;
		int var53 = 0;
		int var54 = 0;
		int var55 = 0;
		int var56 = 0;
		int var57 = 0;
		int var58 = 0;
		std::vector<int> var59(128);
		controllerNumber = 0;

		for (int var60 = 0; var60 < tracks; ++var60)
		{
			var51->writeInt(MTRK_MAGIC); // MTrk
			var51->skip(4); // length gets written here later
			int var61 = var51->getOffset();
			int var62 = -1;

			while (true)
			{
				int deltaTick = var1->readVarInt();
				var51->writeVarInt(deltaTick); // delta time
				int status = var1->getArray()[var29++] & 255;
				bool var65 = status != var62;
				var62 = status & 15;
				if (status == JAG_END_OF_TRACK)
				{
					{
					//if (var65) -- client has this if, but it causes broken midi to be produced
						var51->writeByte(META);
					}

					var51->writeByte(END_OF_TRACK); // type - end of track
					var51->writeByte(0); // length
					var51->writeLengthFromMark(var51->getOffset() - var61);
					goto label361Continue;
				}

				if (status == JAG_TEMPO)
				{
					{
					//if (var65) -- client has this if, but it causes broken midi to be produced
						var51->writeByte(META); // meta event FF
					}

					var51->writeByte(TEMPO); // type - set tempo
					var51->writeByte(3); // length
					var51->writeByte(var1->getArray()[tempoOffset++]);
					var51->writeByte(var1->getArray()[tempoOffset++]);
					var51->writeByte(var1->getArray()[tempoOffset++]);
				}
				else
				{
					channel ^= status >> 4;
					if (var62 == JAG_NOTE_ON)
					{
						if (var65)
						{
							var51->writeByte(NOTE_ON + channel);
						}

						var53 += var1->getArray()[notesIndex++];
						var54 += var1->getArray()[notesOnIndex++];
						var51->writeByte(var53 & 127);
						var51->writeByte(var54 & 127);
					}
					else if (var62 == JAG_NOTE_OFF)
					{
						if (var65)
						{
							var51->writeByte(NOTE_OFF + channel);
						}

						var53 += var1->getArray()[notesIndex++];
						var55 += var1->getArray()[notesOffIndex++];
						var51->writeByte(var53 & 127);
						var51->writeByte(var55 & 127);
					}
					else if (var62 == JAG_CONTROL_CHANGE)
					{
						if (var65)
						{
							var51->writeByte(CONTROL_CHANGE + channel);
						}

						controllerNumber = controllerNumber + var1->getArray()[controlChangeIndex++] & 127;
						var51->writeByte(controllerNumber);
						signed char var66;
						if (controllerNumber == CONTROLLER_BANK_SELECT || controllerNumber == CONTROLLER_BANK_SELECT_2)
						{
							var66 = var1->getArray()[programChangeIndex++];
						}
						else if (controllerNumber == CONTROLLER_MODULATION_WHEEL)
						{
							var66 = var1->getArray()[modulationWheelOffset++];
						}
						else if (controllerNumber == CONTROLLER_MODULATION_WHEEL2)
						{
							var66 = var1->getArray()[modulationWheel2Offset++];
						}
						else if (controllerNumber == CONTROLLER_CHANNEL_VOLUME)
						{
							var66 = var1->getArray()[channelVolumeOffset++];
						}
						else if (controllerNumber == CONTROLLER_CHANNEL_VOLUME_2)
						{
							var66 = var1->getArray()[channelVolume2Offset++];
						}
						else if (controllerNumber == CONTROLLER_PAN)
						{
							var66 = var1->getArray()[panOffset++];
						}
						else if (controllerNumber == CONTROLLER_PAN_2)
						{
							var66 = var1->getArray()[pan2Offset++];
						}
						else if (controllerNumber == CONTROLLER_NON_REGISTERED_PARAMETER_NUMBER_MSB)
						{
							var66 = var1->getArray()[nonRegisteredMsbIndex++];
						}
						else if (controllerNumber == CONTROLLER_NON_REGISTERED_PARAMETER_NUMBER_LSB)
						{
							var66 = var1->getArray()[nonRegisteredLsbIndex++];
						}
						else if (controllerNumber == CONTROLLER_REGISTERED_PARAMETER_NUMBER_MSB)
						{
							var66 = var1->getArray()[registeredMsbIndex++];
						}
						else if (controllerNumber == CONTROLLER_REGISTERED_PARAMETER_NUMBER_LSB)
						{
							var66 = var1->getArray()[registeredLsbIndex++];
						}
						else if (controllerNumber != CONTROLLER_DAMPER_PEDAL && controllerNumber != CONTROLLER_PORTAMENTO && controllerNumber != CONTROLLER_ALL_SOUND_OFF && controllerNumber != CONTROLLER_RESET_ALL_CONTROLLERS && controllerNumber != CONTROLLER_ALL_NOTES_OFF)
						{
							var66 = var1->getArray()[otherIndex++];
						}
						else
						{
							var66 = var1->getArray()[commandsIndex++];
						}

						int var67 = var66 + var59[controllerNumber];
						var59[controllerNumber] = var67;
						var51->writeByte(var67 & 127);
					}
					else if (var62 == JAG_PITCH_BEND)
					{
						if (var65)
						{
							var51->writeByte(PITCH_WHEEL_CHANGE + channel);
						}

						var56 += var1->getArray()[pitchWheelLowIndex++];
						var56 += var1->getArray()[pitchWheelHighIndex++] << 7;
						var51->writeByte(var56 & 127);
						var51->writeByte(var56 >> 7 & 127);
					}
					else if (var62 == JAG_CHANNEL_PRESSURE)
					{
						if (var65)
						{
							var51->writeByte(CHANNEL_PRESSURE + channel);
						}

						var57 += var1->getArray()[channelPressureIndex++];
						var51->writeByte(var57 & 127);
					}
					else if (var62 == JAG_POLY_PRESSURE)
					{
						if (var65)
						{
							var51->writeByte(POLYPHONIC_KEY_PRESSURE + channel);
						}

						var53 += var1->getArray()[notesIndex++];
						var58 += var1->getArray()[polyPressureIndex++];
						var51->writeByte(var53 & 127);
						var51->writeByte(var58 & 127);
					}
					else if (var62 == JAG_PROGRAM_CHANGE)
					{

						if (var65)
						{
							var51->writeByte(PROGRAM_CHANGE + channel);
						}

						var51->writeByte(var1->getArray()[programChangeIndex++]);
					}
					else
					{
//JAVA TO C++ CONVERTER TODO TASK: This exception's constructor requires an argument:
//ORIGINAL LINE: throw new RuntimeException();
						throw std::runtime_error();
					}
				}
			}
			label361Continue:;
		}
		label361Break:

		def->midi = var51->flip();
	}
}
