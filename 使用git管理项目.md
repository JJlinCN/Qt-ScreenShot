## 使用git管理项目

1.配置本地全局信息

------

```c++
git config --global user.name "..." /*设置全局用户名*/
git config --global	user.email "..." /*设置全局邮箱*/
git config --list /*查看当前已经配置的全局信息*/
```

2.获取Git仓库

1. 将尚未进行版本控制的本地目录转换为 Git 仓库

   ```
   git init
   ```

2. 从其它服务器克隆一个已存在的 Git 仓库

   ```c++
   git clone /*克隆下来的仓库自动变为git管理的仓库，自动设置远程分支origin并设置远程跟踪分支origin/当前分支*/
   ```

3.本地仓库的暂存（追踪）和提交

------

```c++
git add *.c /*将任意后缀为.c的文件加入暂存区(index文件夹) git add .将所有文件加入文件夹*/
git commit -m 'initial project version' /*-m参数 添加提交批注 -a跳过暂存区直接提交*/
git status [-s/--short]/*查看当前管理的文件处于什么状态*/
```

4.快速查看文件差异

------

```c++
git diff /*workspace index*/
git diff --staged /*index commit*/
```

5.移除文件

------

```c++
git rm -f /*删除已经暂存或修改的文件，和rm一起使用移除工作目录文件*/
git rm --cached /*只暂存区移除，工作目录保存*/
```

6.重命名文件

------

```c++
git mv filename file 
//等同于这三条命令
//mv filename file /*重命名filename->file*/
//git rm filename /*移除旧文件*/
//git add file /*将新文件加入暂存区*/
```

7.查看项目提交历史

------

```c++
git log /*查看提交历史*/
git log -2 /*查看最近两条提交历史*/
```

8.追加操作

------

```c++
git commit --amend /*追加操作，第二次的提交会指向第一次提交点并覆盖，最终只有一个提交节点*/
```

9.远程仓库使用

------

``` c++
git remote [-v]/*查看远程服务器列表，加-v显示详细url*/
git remote add <shortname> <url> /*添加远程服务器并指定简写*/
git fetch <remote> /*抓取远程服务器数据到本地，但不修改暂存区和工作目录*/
git pull <remote> /*等同于fetch + merge 抓取加合并,加参数--rebase 以rebase变基方式合并*/
/*尽量用fetch + merge,git pull太快了有时候不好掌控*/
git push <remote> <branch>
/*推送分支到远程仓库
上面push命令简化了一些操作，默认为推送本地和远程同名分支
全称为 git push origin serverfix：serverfix
意思为推送本地serverfix分支到远程serverfix分支
git push origin serverfix：awesomefix
推送本地serverfix推送到远程awesomefix分支
*/
git remote show <remote> /*查看某个远程仓库的具体信息*/
git remote rename branchname branch /*分支重命名*/
git remote rm branchname/*移除分支（remove）*/
/*
先fetch更新，查看远程分支数据是否为最新，最新就不需要合并，直接push
先pull = fetch+merge 在push
git branch 查看当前分支
git branch -a 查看所有分支
git branch -d 删除分支指针
github协作着邀请需要双方同意确认
*/
远程跟踪分支
git checkout -b <branch> <remote>/<branch>
/*创建branch分支并设置其跟踪远程分支origin/branch*/
git branch -u origin/main /*设置当前分支跟踪远程分支，方便拉取和合并推送*/
git branch -vv /*查看所有的跟踪分支*/
    
//只涉及到本地操作或者尚未提交至公共服务器的分支可以用rebase整理提交记录，可以使log成线性，提交后就避免再rebase,协同操作中使用rebase,这样会使别人丢掉一些历史记录！！！
```

10.分支合并理解

------

```c++
git merge targetBranchName /*合并目标分支*/
/*合并没有冲突，git会将当前分支和目标分支的所有文件合并在当前分支并自动git add 所有文件然后自动提交为一个新的合并节点，再将当前分支指针前移
当合并冲突发生时，这个过程将不再连续，此时git会将未冲突的文件add后放在暂存区，冲突的文件不会自动加入暂存区，git会提醒你发生冲突的文件并在当前分支的对应文件中标记出发生冲突的代码位置，这时你可以打开这些文件做手动冲突解决，当解决完了之后就输入git add将其加入暂存区，git add后的文件git会认为其冲突已解决，当所有文件都解决完冲突后你可以commit提交一个新的节点，至此分支的冲突合并过程就完成了*/
```

11.项目管理中遇到的一些问题

------

```c++
1.第一次设置git init，fetch后，此时本地分支和远程分支不处于同一个起点，是没有共同祖先的，此时用merge合并就会提示“拒绝合并无关的历史”，这是git2.9的新特性导致的，可以加
--allow-unrelated-histories参数强制合并，也可以用git rebase origin/main变基合并
正如前面所说，在push后就不要再用rebase了，有可能丢掉别人的操作记录
```

