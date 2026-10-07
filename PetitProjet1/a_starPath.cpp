#include "a_starPath.h"
#include <vector>

int heuristique(sf::Vector2i a, sf::Vector2i b)
{
    return std::abs(a.x-b.x) + std::abs(a.y-b.y);
}

Direction nextDirection(sf::Vector2i start, sf::Vector2i end, std::array<std::string, 20> map)
{
    if (start == end) return Direction::None;

    int hauteur = 20;
    int largeur = 20;

    std::vector<sf::Vector2i> explore;
    explore.push_back(start); 
    std::vector<std::vector<int>> g(hauteur, std::vector<int>(largeur, 400));
    std::vector<std::vector<sf::Vector2i>> parent(hauteur, std::vector<sf::Vector2i>(largeur, sf::Vector2i(-1, -1)));
     
    g[start.y][start.x] = 0;

    while (!explore.empty())
    {
        int meilleur = 0;
        for (int i = 1; i < explore.size(); i++)
        {
            sf::Vector2i p = explore[i];
            sf::Vector2i m = explore[meilleur];
            if ((g[p.y][p.x] + heuristique(p, end))< (g[m.y][m.x] + heuristique(m, end)))
            {
                meilleur = i;
            }
        }

        sf::Vector2i actuel = explore[meilleur];
        explore.erase(explore.begin() + meilleur);
        if (actuel == end)
        {
            sf::Vector2i first_step = end;
            while (!(parent[first_step.y][first_step.x]==start))
            {
                first_step = parent[first_step.y][first_step.x];
            }

            if (first_step.x > start.x) return Direction::East;
            if (first_step.x < start.x) return Direction::West;
            if (first_step.y > start.y) return Direction::south;
            if (first_step.y < start.y) return Direction::North;
        }
        sf::Vector2i Direction[] = { {1,0},{-1,0},{0,1},{0,-1} };
        for (sf::Vector2i dir : Direction)
        {
            sf::Vector2i voisin = { actuel.x + dir.x,actuel.y + dir.y };
            if (voisin.y >=0 && voisin.y<hauteur &&
                voisin.x >= 0 && voisin.x < largeur &&
                map[voisin.y][voisin.x] != '#')
            {
                int newG = g[actuel.y][actuel.x] + 1;
                if (newG < g[voisin.y][voisin.x])
                {
                    g[voisin.y][voisin.x] = newG;
                    parent[voisin.y][voisin.x] = actuel;
                    explore.push_back(voisin);
                }
            }
        }

    }
    return Direction::None;
}
