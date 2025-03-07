/***************************************************************************
	Copyright (c) 2020 Philip Fortier

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
***************************************************************************/
#pragma once

#include "Components.h"
#include "interfaces.h"

enum class TextChangeHint
{
	None = 0,
	// Text is ready
	Changed = 0x00000100,
};

DEFINE_ENUM_FLAGS(TextChangeHint, uint32_t)

enum class MessagePropertyFlags : uint16_t
{
	None = 0,
	Noun = 0x0001,
	Verb = 0x0002,
	Condition = 0x0004,
	Sequence = 0x0008,
	Talker = 0x0010
};

DEFINE_ENUM_FLAGS(MessagePropertyFlags, uint16_t)

// These are used for both message and text resources.
struct TextEntry
{
	// Do not change the order of these items.
	uint8_t Noun;
	uint8_t Verb;
	uint8_t Condition;
	uint8_t Sequence;
	uint8_t Talker;
	uint32_t Reference;
	std::string Text;

	bool operator==(const TextEntry &other) const;
	bool operator!=(const TextEntry &other) const;
};

extern std::string AutoGenTextSentinel;

struct TextComponent : public ResourceComponent, public ILookupNames
{
	TextComponent() { }
	TextComponent(const TextComponent &src) = default;
	ResourceComponent *Clone() const override
	{
		return new TextComponent(*this);
	}

	typedef std::vector<TextEntry>::iterator iterator;
	typedef std::vector<TextEntry> container_type;
	typedef std::vector<TextEntry>::const_iterator const_iterator;

	container_type Texts;

	// Support for message resources:
	MessagePropertyFlags Flags;
	uint16_t msgVersion;
	uint16_t MysteryNumber;

	// Used by the compiler (resource tuples) (why? oh... that is for automatic resource tuples, got it...)
	int AddStringDedupe(const std::string &theString);
	int AddString(const std::string &theString);
	// Set string at (used by the editor).  Returns TRUE if it was modified.
	TextChangeHint SetStringAt(int iIndex, const std::string &theString);
	TextChangeHint MoveStringUp(int iIndex);
	TextChangeHint MoveStringDown(int iIndex);
	TextChangeHint DeleteString(int iIndex);

	// ILookupNames
	std::string Lookup(uint16_t wName) const;

	bool AreTextsEqual(const TextComponent &other) const;
	bool WasAutoGenerated() const;
};

ResourceEntity *CreateTextResource(SCIVersion version);
ResourceEntity *CreateDefaultTextResource(SCIVersion version);

std::string Dos2Win(std::string &str);
std::string Win2Dos(const std::string &str);

// Function to help search a byte in Dos/Windows conversion tables.
unsigned char Dos2WinChar(unsigned char uWinChar);
