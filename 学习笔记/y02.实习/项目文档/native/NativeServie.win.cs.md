+ 元素
+ 窗口
  + 根据选择器的第一个节点计算窗口
    + public int GetWindowBySelector(Selector selector)
  + 根据handle获取窗口
    +  public int GetWindowByHandle(int handle)
    + 异常：NoSuchWindow
  + 根据标题获取窗口列表
    + public int[] GetWindowListByTitle(string title = "", bool useWildcard = false)
    + 异常
      + 标题或者类型名为空
      + NoSuchWindow
  + 获取桌面窗口handle
    + GetDesktopWindow()
  + 获取已激活窗口handle
    + GetActiveWindow()
  + 获取已激活浏览器窗口类型
    + public UIFramework GetActiveWebType()
  + 获取已激活浏览器窗口ProductName()
    + public string GetActiveWebProductName()
  + 最小化所有窗口
    + public void MinimizeAllWindows()
  + 是否存在窗口
    + public bool Exists(IntPtr hWnd)
  + 