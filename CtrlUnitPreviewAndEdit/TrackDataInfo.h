#pragma once

#include <list>
#include <map>
#include <rpc.h>
#pragma comment(lib ,"rpcrt4.lib")

class ClipDataRect;

// TrackDataInfo �R�}���h �^�[�Q�b�g

typedef std::map<int, ClipDataRect*> ClipDataInfoMap;	//InPoint,ClipId 
//typedef std::map<int, UUID> ClipDataInfoMap;	//InPoint,ClipId 

class TrackDataInfo : public CObject
{
public:
	TrackDataInfo();
	virtual ~TrackDataInfo();

	// TODO: ����̓g���b�N�}�l�[�W���[�ɁI
	enum TrackDataTag{ TRACKDATATAG_INFO };
	enum TrackKind {
		VIDEO,
		AUDIO,
		TITLE,
		INFO,
		MASTER_VIDEO,
		MASTER_AUDIO
	};

private:
	TrackDataTag m_eTrackDataInfoTag;
	UUID m_uiTrackId;
	TrackKind m_eTrackKind;
	UUID m_uiInputChannel;
	UUID m_uiOutputChannel;
	ClipDataInfoMap m_mpClipDataInfoMap;

	// �Đ����Q�ƍ���
	BOOL m_fSolo;
	BOOL m_fAudioRecordable;
	BOOL m_fMuted;
	BOOL m_fLevelPointRecordable;
	

public:
	BOOL InitTrackData(void);
	BOOL InitializeClipId(UUID& uiClipId);

	// TODO: �܂��̓N���b�v���d�Ȃ�Ȃ��O��
	ClipDataRect* GetClipDataInfo(int iFrame, int& iInPoint);
	int GetClipDataArray(int iStartFrame, int iEndFrame, ClipDataInfoMap& mpClipMap);

	void AddClip(const int iInPoint, ClipDataRect* pClipData);
	void DeleteClip(const int iInPoint);
	void ChangeClip(const int iOldInPoint, const int iNewInPoint, ClipDataRect* pClipData);

	// TODO: ����̓R���g���[���[�ɁI
	ClipDataRect* CheckMove(ClipDataRect* pCheckClipData, const int iInPoint, const int iOutPoint);

};


