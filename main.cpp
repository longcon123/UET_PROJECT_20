//code them va cham nhan vat voi enemy, code them bo vu khi, code them victory win;
#define SDL_MAIN_HANDLED
#include "ObjectControl.h"
#include "boss.h"
#include "player.h"
#include "head.h"
#include "hand.h"
#include "map.h"
#include "block.h"
#include "gun.h"
#include "bullet.h"
#include "lsb.h"
#include "infor.h"
#include "blood.h"
#include "enemy.h"
#include "sound.h"
#include "bua.h"
const int WIDTH = 900;
const int HEIGHT = 600;

int main() {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window;
	SDL_Renderer* render;
	SDL_Event e;
	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &render);
	bool game_start = 1;
	bool isRunning = true;
	ObjectControl obj;
	obj.setPos(0, 0);
	obj.setRect1(0, 0, 900, 600);
	obj.setRect2(900, 600);
	obj.setImage("start_end.png", render);
	bool play = false;
	while (game_start) {
		int x_mouse, y_mouse;
		SDL_GetMouseState(&x_mouse, &y_mouse);
		if (game_start) {
			if (0 <= x_mouse && x_mouse <= 555 && 220 <= y_mouse && y_mouse <= 312) {
				obj.rect1.x = 900;
			}
			else obj.rect1.x = 0;
		}
		obj.draw(render);
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) game_start = false;
			if (e.type == SDL_MOUSEBUTTONDOWN) {
				if (e.button.button == SDL_BUTTON_LEFT && 0 <= x_mouse && x_mouse <= 555 && 220 <= y_mouse && y_mouse <= 312) {
					play = true;
				}
			}
		}
		if (play) {
			Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
			Mix_Chunk* sound_gun = Mix_LoadWAV("laser1.wav");
			Mix_Chunk* sound_jump = Mix_LoadWAV("jump.wav");
			Mix_Chunk* sound_reload = Mix_LoadWAV("reload.wav");
			Mix_Chunk* sound_lsb = Mix_LoadWAV("lsb_sound.mp3");
			Mix_Chunk* lsb_active = Mix_LoadWAV("lsb_on.wav");
			Mix_Chunk* end_game = Mix_LoadWAV("end_music.mp3");
			Mix_Chunk* bua_sound = Mix_LoadWAV("bua.wav");
			Mix_Music* back_ground = Mix_LoadMUS("Merry Go.mp3");

			Infor infor;
			infor.setPos(infor.x, infor.y);
			infor.setRect1(0, 0, infor.w_val, infor.h_val);
			infor.setRect2(infor.w_val, infor.h_val);
			infor.setImage("player_blood.png", render);
			Sound sound;
			sound.setPos(sound.x, sound.y);
			sound.setRect1(0, 0, sound.w_val, sound.h_val);
			sound.setRect2(sound.w_val, sound.h_val);
			sound.setImage("sound_be.png", render);
			Blood p_blood;
			p_blood.setPos(p_blood.x_p, p_blood.y_p);
			p_blood.setRect1(0, 0, p_blood.w_val_p, p_blood.h_val_p);
			p_blood.setRect2(p_blood.w_val_p, p_blood.h_val_p);
			p_blood.setImage("blood.png", render);
			Enemy enemy;
			enemy.setPos(enemy.x_pos, enemy.y_pos);
			enemy.setRect1(0, 0, enemy.w_val, enemy.h_val);
			enemy.setRect2(enemy.w_val, enemy.h_val);
			enemy.setImage("enemy.png", render);
			Boss boss;
			boss.setPos(boss.x_pos, boss.y_pos);
			boss.setRect1(0, 0, boss.w_val, boss.h_val);
			boss.setRect2(boss.w_val, boss.h_val);
			boss.setImage("boss.png", render);
			Blood e_blood;
			e_blood.setPos(enemy.x_pos - 5, enemy.y_pos - 20);
			e_blood.setRect1(0, 0, enemy.x_pos, enemy.y_pos);
			e_blood.setRect2(e_blood.w_val_e, e_blood.h_val_e);
			e_blood.setImage("enemy_blood.png", render);
			Blood b_blood;
			b_blood.setPos(boss.x_pos - 5, boss.y_pos - 20);
			b_blood.setRect1(0, 0, boss.x_pos, boss.y_pos);
			b_blood.setRect2(b_blood.w_val_b, b_blood.h_val_b);
			b_blood.setImage("b_blood.png", render);
			Player player;
			player.setPos(player.x_pos, player.y_pos);
			player.setRect1(0, 0, player.w_val, player.h_val);
			player.setRect2(player.w_val, player.h_val);
			player.setImage("nbdj1.png", render);
			Head head;
			head.setPos(player.x_pos + 13, player.y_pos - 15);
			head.setRect1(0, 0, head.w_val, head.h_val);
			head.setRect2(head.w_val, head.h_val);
			head.setImage("headnew.png", render);
			Hand hand;
			hand.setPos(hand.x_hand, hand.y_hand);
			hand.setRect1(0, 0, hand.w_val, hand.h_val);
			hand.setRect2(hand.w_val, hand.h_val);
			hand.setImage("handnew.png", render);
			Lsb lsb;
			lsb.setPos(lsb.x_gun + 50, lsb.y_gun);
			lsb.setRect1(0, 0, lsb.w_val, lsb.h_val);
			lsb.setRect2(lsb.w_val, lsb.h_val);
			lsb.setImage("kiem.png", render);
			Gun gun;
			gun.setPos(gun.x_gun + 10, gun.y_gun);
			gun.setRect1(0, 0, gun.w_val, gun.h_val);
			gun.setRect2(gun.w_val, gun.h_val);
			gun.setImage("gun.png", render);
			Bua bua;
			bua.setPos(bua.x, bua.y);
			bua.setRect1(0, 0, bua.w_val, bua.h_val);
			bua.setRect2(bua.w_val, bua.h_val);
			bua.setImage("bua.png", render);
			vector <Bullet*> bulletVec;
			//bullet.set_is_move(true);
			const int fps = 100;
			const int frameDelay = 1000 / fps;
			int frameTime;
			Uint32 frameStart;
			Map map1, map2, map3;
			map1.loadLevel(render, 1);
			map2.loadLevel(render, 2);
			map3.loadLevel(render, 3);
			player.player_blood = 260;
			player.weapon_on = 0;
			enemy.blood = 70;
			//int temp;
			bool ong = true;
			bool cham_tuong = false;
			double tjump = 0;
			int bang_dan = 30;
			bool cham_t = false;
			bool duoi = false;
			int enemy_run_time = 0;
			bool lv1 = 1, lv2 = 0, lv3 = 0;
			bool mute = false;
			bool da_nhat = false;
			bool nha = true;
			bool chem = false;
			double end_time = 0;
			Mix_PlayMusic(back_ground, -1);
			while (play) {
				frameStart = SDL_GetTicks();
				// lay vi tri chuot neu x player < x chuot set flip horizontal = true
				//------------------------------------------
				int x, y;
				SDL_GetMouseState(&x, &y);
				SDL_SetRenderDrawColor(render, 155, 130, 100, SDL_ALPHA_OPAQUE);
				//cout << sound.volumn << endl;
				if (player.player_blood > 0) {
					while (SDL_PollEvent(&e)) {
						if (e.type == SDL_QUIT) play = false;
						if (e.type == SDL_MOUSEBUTTONDOWN) {
							if (sound.x <= x && x <= sound.x + sound.w_val && sound.y <= y && y <= sound.y + sound.h_val) {
								if (e.button.button == SDL_BUTTON_LEFT) {
									if (!(sound.rect2.w < 30) and !mute) {
										sound.update_volumn(mute);
									}
									else mute = true;
									if (!(sound.rect2.w > 60) and mute) {
										sound.update_volumn(mute);
									}
									else mute = false;
								}
								Mix_VolumeMusic(sound.volumn);
							}
							else {
								if (player.get_typeWeapon() == 1) {
									if (e.button.button == SDL_BUTTON_LEFT and bang_dan > 0) {
										Bullet* bullet = new Bullet();
										bullet->setPos(hand.get_x() - 10, hand.get_y() + 5);
										bullet->setRect1(0, 0, bullet->w_val, bullet->h_val);
										bullet->setRect2(bullet->w_val, bullet->h_val);
										bullet->setImage("bullet1.png", render);
										bullet->isShooting = true;
										bulletVec.push_back(bullet);
										bang_dan -= 1;
										Mix_PlayChannel(-1, sound_gun, 0);
									}
									else if (e.button.button == SDL_BUTTON_LEFT and bang_dan == 0) {
										Mix_PlayChannel(-1, sound_reload, 0);
									}
								}
								else if (player.get_typeWeapon() == 2) {
									if (e.button.button == SDL_BUTTON_LEFT) {
										if (lsb.lsb_on == false) {
											lsb.setSprite(50, 10, 0);
											Mix_PlayChannel(-1, lsb_active, 0);
											lsb.lsb_on = true;
										}
										else if (chem == false and lsb.lsb_on == true) {
											Mix_PlayChannel(-1, sound_lsb, 0);
											chem = true;
											lsb.angle = 90;
											if (obj.checkColli(lsb.getRect2(), enemy.getRect2())) enemy.blood -= enemy.blood;
											if (obj.checkColli(boss.getRect2(), lsb.getRect2()) and lv3) boss.blood -= 100;
										}
										else if (chem == true and lsb.lsb_on == true)
										{
											lsb.angle = 0;
											chem = false;
										}
									}

								}
							}
						}

						else if (e.type == SDL_KEYDOWN) {
							if (e.key.keysym.sym == SDLK_SPACE) {
								if (ong == true) {
									ong = false;
									player.y_step = -5;
									player.isJumping = true;
									Mix_PlayChannel(-1, sound_jump, 0);
									player.rect1.y = 0;
									player.rect1.x = 31;
								}
							}
							if (e.key.keysym.sym == SDLK_a) {
								player.x_step = -3;
								player.isMoving = true;
							}
							if (e.key.keysym.sym == SDLK_d) {
								player.x_step = 3;
								player.isMoving = true;
							}
							if (e.key.keysym.sym == SDLK_r && bang_dan < 30) {
								Mix_PlayChannel(-1, sound_reload, 0);
								bulletVec.clear();
								bang_dan = 30;
							}
							if (e.key.keysym.sym == SDLK_g and player.get_typeWeapon() == 0) {
								da_nhat = false;
							}
							else if (e.key.keysym.sym == SDLK_g and player.get_typeWeapon() != 0) {
								da_nhat = true;
							}

						}
						else if (e.type == SDL_KEYUP) {
							if (e.key.keysym.sym == SDLK_a) {
								player.x_step = 0;
								player.isMoving = false;
							}
							if (e.key.keysym.sym == SDLK_d) {
								player.x_step = 0;
								player.isMoving = false;
							}
						}
					}
				}
				if (player.rect2.y >= 600) player.player_blood = 0; // neu roi xuong khoi game thi thua luon
				
				if (lv1) {
					map1.drawMap(render); // ve map
					if (player.rect2.x < 400) player.rect2.x += player.x_step; // nhan vat di chuyen den giua man hinh thi khong di, chi co camera move
				// ---- kiem tra dang o lv 1
					// kiem tra va cham theo huong cua x axis cua nhan vat voi block map
					for (int i = 0; i < map1.blockVec.size(); i++) {
						map1.blockVec[i]->rect2.x -= player.x_step; // di chuyen camera theo nhan vat, tat ca object di chuyen nguoc lai
						if (obj.checkColli(player.getRect2(), map1.blockVec[i]->getRect2())) {// neu va cham
							if (map1.blockVec[i]->block_type == 'n' and player.get_key) { lv1 = false; lv2 = false, lv3 = true;}
							if (player.x_step > 0) { // new xstep > 0 => nhan vat dang tien thi se k cho tien nua
								player.rect2.x = map1.blockVec[i]->rect2.x - player.rect2.w; cham_t = true; // khong cho tien
							}
							if (player.x_step < 0) {// new xstep < 0 => nhan vat dang tien thi se k cho lui` nua
								player.rect2.x = map1.blockVec[i]->rect2.x + map1.blockVec[i]->rect2.w; cham_t = true; //ko chu lui`
							}
						}
					}
					// kiem tra va cham theo axis y cua nhan vat voi block map
					if ((!player.isJumping and !ong) || (!player.isJumping && !cham_tuong)) { // neu ma ko nhay va khong cham tuong suy ra player roi xuong
						player.y_step = 10; // roi xuong
					}
					else {
						tjump += 0.05; // neu ma nhay len thi set thoi gian nhay tjump += 0.05 

					}
					if (tjump >= 1.5 || cham_tuong || ong) { // neu ma da nhay len dc >= 1.5 thi set time = 0; roi xuong
						tjump = 0; player.isJumping = false;
					}
					player.rect2.y += player.y_step; // cong vi tri y nhan vat voi step
					for (int i = 0; i < map1.blockVec.size(); i++) {
						if (obj.checkColli(player.getRect2(), map1.blockVec[i]->getRect2())) {
							if (map1.blockVec[i]->block_type == 'd') { lv1 = false; lv2 = true; } // kiem tra va cham voi block door thi chuyen map level
							if (map1.blockVec[i]->block_type == 'w') player.player_blood -= 1; // kiem tra va cham block water thi tru mau'
							else if (map1.blockVec[i]->block_type == 's') player.player_blood -= 10; // kiem tra va cham block gai thi tru mau nhieu hon
							if (player.y_step > 0) { player.rect2.y = map1.blockVec[i]->rect2.y - player.rect2.h; player.y_step = 0; cham_tuong = false; ong = true; }  // khi roi xuong va gap block thi k xuong duoc nua
							if (player.y_step < 0) { player.rect2.y = map1.blockVec[i]->rect2.y + map1.blockVec[i]->rect2.h; cham_tuong = true; ong = false; } // khi nhay len ma gap block thi roi xuong
						}
					}
				}
				// -------------
				//kiem tra dang o lv2 
				if (lv2) {
					map2.drawMap(render);
					if (player.rect2.x < 400) player.rect2.x += player.x_step; // nhan vat di chuyen den giua man hinh thi khong di, chi co camera move
				// ---- kiem tra dang o lv 1
					for (int i = 0; i < map2.blockVec.size(); i++) {
						map2.blockVec[i]->rect2.x -= player.x_step;
						if (obj.checkColli(player.getRect2(), map2.blockVec[i]->getRect2())) {
							if (map2.blockVec[i]->block_type == 'd') { lv2 = false; lv1 = true; }
							else if (map2.blockVec[i]->block_type == 'k') { map2.blockVec[i]->rect1.x = 40; player.get_key = true; player.player_blood += 50; }
							if (player.x_step > 0) {
								player.rect2.x = map2.blockVec[i]->rect2.x - player.rect2.w; cham_t = true;
							}
							if (player.x_step < 0) {
								player.rect2.x = map2.blockVec[i]->rect2.x + map2.blockVec[i]->rect2.w; cham_t = true;
							}
						}
					}
					if ((!player.isJumping and !ong) || (!player.isJumping && !cham_tuong)) {
						player.y_step = 10;
					}
					else {
						tjump += 0.05;

					}
					if (tjump >= 1.5 || cham_tuong || ong) {
						tjump = 0; player.isJumping = false;
					}
					player.rect2.y += player.y_step;
					for (int i = 0; i < map2.blockVec.size(); i++) {
						if (obj.checkColli(player.getRect2(), map2.blockVec[i]->getRect2())) {
							if (map2.blockVec[i]->block_type == 'w') player.player_blood -= 1;
							else if (map2.blockVec[i]->block_type == 's') player.player_blood -= 5;
							if (player.y_step > 0) { player.rect2.y = map2.blockVec[i]->rect2.y - player.rect2.h; player.y_step = 0; cham_tuong = false; ong = true; }
							if (player.y_step < 0) { player.rect2.y = map2.blockVec[i]->rect2.y + map2.blockVec[i]->rect2.h; cham_tuong = true; ong = false; }
						}
					}
				}
				//-------------------------------------------------------------------------------------------------------------------------------------
				if (lv3) {
					map3.drawMap(render);
					bua.draw(render);
					if(boss.blood > 0) boss.draw(render);
					b_blood.draw(render);
					bua.rect2.x -= player.x_step;
					bua.rect2.y -= 2;
					boss.rect2.x -= player.x_step;
					b_blood.update(boss.rect2.x-170, boss.rect2.y-100);
					//bua.rect1.y -= 1;
					if (bua.rect2.y <= 60) {
						bua.rect2.y = 310;
						Mix_PlayChannel(-1, bua_sound, 0);
					}
					if (obj.checkColli(bua.getRect2(), player.getRect2())) player.player_blood -= 50;
					if (player.rect2.x < 500) player.rect2.x += player.x_step; // nhan vat di chuyen den giua man hinh thi khong di, chi co camera move
				// ---- kiem tra dang o lv 1
					for (int i = 0; i < map3.blockVec.size(); i++) {
						map3.blockVec[i]->rect2.x -= player.x_step;
						if (obj.checkColli(player.getRect2(), map3.blockVec[i]->getRect2())) {
							if (player.x_step > 0) {
								player.rect2.x = map3.blockVec[i]->rect2.x - player.rect2.w; cham_t = true;
							}
							if (player.x_step < 0) {
								player.rect2.x = map3.blockVec[i]->rect2.x + map3.blockVec[i]->rect2.w; cham_t = true;
							}
						}
					}
					if ((!player.isJumping and !ong) || (!player.isJumping && !cham_tuong)) {
						player.y_step = 10;
					}
					else {
						tjump += 0.05;

					}
					if (tjump >= 1.5 || cham_tuong || ong) {
						tjump = 0; player.isJumping = false;
					}
					player.rect2.y += player.y_step;
					for (int i = 0; i < map3.blockVec.size(); i++) {
						if (obj.checkColli(player.getRect2(), map3.blockVec[i]->getRect2())) {
							if (map3.blockVec[i]->block_type == 'e') {
								map3.blockVec[i]->rect2.x += 2;
								player.x_step = 1;
							}
							else if (map3.blockVec[i]->block_type == 'u' and map3.blockVec[i]->rect2.y > 50) {
								map3.blockVec[i]->rect2.y -= 1;
							}
							if (map3.blockVec[i]->block_type == 'w') player.player_blood -= 1;
							else if (map3.blockVec[i]->block_type == 's') player.player_blood -= 5;
							else if (map3.blockVec[i]->block_type == 'n' and boss.blood <= 0) { play = 0; }
							if (player.y_step > 0) { player.rect2.y = map3.blockVec[i]->rect2.y - player.rect2.h; player.y_step = 0; cham_tuong = false; ong = true; }
							if (player.y_step < 0) { player.rect2.y = map3.blockVec[i]->rect2.y + map3.blockVec[i]->rect2.h; cham_tuong = true; ong = false; }
						}
					}
				}
				
				if (x >= player.get_x())
				{
					player.moveL = false;
					player.moveR = true;
				}
				else
				{
					player.moveR = false;
					player.moveL = true;
				}
				player.setFlip(player.moveL, player.moveR);
				//-----------------------------------------
				//neu di chuyen thi sprite
				if (player.isMoving and !player.isJumping) {
					player.rect1.y = player.Move;
					player.setSprite(60, 31, 1);
				}
				//else player.rect1.y = player.Idle;
				
				if (enemy.blood > 0 and enemy.isAlive) { // neu enemy con song va con mau
					//
					//cho enemy di lai 
					enemy_run_time++;
					if (enemy_run_time >= 80) {
						enemy.rect2.x -= 3;
						if (enemy_run_time >= 160) enemy_run_time = 0;
					}
					else enemy.rect2.x += 3;// enemy di lai
					if (obj.checkColli(player.getRect2(), enemy.getRect2())) { // kiem tra va cham nhan vat voi enemy
						player.player_blood -= 5;
					}
				}
				else if (enemy.blood <= 0 and enemy.isAlive) { // het mau nhung ma van song va thanh vat pham bonus mau
					enemy.rect1.x = 60;
					if (obj.checkColli(player.getRect2(), enemy.getRect2())) { // neu ma nguoi choi an thi huy luon bonus
						player.player_blood += 50;
						if (player.player_blood > 260) player.player_blood = 260;
						enemy.isAlive = false;
					}
				}
				
				//kiem tra nhat vu khi va set type weapon cho player
				if (!da_nhat) {
					if (obj.checkColli(gun.getRect2(), player.getRect2()) ) { 
						player.weapon_on = 1;
					}
					if (obj.checkColli(lsb.getRect2(), player.getRect2())) {
						player.weapon_on = 2;
					}
				}
				else if (da_nhat) {
					player.weapon_on = 0;
				}
				//

				// update blood cho enemy va player
				p_blood.rect2.w = player.player_blood;
				p_blood.rect1.w = player.player_blood;
				e_blood.rect2.w = enemy.blood;
				e_blood.rect1.w = enemy.blood;
				b_blood.rect2.w = boss.blood;
				b_blood.rect1.w = boss.blood;
				// update blood cho enemy va player


				// lay goc va ve cho head va hand theo mouse x y
				head.getAngle(x, y);
				head.setFlip(player.moveL, player.moveR);
				head.draw_with_angle(render);
				hand.getAngle(x, y);
				// lay goc va ve cho head va hand theo mouse x y

				// kiem tra xem nhat vu khi gi
				if (player.get_typeWeapon() == 1) {
					gun.getAngle(x, y);
					gun.setFlip(player.moveL, player.moveR);
					gun.draw_with_angle(render);
					for (int i = 0; i < bulletVec.size(); ++i) {
						if (bulletVec[i]->isShooting) {
							bulletVec[i]->getAngle(x, y);
						}
						bulletVec[i]->update();
						bulletVec[i]->move(bulletVec[i]->new_x, bulletVec[i]->new_y, 1);
						bulletVec[i]->setFlip(player.moveL, player.moveR);
						bulletVec[i]->draw_with_angle(render);
						bulletVec[i]->outScreen();
						if (obj.checkColli(enemy.getRect2(), bulletVec[i]->getRect2())) enemy.blood -= 10;
						if (obj.checkColli(boss.getRect2(), bulletVec[i]->getRect2()) and lv3) boss.blood -= 50;
						bulletVec[i]->isShooting = false;
					}
					gun.update(player.rect2.x, player.rect2.y - 20);
				}
				else {
					gun.angle = 90;
					gun.rect2.x -= player.x_step;
				}
				if (player.get_typeWeapon() == 2) {
					//lsb.getAngle(x, y);
					//
					if (lsb.lsb_on) {
						lsb.setSprite(50, 10, 0);
					}//kich hoat sprite light saber
					lsb.update(player.rect2.x+5, player.rect2.y - 50);
					
				}
				else {
					lsb.angle = 90;
					lsb.rect2.x -= player.x_step;
				}
				// kiem tra xem nhat vu khi gi, khong nhat thi update vitri moi
				if (enemy.isAlive and lv2 or enemy.isAlive and lv1 or lv3) {
					enemy.draw(render); 
					//cho enemy di chuyen nguoc voi camera
					enemy.rect2.x -= player.x_step;
				}
				
				// ve va update vi tri
				player.draw(render);
				lsb.draw_with_angle(render);
				gun.draw_with_angle(render);
				sound.draw(render);
				infor.draw(render);
				p_blood.draw(render);
				e_blood.draw(render);
				hand.draw_with_angle(render);
				e_blood.update(enemy.rect2.x - 5, enemy.rect2.y - 20);
				hand.update(player.rect2.x+10, player.rect2.y+5);
				head.update(player.rect2.x, player.rect2.y - 20);
				//	
				//kiem tra nhan vat con alive hay khong de play again
				if(player.player_blood <= 0) {
					Mix_HaltMusic();//stop background music
					player.player_blood = 0;
					player.is_alive = false;
					obj.rect1.y = 600;
					obj.rect1.x = 0;
					end_time += 0.05;
					if (end_time >= 0 and end_time < 1) { Mix_PlayChannel(1, end_game, 0); }
					else if (end_time > 30) {
						end_time = 0;
						obj.rect1.y = 0;
						obj.rect1.x = 0;
						play = 0;
					}
					obj.draw(render);
				}
				// gioi han fps
				frameTime = SDL_GetTicks() - frameStart;
				if (frameDelay > frameTime)
					SDL_Delay(frameDelay - frameTime);
				// gioi han fps

				SDL_RenderPresent(render);
				SDL_RenderClear(render);
			}
		}	
		SDL_RenderPresent(render);
		SDL_RenderClear(render);
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}