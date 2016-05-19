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

// Description : Operator functions for common variable types


#ifndef ITEM_PARAMS_REGISTRATION_OPERATORS
#define ITEM_PARAMS_REGISTRATION_OPERATORS


static bool operator < (const Vec3& a, const Vec3& b) 
{ 
	if(a.x != b.x) 
	{
		return (a.x < b.x);
	}
	
	if(a.y != b.y)
	{
		return (a.y < b.y);
	}
	
	return (a.z < b.z); 
}

static bool operator < (const Vec2& a, const Vec2& b) 
{ 
	if(a.x != b.x)
	{
		return (a.x < b.x);
	}
	
	return (a.y < b.y); 
}

static bool operator < (const Ang3& a, const Ang3& b) 
{ 
	if(a.x != b.x)
	{
		return (a.x < b.x);
	}
	
	if(a.y != b.y)
	{ 
		return (a.y < b.y);
	}
	
	return (a.z < b.z); 

}

static bool operator != (const Ang3& a, const Ang3& b) 
{ 
	return (a.x != b.x && a.y != b.y && a.z != b.z); 
}


#endif