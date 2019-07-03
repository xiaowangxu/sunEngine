# **sunEngine** 

![sunEngineIcon](https://github.com/xiaowangxu/sunEngine/blob/master/image/sunEngine.png?raw=true)

一个由 *studio* **UNNAMED** 编写的小小的游戏框架（无用）

## 为什么
这只是在我的大学课程中为了能便利地进行一个小游戏开发，简化代码结构的绘图框架，并不是一个完整好用的游戏引擎，个人使用请注意

## 如何使用

### 0. 项目设置
在 `sunEngine_Utility.h` 中：
```c++
struct Application
{
	string Title = "TTT999 by studio UNNAMED";	// 游戏窗口标题
	Vector2<int> WindowSize = Vector2<int>(960,700);	// 弹出的窗口大小
	Vector2<GLdouble> ViewportSize = Vector2<GLdouble>(1920.0, 1400);	// 游戏画面大小
	Vector2<GLdouble> Origin = Vector2<GLdouble>(0., 0.);	// 游戏绘制原点，不必修改
	Vector3<GLclampf> BgColor = Vector3<GLclampf>(0.16f, 0.2f, 0.37f);	// 游戏背景色
	int dt = 16;	// 帧生成时间（毫秒）
};
```
### 1. 游戏编程
在 `sunEngine.cpp` 中：
```c++
// config your game setting in "sunEngine_Utility.h"
// global Mouse Plugin
// 在"sunEngine_Utility.h"中进行项目设置
// 全局鼠标插件
extern MouseObj Mouse;

// Put Your Game Object Here
// 在这里声明游戏插件或类

// Game Loop
// 游戏循环
void game_Initialize()
{
	// the script here will only run once before the game start
	// 游戏初始化
}

void game_MainLoop()
{
	// put your main game logic here
	// 游戏主循环
}
```
### 2. 插件
您只能使用插件进行绘图

目前支持的插件仅有 `Shape`

	注意插件在被构造时将被自动加入绘图列表中，因此绘制的顺序由构造顺序决定

### 3. 行为
目前只有两种行为：
+ `Animater`
+ `MouseSensor`

将行为附加到插件上：
```c++
Shape Circle;
Animater SizeChanger;

Circle.AddBehaviour(SizeChanger);
```
## 一个样例
当鼠标移动到圆上时放大，移出时缩小

在 `sunEngine.cpp` 中：
```c++
#include "pch.h"
#include "sunEngine.h"
#include "stdlib.h"
using namespace std;

// config your game setting in "sunEngine_Utility.h"
// global Mouse Plugin
// 在"sunEngine_Utility.h"中进行项目设置
// 全局鼠标插件
extern MouseObj Mouse;

// Put Your Game Object Here
// 在这里声明游戏插件或类
class GameObject
{
public:
	Shape Circle;
	Animater SizeChanger;
	MouseSensor Sensor;

	GameObject()
	{
		Circle.AddBehaviour(SizeChanger);
		Circle.AddBehaviour(Sensor);
	}
};

GameObject Object;

// Game Loop
// 游戏循环
void game_Initialize()
{
	// the script here will only run once before the game start
	// 游戏初始化
	Object.Circle.SetShape(4,1.0,1.0,1.0);
	Object.Circle.SetPosition(960,540);
	Object.Circle.SetSize(200,200);
}

void game_MainLoop()
{
	// put your main game logic here
	// 游戏主循环
	if(Object.Sensor.OnRollIn())	// MouseSensor 行为检测到鼠标移入
	{
		Object.SizeChanger.StopAnimation();
		Object.SizeChanger.SetAnimation(Object.Circle.GetSize().X,220,0.3,bh_Animater::BackOut,bh_Animater::Once,bh_Animater::Size);
		Object.SizeChanger.StartAnimation();
	}
	if(Object.Sensor.OnRollOut())	// MouseSensor 行为检测到鼠标移出
	{
		Object.SizeChanger.StopAnimation();
		Object.SizeChanger.SetAnimation(Object.Circle.GetSize().X,200,0.3,bh_Animater::BackOut,bh_Animater::Once,bh_Animater::Size);
		Object.SizeChanger.StartAnimation();
	}
}
```
