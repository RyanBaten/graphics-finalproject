#include <stdio.h>
#include <string.h>

#include "object.h"
#include "load_image.h"

Object::Object() {}

// Used openGL tutorial at http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/ as reference for object loading
bool Object::loadFile(const char* file) {
  int v1, v2, v3;
  int uv1, uv2, uv3;
  int n1, n2, n3;
  float x, y, z;
  FILE* infile = fopen(file, "r"); 
  char buff[128];
  std::vector<double> vertices;
  std::vector<double> texture_uvs;
  std::vector<double> normals;

  if (!infile) {
    fprintf(stderr, "Failed to open object file %s\n", file);
    return false;
  }

  while (fscanf(infile, "%s", buff)!=EOF) {
    // Vertex coords
    if (!strcmp(buff, "v")) {
      if (fscanf(infile, "%f %f %f\n", &x, &y, &z) != 3) {
        fprintf(stderr, "Failed to parse file %s\n", file);
        return false;
      }
      vertices.push_back(x);
      vertices.push_back(y);
      vertices.push_back(z);
    // UV coords
    } else if (!strcmp(buff, "vt")) {
      if (fscanf(infile, "%f %f\n", &x, &y) != 2) {
        fprintf(stderr, "Failed to parse file %s\n", file);
        return false;
      }
      texture_uvs.push_back(x);
      texture_uvs.push_back(y);
    // Vertex normal coords
    } else if (!strcmp(buff, "vn")) {
      if (fscanf(infile, "%f %f %f\n", &x, &y, &z) != 3) {
        fprintf(stderr, "Failed to parse file %s\n", file);
        return false;
      }
      normals.push_back(x);
      normals.push_back(y);
      normals.push_back(z);
    // Specification of which 
    } else if (!strcmp(buff, "f")) {
      int matches = fscanf(infile, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &v1,&uv1,&n1, &v2,&uv2,&n2, &v3,&uv3,&n3);
      if (matches != 9) {
        fprintf(stderr, "Failed to parse file %s\n", file);
        return false;
      }
      // Adding the vertex coordinates
      vertexCoords.push_back(vertices.at(3*v1-3));
      vertexCoords.push_back(vertices.at(3*v1-2));
      vertexCoords.push_back(vertices.at(3*v1-1));

      vertexCoords.push_back(vertices.at(3*v2-3));
      vertexCoords.push_back(vertices.at(3*v2-2));
      vertexCoords.push_back(vertices.at(3*v2-1));

      vertexCoords.push_back(vertices.at(3*v3-3));
      vertexCoords.push_back(vertices.at(3*v3-2));
      vertexCoords.push_back(vertices.at(3*v3-1));
      // Adding the texture coordinates
      texCoords.push_back(texture_uvs.at(2*uv1-2));
      texCoords.push_back(1-texture_uvs.at(2*uv1-1));

      texCoords.push_back(texture_uvs.at(2*uv2-2));
      texCoords.push_back(1-texture_uvs.at(2*uv2-1));

      texCoords.push_back(texture_uvs.at(2*uv3-2));
      texCoords.push_back(1-texture_uvs.at(2*uv3-1));
      // Adding the normal coordinates
      normalCoords.push_back(normals.at(3*n1-3));
      normalCoords.push_back(normals.at(3*n1-2));
      normalCoords.push_back(normals.at(3*n1-1));

      normalCoords.push_back(normals.at(3*n2-3));
      normalCoords.push_back(normals.at(3*n2-2));
      normalCoords.push_back(normals.at(3*n2-1));

      normalCoords.push_back(normals.at(3*n3-3));
      normalCoords.push_back(normals.at(3*n3-2));
      normalCoords.push_back(normals.at(3*n3-1));
    }
  }
  fclose(infile);
  return true;
}

void Object::loadTexture(const char* file) {
  texture = loadImage(file);
}

void Object::draw(double x, double y, double z, double rx, double ry, double rz, double scale) {
  int iterations = vertexCoords.size()/3;

  glPushMatrix();
  // Translation and scaling
  glTranslated(x,y,z);
  glRotated(rx,1,0,0);
  glRotated(ry,0,1,0);
  glRotated(rz,0,0,1);
  glScaled(scale,scale,scale);

  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glBindTexture(GL_TEXTURE_2D, texture);

  glBegin(GL_TRIANGLES);
  for (int i=0; i<iterations; i++) {
    // Read the coordinates in order
    glNormal3f(normalCoords.at(3*i), normalCoords.at(3*i+1), normalCoords.at(3*i+2));
    glTexCoord2f(texCoords.at(2*i), texCoords.at(2*i+1));
    glVertex3f(vertexCoords.at(3*i), vertexCoords.at(3*i+1), vertexCoords.at(3*i+2));
  }
  glEnd();

  glDisable(GL_TEXTURE_2D);
  glPopMatrix();
}
