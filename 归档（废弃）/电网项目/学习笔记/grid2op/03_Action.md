## action

change and set

ambiguous action

## 不同种类action

每个智能体都有自己的action space,用self.action_space访问

改变多个powerlines状态代码

```python
line_id_to_change = [0,1,2]
change_status = action_space()
change_status.line_change_status = line_id_to_change

print("The action `change_status` is ")
print(change_status)
print() 

line_id_to_set = [3, 4, 5, 6]
new_status = [1, 1, -1, -1]
set_status = action_space()
set_status.line_set_status = [[l_id, status] for l_id, status in zip(line_id_to_set, new_status)]
print("The action `set_status` is ")
print(set_status)
print()

both_action = change_status + set_status
print("When i combine them its")
print(both_action)
```



## action和其他操作的比较

## 相关代码