bool RayVsRect( vec2d& ray_origin, vec2d& ray_dir, Rectangle *target,vec2d& contact_point, vec2d& contact_normal, float& t_hit_near)
{
    contact_normal = { 0,0 };
    contact_point = { 0,0 };

    // Cache division
    vec2d invdir = {1.0f / ray_dir.x,  1.0f / ray_dir.y };

    // Calculate intersections with rectangle bounding axes
    vec2d t_near;
    t_near.x = (target->src.x - ray_origin.x) * invdir.x;
    t_near.y = (target->src.y - ray_origin.y) * invdir.y;

    vec2d t_far;
    t_far.x = (target->src.x + target->src.w - ray_origin.x) * invdir.x;
    t_far.y = (target->src.y + target->src.h - ray_origin.y) * invdir.y;

    if (std::isnan(t_far.y) || std::isnan(t_far.x)) return false;
    if (std::isnan(t_near.y) || std::isnan(t_near.x)) return false;

    // Sort distances
    if (t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
    if (t_near.y > t_far.y) std::swap(t_near.y, t_far.y);

    // Early rejection
    if (t_near.x > t_far.y || t_near.y > t_far.x) return false;

    // Closest 'time' will be the first contact
    t_hit_near = std::max(t_near.x, t_near.y);

    // Furthest 'time' is contact on opposite side of target
    float t_hit_far = std::min(t_far.x, t_far.y);

    // Reject if ray direction is pointing away from object
    if (t_hit_far < 0)
        return false;

    // Contact point of collision from parametric line equation
    contact_point.x = ray_origin.x + t_hit_near * ray_dir.x;
    contact_point.y = ray_origin.y + t_hit_near * ray_dir.y;

    if (t_near.x > t_near.y)
        if (invdir.x < 0)
            contact_normal = { 1, 0 };
        else
            contact_normal = { -1, 0 };
    else if (t_near.x < t_near.y)
        if (invdir.y < 0)
            contact_normal = { 0, 1 };
        else
            contact_normal = { 0, -1 };

    return true;
}

bool DynamicRectVsRect(Rectangle* r_dynamic,  Rectangle* r_static, vec2d& contact_point, vec2d& contact_normal, float& contact_time)
{
    // Check if dynamic rectangle is actually moving - we assume rectangles are NOT in collision to start
    if (r_dynamic->vel.x == 0.0f && r_dynamic->vel.y == 0.0f)
        return false;

    // Expand target rectangle by source dimensions
    Rectangle expanded_target;
    expanded_target.src.x = r_static->src.x - r_dynamic->src.w / 2;
    expanded_target.src.y = r_static->src.y - r_dynamic->src.h / 2;
    expanded_target.src.w = r_static->src.w + r_dynamic->src.w;
    expanded_target.src.h = r_static->src.h + r_dynamic->src.h;

    vec2d rayDir;
    rayDir.x = r_dynamic->src.x + r_dynamic->src.w / 2;
    rayDir.y = r_dynamic->src.y + r_dynamic->src.h / 2;

    if (RayVsRect(rayDir, r_dynamic->vel, &expanded_target, contact_point, contact_normal, contact_time))
        return (contact_time >= 0.0f && contact_time < 1.0f);
    else
        return false;
}

void ResolveDynamicRectVsRect(Rectangle *Rect)
{
    vec2d contact_point, contact_normal;
    float contact_time = 0.0f;
    std::vector<std::pair< float, Rectangle *>> z;

    int x = Rect->src.x / CELL_W;
    int y = Rect->src.y / CELL_H;

    for(int i = -5; i < 5; i++)
    {
        for(int j = -5; j < 5; j++ )
        {
            int px = x - j;
            int py = y - i;

            if(px >= 0 && py >= 0 && py < plateform.size() && px < plateform[0].length())
            {
                if(plateform[py][px] == '#' || plateform[py][px] == '*' || plateform[py][px] == 'g')
                {
                    if (DynamicRectVsRect( Rect, Rects[py][px], contact_point, contact_normal, contact_time))
                    {
                        if(Rect->id == player->id && contact_normal.y != 1 )
                        {
                            player_jump = 2;
                        }
                        z.push_back({contact_time, Rects[py][px] });
                    }
                }
            }
        }
    }

    resoleForEnemeyHelper(z, Rect);
    resoleForBoxHelper(z, Rect);

    std::sort(z.begin(), z.end(), [](const std::pair< float, Rectangle* >& a, const std::pair< float, Rectangle *>& b)
    {
        return a.first < b.first;
    });

    for(unsigned int i = 0; i < z.size(); i++)
    {
        if (DynamicRectVsRect( Rect, z[i].second, contact_point, contact_normal, contact_time))
        {
            Rect->vel.x += contact_normal.x * std::abs(Rect->vel.x) * (1 - contact_time);
            Rect->vel.y += contact_normal.y * std::abs(Rect->vel.y) * (1 - contact_time);
        }
    }

}

