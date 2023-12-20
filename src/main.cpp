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
    SampleWindow(int width, int height, std::string labelName);
    virtual ~SampleWindow() = default;

private:
    Gtk::Label label_;
};

SampleWindow::SampleWindow(int width, int height, std::string labelName)
{
    set_title("タイトル");
    set_default_size(width, height);

    // テキストの表示
    label_.set_text(labelName);
    label_.show();

    //
    add(label_);
}

int main(int argc, char* argv[])
{
    auto app = Gtk::Application::create(argc, argv, "work.jitaku.gtkmm.sample");
    SampleWindow sample_window(640, 480, "test,test");
    return app->run(sample_window);
}

bool trimingScaling(
    unsigned char *src, int srcW, int srcH,
    int trimSx, int trimSy, int trimW, int trimH, double scale, 
    unsigned char *dst, int dstW, int dstH
) {

    int x,y;
    int dx, dy;

    for (dy=0; dy < dstH; dy++) {
        for (dx=0; dx<dstW; dx++) {
            // 逆変換で入力画像の座標
            x = (int)((dx / scale) + trimSx + 0.5);
            y = (int)((dy / scale) + trimSy + 0.5);

            if(x<0 || x >= srcW || y<0 || y>= srcH) continue;

            dst[dx+dy*dstW] = src[x+y*srcW];
        }
    }

    return true;
}