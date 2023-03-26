# 開発メモ
## 1. GTK事始め
* とにかく初めてだったので、調べたことや試したことをここに書く
* 参照したサイトがあったが、時々Chat-GPTに助けてもらった

## 2. 事前準備
### 参考にしたサイト
* [GTK+3入門 (C++版)](https://jitaku.work/it/category/gui/gtkmm/) という記事
  * 2021.12.24 に書かれていたので、比較的新しい
  * C言語とC++言語に分けて記載されていた
  * 今回は、C++言語の gtkmm を使ったサンプルを試した

## 3. パッケージインストール
* C++とするので、上記記事の通り、libgtkmm をインストール。
* `sudo apt install -y libgtkmm-3.0-dev`
* ちなみにC言語の場合、libgtk をインストール らしい

## 4. ソースコード準備とビルド
* 上記記事に沿ってサンプルコードを作成
* `#include <gtkmm.h>` を、main.cpp の頭にこれを書くが、ソースファイルを開けないって警告がエディタにでる。が、一旦無視。
* ビルドは、いつも自分が使っているMakefileを使いまわす
* 記事に従い、`LDFLAGS` に `gtkmm-3.0` を追加した
* だがしかし、エラーが出てビルドが出来ない。

## 5. ビルド試行錯誤
### gtk-4 の自前ビルド
* 最初にやったのは、gtkmm-4 のビルド。
* [How to install GTKMM 4 on Ubuntu 22.04](https://terminalroot.com/how-to-install-gtkmm-4-on-ubuntu-2204/) を参考にしてみた
* だが、何やらの必要なパッケージが見つからず、やはり手動ビルドとなったがこれもエラーが出たため断念。
### Chat-GPT に聞いてみた
* 埒が明かないので、Chat-GPT に聞いたところ、以下の回答を得た。
  * C++でGUIを作成するには、いくつかの選択肢がありますが、ここではGTKライブラリを使用した方法を紹介します。

  1. GTKライブラリをインストールする
       * Ubuntuであれば、以下のコマンドでインストールできます。
       * `sudo apt-get install libgtk-3-dev`
  2. プログラムを作成する
       * 以下のようなC++プログラムを作成して、ボタンを配置するGUIを作成することができます。

        ``` C++
        #include <gtk/gtk.h>

        // ボタンがクリックされたときのコールバック関数
        static void button_clicked(GtkWidget *widget, gpointer data) {
          g_print("Button clicked\n");
        }

        int main(int argc, char *argv[]) {
          // GTKの初期化
          gtk_init(&argc, &argv);

          // ウィンドウを作成
          GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
          gtk_window_set_title(GTK_WINDOW(window), "Hello World");
          gtk_container_set_border_width(GTK_CONTAINER(window), 10);

          // ボタンを作成
          GtkWidget *button = gtk_button_new_with_label("Click me");
          g_signal_connect(button, "clicked", G_CALLBACK(button_clicked), NULL);

          // ボタンをウィンドウに追加
          gtk_container_add(GTK_CONTAINER(window), button);

          // ウィンドウを表示
          gtk_widget_show_all(window);

          // GTKのメインループを開始
          gtk_main();

          return 0;
        }

        ```
  3. プログラムをコンパイルする
     * 以下のようなコマンドでコンパイルできます。
     * ``` g++ -o program program.cpp `pkg-config --cflags --libs gtk+-3.0` ```
     * これ、gtkmm+3

  4. プログラムを実行する
     * 以下のようにコマンドを入力して、プログラムを実行します。
     * `./program`

  * これで、ボタンを配置するだけの簡単なGUIが作成できます。

### 更に、Chat-GPT に Makefile の作り方を聞いてみた
* 続けて、Makefileの作り方も聞いてみた。
* Makefileを使ってコンパイルする場合、以下のようなMakefileを作成することができます。
  ```
  CC = g++
  CFLAGS = -Wall `pkg-config --cflags gtk+-3.0`
  LDFLAGS = `pkg-config --libs gtk+-3.0`

  all: program

  program: program.cpp
    $(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

  clean:
    rm -f program
  ```

* Makefileを作成したら、以下のコマンドでコンパイルすることができます。
* `make`
* コンパイルが成功すると、プログラムが"program"という名前の実行可能ファイルとして生成されます。
* また、以下のコマンドで生成された実行可能ファイルを削除することができます。
* `make clean`

## 6. ビルドに成功！
* Chat-GPT の回答だけど、
  * `gtk+-3.0` ではなく `gtkmm-3.0` なので、修正した。
  * それと、main関数のインクルードヘッダも `gtkmm` に修正した。
* Makefileに関しては、最初は `LDFLAGS` だけに gtk を追加したんだが、Chat-GPT の言う通り、`CFLAGS` にも追記が必要だった。このあたりは自分の理解が出来てないためだった
* ただし、ビルドが通っても、main.cpp でインクルードしてる `gtkmm.h` は、警告が残っています。