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

// Description : PlaylistActivityTracker - reports joining a playlist game to webserver, and retrieves counts of current activity from the same


#ifndef __PLAYLISTACTIVITYUTILITY_H__
#define __PLAYLISTACTIVITYUTILITY_H__

//////////////////////////////////////////////////////////////////////////
// Important Includes
#include "ICryTCPService.h"
#include "IConsole.h"
#include "ILevelSystem.h"
#include "DownloadMgr.h"


#define MAX_PLAYLISTS 10
#define MAX_VARIANTS 6
#define MAX_LEN_PLAYLIST_NAME 20

//////////////////////////////////////////////////////////////////////////
// CPlaylistActivityTracker definition
class CPlaylistActivityTracker : public IDataListener
{
public:
	//Constructor/Destructor
	CPlaylistActivityTracker();
	~CPlaylistActivityTracker();

//------------------------------------------------------------------------
// public types
	enum EActivityTrackerState
	{
		eATS_Idle,
		eATS_GetActivity,
		eATS_OnPlaylist,
	};

	struct VariantActivity
	{
		char		name[ MAX_LEN_PLAYLIST_NAME ];
		uint32	nPlayers;
		uint32	nGames;
		uint8		id;
	};

	struct PlaylistActivity
	{
		VariantActivity							variants[ MAX_VARIANTS ];
		char												name[ MAX_LEN_PLAYLIST_NAME ];
		uint32											nPlayers;
		uint32											nGames;
		ILevelRotation::TExtInfoId	id;
		uint32											nVariants;
		
	};

	typedef void			( *PlayListActivityCallback )( bool success, const PlaylistActivity* results, int numResults );
	
//------------------------------------------------------------------------
// public functions
	void Update( float dt );
	void SetState( EActivityTrackerState state );

	//'Advertise' joining a playlist
	//returns false if request fails to start
	bool JoinedPlaylist( ILevelRotation::TExtInfoId playlistId, uint32 variantId );

	//'Advertise' creating a game
	//returns false if request fails to start
	bool CreatedGame( ILevelRotation::TExtInfoId playlistId, uint32 variantId );

	//Request info on a playlist/playlists, with callback for results
	//returns false if request fails to start
	bool RequestCurrentActivity( PlayListActivityCallback callback = NULL );
	
	bool GetCachedActivity( ILevelRotation::TExtInfoId playlistId, uint32& players, uint32& games ) const;
	bool GetCachedActivity( ILevelRotation::TExtInfoId playlistId, uint32 variantId, uint32& players, uint32& games ) const;
	
	// IDataListener
	virtual void			DataDownloaded( CDownloadableResourcePtr inResource );
	virtual void			DataFailedToDownload( CDownloadableResourcePtr inResource );
	// ~IDataListener

//------------------------------------------------------------------------
// private members
private:

	enum ERequestTaskType
	{
		eRTT_AnnounceJoinPlaylist,
		eRTT_AnnounceCreateGame,
		eRTT_RequestActivity,
		eRTT_MaxCount,
	};

	enum EPlatformType
	{
		ePT_Unknown=0,
		ePT_PC,
		ePT_PS4,
		ePT_XBOXONE,
	};

	bool	UploadData( const char* pUrlPath, const char* pUrlParams, int receiveSize, ERequestTaskType taskType );
	bool	AnyActiveRequestsOfType( ERequestTaskType type );
	
	void	ReleaseResourceReference( CDownloadableResourcePtr resource );
	int		GetPlatformType();

	//server we communicate with
	ICVar					*m_serverNameCVar;
	ICVar					*m_serverPortCVar;

	//Downloadable resources for receiving data, we may have multiple in flight at the same time
	CDownloadableResourcePtr m_downloadableResources [eRTT_MaxCount]; 


	//callback to pass processed data to
	PlayListActivityCallback m_currentActivityCallback;

	//state data for update
	EActivityTrackerState	m_state;
	float	m_timeUntilNextAction;

	//cache of playlist activity
	uint32						m_nKnownPlaylists;
	PlaylistActivity	m_activityData[ MAX_PLAYLISTS ];
};

#endif //__PLAYLISTACTIVITYUTILITY_H__
