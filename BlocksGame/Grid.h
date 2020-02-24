#pragma once
#include "GameObject.h"
#include <map>
#include <set>
#include "Jelly.h"
#include <deque>
#include <cstdint>
#include <random>
#include <functional>

typedef std::function<Uint32()> RandomSource;

/*!
 * \class Grid
 *
 * \brief Represents the play grid logically. The grid is a dynamic 2D array where columns can appear and dissapear at any point as well as elements of the columns.
 *
 */
class Grid : public GameObject	
{
	std::map<unsigned int, std::string> TypeToSprite = {
		{0, "JellyR"}, {1, "JellyG"}, {2, "JellyB"}, {3, "JellyP"}
	};

	 enum CubeColor : Uint8{
		RED, GREEN, BLUE, GRAY
	};

	int GridHeight = 10;
	int TileSize = 24;
	unsigned int MinimumCombo = 2;
	std::vector<Texture*> TexForCubes;
	float SpawnTime = 3;
	float ElapsedTime = 0;
	Uint32 CurrentScore = 0;
	
	std::map<Uint8, Uint32> JellyCount;


	Vector2 SpawnPosition;
	Vector2 EndPosition;
	std::deque<std::vector < Jelly* >> grid;
	void UpdateGrid();
	void UpdateScore(Uint32 _destroyed);
	
	std::vector<Jelly*> FindNeighbors(int _gridX, int _gridY, Uint8 _type);
	std::set<Jelly*> FindAllNeighbors(int _gridX, int _gridY, Uint8 _type);

	bool IsLeftSimilar(int _gridX, int _gridY, Uint8 _type);
	bool IsRightSimilar(int _gridX, int _gridY, Uint8 _type);
	bool IsAboveSimilar(int _gridX, int _gridY, Uint8 _type);
	bool IsBelowSimilar(int _gridX, int _gridY, Uint8 _type);
	RandomSource Random;

public:

	void SpawnColumn();
	void Reset();
	Uint32 GetCurrentScore();
	std::map<Uint8, Uint32> GetJellyCount();
	void Disable();
	void Enable();

	virtual void OnUpdate() override;
	virtual void OnInitialize() override;
	void OnCubeClicked(int _gridX, int _gridY, Uint8 _type);
	Grid(std::vector<Texture*> _textures, Vector2(_spawnPosition) ): TexForCubes(_textures), SpawnPosition(_spawnPosition), EndPosition(_spawnPosition){};
	Grid();
	~Grid();
};

