// TrackDataRect.cpp : 実装ファイル
//

#include "stdafx.h"
#include "CtrlUnitPreviewAndEdit.h"
#include "TrackDataRect.h"
//#include "ClipDataRect.h"


// TrackDataRect

TrackDataRect::TrackDataRect()
{
}

TrackDataRect::~TrackDataRect()
{
}


// TrackDataRect メンバー関数

BOOL TrackDataRect::InitTrackData(void)
{
	SetColor(TIMELINETRACKCOLOR_BRUSH_FLOAT, TIMELINETRACKCOLOR_BRUSH_FLOAT, TIMELINETRACKCOLOR_BRUSH2_FLOAT, TIMELINETRACKCOLOR_BRUSH2_FLOAT);
	SetBorderColor(TIMELINETRACKBORDERCOLOR_BRUSH2_FLOAT, TIMELINETRACKBORDERCOLOR_BRUSH_FLOAT, TIMELINETRACKBORDERCOLOR_BRUSH2_FLOAT, TIMELINETRACKBORDERCOLOR_BRUSH_FLOAT);
	return TRUE;
}

BOOL TrackDataRect::InitializeTrackRectId(UUID& uiClipId)
{
	if (RPC_S_OK == UuidCreate(&m_uiTrackRectId))
	{
		uiClipId = m_uiTrackRectId;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//ClipDataRect* TrackDataRect::GetClipDataInfo(int iFrame, int& iInPoint)
//{
//	if (m_mpClipDataInfoMap.size() == 0)
//	{
//		return nullptr;
//	}
//	ClipDataInfoMap::iterator itr = m_mpClipDataInfoMap.upper_bound(iFrame);
//	if (itr == m_mpClipDataInfoMap.begin())
//	{
//		return nullptr;
//	}
//	--itr;
//	ClipDataRect* pClipData = (*itr).second;
//	if (((*itr).first <= iFrame) && (iFrame <= ((*itr).first + pClipData->GetDuration() - 1)))
//	{
//		iInPoint = (*itr).first;
//		return pClipData;
//	}
//	else
//	{
//		return nullptr;
//	}
//
//}
//
//int TrackDataRect::GetClipDataArray(int iStartFrame, int iEndFrame, ClipDataInfoMap& mpClipMap)
//{
//	int iSize = 0;
//	if (m_mpClipDataInfoMap.size() == 0)
//	{
//		return iSize;
//	}
//	ClipDataRect* pClipData;
//	ClipDataInfoMap::iterator itr = m_mpClipDataInfoMap.upper_bound(iStartFrame);
//	if (itr != m_mpClipDataInfoMap.begin())
//	{
//		--itr;
//		pClipData = (*itr).second;
//		if (iStartFrame <= ((*itr).first + pClipData->GetDuration() - 1))
//		{
//			mpClipMap[(*itr).first] = pClipData;
//			++iSize;
//		}
//		++itr;
//	}
//	while (itr != m_mpClipDataInfoMap.end())
//	{
//		pClipData = (*itr).second;
//		if ((*itr).first <= iEndFrame)
//		{
//			mpClipMap[(*itr).first] = pClipData;
//			++itr;
//			++iSize;
//		}
//		else
//		{
//			break;
//		}
//	}
//
//	return iSize;
//}
//
//
//
//
//void TrackDataRect::AddClip(const int iInPoint, ClipDataRect* pClipData)
//{
//	m_mpClipDataInfoMap[iInPoint] = pClipData;
//}
//
//void TrackDataRect::DeleteClip(const int iInPoint)
//{
//	m_mpClipDataInfoMap.erase(iInPoint);
//}
//
//void TrackDataRect::ChangeClip(const int iOldInPoint, const int iNewInPoint, ClipDataRect* pClipData)
//{
//	DeleteClip(iOldInPoint);
//	AddClip(iNewInPoint, pClipData);
//}
//
//
//// TODO: これはコントローラーにあるべき
//ClipDataRect* TrackDataRect::CheckMove(ClipDataRect* pCheckClipData, const int iInPoint, const int iOutPoint)
//{
//	ClipDataRect* pClipData;
//	int iPoint;
//	pClipData = GetClipDataInfo(iInPoint, iPoint);
//	if ((pClipData != nullptr) && (pClipData != pCheckClipData))
//	{
//		return pClipData;
//	}
//	pClipData = GetClipDataInfo(iOutPoint, iPoint);
//	if ((pClipData != nullptr) && (pClipData != pCheckClipData))
//	{
//		return pClipData;
//	}
//	// 移動中のクリップに含まれるクリップがないかをチェック
//	ClipDataInfoMap::iterator itr = m_mpClipDataInfoMap.upper_bound(iInPoint);
//	if (itr == m_mpClipDataInfoMap.end())
//	{
//		return nullptr;
//	}
//	if (iOutPoint < (*itr).first)
//	{
//		return nullptr;
//	}
//	else
//	{
//		return (*itr).second;
//	}
//
//}