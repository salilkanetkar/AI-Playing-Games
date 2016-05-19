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

// Description: Implements statistic serializers
//              This one serializes to a file based on kiev game code


#ifndef __XMLSTATSSERIALIZER_H__
#define __XMLSTATSSERIALIZER_H__

#if _MSC_VER > 1000
# pragma once
#endif

#include "IGameStatistics.h"
#include "IXml.h"

//////////////////////////////////////////////////////////////////////////

struct SStatNode
{
	typedef std::map<uint32, SStatNode*> TNodes;

	SNodeLocator						locator;
	XmlNodeRef							xml;
	SStatNode*							parent;
	TNodes									children;
	IStatsContainer&				container;

	SStatNode(const SNodeLocator& loc, IStatsContainer& cont, SStatNode* prnt = 0);
	SStatNode* addOrFindChild(const SNodeLocator& loc, IStatsContainer& cont);
	void removeChild(const SNodeLocator& loc);
};

//////////////////////////////////////////////////////////////////////////

class CXMLStatsSerializer : public IStatsSerializer
{
public:
	CXMLStatsSerializer(IGameStatistics* pGS, CStatsRecordingMgr* pMissionStats);
	virtual void VisitNode(const SNodeLocator& locator, const char* serializeName, IStatsContainer& container, EStatNodeState state);
	virtual void LeaveNode(const SNodeLocator& locator, const char* serializeName, IStatsContainer& container, EStatNodeState state);

private:
	void OnNodeSaved(const SNodeLocator& locator, XmlNodeRef node);
	void SaveContainerData(const IStatsContainer& container, XmlNodeRef node);
	void SaveEventTrack(XmlNodeRef n, const char* name, const IStatsContainer& container, size_t eventID);
	void SaveStatValToXml(XmlNodeRef node, const char* name, const SStatAnyValue& val);

	SStatNode* m_rootNode;
	SStatNode* m_currentNode;
	IGameStatistics* m_stats;
	CStatsRecordingMgr* m_statsRecorder;
};

//////////////////////////////////////////////////////////////////////////

#endif // __XMLSTATSSERIALIZER_H__
