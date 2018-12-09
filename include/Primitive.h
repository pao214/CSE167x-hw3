#pragma once

#include "General.h"
#include "Ray.h"
#include "LocalGeo.h"
#include "Material.h"

/**
 * FIXME: Combine emission and ambient.
 * FIXME: Derive using `virtual` keyword.
 * FIXME: Is a protected routine necessary, can we override private routines?
 */
struct Primitive
{
private:
    // Members
    glm::vec3 ambient;
    Material material;
    glm::mat4 objToWorld, worldToObj;
    glm::mat4 norObjToWorld, norWorldToObj;

protected:
    // Primitive specific logic.
    virtual bool intersectV(const Ray& ray, float* tHitP, LocalGeo* localGeoP) const = 0;

public:
    // Constructor
    Primitive(const Material& material, const glm::mat4& objToWorld):
        material(material), objToWorld(objToWorld), worldToObj(glm::inverse(objToWorld)),
        norObjToWorld(glm::transpose(worldToObj)), norWorldToObj(glm::transpose(objToWorld)) {}

    // Base class requires a virtual destructor.
    virtual ~Primitive() {}

    // Setters and getters
    void getMaterial(Material* materialP)
    {
        new(materialP) Material{material};
    }

    // Operations
    bool intersect(const Ray& ray, float* tHitP, LocalGeo* localGeoP) const
    {
        // Intersect using the transformed ray.
        const float scale = glm::length(worldToObj*glm::vec4(ray.getDir(), 1.0f));
        const Ray objRay{
            glm::vec3(worldToObj*glm::vec4(ray.getPoint(), 1.0f)),
            glm::vec3(glm::normalize(worldToObj*glm::vec4(ray.getDir(), 1.0f))),
            scale*ray.getMin(),
            scale*ray.getMax()
        };

        // Intersect using the primitive specific logic.
        if (!intersectV(objRay, tHitP, localGeoP))
        {
            return false;
        }

        // Return the intersection point and normal.
        new(localGeoP) LocalGeo(
            glm::vec3(objToWorld*glm::vec4(localGeoP->getPoint(), 1.0f)),
            glm::vec3(glm::vec3(norObjToWorld*glm::vec4(localGeoP->getNormal(), 1.0f)))
        );
        return true;
    }
};