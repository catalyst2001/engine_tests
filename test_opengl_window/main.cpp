#include <stdio.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

HWND  h_wnd;
HGLRC h_glctx;
bool  b_alive = true;

LRESULT CALLBACK wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  switch (msg)
  {
  case WM_CLOSE: {
    PostQuitMessage(0);
    break;
  }

  case WM_SIZE: {

    break;
  }
  }
  return DefWindowProcA(hwnd, msg, wparam, lparam);
}

int main()
{
  printf("hello\n");

  WNDCLASSA wc{};
  wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wc.hCursor = LoadCursorW(NULL, MAKEINTRESOURCEW(IDC_ARROW));
  wc.lpszClassName = "test_engine_window";
  wc.lpfnWndProc = &wndproc;
  if (!RegisterClassA(&wc)) {
    printf("failed to register window class\n");
    return 1;
  }
  
  /**
  * create win32 window
  */
  const int width = 800;
  const int height = 600;
  int mwidth = GetSystemMetrics(SM_CXSCREEN);
  int mheight = GetSystemMetrics(SM_CYSCREEN);
  int posx = (mwidth - width) >> 1;
  int posy = (mheight - height) >> 1;
  h_wnd = CreateWindowExA(0, "test_engine_window", "Test OpenGL window",
    WS_OVERLAPPEDWINDOW | WS_VISIBLE, posx, posy, width, height, HWND_DESKTOP, (HMENU)0, nullptr, nullptr);
  if (!h_wnd) {
    printf("failed to create window\n");
    return 1;
  }

  /**
  * create opengl context
  */
  HDC window_ctx = GetDC(h_wnd);
  if (!window_ctx) {
    printf("failed to get window context\n");
    //TODO: K.D. free resources...
    return 1;
  }

  PIXELFORMATDESCRIPTOR pfd = {
    sizeof(PIXELFORMATDESCRIPTOR),  //  size of this pfd  
    1,                     // version number  
    PFD_DRAW_TO_WINDOW |   // support window  
    PFD_SUPPORT_OPENGL |   // support OpenGL  
    PFD_DOUBLEBUFFER,      // double buffered  
    PFD_TYPE_RGBA,         // RGBA type  
    24,                    // 24-bit color depth  
    0, 0, 0, 0, 0, 0,      // color bits ignored  
    0,                     // no alpha buffer  
    0,                     // shift bit ignored  
    0,                     // no accumulation buffer  
    0, 0, 0, 0,            // accum bits ignored  
    32,                    // 32-bit z-buffer      
    0,                     // no stencil buffer  
    0,                     // no auxiliary buffer  
    PFD_MAIN_PLANE,        // main layer  
    0,                     // reserved  
    0, 0, 0                // layer masks ignored  
  };
  int pixelformat = ChoosePixelFormat(window_ctx, &pfd);
  if (!pixelformat) {
    printf("failed to get window context\n");
    //TODO: K.D. free resources...
    return 1;
  }

  if (!SetPixelFormat(window_ctx, pixelformat, &pfd)) {
    printf("SetPixelFormat failed\n");
    //TODO: K.D. free resources...
    return 1;
  }

  h_glctx = wglCreateContext(window_ctx);
  if (!h_glctx) {
    printf("wglCreateContext failed\n");
    //TODO: K.D. free resources...
    return 1;
  }

  //TODO: K.D. add creation of new context

  if (!wglMakeCurrent(window_ctx, h_glctx)) {
    printf("wglMakeCurrent failed\n");
    //TODO: K.D. free resources...
    return 1;
  }

  //TODO: K.D. 

  MSG msg;
  while (b_alive) {
    while (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE)) {
      if (msg.message == WM_QUIT) {
        b_alive = false;
        break;
      }
      TranslateMessage(&msg);
      DispatchMessageA(&msg);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);




    Sleep(1);
  }
  DestroyWindow(h_wnd);
  UnregisterClassA(wc.lpszClassName, nullptr);
  return 0;
}