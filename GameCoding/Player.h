#pragma once

#include "Object.h"

enum class PlayerType
{
	MissileTank,
	CannonTank,
};

class Player : public Object
{
public:
	Player();
	virtual ~Player() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	wstring		GetMeshKey();

	void		SetPlayerId(int32 playerId) { _playerId = playerId; }
	void		SetPlayerType(PlayerType playerType) { _playerType = playerType; }
	void		SetPlayerTurn(bool playerTurn) { _playerTurn = playerTurn; }
	
	int32		GetPlayerId() { return _playerId; }
	PlayerType	GetPlayerType() { return _playerType; }
	bool		GetPlayerTurn() { return _playerTurn; }
	
private:
	void		UpdateFireAngle();

private:
	int32		_playerId = 0; 
	PlayerType	_playerType = PlayerType::MissileTank;
	bool		_playerTurn = false;
	float		_fireAngle = 0.f;
};

