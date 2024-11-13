#pragma once

#include <functional>
#include <array>
#include <set>
#include <string>
#include <thread>
#include <atomic>

#include "MuHelperData.h"

class CMuHelper
{
public:
	CMuHelper();
	~CMuHelper() = default;

public:
	static void CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);

	void Save(const cMuHelperConfig& config);
	void Load(const cMuHelperConfig& config);
	cMuHelperConfig GetConfig() const;
	void Start();
	void Stop();
	void Toggle();
	bool IsActive() { return m_bActive; }

	void AddTarget(int iTargetId, bool bIsAttacking);
	void DeleteTarget(int iTargetId);
	void DeleteAllTargets();

	void AddItem(int iItemId, POINT posDropped);
	void DeleteItem(int iItemId);

private:
	void WorkLoop(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
	void Work();
	int Buff();
	int BuffTarget(CHARACTER* pTargetChar, int iBuffSkill);
	int Heal();
	int HealSelf(int iHealingSkill);
	int ConsumePotion();
	int Attack();
	int RepairEquipments();
	int Regroup();
	int SimulateAttack(int iSkill);
	int SimulateSkill(int iSkill, bool bTargetRequired, int iTarget);
	int SimulateComboAttack();
	int GetNearestTarget();
	int GetFarthestTarget();
	int ComputeDistanceByRange(int iRange);
	int ComputeDistanceFromTarget(CHARACTER* pTarget);
	int ComputeDistanceBetween(POINT posA, POINT posB);
	int SimulateMove(POINT posMove);
	int ObtainItem();
	int SelectItemToObtain();
	bool ShouldObtainItem(int iItemId);
	int GetHealingSkill();
	bool HasAssignedBuffSkill();

private:
	cMuHelperConfig m_config;
	POINT m_posOriginal;
	std::thread m_timerThread;
	std::atomic<bool> m_bActive;
	std::set<int> m_setTargets;
	std::set<int> m_setItems;
	int m_iCurrentItem;
	int m_iCurrentTarget;
	int m_iCurrentBuffIndex;
	int m_iCurrentBuffPartyIndex;
	int m_iCurrentHealPartyIndex;
	int m_iComboState;
	int m_iHuntingDistance;
	int m_iObtainingDistance;
	int m_iLoopCounter;
	int m_iSecondsElapsed;
	int m_iSecondsAway;
	int m_iSecondsSinceLastBuff;
};

extern CMuHelper g_MuHelper;