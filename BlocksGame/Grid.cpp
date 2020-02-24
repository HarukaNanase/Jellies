#include "Grid.h"
#include "World.h"
#include <TransformComponent.h>
#include <CollisionComponent.h>
#include "TextComponent.h"
#include "InputComponent.h"
#include "MovementComponent.h"
#include "Jelly.h"
#include <time.h>


void Grid::SpawnColumn()
{

	std::vector<Jelly*> column;
	EndPosition.x -= TileSize;

	for (int i = grid.size() - 1; i >= 0; i--) {
		auto& column = grid[i];
		for (auto& cube : column) {
			cube->GridPosition.x += 1;
		}
	}

	
	for (int i = 0; i < GridHeight; i++) {
		auto startPosition = Vector2(SpawnPosition.x + TileSize, SpawnPosition.y + i * TileSize);
		auto type = Random();
		auto spriteName = TypeToSprite[type];
		auto _cube = Jelly(TexForCubes[type], startPosition, type, this);
		_cube.GetComponent<TransformComponent>()->GetSize().x = TileSize;
		_cube.GetComponent<TransformComponent>()->GetSize().y = TileSize;
		_cube.GridPosition = Vector2(0, i);
		auto cube = GetWorld()->AddGameObject(_cube);
		column.push_back(cube);
	}
	
	this->grid.push_front(column);
	
	UpdateGrid();
}

void Grid::Reset()
{
	this->JellyCount.clear();
	for (auto pairColumn : grid) {
		for (auto jelly : pairColumn)
			jelly->Destroy();
	}
	this->grid.clear();
	this->SpawnColumn();
	this->CurrentScore = 0;
	this->IsActive = true;
	GetComponent<TextComponent>()->GetText("score")->SetText("0");
}

Uint32 Grid::GetCurrentScore()
{
	return CurrentScore;
}

std::map<Uint8, Uint32> Grid::GetJellyCount()
{
	return this->JellyCount;
}



void Grid::Disable()
{
	for (auto& pair : grid) {
		for (auto& jelly : pair) {
			jelly->GetComponent<InputComponent>()->SetIsEnabled(false);
		}
	}
	this->IsActive = false;
}

void Grid::Enable()
{
	for (auto& pair : grid) {
		for (auto& jelly : pair) {
			jelly->GetComponent<InputComponent>()->SetIsEnabled(true);
		}
	}
	this->IsActive = true;
}

void Grid::OnUpdate()
{

	ElapsedTime += GetWorld()->GetDeltaTime() * 0.001;
	if (ElapsedTime >= SpawnTime) {
		this->SpawnColumn();
		ElapsedTime = 0;
	}

	
}

void Grid::OnInitialize()
{
	
	std::mt19937::result_type seed = time(0);

	Random = std::bind(std::uniform_int_distribution<Uint32>(0, 3), std::mt19937(seed));


	this->AddComponent<SoundComponent>();
	this->AddComponent<CollisionComponent>(SpawnPosition, Vector2(TileSize, TileSize), *this);		
	this->AddComponent<TextComponent>();
	this->GetComponent<TextComponent>()->AddText("score", GetWorld()->GetFontManager().Get("OpenSans-Regular"), Color(0xff, 0xFF, 0xFF, 0xFF), "0", Vector2(-260, 160));
	this->AddTag("grid");
}

Grid::Grid()
{
}


void Grid::UpdateGrid()
{
	

	grid.erase(std::remove_if(grid.begin(), grid.end(), [](std::vector<Jelly*> _column) {
		return _column.size() == 0;
	}), grid.end());
	

	for(int i = grid.size()-1; i>=0; i--){
		for (int k = 0; k < grid[i].size(); k++) {
			auto cube = grid[i][k];
			cube->GridPosition.x = i;
			cube->GridPosition.y = k;
			auto& cubePosition = cube->GetComponent<TransformComponent>()->GetPosition();
			Vector2 newCubePosition(SpawnPosition.x - i * TileSize, SpawnPosition.y + k * TileSize);
			cube->GetComponent<MovementComponent>()->MoveTo(cubePosition, newCubePosition, 0.15f);
		}
	}

	if (grid.size() > 0) {
		GetComponent<CollisionComponent>()->Position = grid[grid.size()-1][0]->GetComponent<TransformComponent>()->GetPosition();
	}
	else {
		GetComponent<CollisionComponent>()->Position = SpawnPosition;
	}

}



void Grid::UpdateScore(Uint32 _destroyed)
{
	CurrentScore += 100 * _destroyed;
	std::string score = std::to_string(CurrentScore);
	this->GetComponent<TextComponent>()->GetText("score")->SetText(score);
}

void Grid::OnCubeClicked(int _gridX, int _gridY, Uint8 _type)
{
	if (IsActive) {
		auto candidates = FindAllNeighbors(_gridX, _gridY, _type);

		if (candidates.size() >= MinimumCombo) {
			for (auto candidate : candidates) {
				auto& candidateRow = grid[candidate->GridPosition.x];
				JellyCount[candidate->Type]++;
				candidateRow.erase(std::remove_if(candidateRow.begin(), candidateRow.end(), [&candidate](Jelly* cube) { return candidate->GetObjectId() == cube->GetObjectId(); }), candidateRow.end());
				candidate->Destroy();
			}
			this->GetComponent<SoundComponent>()->Play2DSound("slimedestroy", false);
			UpdateGrid();
			UpdateScore(candidates.size());
		}
	}
	//std::cout << _cubeColor << " Cube at (" << _gridX << "," << _gridY << ")" << " has " <<  candidates.size() << " candidates." << std::endl;
}

std::vector<Jelly*> Grid::FindNeighbors(int _gridX, int _gridY, Uint8 _type)
{
	std::vector<Jelly*> adjacentCandidates;

	if(IsAboveSimilar(_gridX, _gridY, _type))
			adjacentCandidates.push_back(grid[_gridX][_gridY + 1]);

	if(IsBelowSimilar(_gridX, _gridY, _type))
			adjacentCandidates.push_back(grid[_gridX][_gridY - 1]);

	if(IsLeftSimilar(_gridX, _gridY, _type))
				adjacentCandidates.push_back(grid[_gridX + 1][_gridY]);
	
	if(IsRightSimilar(_gridX, _gridY, _type))
				adjacentCandidates.push_back(grid[_gridX - 1][_gridY]);
	

	return adjacentCandidates;
}

std::set<Jelly*> Grid::FindAllNeighbors(int _gridX, int _gridY, Uint8 _type)
{
	std::vector<Jelly*> unvisitedNeighbors;
	std::set<Jelly*> visitedNeighbors;
	unvisitedNeighbors.push_back(grid[_gridX][_gridY]);

	while (unvisitedNeighbors.size() > 0) {
		auto cube = unvisitedNeighbors.back();
		unvisitedNeighbors.pop_back();
		visitedNeighbors.insert(cube);
		auto cubeNeighbors=FindNeighbors(cube->GridPosition.x, cube->GridPosition.y, _type);
		for (auto neighbor : cubeNeighbors) {
			if (std::find_if(visitedNeighbors.begin(), visitedNeighbors.end(), [&](Jelly* _cube) {return neighbor->GridPosition == _cube->GridPosition; }) == visitedNeighbors.end()) {
				unvisitedNeighbors.push_back(neighbor);
			}
		}
	}
	
	return visitedNeighbors;
}

bool Grid::IsLeftSimilar(int _gridX, int _gridY, Uint8 _type)
{
	return (_gridX < grid.size() - 1) && (grid[_gridX + 1].size() > _gridY) && (grid[_gridX + 1][_gridY]->Type == _type);
}

bool Grid::IsRightSimilar(int _gridX, int _gridY, Uint8 _type)
{
	return (_gridX > 0) && (grid[_gridX - 1].size() - 1 >= _gridY) && (grid[_gridX - 1][_gridY]->Type == _type);
}

bool Grid::IsAboveSimilar(int _gridX, int _gridY, Uint8 _type)
{
	return (grid[_gridX].size() > _gridY + 1) && (grid[_gridX][_gridY + 1]->Type == _type);
}

bool Grid::IsBelowSimilar(int _gridX, int _gridY, Uint8 _type)
{
	return (_gridY > 0) && (grid[_gridX][_gridY - 1]->Type == _type); // can i look down?
	
}

Grid::~Grid()
{
	for (auto& pair : grid) {
		for (auto& obj : pair) {
			obj->Destroy();
		}
	}
}
