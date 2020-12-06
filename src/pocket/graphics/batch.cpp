#include "batch.hpp"

#include <glad/glad.h>
#include <pocket/graphics/graphics.hpp>
#include <pocket/types.hpp>


namespace {
    void draw_single_batch(gfx::draw_batch &b);
} // namespace

namespace gfx {
    draw_batch::draw_batch(const draw_batch& other) {
        deep_copy(other);
    }

    void draw_batch::quad(const rectf &frame, const rectf &tex_coordinate, const mat3x2 &m) {
        indices.reserve(6);
        u32 i = vertices.size();
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

        elements++;
    }

    void draw_batch::quad(const rectf &frame, f32 z_pos, const rectf &tex_coordinate, const mat3x2 &m) {
        indices.reserve(6);
        u32 i = vertices.size();
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
        vertices.emplace_back(m.transform_point(x, y), z_pos, tx, ty);
        vertices.emplace_back(m.transform_point(w, y), z_pos, tw, ty);
        vertices.emplace_back(m.transform_point(w, h), z_pos, tw, th);
        vertices.emplace_back(m.transform_point(x, h), z_pos, tx, th);

        elements++;
    }

    void draw_batch::deep_copy(const draw_batch &other) {
        elements = other.elements;
        tex_id = other.tex_id;
        vertices.deep_copy(other.vertices);
        indices.deep_copy(other.indices);
    }

    batcher::batcher() {
        batches.emplace_back();
        curbatch = batches.data();
    }

    void batcher::push_matrix(const mat3x2 &m) {
        matrices.emplace_back(curmat);
        curmat = m * curmat;
    }

    void batcher::pop_matrix() {
        curmat = matrices.pop();
    }

    void batcher::set_texture(const texture_t &t) {
//        for(auto &b: batches) {
//            if(b.tex_id == t.id) {
//                curbatch = &b;
//                return;
//            }
//        }
        if(curbatch->tex_id == t.id)
            return;

        batches.emplace_back();
        curbatch = batches.end()-1;
        curbatch->tex_id = t.id;
    }

    void batcher::set_z_position(const f32 z_pos) const {
        curbatch->z_pos = z_pos;
    }

    void batcher::rect(const rectf &position, const rectf &tex_coordinate) const {
        curbatch->quad(position, tex_coordinate, curmat);
    }

    void batcher::rect(const rectf &position, const f32 z_pos, const rectf &tex_coordinate) const {
        curbatch->quad(position, z_pos, tex_coordinate, curmat);
    }



    void batcher::render() {
        for(auto &b: batches)
            draw_single_batch(b);
    }

    void batcher::clear() {
        matrices.clear();
        batches.clear();
        curmat = mat3x2::identity();

        batches.emplace_back();
        curbatch = batches.data();
    }

} // namespace gfx

namespace {
    void draw_single_batch(gfx::draw_batch &b) {
        if(b.elements == 0)
            return;

        u32 vao, vbo, ebo;

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(gfx::vertex) * b.vertices.size(), b.vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(gfx::vertex), (void*)0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(gfx::vertex), (void*)(sizeof(vec3f)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * b.indices.size(), b.indices.data(), GL_STATIC_DRAW);

        glBindTexture(GL_TEXTURE_2D, b.tex_id);
        glDrawElementsInstanced(GL_TRIANGLES, b.indices.size(), GL_UNSIGNED_INT, nullptr, b.elements);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);

        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
    }
} // namespace