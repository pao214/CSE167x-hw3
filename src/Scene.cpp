#include <Scene.h>

void Scene::draw()
{
    Sampler sampler;
    Film film;
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            Vec3 sample = sampler.sample(i, j);
            film.record(i, j, Vec3(0., 0., 0.));
        }
    }
}
