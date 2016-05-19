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

// Description : BlendNodes and BlendGroups for ScreenEffects


#ifndef _BLEND_NODE_H_
#define _BLEND_NODE_H_

//-BlendJobNode------------------------
// Has all of the information for one blend.
// That is, a blend type, an effect, and a speed.
// Speed is how fast progress goes from 0 to 1.

struct IBlendedEffect;
struct IBlendType;

class CBlendGroup;

class CBlendJobNode
{
	
	friend class CBlendGroup;

	public:
		CBlendJobNode();
		~CBlendJobNode();

		void Init(IBlendType* pBlend, IBlendedEffect* pFx, float speed);
		void Update(float frameTime);
		bool Done() const{ return (m_progress==1.0f);}

		void Reset();

		void GetMemoryUsage(ICrySizer *pSizer ) const {}
	private:
		IBlendedEffect	*m_myEffect;
		IBlendType			*m_blendType;
	
		float m_speed;
		float m_progress;

};


// A blend group is a queue of blend jobs.
class CBlendGroup 
{
	public:
		CBlendGroup();
		~CBlendGroup();

		void Update(float frameTime);
		void AddJob(IBlendType* pBlend, IBlendedEffect* pFx, float speed);
		bool HasJobs();
		void Reset();

		void GetMemoryUsage(ICrySizer* s) const;

	private:

		void AllocateMinJobs();
		typedef std::vector<CBlendJobNode*> TJobVector;
		TJobVector			m_jobs; 

		int						m_currentJob;
		uint32					m_nextFreeSlot;
		uint32					m_activeJobs;

		uint32					m_maxActiveJobs;
			
};

#endif