#include "batch.hpp"

#include <pocket/core/types.hpp>
#include <pocket/util/pkassert.h>

constexpr int max_vertices = 60000;
constexpr int max_indices = 30000;

namespace gfx {
    draw_batch::draw_batch() {
        //glGenVertexArrays(1, &vao);
        //glGenBuffers(1, &vbo);
        //glGenBuffers(1, &ebo);
    }

    draw_batch::~draw_batch() {
        printf("deleting a batch\n");
        //glDeleteVertexArrays(1, &vao);
        //glDeleteBuffers(1, &vbo);
        //glDeleteBuffers(1, &ebo);
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

    void draw_batch::render(batcher &b) {
        sg_update_buffer(vbuf, vertices.data(), vertices.size() * sizeof(vertex));
        sg_update_buffer(ibuf, indices.data(), indices.size() * sizeof(u32));
        b.bind.vertex_buffers[0] = vbuf;
        b.bind.index_buffer = ibuf;

        for (auto &cmd : info) {
            if (cmd.img.id != 0)
                b.bind.fs_images[0] = cmd.img;
            else
                b.bind.fs_images[0] = b.default_img;
            sg_apply_bindings(b.bind);
            sg_draw(cmd.base_index, cmd.num_indices, 1);
        }
    }

    void draw_batch::reset() {
        vertices.clear();
        indices.clear();
        info.clear();
        info.emplace_back();
    }

    // == BATCHER ==================================

    void batcher::init() {
        sg_buffer_desc vbuf_d{};
        vbuf_d.size = max_vertices * sizeof(vertex);
        vbuf_d.type = SG_BUFFERTYPE_VERTEXBUFFER;
        vbuf_d.usage = SG_USAGE_STREAM;

        sg_buffer_desc ibuf_d{};
        ibuf_d.size = max_indices * sizeof(u32);
        ibuf_d.type = SG_BUFFERTYPE_INDEXBUFFER;
        ibuf_d.usage = SG_USAGE_STREAM;

        for(auto &layer: batch_layers) {
            layer.vbuf = sg_make_buffer(vbuf_d);
            layer.ibuf = sg_make_buffer(ibuf_d);
        }

        u32 pixels[1]{ 0xFF'FF'FF'FF };

        sg_image_desc imgd{};
        imgd.width = 1;
        imgd.height = 1;
        imgd.content.subimage[0][0].ptr = pixels;
        imgd.content.subimage[0][0].size = sizeof(pixels);
        default_img = sg_make_image(imgd);

        sg_shader_desc sd{};

        sd.vs.source = R"(#version 330 core
layout (location = 0) in vec2 vert;
layout (location = 1) in vec2 in_texc;
layout (location = 2) in vec3 in_col;

uniform mat4 ortho;

out vec2 texc;
out vec3 col;

void main() {
    gl_Position = ortho * vec4(vert, 0.0, 1.0);
    texc = in_texc;
    col = in_col;
}
)";
        sd.fs.source = R"(#version 330 core
in vec2 texc;
in vec3 col;
uniform sampler2D tex;

out vec4 frag_col;

void main() {
    frag_col = texture(tex, texc) + vec4(col, 0.0);
    if(frag_col.a < 1.0)
        discard;
}
)";
        
        auto *ub = &sd.vs.uniform_blocks[0];
        ub->size = sizeof(mat4);
        ub->uniforms[0].name = "ortho";
        ub->uniforms[0].type = SG_UNIFORMTYPE_MAT4;
        ub->uniforms[0].array_count = 1;

        sd.fs.images[0].name = "tex";
        sd.fs.images[0].type = SG_IMAGETYPE_2D;
        sd.fs.images[0].sampler_type = SG_SAMPLERTYPE_FLOAT;

        shader = sg_make_shader(sd);

        sg_pipeline_desc pd{};
        pd.shader = shader;
        pd.layout.buffers[0].stride = sizeof(sok_vertex);
        {
            auto *pos = &pd.layout.attrs[0];
            pos->offset = offsetof(sok_vertex, pos);
            pos->format = SG_VERTEXFORMAT_FLOAT2;
        }
        {
            auto *uv = &pd.layout.attrs[1];
            uv->offset = offsetof(sok_vertex, texc);
            uv->format = SG_VERTEXFORMAT_FLOAT2;
        }
        {
            auto *rgba = &pd.layout.attrs[2];
            rgba->offset = offsetof(sok_vertex, col);
            rgba->format = SG_VERTEXFORMAT_FLOAT3;
        }

        pd.index_type = SG_INDEXTYPE_UINT32;

        pip = sg_make_pipeline(pd);

        pass.colors[0] = {
            SG_ACTION_CLEAR,
            {0.1f, 0.1f, 0.1f, 1.f}
        };

        for (auto &layer : batch_layers)
            layer.info.emplace_back();
    }

    void batcher::push_matrix(const mat3x2 &m) {
        matrices.emplace_back(curmat);
        curmat = m * curmat;
    }

    void batcher::set_texture(const texture_t &t) {
        sg_image &current_img = current_info().img;
        if (current_img.id == 0) {
            current_img = t.image_id;
        }
        else if (current_img.id != t.image_id.id) {
            // bit of a mouthful, divided in multiple lines for
            // readability
            current_batch()
                .info
                .emplace_back(
                current_info().base_index + current_info().num_indices,
                t.image_id
            );
        }
    }

    void batcher::render() {
        sgl_viewport(0, 0, sapp_width(), sapp_height(), true); 
        sg_begin_default_pass(pass, sapp_width(), sapp_height());

        sg_apply_pipeline(pip);

        sg_apply_uniforms(SG_SHADERSTAGE_VS, 0, uniform_mat.m, sizeof(mat4));

        for (auto &layer : batch_layers)
            layer.render(*this);

        sg_end_pass();
        sg_commit();
    }

    void batcher::clear() {
        matrices.clear();
        for (auto &layer : batch_layers)
            layer.reset();
        curmat = mat3x2::identity();
    }
} // namespace gfx