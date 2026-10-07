#include "tilemap.h"

Tilemap::Tilemap()
{
    m_codeMap = {
    "###################",
    "#0 ..... #       0#",
    "# ## ### # ### ## #",
    "# ## ### # ### ## #",
    "#                 #",
    "# ## # ##### # ## #",
    "#    #   #   #    #",
    "#### ### # ### ####",
    "#### #       # ####",
    "       #####       ",
    "#### #       # ####",
    "#### # ##### # ####",
    "#        #        #",
    "# ## ### # ### ## #",
    "#  #           #  #",
    "## # # ##### # # ##",
    "#    #   #   #    #",
    "# ###### # ###### #",
    "#                 #",
    "###################"
    };


}

sf::VertexArray Tilemap::LoadMap()
{
    sf::VertexArray map(sf::PrimitiveType::Triangles);
    map.resize(20 * 20 * 6);
    int size = 40;
    

    for (int i = 0; i < 20 ; ++i)
    {
        for (int j = 0; j < 20; ++j) {

            sf::Vertex* triangles = &map[(i + j*20) * 6];

            triangles[0].position = sf::Vector2f(i * size, j * size);
            triangles[1].position = sf::Vector2f((i + 1) * size, j * size);
            triangles[2].position = sf::Vector2f(i * size, (j + 1) * size);
            triangles[3].position = sf::Vector2f(i * size, (j + 1) * size);
            triangles[4].position = sf::Vector2f((i + 1) * size, j * size);
            triangles[5].position = sf::Vector2f((i + 1) * size, (j + 1) * size);


                if (m_codeMap[j][i]=='#')
                {
                    for (int x = 0; x < 6; x++)
                    {
                        triangles[x].color = sf::Color::Blue;
                    }
                }
                else
                {
                    for (int x = 0; x < 6; x++)
                    {
                        triangles[x].color = sf::Color::Black;
                    }
                }
        }
    }

    return map;
}


bool Tilemap::IsAWall(const sf::Vector2i& pos)
{
    if (m_codeMap[pos.y][pos.x]=='#')
    {
        return true;
    }
    return false;
}

bool Tilemap::IsACoin(const sf::Vector2i& pos)
{
    if (m_codeMap[pos.y][pos.x] == '.')
    {
        return true;
    }
    return false;
}

bool Tilemap::IsAPacGum(const sf::Vector2i& pos)
{
    if (m_codeMap[pos.y][pos.x] == '0')
    {
        return true;
    }
    return false;
}

std::array<std::string, 20>& Tilemap::GetCodeMap()
{
    return m_codeMap;
}
