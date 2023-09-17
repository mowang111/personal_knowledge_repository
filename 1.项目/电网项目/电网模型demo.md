

## 步骤

1. 环境()
2. reward(https://grid2op.readthedocs.io/en/latest/reward.html#module-grid2op.Reward)



## environment

现有环境https://grid2op.readthedocs.io/en/latest/available_envs.html

定制环境https://grid2op.readthedocs.io/en/latest/environment.html#customization

agent

action

### reward

|                                                              |                                                              |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [`AlarmReward`](https://grid2op.readthedocs.io/en/latest/reward.html#grid2op.Reward.AlarmReward)() | This reward is based on the "alarm feature" where the agent is asked to send information about potential issue on the grid. |
| [`BaseReward`](https://grid2op.readthedocs.io/en/latest/reward.html#grid2op.Reward.BaseReward)() | Base class from which all rewards used in the Grid2Op framework should derived. |
| [`BridgeReward`](https://grid2op.readthedocs.io/en/latest/reward.html#grid2op.Reward.BridgeReward)([min_pen_lte, max_pen_gte]) | This reward computes a penalty based on how many bridges are present in the grid network. |
| [`CloseToOverflowReward`](https://grid2op.readthedocs.io/en/latest/reward.html#grid2op.Reward.CloseToOverflowReward)([max_lines]) | This reward finds all lines close to overflowing.            |
| [`CombinedReward`](https://grid2op.readthedocs.io/en/latest/reward.html#grid2op.Reward.CombinedReward)() | This class allows to combine multiple pre defined reward.    |
| [`CombinedScaledReward`](https://grid2op.readthedocs.io/en/latest/reward.html#grid2op.Reward.CombinedScaledReward)() | This class allows to combine multiple rewards.               |
| [`ConstantReward`](https://grid2op.readthedocs.io/en/latest/reward.html#grid2op.Reward.ConstantReward)() | Most basic implementation of reward: everything has the same values: 0.0 |
| [`DistanceReward`](https://grid2op.readthedocs.io/en/latest/reward.html#grid2op.Reward.DistanceReward)() | This reward computes a penalty based on the distance of the current grid to the grid at time 0 where everything is connected to bus 1. |
| [`EconomicReward`](https://grid2op.readthedocs.io/en/latest/reward.html#grid2op.Reward.EconomicReward)() | This reward computes the marginal cost of the powergrid.     |
| [`EpisodeDurationReward`](https://grid2op.readthedocs.io/en/latest/reward.html#grid2op.Reward.EpisodeDurationReward)([per_timestep]) | This reward will always be 0., unless at the end of an episode where it will return the number of steps made by the agent divided by the total number of steps possible in the episode. |
| [`FlatReward`](https://grid2op.readthedocs.io/en/latest/reward.html#grid2op.Reward.FlatReward)([per_timestep]) | This reward return a fixed number (if there are not error) or 0 if there is an error. |
| [`GameplayReward`](https://grid2op.readthedocs.io/en/latest/reward.html#grid2op.Reward.GameplayReward)() | This rewards is strictly computed based on the Game status.  |
| [`IncreasingFlatReward`](https://grid2op.readthedocs.io/en/latest/reward.html#grid2op.Reward.IncreasingFlatReward)([per_timestep]) | This reward just counts the number of timestep the agent has successfully manage to perform. |
| [`L2RPNReward`](https://grid2op.readthedocs.io/en/latest/reward.html#grid2op.Reward.L2RPNReward)() | This is the historical [`BaseReward`](https://grid2op.readthedocs.io/en/latest/reward.html#grid2op.Reward.BaseReward) used for the Learning To Run a Power Network competition on WCCI 2019 |
| [`L2RPNSandBoxScore`](https://grid2op.readthedocs.io/en/latest/reward.html#grid2op.Reward.L2RPNSandBoxScore)([alpha_redisph]) | INTERNAL                                                     |
| [`LinesCapacityReward`](https://grid2op.readthedocs.io/en/latest/reward.html#grid2op.Reward.LinesCapacityReward)() | Reward based on lines capacity usage Returns max reward if no current is flowing in the lines Returns min reward if all lines are used at max capacity |
| [`LinesReconnectedReward`](https://grid2op.readthedocs.io/en/latest/reward.html#grid2op.Reward.LinesReconnectedReward)() | This reward computes a penalty based on the number of powerline that could have been reconnected (cooldown at 0.) but are still disconnected. |
| [`N1Reward`](https://grid2op.readthedocs.io/en/latest/reward.html#grid2op.Reward.N1Reward)([l_id]) | This class implements the "n-1" reward, which returns the maximum flows after a powerline |
| [`RedispReward`](https://grid2op.readthedocs.io/en/latest/reward.html#grid2op.Reward.RedispReward)() | This reward can be used for environments where redispatching is available. |
| [`RewardHelper`](https://grid2op.readthedocs.io/en/latest/reward.html#grid2op.Reward.RewardHelper)([reward_func]) | INTERNAL                                                     |

### action

| Name(s)                                                      | Type  | Size (each)                                                  |
| ------------------------------------------------------------ | ----- | ------------------------------------------------------------ |
| [set_bus](https://grid2op.readthedocs.io/en/latest/action.html#grid2op.Action.BaseAction.set_bus) | int   | [dim_topo](https://grid2op.readthedocs.io/en/latest/space.html#grid2op.Space.GridObjects.dim_topo) |
| [gen_set_bus](https://grid2op.readthedocs.io/en/latest/action.html#grid2op.Action.BaseAction.gen_set_bus) | int   | [n_gen](https://grid2op.readthedocs.io/en/latest/space.html#grid2op.Space.GridObjects.n_gen) |
| [load_set_bus](https://grid2op.readthedocs.io/en/latest/action.html#grid2op.Action.BaseAction.load_set_bus) | int   | [n_load](https://grid2op.readthedocs.io/en/latest/space.html#grid2op.Space.GridObjects.n_load) |
| [line_or_set_bus](https://grid2op.readthedocs.io/en/latest/action.html#grid2op.Action.BaseAction.line_or_set_bus) | int   | [n_line](https://grid2op.readthedocs.io/en/latest/space.html#grid2op.Space.GridObjects.n_line) |
| [line_ex_set_bus](https://grid2op.readthedocs.io/en/latest/action.html#grid2op.Action.BaseAction.line_ex_set_bus) | int   | [n_line](https://grid2op.readthedocs.io/en/latest/space.html#grid2op.Space.GridObjects.n_line) |
| [storage_set_bus](https://grid2op.readthedocs.io/en/latest/action.html#grid2op.Action.BaseAction.storage_set_bus) | int   | [n_storage](https://grid2op.readthedocs.io/en/latest/space.html#grid2op.Space.GridObjects.n_storage) |
| [change_bus](https://grid2op.readthedocs.io/en/latest/action.html#grid2op.Action.BaseAction.change_bus) | bool  | [dim_topo](https://grid2op.readthedocs.io/en/latest/space.html#grid2op.Space.GridObjects.dim_topo) |
| [gen_change_bus](https://grid2op.readthedocs.io/en/latest/action.html#grid2op.Action.BaseAction.gen_change_bus) | bool  | [n_gen](https://grid2op.readthedocs.io/en/latest/space.html#grid2op.Space.GridObjects.n_gen) |
| [load_change_bus](https://grid2op.readthedocs.io/en/latest/action.html#grid2op.Action.BaseAction.load_change_bus) | bool  | [n_load](https://grid2op.readthedocs.io/en/latest/space.html#grid2op.Space.GridObjects.n_load) |
| [line_or_change_bus](https://grid2op.readthedocs.io/en/latest/action.html#grid2op.Action.BaseAction.line_or_change_bus) | bool  | [n_line](https://grid2op.readthedocs.io/en/latest/space.html#grid2op.Space.GridObjects.n_line) |
| [line_ex_change_bus](https://grid2op.readthedocs.io/en/latest/action.html#grid2op.Action.BaseAction.line_ex_change_bus) | bool  | [n_line](https://grid2op.readthedocs.io/en/latest/space.html#grid2op.Space.GridObjects.n_line) |
| [storage_change_bus](https://grid2op.readthedocs.io/en/latest/action.html#grid2op.Action.BaseAction.storage_change_bus) | bool  | [n_storage](https://grid2op.readthedocs.io/en/latest/space.html#grid2op.Space.GridObjects.n_storage) |
| [line_set_status](https://grid2op.readthedocs.io/en/latest/action.html#grid2op.Action.BaseAction._line_set_status) | int   | [n_line](https://grid2op.readthedocs.io/en/latest/space.html#grid2op.Space.GridObjects.n_line) |
| [line_change_status](https://grid2op.readthedocs.io/en/latest/action.html#grid2op.Action.BaseAction._line_change_status) | bool  | [n_line](https://grid2op.readthedocs.io/en/latest/space.html#grid2op.Space.GridObjects.n_line) |
| [redispatch](https://grid2op.readthedocs.io/en/latest/action.html#grid2op.Action.BaseAction.redispatch) | float | [n_gen](https://grid2op.readthedocs.io/en/latest/space.html#grid2op.Space.GridObjects.n_gen) |
| [storage_p](https://grid2op.readthedocs.io/en/latest/action.html#grid2op.Action.BaseAction.storage_p) | float | [n_storage](https://grid2op.readthedocs.io/en/latest/space.html#grid2op.Space.GridObjects.n_storage) |
| [curtail](https://grid2op.readthedocs.io/en/latest/action.html#grid2op.Action.BaseAction.curtail) | float | [n_gen](https://grid2op.readthedocs.io/en/latest/space.html#grid2op.Space.GridObjects.n_gen) |

