#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

/**
 * @file GameManager.h 
 * @brief Header files which contains game manager.
*/

#include "Deck/Deck.h"
#include "Players/Character.h"
#include "Game/Spirit/Spirit.h"
#include <vector>

class GameState;

/// @brief Class that provides managment of the game process.
class GameManager
{
private:
    std::unique_ptr<GameState> currentState; //< Current game state (1 of 4)
    Deck& deck; //< Game deck.
    std::vector<std::unique_ptr<Character>> players; //< Players.
    int magicPool = 0; //< General magic pool.
    Character* currentPlayer; //< Current player (AI or human).
    std::vector<std::unique_ptr<Spirit>> activeSpirits; //< Existing spirits.

public: 

    /**
     * @brief GameManager constructor.
     * @param d Game deck.
    */
    GameManager(Deck& d);

    /**
     * @brief GameManager destructor.
    */
    ~GameManager();

    /**
     * @brief Adds player in the game. 
     * @param player Player that is wanted to be added.
    */
    virtual void addPlayer(std::unique_ptr<Character> player);

    /**
     * @brief Provides game manager make transitions between states. 
     * @param state State that is wanted to be set. 
    */
    void setState(std::unique_ptr<GameState> state);

    /**
     * @brief Starts the main game loop.
     *
     * Enters a loop that continues as long as a current state is set,
     * calling updateState() on the current state in each iteration.
    */
    void run(); // set state to 'MainMenuState'

    /**
     * @brief Get players that are now in the game. 
     * @details Virtual to override in MockGameManager for tests.
     * @return Constant link on vector containing the unique pointers on class Character objects.
    */
    virtual const std::vector<std::unique_ptr<Character>>& getPlayers() const;

    /**
     * @brief Get game deck. 
     * @return Link on class Deck object which represents the game deck.
    */
    Deck& getDeck();

    /**
     * @brief Clear existing players.
    */
    void clearPlayers();

    /**
     * @brief Get general magic pool. 
     * @return Integer which represents magic pool on the gaming table. 
    */
    virtual int getMagicPool() const;

    /**
     * @brief Get player whose turn is now. 
     * @details Virtual to override in MockGameManager for tests.
     * @return Pointer on the class Character object which represents the current player. 
    */
    virtual Character* getCurrentPlayer();

    /**
     * @brief Set current player. 
     * @details Virtual to override in MockGameManager for tests.
     * @param player Player that is wanted to be set. 
    */
    virtual void setCurrentPlayer(Character* player);

    /**
     * @brief Reduce or increase magic pool by the amount. 
     * @details Virtual to override in MockGameManager for tests.
     * @param amount Integer which represents change in magic pool, may be positive or negative.
    */
    virtual void updateMagicPool(int amount);

    /**
     * @brief Check if card now should be amplified. 
     * @details Virtual to override in MockGameManager for tests.
     * @return True, if card should be amplified, false otherwise.
    */
    virtual bool shouldAmplify() const;

    /**
     * @brief Set magic pool to 0. 
     * @details Virtual to override in MockGameManager for tests.
    */
    virtual void resetMagicPool();

    /**
     * @brief Add spirit to the game. 
     * @details Virtual to override in MockGameManager for tests.
     * @param spirit Unique pointer on the class Spirit object which represents the spirit that is want to be added. 
    */
    virtual void addSpirit(std::unique_ptr<Spirit> spirit);

    /**
     * @brief Process spirits effects. 
    */
    void processSpirits();
};

#endif