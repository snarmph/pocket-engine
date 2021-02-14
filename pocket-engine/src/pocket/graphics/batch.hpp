#ifndef BATCH_HPP
#define BATCH_HPP

#include <sokol/sokol.h>

#include <pocket/math/mat.hpp>
#include <pocket/graphics/texture.hpp>
#include <pocket/containers/containers.hpp>
#include <pocket/math/rect.hpp>

struct sok_vertex {
    vec2f pos;
    vec2f texc;
    vec3f col;
};

struct command {
    sg_image img{};
    u32 base_index{};
    u32 num_indices{};
};

struct batch {
    vector<sok_vertex> vertices;
    vector<u32> indices;
    vector<command> cmds;
};

struct help {
    sg_buffer vbuf{};
    sg_buffer ibuf{};
    sg_shader shd{};
    sg_bindings bind{};
    sg_pipeline pip{};
    sg_pass_action pass{};

    sg_image def_img{};

    mat4 uniform_mat;

    vector<mat4> matstack;

    vector<batch> batches;
};

namespace gfx {
    struct batcher;

    enum layers : u8 {
        background,
        objects,
        foreground,
        number_of_layers
    };

    struct vertex {
        vec2f pos;
        vec2f texc{};
        vec3f col{};

        vertex() = default;
        vertex(f32 x, f32 y)
                : pos(x, y) {}
        vertex(f32 x, f32 y, f32 tx, f32 ty)
                : pos(x, y), texc(tx, ty) {}
        vertex(f32 x, f32 y, f32 tx, f32 ty, f32 r, f32 g, f32 b)
                : pos(x, y), texc(tx, ty), col(r, g, b) {}
        vertex(const vec2f &p)
                : pos(p) {}
        vertex(const vec2f &p, f32 tx, f32 ty)
                : pos(p), texc(tx, ty) {}
        vertex(const vec2f &p, const vec2f &t, f32 r, f32 g, f32 b)
                : pos(p), texc(t), col(r, g, b) {}
        vertex(const vec2f &p, const vec2f &t, const vec3f &c)
                : pos(p), texc(t), col(c) {}
    };

    struct batch_info {
        //u32 offset = 0;
        //u32 tex_id = 0;
        //u32 elements = 0;
        //mat3x2 mat = mat3x2::identity();
        
        sg_image img{};
        u32 base_index{};
        u32 num_indices{};

        batch_info() = default;
        batch_info(u32 base, sg_image _img)
            : base_index(base), img(_img) {}
    };

    struct draw_batch {
        sg_buffer vbuf{};
        sg_buffer ibuf{};
        vector<vertex> vertices;
        vector<u32> indices;
        vector<batch_info> info;

        draw_batch() = default;
        draw_batch(const draw_batch& other) = delete;
        void reset();

        void quad(const rectf &frame, const rectf &tex_coordinate = rectf(), const mat3x2 &m = mat3x2::identity());
        void quad_vector(const vector<rectf> &frames, const vector<rectf> &tex_coords, const mat3x2 &m);

        void render(batcher &b);
    };

    struct batcher {
        vector<mat3x2> matrices;
        array<draw_batch, layers::number_of_layers> batch_layers;
        mat3x2 curmat = mat3x2::identity();
        layers curlayer = layers::background;

        sg_shader shader{};
        sg_bindings bind{};
        sg_pipeline pip{};
        sg_pass_action pass{};

        sg_image default_img{};
        mat4 uniform_mat;

        //help state;

        batcher() = default;

        void init();

        void push_matrix(const mat3x2 &m);
        inline void pop_matrix() {
            curmat = matrices.back();
            matrices.pop();
        }

        void set_texture(const texture_t &t);
        inline void set_layer(const layers layer) {
            curlayer = layer;
        }

        inline void rect(const rectf &frame, const rectf &tex_coordinate = rectf()) {
            current_info().base_index = (u32)current_batch().indices.size();
            current_batch().quad(frame, tex_coordinate, curmat);
            current_info().num_indices += 6;
        }

        inline void rect_vec(const vector<rectf> &frames, const vector<rectf> &texcoords) {
            current_info().base_index = (u32)current_batch().indices.size();
            current_batch().quad_vector(frames, texcoords, curmat);
            current_info().num_indices += (u32)current_batch().indices.size() - current_info().base_index;
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