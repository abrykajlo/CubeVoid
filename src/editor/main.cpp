#include <editor/editor.h>
#undef main

int
main()
{
    cv::editor::Editor editor;
    if (editor.Init() < 0) {
        return -1;
    }
    
    editor.Run();

    if (editor.Quit() < 0) {
        return -1;
    }
}