////////////////////////////////////////////////////////////////////////////////
//
// (C) Andy Thomason 2016
//
// meshutils: Stanford PLY encoder class
// 

#ifndef MESHUTILS_PLY_ENCODER_INCLUDED
#define MESHUTILS_PLY_ENCODER_INCLUDED

namespace meshutils {

class ply_encoder {
public:
  ply_encoder() {
  }

  template <class MeshTraits, class Writer>
  void encode(const basic_mesh<MeshTraits> &mesh, Writer &writer) {
    auto wr = [&writer](const char *stuff) {
      writer.write(stuff, strlen(stuff));
    };

    char tmp[256];
    wr("ply\n");
    wr("format ascii 1.0\n");
    wr("comment Created by https://github.com/andy-thomason/meshutils\n");
    snprintf(tmp, sizeof(tmp), "element vertex %d\n", (int)mesh.numVertices());
    wr(tmp);
    wr("property float x\n");
    wr("property float y\n");
    wr("property float z\n");
    wr("property float nx\n");
    wr("property float ny\n");
    wr("property float nz\n");
    wr("property float u\n");
    wr("property float v\n");
    snprintf(tmp, sizeof(tmp), "element face %d\n", (int)mesh.numIndices()/3);
    wr(tmp);
    wr("property list uchar uint vertex_indices\n");
    wr("end_header\n");

    auto *vertices = mesh.vertices();
    for (size_t i = 0; i != mesh.numVertices(); ++i) {
      glm::vec3 pos = vertices[i].pos();
      glm::vec3 normal = vertices[i].normal();
      glm::vec2 uv = vertices[i].uv();
      snprintf(tmp, sizeof(tmp), "%f %f %f %f %f %f %f %f\n", pos.x, pos.y, pos.z, normal.x, normal.y, normal.z, uv.x, uv.y);
      wr(tmp);
    }

    auto *indices = mesh.indices();
    for (size_t i = 0; i < mesh.numIndices(); i += 3) {
      snprintf(tmp, sizeof(tmp), "3 %d %d %d\n", indices[i], indices[i+1], indices[i+2]);
      wr(tmp);
    }
  }
private:
  
};

}

#endif
