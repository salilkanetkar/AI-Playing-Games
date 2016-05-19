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

#ifndef __RANDOMDECK_H__
#define __RANDOMDECK_H__

// Functor object for the stl shuffle algorithm currently used by CRandomDeck
class CRandomIntGenerator
{
public:
	CRandomIntGenerator(){}; 

	void Seed(int seed);

	template <typename Distance>
	Distance operator () (const Distance& n)
	{
		return static_cast<Distance>(m_twisterNumberGen.GenerateUint32() % n);
	}

	// Random number gen based on Mersenne twister 
	CMTRand_int32 m_twisterNumberGen; 
};

// Helper class
// - shuffles a contiguous series of integers in range minIndex->maxIndex
// and hands out a new index when DealNext() is called. Automatically 
// reshuffles when deck emptied
class CRandomNumberDeck
{
public:

	// TODO - could support weightings here too (e.g. adding more of specified indecies to the deck)
	CRandomNumberDeck(); 
	~CRandomNumberDeck(); 

	uint8 DealNext();
	void Init(int seed, uint8 maxIndexValue, uint8 minIndexValue = 0, const bool autoReshuffleOnEmpty = true); 

	void Shuffle(); 
	ILINE bool Empty() {return m_deck.empty();} 
private:

	std::vector<int> m_deck; 
	int m_seed; 
	uint8 m_minIndex; 
	uint8 m_maxIndex;
	bool m_bAutoReshuffleOnEmpty; 

	CRandomIntGenerator m_randomIntGenerator;
};


#endif //#ifndef __RANDOMDECK_H__
