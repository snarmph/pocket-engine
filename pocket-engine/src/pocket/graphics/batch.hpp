#ifndef BATCH_HPP
#define BATCH_HPP

#include <pocket/math/mat.hpp>
#include <pocket/graphics/texture.hpp>
#include <pocket/containers/containers.hpp>
#include <pocket/math/rect.hpp>

namespace gfx {
    enum layers : u8 {
        background,
        objects,
        foreground,
        number_of_layers
    };

    struct vertex {
        vec2f pos;
        vec2f texc;

        vertex() = default;
        vertex(f32 x, f32 y)
                : pos(x, y) {}
        vertex(f32 x, f32 y, f32 tx, f32 ty)
                : pos(x, y), texc(tx, ty) {}
        vertex(const vec2f &p)
                : pos(p) {}
        vertex(const vec2f &p, f32 tx, f32 ty)
                : pos(p), texc(tx, ty) {}
        vertex(const vec2f &p, const vec2f &t)
                : pos(p), texc(t) {}
    };

    struct batch_info {
        u32 offset = 0;
        u32 tex_id = 0;
        u32 elements = 0;
        mat3x2 mat = mat3x2::identity();

        batch_info() = default;
        batch_info(u32 _off, u32 _id)
            : offset(_off), tex_id(_id) {}
    };

    struct draw_batch {
        u32 vao, vbo, ebo;
        vector<vertex> vertices;
        vector<u32> indices;
        vector<batch_info> info;

        draw_batch();
        ~draw_batch();
        draw_batch(const draw_batch& other) = delete;
        void reset();

        void quad(const rectf &frame, const rectf &tex_coordinate = rectf(), const mat3x2 &m = mat3x2::identity());
        void quad_vector(const vector<rectf> &frames, const vector<rectf> &tex_coords, const mat3x2 &m);

        void render();
    };

    struct batcher {
        vector<mat3x2> matrices;
        array<draw_batch, layers::number_of_layers> batch_layers;
        mat3x2 curmat = mat3x2::identity();
        layers curlayer = layers::background;

        batcher();

        void push_matrix(const mat3x2 &m);
        inline void pop_matrix() {
            curmat = matrices.pop();
        }

        void set_texture(const texture_t &t);
        inline void set_layer(const layers layer) {
            curlayer = layer;
        }

        inline void rect(const rectf &frame, const rectf &tex_coordinate = rectf()) {
            current_batch().quad(frame, tex_coordinate, curmat);
            current_info().elements++;
        }

        inline void rect_vec(const vector<rectf> &frames, const vector<rectf> &texcoords) {
            current_batch().quad_vector(frames, texcoords, curmat);
            current_info().elements += (u32)frames.size();
        }

        void render();

        void clear();

    private:
        inline batch_info &current_info() {
            return batch_layers[curlayer].info.back();
        }
        inline draw_batch &current_batch() {
            return batch_layers[curlayer];
        }
        inline const draw_batch &current_batch() const {
            return batch_layers[curlayer];
        }
    };
} // namespace gfx


#endif
