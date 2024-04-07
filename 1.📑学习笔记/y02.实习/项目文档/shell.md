# shell代码

+ .Shell

  + Product

    + local
    + oversea

  + ShadowBot.Shell

    + 入口程序，这里会调用真实程序，并加一些程序执行参数
    + 从这里会调用ShadowBot.Products.Local(oversea)，启动的时候调用这里的OnStartup函数

  + ShadowBot.Shell.Console

    + IStudioManager.cs 这是管理设计器的

      + workspace

        ![image-20230419193051905](https://raw.githubusercontent.com/mowang111/image-hosting/master/img/image-20230419193051905.png)

  + ShadowBot.Shell.Development

    + BlockSettings
      + 更新Block组件时会调用里面的submit函数

+ Components

  + ShadowBot.Components

    + Engine

      + PythonFactory.cs

      + EngineComponent.cs

      + XbotEngine.cs

        + ```c#
          //这里在运行应用的时候会启用这段代码
          public virtual void Start()
                  {
                      // 启动引擎过程处理服务
                      _ipc.Start(_pipeId);//进程间通信
                      // 获取/启动UI自动化服务
                      var uiaPipe = UIAProviderManagement.Start(false);
                      // 获取/启动python进程
                      _process = _pythonFactory.Take();
                      _process.OutputDataReceived += process_OutputDataReceived;
                      _process.ErrorDataReceived += process_ErrorDataReceived;
                      _info.ProcessId = _process.Id;
                      // 不使用Exited事件监听，因为ErrorDataReceived和Exited事件的触发顺序无法预期
                      Task.Factory.StartNew(WaitForPythonExit);
          
                      OnStarted(new EngineStartedEventArgs(_id, _process.Id));
          
                      // 拼接path，robot虚拟环境+工程folder
                      var sysPathList = new List<string>();
                      if (_options.SitePackages != null)
                          sysPathList.AddRange(_options.SitePackages);
                      sysPathList.Add(Path.GetFullPath(Path.Combine(_options.RobotFolder, @"..")));
          
                      // 给robot传递信息，执行任务_process
                      var robotInputs = JsonConvert.SerializeObject(new
                      {
                          robot_pip = _pipeId,
                          uia_pip = uiaPipe,
                          sys_path_list = sysPathList,
                          environment_variables = _options.EnvironmentVariables,
                          mod = _options.Module,
                          debug = _options.DebuggerOptions != null,
                          inputs = _options.Inputs
                      });
          
                      // 使用Base64封装发送的原因是部分机器的stdin编码无法确定，当内容包含中文时，经常导致python反序列化失败3
                      robotInputs = Convert.ToBase64String(new UTF8Encoding(false).GetBytes(robotInputs));
          
                      WriteToPython(robotInputs);
                      Logging.Info($"xbot engine running, pid:{_process.Id},engineid:{_id}");
                  }
          ```

      + XbotEngineHandlers.cs

  + ShadowBot.Components.Protocol

+ Framework

  + ShadowBot.Common
    + IPC

  + **ShaowBot.Runtime.Console**
    + ViewModels
      + MyApp
        + DevelopedAppVIewModel.cs
        + AppItemViewModel.cs
          + EditApp()编辑应用
  + **ShaowBot.Runtime.Development**
    + Blockly/ : block就是一条条指令，关于指令的管理基本在这
      + Handlers 处理各种指令，修改完指令后会调用这里对应的部分
      + PythonCodeBuilder 用来生成python代码
    + Brief/
    + LocalizationResources/
    + PLS/
    + **Resources/**
      + **zh-CN 这里包括的*.blocks.json**
    + Validation/
    + **Workspace.cs**
      + 这里面管理了设计器中的各种窗口，包括选择器窗口等
    + SelectorCollection

+ Launcher

+ Solution Items

+ **UIAutomation**

  + **ShadowBot.UIAutomation**
    + Primitive 一些很基础的组件
      + ISelector.cs
      + Point.cs
      + Rectangle.cs
  + **ShadowBot.UIAutomation.Tools**
    + SelectorEditor
      + SelectorEditWindow.cs
        + OnHighlight() 校验高亮元素时，会调用这个函数
          + FindElementBounding()
    + UIAAgent
      + UIAClient.cs
        + Send()方法通过管道发送消息给provider，并接收处理的结果
      + UIAConnection.cs
    + UISpy

+ VirtualDesktop

## 指令从建立到运行到结束的流程

1. 打开设计器之前，会通过BlockPrototypeFactory.cs加载workspace，也是在这里加载所有的*.blocks.json

   编辑模块的时候，同样是加载对应的blocks.json，比如填写输入框（web），会加载web.element.bloks.json，其中对应的是"web.element.input"。

   下面这个框是怎么渲染出来的？

   ![image-20230420162019786](https://raw.githubusercontent.com/mowang111/image-hosting/master/img/image-20230420162019786.png)

   ```json
   {
     "name": "web.element.input",
     "title": "填写输入框(web)",
     "description": "在网页的输入框中输入内容",
     "comment": "在网页%browser%的%element%中，%input_type%%text%",
     "icon": "BlockIcons/2-3.png",
     "settingsControl": "ShadowBot.Shell.Development.BlockSettings.Controls.Element.InputControl, ShadowBot.Shell.Development",
     "function": "xbot_visual.web.element.input",
     "helpUrl": "yddoc/language/zh-cn/指令文档/网页自动化/填写输入框（web）.html",
     "video": {
       "time": "06:49"
     },
     "handlers": [
       {
         "name": "ShadowBot.Runtime.Development.Blockly.Handlers.Web.InputBrowserHandler"
       }
     ],
     "inputs": [
       {
         "name": "browser",
         "label": "网页对象",
         "required": true,
         "tips": "输入一个获取到的或者通过\"打开网页\"创建的网页对象",
         "type": "xbot._web.browser.WebBrowser",
         "editor": {
           "kind": "select",
           "useVariableOptions": true
         }
       },
       {
         "name": "element",
         "label": "操作目标",
         "required": true,
         "tips": "选择要操作的网页元素",
         "type": "xbot._web.element.WebElement",
         "editor": {
           "kind": "uitarget",
           "selectorType": "simple"
         }
       },
       {
         "name": "text",
         "label": "输入内容",
         "tips": "填写要输入的内容",
         "type": "str",
         "editor": {
           "kind": "memoedit"
         }
       },
       {
         "name": "append",
         "label": "",
         "required": true,
         "default": "13:False",
         "tips": "如果勾选追加输入则在现有内容后继续追加输入,否则清空现有内容后再进行输入",
         "type": "bool",
         "editor": {
           "label": "追加输入",
           "kind": "checkbox"
         }
       },
       {
         "name": "simulate",
         "label": "",
         "required": true,
         "default": "13:True",
         "category": "advanced",
         "tips": "如果使用模拟人工输入则通过模拟人工的方式触发输入事件,否则将根据目标元素的自动化接口触发输入",
         "type": "bool",
         "editor": {
           "label": "模拟人工输入",
           "kind": "checkbox"
         }
       },
       {
         "name": "save_to_clipboard",
         "label": "",
         "required": true,
         "default": "13:False",
         "category": "advanced",
         "tips": "将输入内容添加到剪切板通过Ctrl+V指令将内容填写到输入框避免输入法问题",
         "type": "bool",
         "editor": {
           "label": "剪切板输入",
           "kind": "checkbox"
         }
       },
       {
         "name": "input_type",
         "label": "输入方式",
         "required": true,
         "tips": "模拟人工输入: 通过模拟人工的方式触发输入事件(会自动切换当前输入法为英文输入状态, 以避免输入法造成的输入错误问题)\r\n剪切板输入: 将输入内容添加到剪切板通过Ctrl+V指令将内容填写到输入框避免输入法问题\r\n自动化接口输入: 调用元素自身实现的自动化接口输入",
         "type": "str",
         "default": "10:simulate",
         "category": "advanced",
         "defaultDisplay": "模拟人工输入",
         "autoFill": true,
         "editor": {
           "kind": "select",
           "options": [
             {
               "display": "模拟人工输入",
               "value": "simulate"
             },
             {
               "display": "剪切板输入",
               "value": "clipboard"
             },
             {
               "display": "自动化接口输入",
               "value": "automatic"
             }
           ]
         }
       },
       {
         "name": "contains_hotkey",
         "label": "",
         "required": true,
         "default": "13:False",
         "category": "advanced",
         "tips": "可以在输入内容中加入快捷键,如{enter}代表输入回车键",
         "type": "bool",
         "editor": {
           "label": "输入内容包含快捷键",
           "kind": "checkbox"
         }
       },
       {
         "name": "force_ime_ENG",
         "label": "",
         "required": true,
         "default": "13:False",
         "category": "advanced",
         "tips": "存在不常见的输入法切换英文输入状态不成功的情况\r\n需要指定强制加载美式键盘(ENG), 确保模拟输入不受中文输入法影响",
         "type": "bool",
         "editor": {
           "label": "强制加载美式键盘(ENG)",
           "kind": "checkbox"
         }
       },
       {
         "name": "send_key_delay",
         "label": "按键输入间隔(ms)",
         "required": true,
         "category": "advanced",
         "default": "10:50",
         "tips": "两次按键输入的间隔时间(对影刀浏览器该参数无效), 单位是毫秒, 为避免输入错误, 请将该值调大,最大值为1000ms",
         "type": "int",
         "editor": {
           "kind": "spin",
           "minValue": 5
         }
       },
       {
         "name": "focus_timeout",
         "label": "焦点超时时间(ms)",
         "category": "advanced",
         "default": "10:1000",
         "tips": "设置焦点超时时间(ms), 元素获取焦点后暂停指定时间后进行输入操作",
         "type": "int",
         "editor": {
           "kind": "textbox",
           "minValue": 0
         }
       },
       {
         "name": "delay_after",
         "label": "执行后延迟(s)",
         "required": true,
         "category": "advanced",
         "default": "10:1",
         "tips": "指令执行完成后的等待时间",
         "type": "float",
         "editor": {
           "kind": "spin",
           "minValue": 0
         }
       },
       {
         "name": "click_before_input",
         "label": "",
         "required": true,
         "default": "13:True",
         "category": "advanced",
         "tips": "在执行输入动作前，先点击元素，以便获取焦点",
         "type": "bool",
         "editor": {
           "label": "输入前点击元素",
           "kind": "checkbox"
         }
       },
       {
         "name": "anchor_type",
         "label": "锚点",
         "required": false,
         "tips": "支持点击元素中心位置(元素矩形区域的中心点)、随机位置(自动随机指定元素矩形范围内的点)、自定义位置(手动指定目标点)",
         "type": "str",
         "default": "10:center",
         "defaultDisplay": "中心点",
         "category": "advanced",
         "autoFill": true,
         "editor": {
           "kind": "select",
           "options": [
             {
               "display": "中心点",
               "value": "center"
             },
             {
               "display": "随机位置",
               "value": "random"
             },
             {
               "display": "自定义",
               "value": "custom"
             }
           ]
         }
       },
       {
         "name": "sudoku_part",
         "default": "10:middleCenter",
         "label": "鼠标点击位置",
         "category": "advanced",
         "tips": "该输入指令是通过（先点击输入框，后模拟键盘输入）实现的，默认点击输入框的中心位置，请根据实际情况调整",
         "type": "str",
         "editor": {
           "kind": "sudoku"
         }
       },
       {
         "name": "offset_x",
         "label": "横向偏移",
         "category": "advanced",
         "required": true,
         "default": "10:0",
         "tips": "输入 5 表示将鼠标向右移动 5px，输入负数代表向左移动鼠标",
         "type": "int",
         "editor": {
           "kind": "textbox"
         }
       },
       {
         "name": "offset_y",
         "label": "纵向偏移",
         "category": "advanced",
         "required": true,
         "default": "10:0",
         "tips": "输入 5 表示将鼠标向下移动 5px，输入负数代表向上移动鼠标",
         "type": "int",
         "editor": {
           "kind": "textbox"
         }
       },
       {
         "name": "timeout",
         "label": "等待元素存在(s)",
         "required": true,
         "category": "advanced",
         "default": "10:20",
         "tips": "等待目标输入框存在的超时时间",
         "type": "int",
         "editor": {
           "kind": "textbox",
           "minValue": 0
         }
       }
     ]
   }
   ```

   

2. 指令从可视化模块到生成python代码

   可视化模块的配置保存在main.flow.json中，之后通过这个json文件生成python代码

   ```json
   "blocks":[
       {
         "id": "deb7035b-f3e8-45a9-a998-3f3561f702c2",
         "name": "web.create",//这里就可以找到web.blocks.json中的"web.create"
         "isEnabled": true,
         "comment": "在%web_type%中新建标签页%value%，将网页对象保存到%browser%，网页加载超时后终止流程",
         "inputs": {
           "web_type": {
             "value": "10:cef",
             "display": "影刀浏览器"
           },
           "value": {
             "value": "10:www.baidu.com"
           },
             ......
         },
         "outputs": {
           "browser": {
             "name": "web_page",
             "isEnable": true
           }
         }
       }
   ]
   ```

   然后会调用PythonCodeBuilder中的build函数

3. 然后会在XbotEngine中调用上面建立的python代码，下面的robotInputs包括python路径等信息

   ![image-20230420115014786](https://raw.githubusercontent.com/mowang111/image-hosting/master/img/image-20230420115014786.png)

4. 应用运行的过程中，是如何从元素库中找到元素的？

   + 元素库中的元素都保存在selectorsV2.xml文件中

   + Shell中通过SelectorCollection来管理元素库，里面有一个索引器来索引元素

   ![image-20230420123025314](https://raw.githubusercontent.com/mowang111/image-hosting/master/img/image-20230420123025314.png)

   + 点击校验元素的时候会发生什么?

     + 以网页元素为例

       ```c#
       var bid = UIAClient.Resolve<WebAgent>().GetActiveBrowser(webType, productName);
       var eids = UIAClient.Resolve<WebBrowserAgent>().QuerySelectorAll(webType, productName, bid, selector);
       var rects = UIAClient.Resolve<WebElementAgent>().GetBoundingList(webType, productName, bid, eids, true);
       total = eids.Length;
       return rects;
       ```

       

     + QuerySelectorAll

       + ```c#
         public string[] QuerySelectorAll(UIFramework webType, string productName, int browserId, Selector selector)
         {
             GetProductName(webType, ref productName);
             return _conn.Execute<string[]>($"{Controller(webType)}.QuerySelectorAll", new
             {
                 browserId,
                 selector,
                 productName
             });
         }
         ```

       + 上一层FindElementBounding

5. 元素是如何捕获的

   + 捕获元素的时候，如何根据鼠标的移动，获取对应元素的边界

     + UISpy.cs  Inspect()

       + ```c#
         //2、启动一个线程，实时监测鼠标在哪一个元素上，并高亮显示
         ThreadPool.QueueUserWorkItem(ResolveElementAsync);
         ```

       + ```c#
         public TraceData Trace(Point point)
         {
             return _conn.Execute<TraceData>("UISpy.Trace", new { point });
         }
         ```

       + ```c#
         public IPCResponse Send(string command, object @params = null)
         {
             if (_state == 0)
             {
                 throw new InvalidOperationException("ipc-client is not connected");
             }
             else
             {
                 var request = new IPCRequest
                 {
                     Method = command,
                     Params = @params == null ? null : JToken.FromObject(@params),
                     Options = Options
                 };
                 lock (_lock)
                 {
                     if (_state == 0)
                     {
                         throw new InvalidOperationException("ipc-client is not connected");
                     }
                     else
                     {
                         _pipe.WriteRequest(request, WriteTimeout);
                         var response = _pipe.ReadResponse(ReadTimeout);
                         return response;
                     }
                 }
             }
         }
         ```
