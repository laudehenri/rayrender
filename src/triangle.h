#ifndef TRIANGLEH
#define TRIANGLEH

#include "hitable.h"
#include "material.h"
#include "onbh.h"

class triangle : public hitable {
public:
  triangle() {}
  ~triangle() {
    if(single) {
      if(mp) delete mp;
      if(alpha_mask) delete alpha_mask;
      if(bump_tex) delete bump_tex;
    }
  }
  triangle(vec3 _a, vec3 _b, vec3 _c, bool _single, material *mat, 
           alpha_texture *alpha_mask, bump_texture* bump_tex) :
  a(_a), b(_b), c(_c), single(_single), mp(mat), alpha_mask(alpha_mask), bump_tex(bump_tex) {
    edge1 = b-a;
    edge2 = c-a;
    normal = cross(edge1, edge2);
    area = normal.length()/2;
    normal.make_unit_vector();
    normals_provided = false;
  };
  triangle(vec3 _a, vec3 _b, vec3 _c, vec3 _na, vec3 _nb, vec3 _nc, bool _single, 
           material *mat, alpha_texture *alpha_mask, bump_texture* bump_tex) :
    a(_a), b(_b), c(_c), na(_na), nb(_nb), nc(_nc), single(_single), mp(mat), 
    alpha_mask(alpha_mask), bump_tex(bump_tex) {
    edge1 = b-a;
    edge2 = c-a;
    normal = cross(edge1, edge2);
    area = normal.length()/2;
    normals_provided = true;
  };
  virtual bool hit(const ray& r, Float t_min, Float t_max, hit_record& rec, random_gen& rng);
  virtual bool bounding_box(Float t0, Float t1, aabb& box) const;
  virtual Float pdf_value(const vec3& o, const vec3& v, random_gen& rng);
  virtual vec3 random(const vec3& origin, random_gen& rng);
  virtual vec3 random(const vec3& origin, Sampler* sampler);
  
  vec3 normal;
  vec3 a, b, c, na, nb, nc;
  vec3 edge1, edge2;
  Float area;
  bool normals_provided;
  bool single;
  material *mp;
  alpha_texture *alpha_mask;
  bump_texture *bump_tex;
};

#endif
