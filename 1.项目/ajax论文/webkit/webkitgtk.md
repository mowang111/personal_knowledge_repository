编译

https://www.linuxidc.com/Linux/2011-10/44809.htm

![classdiagram](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/ClassDiagram)

1. 如何处理某个节点的绑定事件
   + webkit [节点对应的点击事件处理api](https://webkitgtk.org/reference/webkitdomgtk/stable/WebKitDOMHTMLElement.html#webkit-dom-html-element-click)
   + [webkit_web_frame_get_dom_document ()](https://webkitgtk.org/reference/webkitgtk/stable/WebKitWebFrame.html#webkit-web-frame-get-global-context)

## [tutrial](https://wiki.gnome.org/Projects/WebKitGtk/ProgrammingGuide/)

```c++
   1 /*
   2  * Copyright (C) 2006, 2007 Apple Inc.
   3  * Copyright (C) 2007 Alp Toker <alp@atoker.com>
   4  * Copyright (C) 2011 Lukasz Slachciak
   5  * Copyright (C) 2011 Bob Murphy
   6  *
   7  * Redistribution and use in source and binary forms, with or without
   8  * modification, are permitted provided that the following conditions
   9  * are met:
  10  * 1. Redistributions of source code must retain the above copyright
  11  *    notice, this list of conditions and the following disclaimer.
  12  * 2. Redistributions in binary form must reproduce the above copyright
  13  *    notice, this list of conditions and the following disclaimer in the
  14  *    documentation and/or other materials provided with the distribution.
  15  *
  16  * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
  17  * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  18  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
  19  * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
  20  * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
  21  * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
  22  * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
  23  * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
  24  * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  25  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  26  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  27  */
  28 
  29 #include <gtk/gtk.h>
  30 #include <webkit2/webkit2.h>
  31 
  32 
  33 static void destroyWindowCb(GtkWidget* widget, GtkWidget* window);
  34 static gboolean closeWebViewCb(WebKitWebView* webView, GtkWidget* window);
  35 
  36 int main(int argc, char* argv[])
  37 {
  38     // Initialize GTK+
  39     gtk_init(&argc, &argv);
  40 
  41     // Create an 800x600 window that will contain the browser instance
  42     GtkWidget *main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  43     gtk_window_set_default_size(GTK_WINDOW(main_window), 800, 600);
  44 
  45     // Create a browser instance
  46     WebKitWebView *webView = WEBKIT_WEB_VIEW(webkit_web_view_new());
  47 
  48     // Put the browser area into the main window
  49     gtk_container_add(GTK_CONTAINER(main_window), GTK_WIDGET(webView));
  50 
  51     // Set up callbacks so that if either the main window or the browser instance is
  52     // closed, the program will exit
  53     g_signal_connect(main_window, "destroy", G_CALLBACK(destroyWindowCb), NULL);
  54     g_signal_connect(webView, "close", G_CALLBACK(closeWebViewCb), main_window);
  55 
  56     // Load a web page into the browser instance
  57     webkit_web_view_load_uri(webView, "http://www.webkitgtk.org/");
  58 
  59     // Make sure that when the browser area becomes visible, it will get mouse
  60     // and keyboard events
  61     gtk_widget_grab_focus(GTK_WIDGET(webView));
  62 
  63     // Make sure the main window and all its contents are visible
  64     gtk_widget_show_all(main_window);
  65 
  66     // Run the main GTK+ event loop
  67     gtk_main();
  68 
  69     return 0;
  70 }
  71 
  72 
  73 static void destroyWindowCb(GtkWidget* widget, GtkWidget* window)
  74 {
  75     gtk_main_quit();
  76 }
  77 
  78 static gboolean closeWebViewCb(WebKitWebView* webView, GtkWidget* window)
  79 {
  80     gtk_widget_destroy(window);
  81     return TRUE;
  82 }
```

