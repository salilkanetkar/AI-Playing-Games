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

#ifndef ITransformationPinning_h
#define ITransformationPinning_h

#include <ICryAnimation.h>

struct ITransformationPinning : public IAnimationPoseModifier
{
	CRYINTERFACE_DECLARE(ITransformationPinning, 0xcc34ddea972e47db, 0x93f9cdcb98c28c8f)

	virtual void SetBlendWeight(float factor)		= 0;
	virtual void SetJoint(uint32 jntID)				= 0;
	virtual void SetSource(ICharacterInstance* source)	= 0;
};

DECLARE_BOOST_POINTERS(ITransformationPinning);


#endif // ITransformationPinning_h
