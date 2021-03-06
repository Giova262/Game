/*
 * Character.h
 *
 *  Created on: Sep 11, 2018
 *      Author: giova
 */

//#include "Headers.h"

#ifndef PLAYER_HH_
#define PLAYER_HH_

#include "../../Utils/BulletTypeHandler.hh"
#include "../../Utils/PlayerStateHandler.hh"
#include "../../Utils/Logger.hh"
#include "../../Utils/ICollisional.hh"
#include "Gun.hh"
#include "Item.hh"
#include "ServerMessageHandler.hh"

class Player : public ICollisional
{
	public:

		Player(CameraLogic* _cameraLogic, ServerMessageHandler* _serverMessageHandler, int _player_id, string _username);
		virtual ~Player();

		//Collisional
		int getLeftLimit() { return col_box_xi; }
		int getRightLimit() { return col_box_xf; }
		int getTopLimit() { return col_box_yi; }
		int getBottomLimit() { return col_box_yf; }

		void updatePlayer();
		void updateCollisionBox();
		void updateGun();

		void renderPlayer();
		void renderLives();
		void renderGun();

		void destroy();

		int getPosX() { return pos_x; }
		int getPosY() { return pos_y; }

		void pickupItem(Item* item);

		void spawn(int x, int y);
		void freeze();
		void dragOfflinePlayer();

		//ACCIONES
		void jump();
		void goDown();
		void walkLeft();
		void walkRight();
		bool canMoveRight(int pixels_to_move);
		void pointUP(bool cond);
		void pointDefault(bool cond);
		void pointDown(bool cond);
		void bodyToGround();
		void normalState();
		void shoot();

		void fallingDownStop() { falling = false; }
		void fallingDown() { falling = true; }
		bool isFalling() { return falling; }

		bool isAlive() { return state != STATE_DEAD; }
		bool isDead() { return state == STATE_DEAD; }
		bool outOfLives() { return lives_remaining <= 0; }
		void kill();
		bool canRevive();
		void handleSpawnImmortality();
		bool isImmortal() { return immortal_mode; }

		void handleKeys(const Uint8* playerKeyStates);
		bool alreadyProcessedKeys() { return processedKeys; }

		void setOnlineAgain();
		bool isOnline() { return state != STATE_FREEZED; }
		bool isOffline() { return state == STATE_FREEZED; }

		void disableMovementBeyondBorder() { movement_beyond_border = false; }
		void enableMovementBeyondBorder() { movement_beyond_border = true; }
		bool canMoveBeyondBorder() { return movement_beyond_border; }

		void increaseLevelScore(int level, int score_points) { level_score[level] += score_points; }
		int getLevelScore(int level) { return level_score[level]; }
		int getTotalScore() { return (level_score[0] + level_score[1] + level_score[2]); }

		string getUsername() { 	return username; }

		list<Bullet*>* getBulletList() { return gun->getBullets(); }

	private:

		int player_id;
		string username;
		int pos_x, pos_y, maxDistanceJump;
		bool falling;

		int lives_remaining;

		// Manejo de tiempo desde que muere hasta que revive
		Uint32 death_time = 0; // Tiempo en ticks cuando murió
		static const Uint32 revive_cooldown = 1500; // En milisegundos, cuanto espero hasta que pueda respawnear luego de morir

		// Manejo del modo inmortal
		bool immortal_mode = false;
		bool immortal_player_activated = false;
		Uint32 immortal_mode_time = 0; // Tiempo en ticks cuando activó o desactivo último modo inmortal
		static const Uint32 immortal_mode_cooldown = 500; // En milisegundos, cuanto espero hasta que pueda procesar nuevamente tecla de modo inmortal

		// Manejo de modo inmortal temporal tras un spawm
		static const Uint32 spawn_immortality_cooldown = 2500;
		Uint32 spawn_time = 0;

		Uint32 timeAtIterationStart=0;

		bool movement_beyond_border;

		PlayerState state;

		enum PlayerDirection {
			DIRECTION_FRONT,
			DIRECTION_BACK
		};
		PlayerDirection direction;

		int col_box_xi, col_box_yi, col_box_xf, col_box_yf;

		// manejo de disparo
		enum AimPosition {AIM_UP,AIM_FRONT,AIM_DOWN,AIM_BODYTOGROUND,AIM_BACK,AIM_UP_BACK,AIM_DOWN_BACK,AIM_BODYTOGROUND_BACK};
		AimPosition aimingAt;

		// arma en lugar de manejo de balas?
		Gun* gun;

		CameraLogic* cameraLogic;
		ServerMessageHandler* serverMessageHandler;

		enum PlayerKeys {
			KEYCODE_UP,
			KEYCODE_DOWN,
			KEYCODE_RIGHT,
			KEYCODE_LEFT,
			KEYCODE_SPACE,
			KEYCODE_LCTRL,
			KEYCODE_I
		};

		bool processedKeys = false; // Esto es para evitar procesar 2 mensajes que hayan llegado muy juntos en el mismo frame, y hacer que por ejemplo, el pj avanze el doble.

		int level_score[3] = {0, 0, 0};
};

#endif /* PLAYER_HH_ */
