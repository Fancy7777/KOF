//
//  Definitions.h
//  KOF
//
//  Created by Dongtao Yu on 12/08/2015.
//
//

#ifndef KOF_Definitions_h
#define KOF_Definitions_h

// GOBAL
#define BORDER_SELECTED                 "selected"
#define BORDER_UNSELECTED               "unselected"
#define BACK_BUTTON                     "buttonBack"
#define CREATE_BUTTON                   "buttonCreate"
#define SEARCH_BUTTON                   "buttonSearch"
#define QUICK_JOIN_BUTTON               "buttonQuickJoin"
#define FB_BUTTON                       "buttonFB"
#define TW_BUTTON                       "buttonTW"

#define CHARACTER_ICON_BIG_PATH         "characters/{0}/icon_big.png"

#define BACKGROUND_PLIST                "backgrounds/backgrounds.plist"
#define BACKGROUND_ICON_PATH            "backgrounds/{0}/icon.png"

#define CHARACTER_SPRITE_PATH           "characters/{0}/sprite.plist"
#define CHARACTER_ANIMATION_PATH        "characters/{0}/animation.plist"

#define BACKGROUND_SPRITE_PATH          "backgrounds/{0}/sprite.plist"
#define BACKGROUND_ANIMATION_PATH       "backgrounds/{0}/animation.plist"

#define COUNTDOWN_SPRITE_PATH           "countdown/sprite.plist"
#define COUNTDOWN_ANIMATION_PATH        "countdown/animation.plist"

#define CHARACTER_SPRITE_PATH           "characters/{0}/sprite.plist"
#define CHARACTER_ANIMATION_PATH        "characters/{0}/animation.plist"

#define CHARACTER_SQUAT                 "{0}/squat"
#define CHARACTER_SQUAT_DOWN            "{0}/squat_down"
#define CHARACTER_SQUAT_HIT             "{0}/squat_hit"
#define CHARACTER_SQUAT_KICK1           "{0}/squat_kick1"
#define CHARACTER_SQUAT_KICK2           "{0}/squat_kick2"
#define CHARACTER_SQUAT_MOVEBACK        "{0}/squat_moveback"
#define CHARACTER_SQUAT_MOVEFORWARD     "{0}/squat_moveforward"
#define CHARACTER_SQUAT_PUNCH1          "{0}/squat_punch1"
#define CHARACTER_SQUAT_PUNCH2          "{0}/squat_punch2"
#define CHARACTER_SQUAT_UP              "{0}/squat_up"

#define CHARACTER_INITIAL_FRAME         "characters/{0}/stand/00.png"

#define CHARACTER_STAND                 "{0}/stand"
#define CHARACTER_STAND_HIT             "{0}/stand_hit"
#define CHARACTER_STAND_JUMP            "{0}/stand_jump"
#define CHARACTER_STAND_KICK1           "{0}/stand_kick1"
#define CHARACTER_STAND_KICK2           "{0}/stand_kick2"
#define CHARACTER_STAND_MOVEBACK        "{0}/stand_moveback"
#define CHARACTER_STAND_MOVEFORWARD     "{0}/stand_moveforward"
#define CHARACTER_STAND_PUNCH1          "{0}/stand_punch1"
#define CHARACTER_STAND_PUNCH2          "{0}/stand_punch2"

#define CHARACTER_KICK_SOUNDEFFECT      "music/soundEffect/{0}/kick.wav"
#define CHARACTER_PUNCH_SOUNDEFFECT     "music/soundEffect/{0}/punch.wav"
#define CHARACTER_DIE_SOUNDEFFECT       "music/soundEffect/{0}/die.wav"
#define CHARACTER_HIT_SOUNDEFFECT       "music/soundEffect/{0}/hit.wav"
#define CHARACTER_START_SOUNDEFFECT     "music/soundEffect/{0}/start.wav"
#define CHARACTER_WIN_SOUNDEFFECT       "music/soundEffect/{0}/win.wav"
#define CHARACTER_GETHIT_SOUNDEFFECT    "music/soundEffect/get_hit.wav"


#define CHARACTER_START                 "{0}/start"
#define CHARACTER_WIN                   "{0}/win"
#define CHARACTER_DIE                   "{0}/die"


#define NUM_BACKGROUNDS 4
#define NUM_BESTOF 3

// Splash Scence
#define DISPLAY_TIME_SPLASH_SCENE       0.5
#define TRANSITION_TIME                 0.5


// Choose Character Scene
#define CHOOSE_CHARACTER_SCENE                      "ChooseCharacterScene"
#define CHOOSE_CHARACTER_SCENE_FILE                 "ChooseCharacter.csb"
#define CHOOSE_CHARACTER_SCENE_CHARACTER_WIDTH      310.0
#define CHOOSE_CHARACTER_SCENE_CHARACTER_HEIGHT     430.0
#define CHOOSE_CHARACTER_SCENE_CHARACTER_PREFIX     "character"
#define CHOOSE_CHARACTER_SCENE_PLAYER_ICON_HOLDER   "player"
#define CHOOSE_CHARACTER_SCENE_OPPONENT_ICON_HOLDER "opponent"
#define CHOOSE_CHARACTER_SCENE_COUNT_DOWN_LABEL     "labelCountDown"
#define CHOOSE_CHARACTER_SCENE_ROOMID               "roomID"
#define CHOOSE_CHARACTER_SCENE_READY_L              "buttonReadyL"
#define CHOOSE_CHARACTER_SCENE_READY_R              "buttonReadyR"
#define CHOOSE_CHARACTER_SCENE_GO_L                 "buttonGoL"
#define CHOOSE_CHARACTER_SCENE_GO_R                 "buttonGoR"
#define CHOOSE_CHARACTER_SCENE_WAITING              "waiting"


// Create Room Scene
#define CREATE_ROOM_SCENE                       "CreateRoomScene"
#define CREATE_ROOM_SCENE_FILE                  "CreateRoom.csb"
#define CREATE_ROOM_SCENE_BACKGROUND_PREFIX     "background"
#define CREATE_ROOM_SCENE_CHECKBOX_PREFIX       "checkbox"
#define CREATE_ROOM_SCENE_BESTOF_LABEL          "label"


// Choose Room Scene
#define CHOOSE_ROOM_SCENE                       "ChooseRoomScene"
#define CHOOSE_ROOM_SCENE_FILE                  "ChooseRoom.csb"
#define CHOOSE_ROOM_SCENE_ROOM_LIST             "listRoom"
#define CHOOSE_ROOM_SCENE_ROOM_LIST_ITEM_ID     "text"
#define CHOOSE_ROOM_SCENE_ROOM_LIST_ITEM_BESTOF "bestof"
#define CHOOSE_ROOM_SCENE_ROOM_LIST_ITEM_STATUS "status"
#define CHOOSE_ROOM_SCENE_ROOM_LIST_ITEM_BACKGROUND "map"
#define CHOOSE_ROOM_SCENE_SPRITE_SEARCH         "spriteSearch"
#define CHOOSE_ROOM_SCENE_TEXT_SEARCH           "textSearch"


// GAME PLAY
#define GAME_PLAY_SCENE                         "GamePlayScene"
#define GAME_PLAY_SCENE_FILE                    "GamePlay.csb"
#define GAME_PLAY_SCENE_FIGHTER_LEFT            "left"
#define GAME_PLAY_SCENE_FIGHTER_RIGHT           "right"
#define GAME_PLAY_SCENE_JOYSTICK_BASE           "Resources/joystick.png"
#define GAME_PLAY_SCENE_JOYSTICK                "Resources/joystick_button.png"
#define GAME_PLAY_SCENE_BUTTON_A_NORMAL "Resources/a.png"
#define GAME_PLAY_SCENE_BUTTON_A_PRESSED "Resources/a_c.png"
#define GAME_PLAY_SCENE_BUTTON_A_X      0.7f
#define GAME_PLAY_SCENE_BUTTON_A_Y      0.35f
#define GAME_PLAY_SCENE_BUTTON_B_NORMAL "Resources/b.png"
#define GAME_PLAY_SCENE_BUTTON_B_PRESSED "Resources/b_c.png"
#define GAME_PLAY_SCENE_BUTTON_B_X      0.85f
#define GAME_PLAY_SCENE_BUTTON_B_Y      0.35f
#define GAME_PLAY_SCENE_BUTTON_C_NORMAL "Resources/c.png"
#define GAME_PLAY_SCENE_BUTTON_C_PRESSED "Resources/c_c.png"
#define GAME_PLAY_SCENE_BUTTON_C_X      0.75f
#define GAME_PLAY_SCENE_BUTTON_C_Y      0.15f
#define GAME_PLAY_SCENE_BUTTON_D_NORMAL "Resources/d.png"
#define GAME_PLAY_SCENE_BUTTON_D_PRESSED "Resources/d_d.png"
#define GAME_PLAY_SCENE_BUTTON_D_X      0.9f
#define GAME_PLAY_SCENE_BUTTON_D_Y      0.15f
#define GMAE_PLAY_SCENE_COMPARE_SUCCESS         0
#define GAME_PLAY_SCENE_SOUND_VOLUME_FULL       100
#define GAME_PLAY_SCENE_SOUND_VOLUME_EMPTY      0
#define GAME_PLAY_SCENE_SOUND_VOLUME_ONE        1.0



// MULTIPLAYER
#define MAX_USERS 2
#define ROOM_NAME "MEMEDA"

// ROOM PROPERTIES
#define ROOM_PROPERTY_BACKGROUND "background"
#define ROOM_PROPERTY_BESTOF      "bestof"

// Multiplayer protocol
#define MP_GLOBLE                           100

#define OP_GB_USER_JOINED                   500
#define OP_GB_USER_LEFT                     501

#define MP_CHOOSE_CHARACTER_SCENE           1

#define OP_CCS_CHARACTER_CHANGED            1
#define OP_CCS_READY                        2
#define OP_CCS_START_COUNTDOWN              3
#define OP_CCS_NOTREADY                     4
#define OP_CCS_START_GAME                   5

#define MP_GAME_PLAY_SCNE                   2

#define MP_GAME_PLAY_SCENE_CONFIRM          3

//#define OP_GPS_BUTTON_A                     1
//#define OP_GPS_BUTTON_B                     2
//#define OP_GPS_BUTTON_C                     3
//#define OP_GPS_BUTTON_D                     4
//#define OP_GPS_STAND_MOVEFORWARD            5
//#define OP_GPS_STAND_MOVEBACK               6
//#define OP_GPS_STAND                        7

//Setting
#define SETTING_SCENE_PERCENTAGE            0.01





// Fighter

#define OP_GPS_ACTION_1_STAND                      100
#define OP_GPS_ACTION_1_STAND_MOVEFORWARD          101
#define ANIMATION_ACTION_1_STAND_MOVEFORWARD       10001
#define OP_GPS_ACTION_1_STAND_MOVEBACK             102
#define ANIMATION_ACTION_1_STAND_MOVEBACK          10002

#define OP_GPS_ACTION_1_SQUAT                      150
#define OP_GPS_ACTION_1_SQUAT_DOWN                 151
#define OP_GPS_ACTION_1_SQUAT_MOVEBACK             152
#define ANIMATION_ACTION_1_SQUAT_MOVEBACK          15002
#define OP_GPS_ACTION_1_SQUAT_MOVEFORWARD          153
#define ANIMATION_ACTION_1_SQUAT_MOVEFORWARD       15003

#define ANIMATION_ACTION_1_STAND_JUMP              2000
#define OP_GPS_ACTION_2_STAND_JUMP                 200
#define OP_GPS_ACTION_2_STAND_PUNCH1               202
#define OP_GPS_ACTION_2_STAND_PUNCH2               203
#define OP_GPS_ACTION_2_STAND_KICK1                204
#define OP_GPS_ACTION_2_STAND_KICK2                205
#define OP_GPS_ACTION_2_STAND_HIT                  206

#define OP_GPS_ACTION_2_SQUAT_PUNCH1               250
#define OP_GPS_ACTION_2_SQUAT_PUNCH2               251
#define OP_GPS_ACTION_2_SQUAT_KICK1                252
#define OP_GPS_ACTION_2_SQUAT_KICK2                253
#define OP_GPS_ACTION_2_SQUAT_HIT                  254

#define OP_GPS_ACTION_3_WIN                        300
#define OP_GPS_ACTION_3_DIE              301

#define OP_GPS_NO_ACTION                         9999

#define ACTION_MOVE_SPEED                   200
#define ACTION_1_MOVE_DURATION              .7f


#define ACTION_UNSTOPPABLE                  1000
#define ACTION_STOPPABLE                    1001
// Camera
#define CAMERA_MOVE_THRESHOLD               150
#define CAMERA_FIGHTER_OFFSET               10
#define SCREEN_FIGHTER_OFFSET               140
#define GAME_FRAME_DELAY                    50

//GamePlayScene
//Physics

#define GRAVITY_X                           0.0f
#define GRAVITY_Y                           0.0f

#define PUNCH1_DAMAGE                       3
#define PUNCH2_DAMAGE                       4
#define KICK1_DAMAGE                        5
#define KICK2_DAMAGE                        6

//#define Character_Gravity_X                 0.0f
//#define Character_Gravity_Y                 -200.0f
//#define Physic_Edge_Offset                  350.0f
//#define Character1_bitmask                  1
//#define Character2_bitmask                  2
//#define Character_Edge_Offset               50.0f
//#define Physic_Box_Density                  1.0f
//#define Physic_Box_Restitution              0.0f
//#define Physic_Box_Friction                 1.0f
//#define Punch1_damage                       3
//#define Punch2_damage                       4
//#define Kick1_damage                        3
//#define Kick2_damage                        4

#define GAME_FRAME_LENGTH                    30
#define GAME_FRAME_PER_LOCKSTEP              2



struct command_t
{
    int sender;
    int scene;
    int operation;
    std::string properties;
};

#endif
