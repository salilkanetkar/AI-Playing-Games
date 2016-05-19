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


// A class which calculates how much memory is needed to duplicate a series of char buffers,
// allocates the memory in a single chunk and then uses the allocated memory to store copies
// of the buffers. Memory is freed up when class is destroyed or by calling Reset().

// NB: No real reason why this couldn't also be used for doing a single memory allocation
// for several objects of types other than char buffers, but that would require some memory
// alignment code adding, so it's not here yet.

#ifndef __SINGLEALLOCTEXTBLOCK_H__
#define __SINGLEALLOCTEXTBLOCK_H__

class CSingleAllocTextBlock
{
	public:
	struct SReuseDuplicatedStrings
	{
		const char * m_charPtr;
	};

	CSingleAllocTextBlock();
	~CSingleAllocTextBlock();
	void Reset();
	void EmptyWithoutFreeing();
	void IncreaseSizeNeeded(size_t theSize);
	void IncreaseSizeNeeded(const char * textIn, bool doDuplicateCheck = true);
	const char * StoreText(const char * textIn, bool doDuplicateCheck = true);
	void Allocate();
	void Lock();

	ILINE size_t GetSizeNeeded() const
	{
		return m_sizeNeeded;
	}

	ILINE const char * GetMem() const
	{
		return m_mem;
	}

	ILINE size_t GetNumBytesUsed() const
	{
		return m_numBytesUsed;
	}

	ILINE void SetDuplicatedStringWorkspace(SReuseDuplicatedStrings * theArray, int arraySize)
	{
		assert (m_reuseDuplicatedStringsArray == NULL);
		assert (m_reuseDuplicatedStringsArraySize == 0);
		assert (m_reuseDuplicatedStringsNumUsed == 0);

		m_reuseDuplicatedStringsArray = theArray;
		m_reuseDuplicatedStringsArraySize = arraySize;
	}

	private:
	const char * FindDuplicate(const char * textIn);
	void RememberPossibleDuplicate(const char * textIn);

	char *                     m_mem;
	size_t                     m_sizeNeeded;
	size_t                     m_sizeNeededWithoutUsingDuplicates;
	size_t                     m_numBytesUsed;
	SReuseDuplicatedStrings *  m_reuseDuplicatedStringsArray;
	int                        m_reuseDuplicatedStringsArraySize;
	int                        m_reuseDuplicatedStringsNumUsed;
};

#endif // __SINGLEALLOCTEXTBLOCK_H__