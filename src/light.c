#include <math.h>
#include <printf.h>

#include "../include/vector.h"
#include "../include/light.h"

static bool	is_reachable_(t_light *me, t_vector incident_dir);
static bool	spotlight_is_reachable(t_light *me, t_vector incident_dir);

void	light_ctor(t_light *me, t_vector pos, t_color intensity)
{
	static t_light_vtbl	vtbl = {
			.is_reachable = is_reachable_,
	};

	me->vptr = &vtbl;
	me->pos = pos;
	me->intensity = intensity;
}

bool	is_reachable_(t_light *me, t_vector incident_dir)
{
	(void)me;
	(void)incident_dir;
	return (true);
}

void	spotlight_ctor(t_spotlight *me, t_vector pos, t_color intensity, t_vector direction, double fov)
{
	static t_light_vtbl	vtbl = {
			.is_reachable = spotlight_is_reachable,
	};

	light_ctor(&me->super, pos, intensity);
	me->super.vptr = &vtbl;
	me->direction = direction;
	me->fov = fov;
}

bool	spotlight_is_reachable(t_light *me_, t_vector incident_dir)
{
	const t_spotlight	*me = (t_spotlight*)me_;
	const t_vector		rev_norm_incident_dir = vec_mult(vec_normalize(incident_dir), -1);
	const double		angle = acos(vec_dot(rev_norm_incident_dir, me->direction)) / M_PI * 180;

	return (angle < me->fov / 2);
}

bool	light_is_reachable(t_light *me, t_vector incident_dir)
{
	return (me->vptr->is_reachable(me, incident_dir));
}
