#ifndef BATCH_HPP
#define BATCH_HPP

#include <pocket/math/mat.hpp>
#include <pocket/graphics/texture.hpp>
#include <pocket/containers/vector.hpp>
#include <pocket/math/rect.hpp>

namespace gfx {
    struct vertex {
        vec3f pos;
        vec2f texc;

        vertex() = default;
        vertex(f32 x, f32 y)
                : pos(x, y, 0.f) {}
        vertex(vec2f p)
                : pos(p, 0.f) {}
        vertex(vec2f p, f32 z_pos)
                : pos(p, z_pos) {}
        vertex(vec2f p, f32 tx, f32 ty)
                : pos(p, 0.f), texc(tx, ty) {}
        vertex(vec2f p, f32 z_pos, f32 tx, f32 ty)
                : pos(p, z_pos), texc(tx, ty) {}
        vertex(vec2f p, vec2f t)
                : pos(p, 0.f), texc(t) {}
        vertex(vec2f p, f32 z_pos, vec2f t)
                : pos(p, z_pos), texc(t) {}
    };

    struct draw_batch {
        u32 elements = 0;
        u32 tex_id = 0;
        f32 z_pos = 0.f;
        mem::vector<vertex> vertices;
        mem::vector<u32> indices;

        draw_batch() = default;
        draw_batch(const draw_batch& other);
        void quad(const rectf &frame, const rectf &tex_coordinate = rectf(), const mat3x2 &m = mat3x2::identity());
        void quad(const rectf &frame, f32 z_pos, const rectf &tex_coordinate = rectf(), const mat3x2 &m = mat3x2::identity());

        void deep_copy(const draw_batch &other);
//        draw_batch &operator=(const draw_batch &other);
//        void shallow_copy(const draw_batch &other);
    };

    struct batcher {
        mem::vector<mat3x2> matrices;
        mem::vector<draw_batch> batches;
        mat3x2 curmat;
        draw_batch *curbatch = nullptr;

        batcher();

        void push_matrix(const mat3x2 &m);
        void pop_matrix();

        void set_texture(const texture_t &t);
        void set_z_position(const f32 z_pos) const;

        void rect(const rectf &position, const rectf &tex_coordinate = rectf()) const;
        void rect(const rectf &position, const f32 z_pos, const rectf &tex_coordinate = rectf()) const;

        void render();

        void clear();
    };

//    namespace batcher {
//        void push_matrix(const mat3x2 &m);
//        void pop_matrix();
//
//        void set_texture(const texture_t &t);
//
//        void rect(const rectf &position, const rectf &tex_coordinate = rectf());
//
////        void push_batch(const draw_batch &batch);
////        void push_batch(const u32 elem, const u32 tex, const mem::vector<vertex> *vert, const mem::vector<u32> *ind);
//
//        void render();
//
//        void clear();
//    } // namespace batcher

} // namespace gfx


#endif
