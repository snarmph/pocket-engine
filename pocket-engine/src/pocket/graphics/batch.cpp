#include "batch.hpp"

#include <glad/glad.h>
#include <pocket/graphics/graphics.hpp>
#include <pocket/core/types.hpp>
#include <pocket/util/pkassert.h>

namespace gfx {
    draw_batch::draw_batch() {
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);
    }

    draw_batch::~draw_batch() {
        printf("deleting a batch\n");
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
    }

    void draw_batch::quad(const rectf &frame, const rectf &tex_coordinate, const mat3x2 &m) {
        indices.reserve(6);
        u32 i = (u32) vertices.size();
        indices.emplace_back(i + 0);
        indices.emplace_back(i + 1);
        indices.emplace_back(i + 2);
        indices.emplace_back(i + 2);
        indices.emplace_back(i + 3);
        indices.emplace_back(i + 0);

        f32 x = frame.x;
        f32 y = frame.y;
        f32 w = x + frame.w;
        f32 h = y + frame.h;

        f32 tx = tex_coordinate.x;
        f32 ty = tex_coordinate.y;
        f32 tw = tx + tex_coordinate.w;
        f32 th = ty + tex_coordinate.h;

        vertices.reserve(4);
        vertices.emplace_back(m.transform_point(x, y), tx, ty);
        vertices.emplace_back(m.transform_point(w, y), tw, ty);
        vertices.emplace_back(m.transform_point(w, h), tw, th);
        vertices.emplace_back(m.transform_point(x, h), tx, th);
    }

    void draw_batch::quad_vector(const mem::vector<rectf> &frames, const mem::vector<rectf> &tex_coords, const mat3x2 &m) {
        pkassert(frames.size() == tex_coords.size(), "frames size and texcoords size should be the same");
        indices.reserve(6 * frames.size());
        vertices.reserve(4 * frames.size());

        for (size_t i = 0; i < frames.size(); i++) {
            u32 j = (u32)vertices.size();
            indices.emplace_back(j + 0);
            indices.emplace_back(j + 1);
            indices.emplace_back(j + 2);
            indices.emplace_back(j + 2);
            indices.emplace_back(j + 3);
            indices.emplace_back(j + 0);

            f32 x = frames[i].x;
            f32 y = frames[i].y;
            f32 w = x + frames[i].w;
            f32 h = y + frames[i].h;

            f32 tx = tex_coords[i].x;
            f32 ty = tex_coords[i].y;
            f32 tw = tx + tex_coords[i].w;
            f32 th = ty + tex_coords[i].h;

            vertices.emplace_back(m.transform_point(x, y), tx, ty);
            vertices.emplace_back(m.transform_point(w, y), tw, ty);
            vertices.emplace_back(m.transform_point(w, h), tw, th);
            vertices.emplace_back(m.transform_point(x, h), tx, th);
        }
    }

    void draw_batch::render() {
        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)(sizeof(vertex::pos)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * indices.size(), indices.data(), GL_STATIC_DRAW);

        for (auto &in : info) {
            glBindTexture(GL_TEXTURE_2D, in.tex_id);
            u32 index_start = in.offset * 6;
            u32 index_count = in.elements * 6;
            glDrawElementsInstanced(
                GL_TRIANGLES, 
                (i32)index_count,
                GL_UNSIGNED_INT, 
                (void *)(sizeof(u32) * index_start),
                1
            );
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        glBindVertexArray(0);
    }

    void draw_batch::reset() {
        vertices.clear();
        indices.clear();
        info.clear();
        info.emplace_back();
    }

    batcher::batcher() {
        for (auto &layer : batch_layers)
            layer.info.emplace_back();
    }

    void batcher::push_matrix(const mat3x2 &m) {
        matrices.emplace_back(curmat);
        curmat = m * curmat;
    }

    void batcher::set_texture(const texture_t &t) {
        u32 &current_tex_id = current_info().tex_id;
        if (current_tex_id == 0) {
            current_tex_id = t.id;
        }
        else if (current_tex_id != t.id) {
            // bit of a mouthful, divided in multiple lines for
            // readability
            current_batch()
                .info
                .emplace_back(
                    current_info().offset + current_info().elements,
                    t.id
                );
        }
    }

    void batcher::render() {
        for (auto &layer : batch_layers)
            layer.render();
    }

    void batcher::clear() {
        matrices.clear();
        for (auto &layer : batch_layers)
            layer.reset();
        curmat = mat3x2::identity();
    }
} // namespace gfx