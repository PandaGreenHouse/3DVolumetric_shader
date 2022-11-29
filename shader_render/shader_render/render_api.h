#pragma once
#include <Eigen/Core>
#include <vector>
#ifdef RECON_EXPORTS
#define RENDER_API __declspec(dllexport) 
#else
#define RENDER_API __declspec(dllimport) 
#endif
RENDER_API int initOpenGL();
RENDER_API void render(float *pVertices, float *pNormals, int vetex_count);
RENDER_API void render(std::vector<Eigen::Vector3f> &vertices, std::vector<Eigen::Vector3f> &normals);

