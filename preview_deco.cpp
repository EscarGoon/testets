// Decorates a built-in test layout and prints the object string.
// Usage: preview_deco <seed> [style] [theme] [detail]
#include "../src/gen/Decorate.hpp"

#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace inspo;

static void blocks(std::vector<LayoutObj>& v, int bx, int by, int w, int h) {
    for (int j = 0; j < h; j++)
        for (int i = 0; i < w; i++) v.push_back({(bx + i) * 30.0 + 15, (by + j) * 30.0 + 15, 30, 30, 0, ObjKind::Solid});
}

static void spikes(std::vector<LayoutObj>& v, int bx, int by, int n) {
    for (int i = 0; i < n; i++) v.push_back({(bx + i) * 30.0 + 15, by * 30.0 + 15, 30, 30, 0, ObjKind::Hazard});
}

int main(int argc, char** argv) {
    std::vector<LayoutObj> L;
    bool real = argc > 5 && std::atoi(argv[5]) == 1;
    if (real) {
        blocks(L, 0, 0, 40, 3);      // thick floor
        blocks(L, 8, 3, 6, 1);       // thin step
        blocks(L, 14, 3, 4, 4);      // block
        blocks(L, 22, 6, 9, 1);      // thin floating platform
        blocks(L, 34, 3, 2, 7);      // pillar
        blocks(L, 0, 10, 26, 2);     // ceiling
        blocks(L, 4, 8, 3, 2);       // hanging chunk
        blocks(L, 40, 0, 12, 6);     // big mass
        blocks(L, 44, 6, 8, 2);      // tier
        blocks(L, 55, 5, 6, 1);      // thin
        blocks(L, 58, 9, 6, 1);      // thin
        spikes(L, 20, 3, 3);
        spikes(L, 26, 3, 2);
        spikes(L, 47, 8, 2);
        DecoSettings s;
        s.seed = argc > 1 ? (uint32_t)std::strtoul(argv[1], nullptr, 10) : 1;
        s.paletteSeed = s.seed;
        if (argc > 2) s.style = argv[2];
        if (argc > 3) s.theme = argv[3];
        if (argc > 4) s.detail = std::atoi(argv[4]);
        auto r = decorate(L, s);
        std::cout << r.levelString;
        for (auto const& o : L) if (o.kind == ObjKind::Hazard) std::cout << "1,8,2," << o.x << ",3," << o.y << ",25,30;";
        std::cout << "\n";
        std::fprintf(stderr, "style=%s palette=%s objects=%zu triggers=%zu groups=%d..%d\n", r.placed.empty() ? "-" : r.placed[0].c_str(),
                     r.palette.name.c_str(), r.objects, r.triggers, r.firstGroup, r.nextGroup - 1);
        return 0;
    }
    blocks(L, 0, 0, 14, 2);    // floor
    blocks(L, 14, 0, 6, 4);    // step up
    blocks(L, 20, 0, 4, 6);    // tall pillar
    blocks(L, 27, 3, 6, 1);    // floating slab
    blocks(L, 35, 0, 10, 3);   // wide block
    blocks(L, 38, 3, 4, 2);    // tier on top
    blocks(L, 5, 6, 8, 2);     // ceiling chunk
    blocks(L, 47, 4, 3, 3);    // floating cube
    for (int i = 0; i < 3; i++) L.push_back({(16 + i) * 30.0 + 15, 4 * 30.0 + 15, 30, 30, 0, ObjKind::Hazard});

    DecoSettings s;
    s.seed = argc > 1 ? (uint32_t)std::strtoul(argv[1], nullptr, 10) : 1;
    s.paletteSeed = s.seed;
    if (argc > 2) s.style = argv[2];
    if (argc > 3) s.theme = argv[3];
    if (argc > 4) s.detail = std::atoi(argv[4]);
    auto r = decorate(L, s);
    std::cout << r.levelString;
    for (int i = 0; i < 3; i++) std::cout << "1,8,2," << (16 + i) * 30 + 15 << ",3," << 4 * 30 + 15 << ",25,30;";
    std::cout << "\n";
    std::fprintf(stderr, "style=%s palette=%s objects=%zu triggers=%zu groups=%d..%d\n", r.placed.empty() ? "-" : r.placed[0].c_str(),
                 r.palette.name.c_str(), r.objects, r.triggers, r.firstGroup, r.nextGroup - 1);
}
