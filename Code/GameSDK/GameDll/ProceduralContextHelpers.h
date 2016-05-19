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

#ifndef __PROCEDURAL_CONTEXT_HELPERS__H__
#define __PROCEDURAL_CONTEXT_HELPERS__H__


namespace ProceduralContextHelpers
{


	template< typename TRequestType >
	class CRequestList
	{
		typedef std::vector< TRequestType > TRequestsVector;

	public:
		uint32 AddRequest( TRequestType& request )
		{
			request.id = m_nextId;
			m_requests.push_back( request );

			// It is extremely unlikely that we'll wrap around and get a clash with a current request, since requests will usually have a short life span.
			++m_nextId;

			return request.id;
		}

		void RemoveRequest( const uint32 cancelRequestId )
		{
			typename TRequestsVector::iterator itEnd = m_requests.end();
			for ( typename TRequestsVector::iterator it = m_requests.begin(); it != itEnd; ++it )
			{
				const TRequestType& request = *it;
				if ( cancelRequestId == request.id )
				{
					m_requests.erase( it );
					return;
				}
			}
		}

		const TRequestType& GetRequest( const size_t index ) const
		{
			return m_requests[ index ];
		}

		const size_t GetCount() const
		{
			return m_requests.size();
		}

	private:
		uint32 m_nextId;
		TRequestsVector m_requests;
	};



}


#endif