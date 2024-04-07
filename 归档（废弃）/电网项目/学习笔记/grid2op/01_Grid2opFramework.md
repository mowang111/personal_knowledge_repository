## 框架的基础用法

### 创建环境

#### 默认设置

#### 自定义设置

使用make创建环境时可添加一些参数：

- `param`: 环境中可以使用的参数. [See `grid2op.Parameters.Parameters`.](https://grid2op.readthedocs.io/en/latest/parameters.html)
- `backend` : The backend to use for the computation. If provided, it must be an instance of the class `grid2op.Backend.Backend`.
- `action_class`: The type of BaseAction that the BaseAgent will be able to perform. If provided, it must be a subclass of `grid2op.BaseAction.BaseAction`.
- `observation_class`: The type of BaseObservation that the BaseAgent will receive. If provided, It must be a subclass of `grid2op.BaseAction.BaseObservation`.
- `reward_class`: The type of reward signal that the BaseAgent will receive. If provided, It must be a subclass of `grid2op.BaseReward.BaseReward`.
- `gamerules_class`: The type of "Rules" that the BaseAgent will need to comply with. Rules are here to model some operational constraints. If provided, it must be a subclass of `grid2op.RulesChecker.BaseRules`.
- `data_feeding_kwargs`: A dictionnary that is used to build the `data_feeding` (chronics) objects.
- `chronics_class`: The type of chronics that represents the dynamics of the created Environment. Usually they come from different folders.
- `data_feeding`: The type of chronics handler you want to use.
- `volagecontroler_class`: The type of `grid2op.VoltageControler.VoltageControler` to use.
- `chronics_path`: The path where to look for the chronics dataset (optional).
- `grid_path`: The path where the powergrid is located. If provided, it must be a string and point to a valid file on the hard drive.

### 创建智能体

### 评估智能体表现（人工）reward

In this example, the cumulated reward is a *FlatReward* that simply computes how many time steps the *Agent* has sucessfully managed before breaking any rules.

```python
done = False
time_step = int(0)
cum_reward = 0.
obs = env.reset()
reward = env.reward_range[0]
max_iter = 10
while not done:
    act = my_agent.act(obs, reward, done) # chose an action to do, in this case "do nothing"
    obs, reward, done, info = env.step(act) # implement this action on the powergrid
    cum_reward += reward
    time_step += 1
    if time_step >= max_iter:
        break
```

### 更便捷的方式评估智能体表现

#### Using the grid2op.runner API

