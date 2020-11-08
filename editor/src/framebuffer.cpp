#include "framebuffer.h"

#include <glad/glad.h>

#include "log.h"

framebuffer::framebuffer(u32 width, u32 height)
    : width(width), height(height) {}

void framebuffer::init() {
  glGenFramebuffers(1, &fbo_id);

  bind();

  glGenTextures(1, &color_id);
  glBindTexture(GL_TEXTURE_2D, render_id);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         color_id, 0);
  glBindTexture(GL_TEXTURE_2D, 0);

  glGenRenderbuffers(1, &render_id);
  glBindRenderbuffer(GL_RENDERBUFFER, render_id);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                            GL_RENDERBUFFER, render_id);
  glBindRenderbuffer(GL_RENDERBUFFER, render_id);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    LERR("Failed to create render buffer");
  }

  unbind();
}

void framebuffer::destroy() {
  unbind();
  glDeleteTextures(1, &color_id);
  glDeleteRenderbuffers(1, &render_id);
  glDeleteFramebuffers(1, &fbo_id);
}

void framebuffer::bind() { glBindFramebuffer(GL_FRAMEBUFFER, fbo_id); }

void framebuffer::unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }
