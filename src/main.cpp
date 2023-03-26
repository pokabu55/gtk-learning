/*
#include <gtk/gtk.h>

int main (int argc, char* argv[])
{
    GtkWidget* window;

    // 初期化
    gtk_init(&argc, &argv);

    // Windowの作成
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    // Windowsの大きさを指定
    gtk_widget_set_size_request(window, 640, 480);

    // Windowタイトルの設定
    gtk_window_set_title(GTK_WINDOW(window), "タイトル");

    // Windowの表示
    gtk_widget_show_all(window);

    // メインループ
    gtk_main(); 

    return 0;
}
*/

#include <gtkmm.h>

class SampleWindow : public Gtk::Window
{
public:
    SampleWindow(int width, int height);
    virtual ~SampleWindow() = default;
};

SampleWindow::SampleWindow(int width, int height)
{
    set_title("タイトル");
    set_default_size(width, height);
}

int main(int argc, char* argv[])
{
    auto app = Gtk::Application::create(argc, argv, "work.jitaku.gtkmm.sample");
    SampleWindow sample_window(320, 240);
    return app->run(sample_window);
}
