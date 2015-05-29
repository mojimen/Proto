// TrackDataInfo.cpp : 実装ファイル
//

#include "stdafx.h"
#include "CtrlUnitPreviewAndEdit.h"
#include "TrackDataInfo.h"
#include "ClipDataRect.h"


// TrackDataInfo

TrackDataInfo::TrackDataInfo()
{
}

TrackDataInfo::~TrackDataInfo()
{
}


// TrackDataInfo メンバー関数

BOOL TrackDataInfo::InitTrackData(void)
{
	return TRUE;
}

BOOL TrackDataInfo::InitializeClipId(UUID& uiClipId)
{
	if (RPC_S_OK == UuidCreate(&m_uiTrackId))
	{
		uiClipId = m_uiTrackId;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

ClipDataRect* TrackDataInfo::GetClipDataInfo(int iFrame, int& iInPoint)
{
	if (m_mpClipDataInfoMap.size() == 0)
	{
		return nullptr;
	}
	ClipDataInfoMap::iterator itr = m_mpClipDataInfoMap.upper_bound(iFrame);
	if (itr == m_mpClipDataInfoMap.begin())
	{
		return nullptr;
	}
	--itr;
	ClipDataRect* pClipData = (*itr).second;
	if (((*itr).first <= iFrame) && (iFrame <= ((*itr).first + pClipData->GetDuration() - 1)))
	{
		iInPoint = (*itr).first;
		return pClipData;
	}
	else
	{
		return nullptr;
	}

}

int TrackDataInfo::GetClipDataArray(int iStartFrame, int iEndFrame, ClipDataInfoMap& mpClipMap)
{
	int iSize = 0;
	if (m_mpClipDataInfoMap.size() == 0)
	{
		return iSize;
	}
	ClipDataRect* pClipData;
	ClipDataInfoMap::iterator itr = m_mpClipDataInfoMap.upper_bound(iStartFrame);
	if (itr != m_mpClipDataInfoMap.begin())
	{
		--itr;
		pClipData = (*itr).second;
		if (iStartFrame <= ((*itr).first + pClipData->GetDuration() - 1))
		{
			mpClipMap[(*itr).first] = pClipData;
			++iSize;
		}
		++itr;
	}
	while (itr != m_mpClipDataInfoMap.end())
	{
		pClipData = (*itr).second;
		if ((*itr).first <= iEndFrame)
		{
			mpClipMap[(*itr).first] = pClipData;
			++itr;
			++iSize;
		}
		else
		{
			break;
		}
	}

	return iSize;
}




void TrackDataInfo::AddClip(const int iInPoint, ClipDataRect* pClipData)
{
	m_mpClipDataInfoMap[iInPoint] = pClipData;
}

void TrackDataInfo::DeleteClip(const int iInPoint)
{
	m_mpClipDataInfoMap.erase(iInPoint);
}

void TrackDataInfo::ChangeClip(const int iOldInPoint, const int iNewInPoint, ClipDataRect* pClipData)
{
	DeleteClip(iOldInPoint);
	AddClip(iNewInPoint, pClipData);
}


// TODO: これはコントローラーにあるべき
ClipDataRect* TrackDataInfo::CheckMove(ClipDataRect* pCheckClipData, const int iInPoint, const int iOutPoint)
{
	ClipDataRect* pClipData;
	int iPoint;
	pClipData = GetClipDataInfo(iInPoint, iPoint);
	if ((pClipData != nullptr) && (pClipData != pCheckClipData))
	{
		return pClipData;
	}
	pClipData = GetClipDataInfo(iOutPoint, iPoint);
	if ((pClipData != nullptr) && (pClipData != pCheckClipData))
	{
		return pClipData;
	}
	// 移動中のクリップに含まれるクリップがないかをチェック
	ClipDataInfoMap::iterator itr = m_mpClipDataInfoMap.upper_bound(iInPoint);
	if (itr == m_mpClipDataInfoMap.end())
	{
		return nullptr;
	}
	if (iOutPoint < (*itr).first)
	{
		return nullptr;
	}
	else
	{
		return (*itr).second;
	}

}