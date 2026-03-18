/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include "./Map.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    /* ----- DEFAULTs ----- */
    Map::Map(int cellSize, const char *fileName, sdl::Render &render)
        : _cellSize(cellSize), _size(0, 0)
    {
        _cellDatas.clear();
        _map.clear();

        _cellDatas[' '] = CellData(EMPTY, false, render);
        _cellDatas['X'] = CellData(WALL, true, render, "wall.png");
        _cellDatas['P'] = CellData(PLAYER, false, render);
        _cellDatas['C'] = CellData(CHEST, false, render);

        _floorTexture = sdl::TextureManager::get().get(render, "floor.png");
        _ceilingTexture = sdl::TextureManager::get().get(render, "ceiling.png");

        _buildMap(fileName);
    }

    /* ----- GETTERs ----- */
    int Map::getCellSize() const
    {
        return _cellSize;
    }

    sdl::Vector<int> Map::getSize() const
    {
        return _size;
    }

    sdl::Vector<double> Map::getPlayerStart() const
    {
        return _playerStart;
    }

    std::shared_ptr<sdl::Texture> Map::getFloorTexture() const
    {
        return _floorTexture;
    }

    std::shared_ptr<sdl::Texture> Map::getCeilingTexture() const
    {
        return _ceilingTexture;
    }

    const std::vector<Map::EntitySpawn> &Map::getEntitySpawns() const
    {
        return _entitySpawns;
    }

    /* ----- FUNCTIONs ----- */
    std::optional<Map::CellData> Map::getCellAt(sdl::Vector<double> pixelCoords) const
    {
        if (pixelCoords.x < 0 || pixelCoords.x >= _size.x * _cellSize || pixelCoords.y < 0 || pixelCoords.y >= _size.y * _cellSize)
            return std::nullopt;

        sdl::Vector<int> mapCoords(int(pixelCoords.x / _cellSize), int(pixelCoords.y / _cellSize));
        return _map[mapCoords.y * _size.x + mapCoords.x];
    }

    bool Map::isSolidCellAt(sdl::Vector<double> pixelCoords) const
    {
        std::optional<Map::CellData> cell = getCellAt(pixelCoords);
        if (!cell) return false;
        return cell->isSolid();
    }

    /* ----- PRIVATE FUNCTIONs ----- */
    void Map::_buildMap(const char *fileName)
    {
        FILE *file = fopen(fileName, "r");
        if (file == nullptr) return;

        char c;
        int x = 0;
        int maxX = 0;
        int y = 0;

        _entitySpawns.clear();

        while ((c = fgetc(file)) != EOF) {
            if (c == '\n') {
                y++;
                maxX = std::max(maxX, x);
                x = 0;
            } else {
                if (c == 'P') {
                    _playerStart = sdl::Vector<double>(x * _cellSize + _cellSize / 2, y * _cellSize + _cellSize / 2);
                    c = ' ';
                } else if (c == 'C') {
                    sdl::Vector<double> spawnPos(x * _cellSize + _cellSize / 2.0, y * _cellSize + _cellSize / 2.0);
                    _entitySpawns.push_back({CellType::CHEST, spawnPos});
                    c = ' ';
                }

                _map.push_back(_cellDatas[c]);
                x++;
            }
        }

        fclose(file);
        _size = sdl::Vector<int>(maxX, y);
    }
}; // namespace Raycaster
