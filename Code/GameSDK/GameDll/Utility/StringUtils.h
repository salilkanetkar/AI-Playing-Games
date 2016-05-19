/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/
// Original file Copyright Crytek GMBH or its affiliates, used under license.

/*
TODO: Move contents of this file into CryEngine/CryCommon/StringUtils.h
and contents of StringUtils.cpp into CryEngine/CryCommon/StringUtils.cpp
*/
#ifndef __STRING_UTILS_H__
#define __STRING_UTILS_H__

//--------------------------------------------------------------------------------
// cry_sprintf: Same as sprintf but null terminates the output \o/
void cry_sprintf(char * destination, size_t size, const char* format, ...);

//--------------------------------------------------------------------------------
// cry_copyStringUntilFindChar: Parameter order is the same as strncpy;
// additional 'until' parameter defines which additional character should
// stop the copying. Return value is number of bytes (including NULL)
// written into 'destination', or 0 if 'until' character not found in
// first 'bufferLength' bytes of 'source'.
size_t cry_copyStringUntilFindChar(char * destination, const char * source, size_t bufferLength, char until);

#if !defined(_DEBUG)
#define cry_displayMemInHexAndAscii(...)			(void)(0)
#else

class ITextOutputHandler
{
public:
	virtual void DoOutput(const char * text) = 0;
};

class CCryWatchOutputHandler : public ITextOutputHandler
{
	virtual void DoOutput(const char * text);
};

class CCryLogOutputHandler : public ITextOutputHandler
{
	virtual void DoOutput(const char * text);
};

class CCryLogAlwaysOutputHandler : public ITextOutputHandler
{
	virtual void DoOutput(const char * text);
};

//--------------------------------------------------------------------------------
// cry_displayMemInHexAndAscii outputs (using an ITextOutputHandler subclass) the
// contents of the first 'size' bytes starting at memory location 'data'.
void cry_displayMemInHexAndAscii(const char * startEachLineWith, const void * data, int size, ITextOutputHandler & output, const int bytesPerLine = 32);
#endif

//--------------------------------------------------------------------------------
// Generates a string in the format X days X hrs X mins X secs, or if useShortForm is set 00:00:00.
const char * GetTimeString(int secs, bool useShortForm=false, bool includeSeconds=true, bool useSingleLetters=false);
const char * GetTimeString(float secs, bool useShortForm=false, bool includeSeconds=true, bool useSingleLetters=false);


#endif // __STRING_UTILS_H__
