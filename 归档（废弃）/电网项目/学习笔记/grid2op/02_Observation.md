## observation

### 获取observation

```python
env = grid2op.make(test=True)
obs = env.reset() 
```

### observation包含的信息

#### 一些基本属性

时间

一般的电力信息：发电机数量，负载数量，电线数量，配电站数量等等

发电机的信息（3个维度）

```python
print("Generators active production: {}".format(obs.gen_p))
print("Generators reactive production: {}".format(obs.gen_q))
print("Generators voltage setpoint : {}".format(obs.gen_v))
```

>Generators active production: [74.8      73.8      29.2       0.       75.578995] 
>
>Generators reactive production: [ 19.329943  74.27505   43.9601    24.940077 -17.105919] 
>
>Generators voltage setpoint : [142.1      142.1       22.        13.200001 142.1     ]

负载信息（3个维度）

电线信息（8个维度）

- active flow
- reactive flow
- voltage magnitude
- current flow

for both its origin and its extremity.

For example, suppose the powerline `line1` is connecting two node `A` and `B`. There are two separate values for the active flow on `line1` : the active flow from `A` to `B` (origin) and the active flow from `B` to `A` (extremity).

还有一个电线的维度 ρ ratio, the ratio between the current flow in the powerline and its thermal limit, *ie.* for each powerline. 

topo_vect存储了连接（电线，负载，发电机等）的信息

```python
load_id = 2
obs.topo_vect[obs.load_pos_topo_vect[load_id]]
```

#### 图的表示

画出电力图

```python
from grid2op.PlotGrid import PlotMatplot
plot_helper = PlotMatplot(env.observation_space)
obs = env.reset()
_ = plot_helper.plot_obs(obs)
```

connectivity matrix

bus connectivity matrix

flow bus matrix

#### 其他方便的方法

#### 仿真

```python
do_nothing_act = env.action_space({})
obs_sim, reward_sim, is_done_sim, info_sim = obs.simulate(do_nothing_act)
```

```
obs.gen_p
```

```
obs_sim.gen_p
```

#### obs+act

也是评估动作之后对电网的影响的

```
action_description = {}
act = env.action_space(action_description)
resulting_partial_obs = obs + act
resulting_partial_obs.connectivity_matrix()
```

### 在observation的基础上take actions