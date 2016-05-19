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

#pragma once

namespace ScreenResolution
{
  struct SScreenResolution
  {
    int iWidth;
    int iHeight;
    unsigned int nDephtPerPixel;
    string sResolution;

    SScreenResolution(unsigned int _iWidth, unsigned int _iHeight, unsigned int _nDepthPerPixel, const char* _sResolution):
        iWidth(_iWidth)
      , iHeight(_iHeight)
      , nDephtPerPixel(_nDepthPerPixel)
      , sResolution(_sResolution)
    {}

    SScreenResolution()
    {}
  };

  void InitialiseScreenResolutions();
  void ReleaseScreenResolutions();

  bool GetScreenResolutionAtIndex(unsigned int nIndex, SScreenResolution& resolution);
	bool HasResolution(const int width, const int height);
	int GetNearestResolution(const int width, const int height);
  unsigned int GetNumScreenResolutions();
}