#include "../src/tree.h"

#define UNUSED(x) (void)(x)

struct planet {
    double mass;
};

void noop (void * v) {
    UNUSED(v);
}

int main ()
{
    // Store planetary masses in 10^24 kg
    struct tree * planent_masses = construct_tree(&noop);

    struct planet mercury;
    struct planet venus;
    struct planet earth;
    struct planet mars;

    double mass;

    mercury.mass = 0.330;
    venus.mass = 4.87;
    earth.mass = 5.97;
    mars.mass = 0.642;

    t_set("Mercury", &mercury, planent_masses);
    t_set("Venus", &venus, planent_masses);
    t_set("Earth", &earth, planent_masses);
    t_set("Mars", &mars, planent_masses);

    mass = ((struct planet *)t_get("Earth", planent_masses))->mass;

    printf("The mass of earth is %f * 10^24 kg\n", mass);

    delete_tree(planent_masses);

    return 0;
}
