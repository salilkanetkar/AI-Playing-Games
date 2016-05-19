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

#include "StdAfx.h"
#include "RandomDeck.h"

CRandomNumberDeck::CRandomNumberDeck():
m_maxIndex(0)
,m_minIndex(0)
,m_bAutoReshuffleOnEmpty(true)
{
	
}

CRandomNumberDeck::~CRandomNumberDeck()
{

}

void CRandomNumberDeck::Shuffle()
{
	if(!m_deck.empty())
	{
		m_deck.clear(); 
	}

	// Call Resize to create new (we have possibly been popping them off up until now)
	const uint8 range = (m_maxIndex - m_minIndex) + 1; // inclusive of both min and max
	m_deck.resize(range); 

	for(uint i = 0; i < m_deck.size(); ++i)
	{
		m_deck[i] = m_minIndex + i; 
	}

	if(!m_deck.empty())
	{
		std::random_shuffle(m_deck.begin(), m_deck.end(), m_randomIntGenerator);
	}
}

uint8 CRandomNumberDeck::DealNext()
{
	if(!m_deck.empty())
	{
		uint8 next = m_deck.back(); 
		m_deck.pop_back(); 
		return next; 
	}
	else
	{
		if(m_bAutoReshuffleOnEmpty)
		{
			Shuffle();
			uint8 next = m_deck.back(); 
			m_deck.pop_back(); 
			return next; 
		}
		else
		{
			return 0; 
		}
	}
}

void CRandomNumberDeck::Init( int seed, uint8 maxIndexValue, uint8 minIndexValue /*= 0*/ , const bool autoReshuffleOnEmpty /*= true*/)
{
	if(!m_deck.empty())
	{
		m_deck.clear(); 
	}

	m_bAutoReshuffleOnEmpty = autoReshuffleOnEmpty; 
	m_maxIndex = maxIndexValue; 
	m_minIndex = minIndexValue; 
	// Error checking
	if(m_minIndex > m_maxIndex)
	{
		m_minIndex = m_maxIndex; 
	}

	m_randomIntGenerator.Seed(seed);
	Shuffle(); 
}


void CRandomIntGenerator::Seed( int seed )
{
	m_twisterNumberGen.seed(seed);
}
