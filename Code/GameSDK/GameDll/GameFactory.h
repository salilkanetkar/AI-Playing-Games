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

// Description : Register the factory templates used to create classes from names
//               e.g. REGISTER_FACTORY pFramework   Player   CPlayer  false
//               or   REGISTER_FACTORY pFramework   Player   CPlayerG4  false
//
//               Since overriding this function creates template based linker errors,
//               it's been replaced by a standalone function in its own cpp file.

#ifndef __GAMEFACTORY_H__
#define __GAMEFACTORY_H__

#if _MSC_VER > 1000
# pragma once
#endif


struct IGameFramework;

// Register the factory templates used to create classes from names. Called via CGame::Init()
void InitGameFactory(IGameFramework *pFramework);


#endif // ifndef __GAMEFACTORY_H__
