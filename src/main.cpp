// +-------------------------------------------------------------------------
// | main.cpp
// |
// | Author: Ali Falsafi
// +-------------------------------------------------------------------------
// | COPYRIGHT:
// |    Copyright Gilbert Bernstein 2013
// |    See the included COPYRIGHT file for further details.
// |
// |    This file is part of the Cork library.
// |
// |    Cork is free software: you can redistribute it and/or modify
// |    it under the terms of the GNU Lesser General Public License as
// |    published by the Free Software Foundation, either version 3 of
// |    the License, or (at your option) any later version.
// |
// |    Cork is distributed in the hope that it will be useful,
// |    but WITHOUT ANY WARRANTY; without even the implied warranty of
// |    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// |    GNU Lesser General Public License for more details.
// |
// |    You should have received a copy
// |    of the GNU Lesser General Public License
// |    along with Cork.  If not, see <http://www.gnu.org/licenses/>.
// +-------------------------------------------------------------------------

#include "cork.hh"
#include "cork_interface.hh"

int main(int argc, char * argv[]) {
  std::vector< point_t> vertices_precipitate;
   point_t origin_precipitate{-0.50, -0.50, -0.50};
   point_t size_precipitate{2.0, 2.30, 2.00};
  vertices_precipitate =
       cube_vertice_maker(origin_precipitate, size_precipitate);

  vertices_precipitate.push_back({0.05, 0.05, 0.05});
  vertices_precipitate.push_back({0.50, 0.05, 0.05});
  vertices_precipitate.push_back({0.05, 0.50, 0.05});
  vertices_precipitate.push_back({0.05, 0.05, 0.50});
  vertices_precipitate.push_back({0.50, 0.50, 0.50});

  std::vector< point_t> vertices_pixel;
   point_t origin_pixel{0.0, 0.0, 0.0};
   point_t size_pixel{1.0, 1.0, 0.20};
  vertices_pixel =  cube_vertice_maker(origin_pixel, size_pixel);

  auto && vol_norm =  calculate_intersection_volume_normal(
      vertices_precipitate, vertices_pixel);

  auto && vol =  calculate_intersection_volume(vertices_precipitate,
                                                      vertices_pixel);

  std::cout <<"verctor:" << std::endl<< vol_norm.normal_vector << std::endl;
  std::cout <<"vol: " <<vol << std::endl;
  std::cout <<"vol_ratio: " <<vol_norm.volume_ratio << std::endl;
  std::cout << "status:" << static_cast<int>(vol_norm.status) << std::endl;
  // auto && normal average

  return 0;
}
