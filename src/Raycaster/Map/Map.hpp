/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- RAYCASTER_MAP_HPP_ ----- */
#ifndef RAYCASTER_MAP_HPP_
#define RAYCASTER_MAP_HPP_

/* ----- INCLUDEs ----- */
#include <SDL2/SDL.h>
#include <fstream>
#include <memory>
#include <optional>
#include <unordered_map>
#include <vector>
#include "SDL/Color/Color.hpp"
#include "SDL/Render/Render.hpp"
#include "SDL/Texture/Texture.hpp"
#include "SDL/TextureManager/TextureManager.hpp"
#include "SDL/Vector/Vector.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    enum CellType {
        EMPTY,
        WALL,
        PLAYER,
        CHEST,
    };

    class Map
    {
        public:
            class CellData
            {
                public:
                    CellData() = default;
                    CellData(CellType type, bool isSolid, sdl::Render &render, std::string textureFile = "");
                    ~CellData() = default;

                    CellType getType() const;
                    bool isSolid() const;
                    std::shared_ptr<sdl::Texture> getTexture() const;

                private:
                    CellType _type = EMPTY;
                    bool _isSolid = false;
                    std::string _textureFile = "";
                    std::shared_ptr<sdl::Texture> _texture = nullptr;
            };

            struct EntitySpawn {
                    CellType type;
                    sdl::Vector<double> position;
            };

            Map(int cellSize, const char *fileName, sdl::Render &render);
            ~Map() = default;

            int getCellSize() const;
            sdl::Vector<int> getSize() const;
            sdl::Vector<double> getPlayerStart() const;
            std::shared_ptr<sdl::Texture> getFloorTexture() const;
            std::shared_ptr<sdl::Texture> getCeilingTexture() const;
            const std::vector<EntitySpawn> &getEntitySpawns() const;

            std::optional<CellData> getCellAt(sdl::Vector<double> pixelCoords) const;
            bool isSolidCellAt(sdl::Vector<double> pixelCoords) const;

        private:
            std::unordered_map<char, CellData> _cellDatas;
            int _cellSize;
            sdl::Vector<int> _size;
            sdl::Vector<double> _playerStart;
            std::vector<CellData> _map;
            std::vector<EntitySpawn> _entitySpawns;

            std::shared_ptr<sdl::Texture> _floorTexture;
            std::shared_ptr<sdl::Texture> _ceilingTexture;

            void _buildMap(const char *fileName);
    };
}; // namespace Raycaster

/* ----- RAYCASTER_MAP_HPP_ ----- */
#endif
