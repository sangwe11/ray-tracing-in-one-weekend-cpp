#ifndef _HITTABLE_LIST_H
#define _HITTABLE_LIST_H

#include <memory>
#include <vector>

#include "common.h"
#include "hittable.h"

class hittable_list : public hittable
{
public:
	hittable_list() {}
	hittable_list(std::shared_ptr<hittable> object) { add(object); }

	void clear() { m_objects.clear(); }
	void add(std::shared_ptr<hittable> object) { m_objects.push_back(object); }

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

public:
	std::vector<std::shared_ptr<hittable>> m_objects;
};

bool hittable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
	hit_record temp_rec;
	bool hit_anything = false;
	auto closest_so_far = t_max;

	for (const auto& object : m_objects)
	{
		if (object->hit(r, t_min, closest_so_far, temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}

	return hit_anything;
}

#endif