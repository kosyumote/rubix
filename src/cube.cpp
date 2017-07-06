#include "cube.hpp"

Cube::Cube()
{
    std::vector< std::vector<float> > colors = {{0.0, 1.0, 1.0},
						{1.0, 1.0, 1.0},
						{},
						{},
						{},
						{}};
    
    for(int i = 0; i < 54; i++)
    {
	m_stickers.push_back(Sticker());
    }
}
