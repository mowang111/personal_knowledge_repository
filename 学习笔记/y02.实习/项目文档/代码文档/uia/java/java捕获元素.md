# java捕获元素

```c#
//捕获鼠标所在点的元素 ShadowBot.UIAutomation.Provider\UIAutomation\Java\JavaAutomation.win.cs
public TraceData Trace(SpyContext context){
    //0.获取Java窗口
    var javaWin = JavaHelper.GetAccessibleWindowFromHWND(context.Control.Handle);//javaWin也是JavaElement类型
    ...
    //1.获取元素
    	//1.1 坐标点转换
    	//1.2 获取所在点的JavaElement
    	var javaEle = javaWin.FromPoint(point);
   	//3.返回TraceData
}
```

```c#
//获取所在点的最小Element
public JavaElement FromPoint(Point point){
    //1、使用 elementFromPoint获取目标元素
    AccessibleContext eleAc;
	if(!_accessBridge.Functions.GetAccessibleContextAt(JvmId, _ac, point.X, point.Y, out eleAc)) return null;//使用 Java Access Bridge (JAB) 的 API 获取指定屏幕坐标下的可访问对象（accessible object）的上下文
    //2、使用 context.window获取目标元素
}
```

