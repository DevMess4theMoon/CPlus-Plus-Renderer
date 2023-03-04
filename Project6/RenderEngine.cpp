#include "RenderEngine.h"
void RenderEngine::AddToRenderQueue(Mesh object) {
    renderQueue.push_back(object);
}
void RenderEngine::AddListToRenderQueue(std::vector<Mesh> objects) {
    renderQueue.insert(std::end(renderQueue), std::begin(objects), std::end(objects));;
}
std::vector<std::vector<Vector2>> RenderEngine::ConvertMeshToRenderObjects(Mesh mesh, RenderEngine rE, int sW, int sH) {
    std::vector<std::vector<Vector2>> arr;
    for (int i = 0; i < size(mesh.triangles); i += 3)
    {
        std::vector<Vector2> triangle(3);
        for (int c = 0; c < 3; c++)
        {
            Vector3 temp = rE.TransformPoint(mesh.vertices[mesh.triangles[i + (uint32_t)c]]);
            triangle[c] = rE.ProjectPoint(temp, sW, sH);
        }
        arr.push_back(triangle);
    }
    return arr;
}
Vector3 RenderEngine::TransformPoint(Vector3 point) {
    Matrix m = currentTransformationMatrix * ((Matrix)point - (Matrix)cameraPosition);  
    return Vector3(m.m[0][0], m.m[1][0], m.m[2][0]);
}
void RenderEngine::UpdateTransformationMatrix() {
    Matrix m;
    m = Rotation::rotX(cameraAngle.x) * Rotation::rotY(cameraAngle.y) * Rotation::rotZ(cameraAngle.z);
    currentTransformationMatrix = m;
}
Vector2 RenderEngine::ProjectPoint(Vector3 point, int screenWidth, int screenHeight) {

    Matrix m = currentProjectionMatrix * (Matrix)point;

    Vector3 pPoint = Vector3(m.m[0][0], m.m[1][0], m.m[2][0]) / m.m[3][0];

    float x = (pPoint.x + 1.0f) * 0.5f * screenWidth;
    float y = (1.0f - pPoint.y) * 0.5f * screenHeight;

    return Vector2(x,y);
}
void RenderEngine::UpdateProjectionMatrix() {
    double r = nearPlane * tan(fov / 2) * aspectRatio;
    double l = -r;
    double t = nearPlane * tan(fov / 2);
    double b = -t;
    currentProjectionMatrix = Matrix(4,4, {
    { 2 * nearPlane / (r - l), 0                      , (r + l) / (r - l)                              , 0                                                 },
    { 0                      , 2 * nearPlane / (t - b), (t + b) / (t - b)                              , 0                                                 },
    { 0                      , 0                      , (farPlane + nearPlane) / (nearPlane - farPlane), 2 * farPlane * nearPlane / (nearPlane - farPlane) },
    { 0                      , 0                      , -1                                             , 0                                                 }
    });
}