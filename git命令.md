git命令
- 切换分支名称：
    `git branch -m oldBranchName newBranchName`
    Tips:当前github已经将master分支改名为了main，而git中仍为master，会出现推拉错误，需要改名为main
- 查看仓库状态：
  `git status`
- 初始化git仓库：
  `git init`
- 添加文件：
  `git add .`增加当前子目录下所有更改过的文件至index
  `git add xyz`添加xyz文件至index


## 常见问题：
- 注意将master分支改名为main，包括使用的命令