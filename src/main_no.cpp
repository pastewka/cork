// +-------------------------------------------------------------------------
// | main.cpp
// |
// | Author: Gilbert Bernstein
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

// This file contains a command line program that can be used
// to exercise Cork's functionality without having to write
// any code.

#include "files.h"

#include <iostream>
using std::cerr;
using std::cout;
using std::endl;
#include <sstream>
using std::string;
using std::stringstream;

using std::ostream;

#include "cork.h"

void file2corktrimesh(const Files::FileMesh &in, CorkTriMesh *out) {
  out->n_vertices = in.vertices.size();
  out->n_triangles = in.triangles.size();

  out->triangles = new uint[(out->n_triangles) * 3];
  out->vertices = new float[(out->n_vertices) * 3];

  for (uint i = 0; i < out->n_triangles; i++) {
    (out->triangles)[3 * i + 0] = in.triangles[i].a;
    (out->triangles)[3 * i + 1] = in.triangles[i].b;
    (out->triangles)[3 * i + 2] = in.triangles[i].c;
  }

  for (uint i = 0; i < out->n_vertices; i++) {
    (out->vertices)[3 * i + 0] = in.vertices[i].pos.x;
    (out->vertices)[3 * i + 1] = in.vertices[i].pos.y;
    (out->vertices)[3 * i + 2] = in.vertices[i].pos.z;
  }
}

void corktrimesh2file(CorkTriMesh in, Files::FileMesh &out) {
  out.vertices.resize(in.n_vertices);
  out.triangles.resize(in.n_triangles);

  for (uint i = 0; i < in.n_triangles; i++) {
    out.triangles[i].a = in.triangles[3 * i + 0];
    out.triangles[i].b = in.triangles[3 * i + 1];
    out.triangles[i].c = in.triangles[3 * i + 2];
  }

  for (uint i = 0; i < in.n_vertices; i++) {
    out.vertices[i].pos.x = in.vertices[3 * i + 0];
    out.vertices[i].pos.y = in.vertices[3 * i + 1];
    out.vertices[i].pos.z = in.vertices[3 * i + 2];
  }
}

void loadMesh(string filename, CorkTriMesh *out) {
  Files::FileMesh filemesh;

  if (Files::readTriMesh(filename, &filemesh) > 0) {
    cerr << "Unable to load in " << filename << endl;
    exit(1);
  }

  file2corktrimesh(filemesh, out);
}
void saveMesh(string filename, CorkTriMesh in) {
  Files::FileMesh filemesh;

  corktrimesh2file(in, filemesh);

  if (Files::writeTriMesh(filename, &filemesh) > 0) {
    cerr << "Unable to write to " << filename << endl;
    exit(1);
  }
}

int main(int argc, char *argv[]) {
  CorkTriMesh pixel;
  CorkTriMesh precipitate140;
  CorkTriMesh intersection140;

  loadMesh("toolbox_graph/precipitate140.off", &precipitate140);
  loadMesh("toolbox_graph/pixel.off", &pixel);

  computeIntersection(precipitate140, pixel, &intersection140);

  saveMesh("toolbox_graph/intersection140.off", intersection140);

  delete[] pixel.vertices;
  delete[] pixel.triangles;
  delete[] precipitate140.vertices;
  delete[] precipitate140.triangles;
  freeCorkTriMesh(&intersection140);
  return 0;
}
