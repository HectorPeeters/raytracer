#pragma once

class application;

class ui_panel {
public:
  ui_panel(const char *title) : title(title) {}
  virtual ~ui_panel(){};

  virtual void init() = 0;
  virtual void draw(application &app) = 0;
  virtual void deinit() = 0;

  const char *get_title() { return title; }

  bool showing{true};

private:
  const char *title;
};
