#include "RenderEngine.h"
void RenderEngine::AddToRenderQueue(RenderObject object) {
	renderQueue.push_back(object);
}
void RenderEngine::AddListToRenderQueue(std::vector<RenderObject> objects) {
	renderQueue.insert(std::end(renderQueue), std::begin(objects), std::end(objects));;
}
std::vector<RenderObject> RenderEngine::ConvertMeshToRenderObjects(Mesh mesh) {
	RenderObject ro;
	int index = 0;
	for(int i = 0; i < size(mesh.triangles); i += 3)
	{
		for(int c = 0; c < 3; c++)
		{
			int screenx = floor((100 * mesh.vertices[i + c].x) / (100 + mesh.vertices[i + c].z));
			int screeny = floor((100 * mesh.vertices[i + c].y) / (100 + mesh.vertices[i + c].z));
			ro.coordinates[index % 3] = Vector2(screenx,screeny);
			index++;
		}
	}
	return {};
}
