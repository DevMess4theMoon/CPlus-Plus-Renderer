#include "RenderEngine.h"
void RenderEngine::AddToRenderQueue(RenderObject object) {
	renderQueue.push_back(object);
}
void RenderEngine::AddListToRenderQueue(std::vector<RenderObject> objects) {
	renderQueue.insert(std::end(renderQueue), std::begin(objects), std::end(objects));;
}
std::vector<RenderObject> RenderEngine::ConvertMeshToRenderObjects(Mesh mesh) {
    std::vector<RenderObject> arr;
    for (int i = 0; i < size(mesh.triangles); i += 3)
    {
        RenderObject ro;
        for (int c = 0; c < 3; c++)
        {
            int screenx = floor((100 * mesh.vertices[mesh.triangles[i + c]].x) / (100 + mesh.vertices[mesh.triangles[i + c]].z));
            int screeny = floor((100 * mesh.vertices[mesh.triangles[i + c]].y) / (100 + mesh.vertices[mesh.triangles[i + c]].z));
            ro.coordinates.push_back(Vector2(screenx, screeny));
        }
        arr.push_back(ro);
    }
    return arr;
}


