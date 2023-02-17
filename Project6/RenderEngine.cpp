
    #include "RenderEngine.h"
    void RenderEngine::AddToRenderQueue(RenderObject object) {
	    renderQueue.push_back(object);
    }
    void RenderEngine::AddListToRenderQueue(std::vector<RenderObject> objects) {
	    renderQueue.insert(std::end(renderQueue), std::begin(objects), std::end(objects));;
    }
    std::vector<RenderObject> RenderEngine::ConvertMeshToRenderObjects(Mesh mesh, float windowWidth, float windowHeight) {
        std::vector<RenderObject> arr;
        for (int i = 0; i < size(mesh.triangles); i += 3)
        {
            float aspectRatio = windowWidth / windowHeight;
            float n = 0.1;
            float f = 100.0;
            float l = -aspectRatio;
            float r = aspectRatio;
            float b = -1.0;
            float t = 1.0;
            RenderObject ro;
            for (int c = 0; c < 3; c++)
            {
                ro.coordinates.push_back(Vector2(mesh.vertices[mesh.triangles[i + c]].x, mesh.vertices[mesh.triangles[i + c]].y));
            }
            arr.push_back(ro);
        }
        return arr;
    }