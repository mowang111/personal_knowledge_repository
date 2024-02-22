# 简单Chrome的CDP调试插件

文件结构：

```
-icons
--icon16.png
--icon48.png
--icon128.png
-background.js
-mainfest.json
-popup.html
-popup.js
```

![image-20230816142432655](https://raw.githubusercontent.com/mowang111/image-hosting/master/img/image-20230816142432655.png)

background.js

```js
chrome.runtime.onMessage.addListener(function(request, sender, sendResponse) {
    if (request.action == "getTitles") {
        chrome.debugger.getTargets((targets) => {
            let titles = targets.filter(t => t.type === 'page').map(t => t.title);
            sendResponse({ titles: titles });
        });
        return true; // indicates the response is sent asynchronously
    }
});
```

manifest.json

```json
{
  "manifest_version": 3,
  "name": "CDP Debugger",
  "version": "1.0",
  "description": "Simple extension to debug using CDP",
  "background": {
    "service_worker": "background.js"
  },
  "permissions": ["debugger", "activeTab", "scripting"],
  "action": {
    "default_popup": "popup.html",
    "default_icon": {
      "16": "icons/icon16.png",
      "48": "icons/icon48.png",
      "128": "icons/icon128.png"
    }
  },
  "icons": {
    "16": "icons/icon16.png",
    "48": "icons/icon48.png",
    "128": "icons/icon128.png"
  }
}
```

popup.html

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>CDP Debugger</title>
</head>
<body>
    <button id="getTitles">Get Tab Titles</button>
    <ul id="titlesList"></ul>
    <script src="popup.js"></script>
</body>
</html>
```

popup.js

```js
document.getElementById('getTitles').addEventListener('click', () => {
  chrome.runtime.sendMessage({ action: "getTitles" }, function(response) {
      const ul = document.getElementById('titlesList');
      if (!ul) {
          console.error("Element with ID 'titlesList' not found");
          return;
      }
      ul.innerHTML = '';
      response.titles.forEach(title => {
          let li = document.createElement('li');
          li.textContent = title;
          ul.appendChild(li);
      });
  });
});
```

