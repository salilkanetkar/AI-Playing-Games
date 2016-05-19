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

#ifndef TransformationPinning_h
#define TransformationPinning_h

class CTransformationPinning :
	public ITransformationPinning
{
public:
	struct TransformationPinJoint
	{
		enum Type
		{
			Copy		= 'C',
			Feather		= 'F',
			Inherit		= 'I'
		};
	};

	CRYINTERFACE_BEGIN()
		CRYINTERFACE_ADD(IAnimationPoseModifier)
		CRYINTERFACE_ADD(ITransformationPinning)
	CRYINTERFACE_END()

	CRYGENERATE_CLASS(CTransformationPinning, "AnimationPoseModifier_TransformationPin", 0xcc34ddea972e47da, 0x93f9cdcb98c28c8e)

public:

public:
	virtual void SetBlendWeight(float factor);
	virtual void SetJoint(uint32 jntID);
	virtual void SetSource(ICharacterInstance* source);

	// IAnimationPoseModifier
public:
	virtual bool Prepare(const SAnimationPoseModifierParams& params) { return true; }
	virtual bool Execute(const SAnimationPoseModifierParams& params);
	virtual void Synchronize() { }

	void GetMemoryUsage( ICrySizer *pSizer ) const
	{
		pSizer->AddObject(this, sizeof(*this));
	}
private:
	float m_factor;

	uint32 m_jointID;
	char *m_jointTypes;
	uint32 m_numJoints;
	ICharacterInstance* m_source;
	bool m_jointsInitialised;

	void Init(const SAnimationPoseModifierParams& params);

} _ALIGN(32);

#endif // TransformationPinning_h
