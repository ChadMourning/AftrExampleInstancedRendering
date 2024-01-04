#include "MGLInstanced.h"
#include "Camera.h"
using namespace Aftr;

MGLInstanced* MGLInstanced::New(WO* parent, const std::string& model)
{
   MGLInstanced* ptr = new MGLInstanced(parent);
   ptr->onCreate(model);
   return ptr;
}

MGLInstanced::~MGLInstanced()
{

}

MGLInstanced::MGLInstanced(WO* parent) : Model(parent)
{

}

void MGLInstanced::render(const Camera& cam)
{
   Mat4 modelMatrix = this->getModelMatrix(); ///< Returns the full 4x4 model matrix used by a shader, including orientation, position, scale.
   Mat4 normalMatrix = cam.getCameraViewMatrix() * this->dispMatrix; //for transforming normals in the shader

   std::tuple< const Mat4&, const Mat4&, const Camera& > shaderParams(modelMatrix, normalMatrix, cam);
   this->getSkin().bind(&shaderParams);

   auto r = this->modelData->getModelMeshes().at(0)->getMeshDataShared()->getModelMeshRenderData(MESH_SHADING_TYPE::mstFLAT, GL_TRIANGLES);

   glBindVertexArray(r->getVAOHandle());
   //glDrawRangeElements(GL_TRIANGLES, 0, r->getVtxSize(), r->getIdxSize(), r->getIdxMemType(), nullptr); // VBO
   glDrawElementsInstanced(GL_TRIANGLES, r->getIdxSize(), r->getIdxMemType(), nullptr, 1000);
   glBindVertexArray(0);
}

void MGLInstanced::onCreate(const std::string& model)
{
   Model::onCreate(model, Vector(1, 1, 1), MESH_SHADING_TYPE::mstFLAT);
}