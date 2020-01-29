#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <memory>
#include <ctime>
#include <vector>

#include <Windows.h>
#include <conio.h>

#include "ConsoleSettingsHandler.h"
#include "KeyboardInput.h"
#include "GameMenu.h"
#include "PacMan.h"
#include "Ghost.h"
#include "Memento.h"
#include "CareTakerGhost.h"

using namespace std;
using namespace game_constants;

class PacMan;
class Ghost;

class Game : public Keyboard
{
public:
    static Game* getInstance(std::shared_ptr<ConsoleSettingsHandler> console_handler);

    void                start();
    void                pause();
    void                setCharFromMap(const char, const int, const int);
    inline void         decreasePointsNum()                                      { --m_points_num_;                             }
    inline void         setPointsNum(const int num)                              { m_points_num_ = num;                         }
    inline void         setCharOfMap(const int x, const int y, const char print) { m_MapToPrint_[y][x] = print;                 }

    inline const int    getPointsNum()                            { return m_points_num_;                                       }
    inline const char   getCharOfBuffer(const int x, const int y) { return m_MapToPrint_[y][x];                                 }
    inline const double getTime ()                                { return (std::clock() - m_timer_ ) / (double)CLOCKS_PER_SEC; }
    inline const double getTime2()                                { return (std::clock() - m_timer2_) / (double)CLOCKS_PER_SEC; }

private:

    static Game* m_GameInstance;

    double m_seconds_in_boost_by_level_  ;
    double m_seconds_to_mode_change_     ;
    int    m_points_num_                 ;
    int    m_level_counter_              ;
    int    m_number_of_ghosts_           ;
    char   m_MapToPrint_[Y_SIZE][X_SIZE] ;
    char   m_substring_[11]              ;
    bool   m_isPaused_                   ;
    bool   m_isGameover_                 ;
    bool   m_check_to_unpause_           ;

    std::clock_t m_timer_                , 
                 m_timer2_               , 
                 m_temp_timer1_          , 
                 m_temp_timer2_          ;

    std::shared_ptr<ConsoleSettingsHandler> m_console_handler_ ;
    std::unique_ptr<GameMenu>               m_menu_            ;
    std::unique_ptr<PacMan>                 m_pacman_          ;
    std::unique_ptr<Ghost>                  m_ghosts_[4]       ;
    
    const bool isDead();
    const bool isEndGame();
    const bool collisionWithGhost();
    const bool renderPause(const bool);
    void       render();
    void       startNewGame();
    void       game_Loop ();
    void       loadLevel ();
    void       moveGhosts();
    void       handleTime();
    void       startLevel();
    void       fillMapToPrint();
    void       initializeAllActors();
    void       setMazeText(std::string, int);
    void       resetMapInCollision();
    void       checkPointersToActors();
    void       changeGhostsModeByTimer();
    void       handleGhostsMovement(const int ghost_num);
    void       handleMenuChoise(const int choise);

    void       handleBlinkyFeature();
    void       handlePinkyFeature();
    void       handleInkyFeature();
    void       handleClydeFeature();

    Game(std::shared_ptr<ConsoleSettingsHandler> console_handler);
    Game           ( const Game&  ) = delete;
    Game           ( const Game&& ) = delete;
    Game& operator=( Game const&  ) = delete;
    Game& operator=( Game const&& ) = delete;
    ~Game();
};
#endif // GAME_H