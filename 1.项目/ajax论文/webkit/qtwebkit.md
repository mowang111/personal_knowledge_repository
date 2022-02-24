## 内存大小占用

![image-20220223203659585](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220223203659585.png)

## 使用方式

#### Architecture

The easiest way to render content is through the [QWebView](https://doc.qt.io/archives/qt-4.8/qwebview.html) class. As a widget it can be embedded into your forms or a graphics view, and it provides convenience functions for downloading and rendering web sites.

```
    QWebView *view = new QWebView(parent);
    view->load(QUrl("http://qt-project.org"));
    view->show();
```

[QWebView](https://doc.qt.io/archives/qt-4.8/qwebview.html) is used to view Web pages. An instance of [QWebView](https://doc.qt.io/archives/qt-4.8/qwebview.html) has one [QWebPage](https://doc.qt.io/archives/qt-4.8/qwebpage.html). [QWebPage](https://doc.qt.io/archives/qt-4.8/qwebpage.html) provides access to the document structure in a page, describing features such as frames, the navigation history, and the undo/redo stack for editable content.

HTML documents can be nested using frames in a frameset. An individual frame in HTML is represented using the [QWebFrame](https://doc.qt.io/archives/qt-4.8/qwebframe.html) class. This class includes the bridge to the JavaScript window object and can be painted using [QPainter](https://doc.qt.io/archives/qt-4.8/porting4.html#qpainter). Each [QWebPage](https://doc.qt.io/archives/qt-4.8/qwebpage.html) has one [QWebFrame](https://doc.qt.io/archives/qt-4.8/qwebframe.html) object as its main frame, and the main frame may contain many child frames.

Individual elements of an HTML document can be accessed via DOM JavaScript interfaces from within a web page. The equivalent of this API in [QtWebKit](https://doc.qt.io/archives/qt-4.8/qtwebkit-module.html) is represented by [QWebElement](https://doc.qt.io/archives/qt-4.8/qtwebkit-bridge.html#qwebelement). [QWebElement](https://doc.qt.io/archives/qt-4.8/qtwebkit-bridge.html#qwebelement) objects are obtained using [QWebFrame](https://doc.qt.io/archives/qt-4.8/qwebframe.html)'s [findAllElements()](https://doc.qt.io/archives/qt-4.8/qwebframe.html#findAllElements) and [findFirstElement()](https://doc.qt.io/archives/qt-4.8/qwebframe.html#findFirstElement) functions with CSS selector queries.

Common web browser features, defaults and other settings can be configured through the [QWebSettings](https://doc.qt.io/archives/qt-4.8/qwebsettings.html) class. It is possible to provide defaults for all [QWebPage](https://doc.qt.io/archives/qt-4.8/qwebpage.html) instances through the default settings. Individual attributes can be overidden by the page specific settings object.